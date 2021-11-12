#define EOF	-1
#define BUFSIZ	1024
#define OPEN_MAX 20

typedef struct _iobuf {
	long int cnt;
	char *ptr;
	char *base;
	void *fd;
	unsigned int _read	:1;
	unsigned int _write 	:1;
	unsigned int _unbuf 	:1;
	unsigned int _eof 	:1;
	unsigned int _err 	:1;
} FILE;
extern FILE _iob[OPEN_MAX];

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) ((p)->_eof)
#define ferror(p) ((p)->_err)
#define fileno(p) ((p)->_fd)

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#define getc(p) (--(p)->cnt >= 0 \
		? (unsigned char) *p->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 \
		? *(p)->ptr++ = (x) : _flushbuf((x),p))

#define getchar() getc(stdin)
#define putchar() putc((x), stdout)

FILE *fopen(const char *name, const char *mode);

void fflush(FILE *stream);
int fclose(FILE *stream);

#define SEEK_SET 0
#define SEEK_CUR 1	
#define SEEK_END 2

int fseek(FILE *fp, long offset, int origin);