#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

void miniprintf(char *fmt, ...);
int readnum(char **p);

int main()
{
    miniprintf("%11s decimal: %10d float: %15f hex: %20x\n", "This is", 1234, 1234.345, 54321);
    return 0;
}

struct {
        int minus;
        int min_width;
        int precision;
} opt;

const char control[] = {
        'd', 'i',
        'o',
        'x', 'X',
        'u',
        'c',
        's',
        'f'
};

void miniprintf(char *fmt, ...)
{
        va_list ap;
        char *p, *sval,
        format[MAXWORD];
        int ival, percent = 0;
        double dval;

        va_start(ap, fmt);
        for (p = fmt; *p; p++) {
                if (*p == '%') {
                        if (percent) {
                                percent = 0;
                                putchar(*p);
                        } else {
                                if (isdigit(*(p+1)))
                                        opt.min_width = readnum(&p);
                                percent = 1;
                        }
                        continue;
                }
                if (percent) {
                        switch (*p) {
                        case 'd':
                        case 'i':
                                ival = va_arg(ap, int);
                                if (opt.min_width != 0)
                                        sprintf(format, "%%%dd", opt.min_width);
                                else
                                        strcpy(format, "%d");
                                printf(format, ival);
                                memset(&opt, 0, sizeof(opt));
                                percent = 0;
                                break;
                        case 'o':
                                ival = va_arg(ap, int);
                                if (opt.min_width != 0)
                                        sprintf(format, "%%%do", opt.min_width);
                                else
                                        strcpy(format, "%o");
                                printf(format, ival);
                                memset(&opt, 0, sizeof(opt));
                                percent = 0;
                                break;
                        case 'x':
                        case 'X':
                                ival = va_arg(ap, int);
                                if (opt.min_width != 0)
                                        sprintf(format, "%%%dx", opt.min_width);
                                else
                                        strcpy(format, "%x");
                                printf(format, ival);
                                memset(&opt, 0, sizeof(opt));
                                percent = 0;
                                break;
                        case 'f':
                                dval = va_arg(ap, double);
                                if (opt.min_width != 0)
                                        sprintf(format, "%%%df", opt.min_width);
                                else
                                        strcpy(format, "%f");
                                printf(format, dval);
                                memset(&opt, 0, sizeof(opt));
                                percent = 0;
                                break;
                        case 's':
                                int printed = 0;
                                for (sval = va_arg(ap, char*); *sval; sval++, printed++)
                                        putchar(*sval);
                                for ( ; printed < opt.min_width; printed++)
                                        putchar(' ');
                                memset(&opt, 0, sizeof(opt));
                                percent = 0;
                                break;
                        case '-':
                                if (opt.minus)
                                opt.minus = 1;
                        default:
                                putchar(*p);
                                break;
                        }
                } else
                        putchar(*p);
        }
        va_end(ap);
}

int readnum(char **p)
{
        (*p)++;
        char numbuf[MAXWORD];

        int i = 0;
        for ( ; **p >= 0 && isdigit(**p); (*p)++)
                numbuf[i++] = **p;
        (*p)--;
        numbuf[i] = '\0';
        return atoi(numbuf);
}













