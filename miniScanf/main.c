#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

int miniscanf(const char *format, ...);

int main()
{
        char buf[100] = {};
	long long int a;
	short int b;
        miniscanf("%10s %10lld %10hd", buf, &a, &b);
	printf("%s, %lld, %hd", buf, a, b);
        return 0;
}

struct sprintf_flags {
        unsigned int width;
	unsigned int asterisk	:1;
        unsigned int hh			:1;
        unsigned int h			:1;
        unsigned int l			:1;
        unsigned int ll			:1;
        unsigned int j      		:1;
        unsigned int z			:1;
        unsigned int t			:1;
        unsigned int L			:1;
};

/*
In debugging purposes */
static void dump_flags(struct sprintf_flags *flg) {
        if (flg->asterisk)
                puts("flag asterisk: *");
	if (flg->width)
		printf("width: %d\n", flg->width);
        if (flg->hh)
                puts("length : hh");
        if (flg->h)
                puts("length : h");
        if (flg->l)
                puts("length: l");
	if (flg->ll)
                puts("length: ll");
	if (flg->j)
                puts("length: jj");
	if (flg->z)
                puts("length: z");
	if (flg->t)
                puts("length: t");
	if (flg->L)
                puts("length: L");

}

static int __miniscanf_read(char specifier, struct sprintf_flags flags, va_list vl)
{
	char buffer[10];
	char *format;
	if (flags.asterisk)
		format = "*%s";
	else
		format = "%s";

	switch (specifier) {
	case 'i':
	case 'd':
		if (flags.hh) {
			signed char *cptr = va_arg(vl, signed char*);
			sprintf(buffer, format, "%hhd");
			return scanf(buffer, cptr);
		} else if (flags.h) {
			short int *hptr = va_arg(vl, short int*);
			sprintf(buffer, format, "%hd");
			return scanf(buffer, hptr);
		} else if (flags.l) {
			long int *lptr = va_arg(vl, long int*);
			sprintf(buffer, format, "%ld");
			return scanf(buffer, lptr);
		} else if (flags.ll) {
			long long int *llptr = va_arg(vl, long long int*);
			sprintf(buffer, format, "%lld");
			return scanf(buffer,llptr);
		} else if (flags.j) {
			intmax_t *jptr = va_arg(vl, intmax_t*);
			sprintf(buffer, format, "%jd");
			return scanf(buffer, jptr);
		} else if (flags.z) {
			size_t *zptr = va_arg(vl, size_t*);
			sprintf(buffer, format, "%zd");
			return scanf(buffer, zptr);
		} else if (flags.t) {
			ptrdiff_t *dptr = va_arg(vl, ptrdiff_t*);
			sprintf(buffer, format, "%td");
			return scanf(buffer, dptr);
		} else {
			int *iptr = va_arg(vl, int*);
			sprintf(buffer, format, "%d");
			return scanf(buffer, iptr);	
		}
		break;
	case 'u':
	case 'o':
	case 'x':
		if (flags.hh) {
			unsigned char *cptr = va_arg(vl, unsigned char*);
			sprintf(buffer, format, "%hhu");
			return scanf(buffer, cptr);
		} else if (flags.h) {
			unsigned short int *hptr = va_arg(vl, unsigned short int*);
			sprintf(buffer, format, "%hu");
			return scanf(buffer, hptr);
		} else if (flags.l) {
			unsigned long int *lptr = va_arg(vl, unsigned long int*);
			sprintf(buffer, format, "%lu");
			return scanf(buffer, lptr);
		} else if (flags.ll) {
			unsigned long long int *llptr = va_arg(vl, unsigned long long int*);
			sprintf(buffer, format, "%llu");
			return scanf(buffer,llptr);
		} else if (flags.j) {
			uintmax_t *jptr = va_arg(vl, uintmax_t*);
			sprintf(buffer, format, "%ju");
			return scanf(buffer, jptr);
		} else if (flags.z) {
			size_t *zptr = va_arg(vl, size_t*);
			sprintf(buffer, format, "%zu");
			return scanf(buffer, zptr);
		} else if (flags.t) {
			ptrdiff_t *dptr = va_arg(vl, ptrdiff_t*);
			sprintf(buffer, format, "%td");
			return scanf(buffer, dptr);
		} else {
			unsigned int *iptr = va_arg(vl, unsigned int*);
			sprintf(buffer, format, "%u");
			return scanf(buffer, iptr);	
		}
		break;
	case 'f':
	case 'e':
	case 'g':
	case 'a':
		if (flags.l) {
			double *dptr = va_arg(vl, double*);
			sprintf(buffer, format, "%lf");
			return scanf(buffer, dptr);
		} else {
			float *fptr = va_arg(vl, float*);
			sprintf(buffer, format, "%f");
			return scanf(buffer, fptr);
		}
		break;
	case 'c':
		if (flags.l) {
			char *cptr = va_arg(vl, char*);
			sprintf(buffer, format, "%lc");
			return scanf(buffer, cptr);

		} else {
			wchar_t *wptr = va_arg(vl, wchar_t*);
			sprintf(buffer, format, "%c");
			return scanf(buffer, wptr);
		}
		break;
	case 's':
		if (flags.l) {
			wchar_t *wptr = va_arg(vl, wchar_t*);
			sprintf(buffer, format, "%ls");
			return scanf(buffer, wptr);

		} else {
			char *cptr = va_arg(vl, char*);
			sprintf(buffer, format, "%s");
			return scanf(buffer, cptr);
		}
		break;
	case 'p':
		void **pptr = va_arg(vl, void**);
			sprintf(buffer, format, "%p");
		return scanf(buffer, pptr);
		break;
	case 'n':
		if (flags.hh) {
			signed char *cptr = va_arg(vl, signed char*);
			sprintf(buffer, format, "%hhn");
			return scanf(buffer, cptr);
		} else if (flags.h) {
			short int *hptr = va_arg(vl, short int*);
			sprintf(buffer, format, "%hn");
			return scanf(buffer, hptr);
		} else if (flags.l) {
			long int *lptr = va_arg(vl, long int*);
			sprintf(buffer, format, "%ln");
			return scanf(buffer, lptr);
		} else if (flags.ll) {
			long long int *llptr = va_arg(vl, long long int*);
			sprintf(buffer, format, "%lln");
			return scanf(buffer,llptr);
		} else if (flags.j) {
			intmax_t *jptr = va_arg(vl, intmax_t*);
			sprintf(buffer, format, "%jn");
			return scanf(buffer, jptr);
		} else if (flags.z) {
			size_t *zptr = va_arg(vl, size_t*);
			sprintf(buffer, format, "%zn");
			return scanf(buffer, zptr);
		} else if (flags.t) {
			ptrdiff_t *dptr = va_arg(vl, ptrdiff_t*);
			sprintf(buffer, format, "%tn");
			return scanf(buffer, dptr);
		} else {
			int *iptr = va_arg(vl, int*);
			sprintf(buffer, format, "%n");
			return scanf(buffer, iptr);	
		}
		break;
	}

	return 0;
}

