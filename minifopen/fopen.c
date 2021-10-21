#include <windows.h>
#include "fopen.h"
#include "geterror.h"
FILE _iob[OPEN_MAX];

FILE *fopen(const char *name, const char *mode)
{
	HANDLE hFile;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->_read | fp->_write) == 0)
			break;
	if (fp >= _iob + OPEN_MAX)
		return NULL;

	if (*mode == 'w')
		hFile = CreateFileA(name,
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	else if (*mode == 'a') {
		hFile = CreateFileA(name,
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	} else
		hFile = CreateFileA(name,
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		PrintCSBackupAPIErrorMessage(GetLastError());
		return NULL;
	}

	fp->fd = hFile;
	fp->cnt = 0;
	fp->base = NULL;
	if (*mode == 'r') {
		fp->_read = 1;
		fp->_write = 0;
	} else {
		fp->_write = 1;
		fp->_read = 0;
	}
	return fp;
}

int _fillbuf(FILE *fp)
{
	int bufsize;

	if (fp->_read != 1)
		return EOF;
	bufsize = (fp->_unbuf) ? 1 : BUFSIZ;
	if (fp->base == NULL)
		if ((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	ReadFile(fp->fd, fp->ptr, bufsize, &fp->cnt, NULL);

	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->_eof = 1;
		else
			fp->_err = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}
