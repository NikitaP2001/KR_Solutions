#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int miniscanf(const char *format, ...);

int main()
{
        char buf[100] = {};
        miniscanf("%10hs ", buf);
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

int miniscanf(const char *format, ...)
{
        struct sprintf_flags flags = {};
        int step = 0, error = 0, readed = 0;
        va_list vl;
        va_start(vl, format);

        for (int i = 0, j = 0; format[i] != '\0' && !error; i++) {

                //Read flags
                if (step == 1) {
			if (format[i] == '*')
				flags.asterisk = 1;
			step = 2;
			continue;
		}

                //Read width
                if (step == 2) {
                        if ('0' <= format[i] && format[i] <= '9')
                                flags.width = flags.width * 10 + format[i] - '0';
                        else 
                                step = 3;
			continue;
                }

                if (step == 3) {
			step = 5;
			switch (format[i]) {
			case 'h':
				flags.h = 1;
				step = 4;
				break;
			case 'l':
				flags.l = 1;
				step = 4;
				break;
			case 'j':
				flags.j = 1;
				break;
			case 'z':
				flags.z = 1;
				break;
			case 't':
				flags.t = 1;
				break;
			case 'L':
				flags.L = 1;
				break;
			}
			continue;
		}

                if (step == 4) {
                        switch (format[i]) {
                        case 'h':
				if (flags.h == 1) {
                                	flags.hh = 1;
                                	flags.h = 0;
				} else 
					error = 1;
				break;
                        case 'l':
				if (flags.l == 1) {
                                	flags.ll = 1;
                                	flags.l = 0;
				} else 
					error = 1;
				break;
                        }
                        step = 5;
			continue;
                }

                if (step == 5) {
                        dump_flags(&flags);
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




















