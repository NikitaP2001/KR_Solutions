#include <windows.h>


#define MAX_READ 1024

int main(int argc, char *argv[])
{
	HANDLE hInput, hOutput;
	char ReadBuffer[MAX_READ];
	DWORD nBytesToRead = MAX_READ;
	DWORD BytesRead = 0;

	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOutput == INVALID_HANDLE_VALUE)
		exit(1);

	// case no arguments reading stdin
	if (argc == 1) {
		hInput = GetStdHandle(STD_INPUT_HANDLE);
		if (hInput == INVALID_HANDLE_VALUE)
			exit(1);
		
		int status;
		do {
			status = ReadFile(hInput,
					&ReadBuffer,
					nBytesToRead,
					&BytesRead,
					NULL);
			if (status == FALSE)
				exit(2);

			status = WriteFile(hOutput,
					&ReadBuffer,
					BytesRead,
					NULL,
					NULL);
			if (status == FALSE)
				exit(2);

		} while (BytesRead > 0);

		status = CloseHandle(hInput);
		if (status == FALSE)
			exit(1);
	} else for(int narg = 1; narg < argc; narg++) {
		hInput = CreateFileA(argv[narg],
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
		if (hInput == INVALID_HANDLE_VALUE)
			continue;

		int status;
		do {
			status = ReadFile(hInput,
					&ReadBuffer,
					nBytesToRead,
					&BytesRead,
					NULL);
			if (status == FALSE)
				exit(2);

			status = WriteFile(hOutput,
					&ReadBuffer,
					BytesRead,
					NULL,
					NULL);
			if (status == FALSE)
				exit(2);

		} while (BytesRead > 0);

		status = CloseHandle(hInput);
		if (status == FALSE)
			exit(1);
	}

	exit(0);
}