int miniscanf(const char *format, ...)
{
        struct sprintf_flags flags = {};
        int step = 0, error = 0, readed = 0;
        va_list vl;
        va_start(vl, format);

        for (int i = 0, j = 0; format[i] != '\0' && !error; i++) {

                // Read flags
                if (step == 1) {
			step = 2;
			if (format[i] == '*') {
				flags.asterisk = 1;
				continue;
			}
		}

                // Read width
                if (step == 2) {
                        if ('0' <= format[i] && format[i] <= '9') {
                                flags.width = flags.width * 10 + format[i] - '0';
				continue;
			} else 
                                step = 3;
                }

		// Read begin of length field
                if (step == 3) {
			step = 5;
			switch (format[i]) {
			case 'h':
				flags.h = 1;
				step = 4;
				continue;
			case 'l':
				flags.l = 1;
				step = 4;
				continue;
			case 'j':
				flags.j = 1;
				continue;
			case 'z':
				flags.z = 1;
				continue;
			case 't':
				flags.t = 1;
				continue;
			case 'L':
				flags.L = 1;
				continue;
			}
		}

		// Read end of length field
                if (step == 4) {
                        step = 5;
                        switch (format[i]) {
                        case 'h':
				if (flags.h == 1) {
                                	flags.hh = 1;
                                	flags.h = 0;
				} else 
					error = 1;
				continue;
                        case 'l':
				if (flags.l == 1) {
                                	flags.ll = 1;
                                	flags.l = 0;
				} else 
					error = 1;
				continue;
                        }
                }

                if (step == 5) {
			readed += __miniscanf_read(format[i], flags, vl);
			va_arg(vl, void*);
			if (readed < 0)
				error = 1;
			step = 6;
			continue;
                }

                if (format[i] == '%') {
                        step = 1;
                        memset(&flags, 0, sizeof(flags));
                } else {
			if (format[i] != getchar())
				error = 1;
			else
				readed++;
		}
        }

        va_end(vl);
        return readed;
}




















