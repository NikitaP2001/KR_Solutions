#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int miniscanf(const char *format, ...);

int main()
{
        char buf[100] = {};
        miniscanf("%10hs %10lld %10hhd", buf);
        miniscanf("%10jd", buf);
        miniscanf("%10Lu", buf);
        miniscanf("%10zu", buf);
        miniscanf("%*20hd ", buf);
        puts(buf);
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
	switch (specifier) {
	case 'i':
	case 'd':
		if (flags.hh)
			; // read signed char*
		else if (flags.h)
			; // read short int*
		else if (flags.l)
			; // read long int*
		else if (flags.ll)
			; // read long long int *
		else if (flags.j)
			; // read intmax_t*
		else if (flags.z)
			; // read size_t*
		else if (flags.t)
			; // read ptrdiff_t*
		else 
			return -1;
		break;
	case 'u':
	case 'o':
	case 'x':
		break;
	case 'f':
	case 'e':
	case 'g':
	case 'a':
		break;
	case 'c':
	case 's':
		break;
	case 'p':
		break;
	case 'n':
		break;
	default:
		return -1;
	}

	return 1;
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
			readed = __miniscanf_read(format[i], flags, vl);
			if (readed < 0)
				error = 1;
			step = 6;
			continue;
                }

                if (format[i] == '%') {
                        step = 1;
                        memset(&flags, 0, sizeof(flags));
                }
        }

        va_end(vl);
        return readed;
}




















