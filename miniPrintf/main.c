#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

void miniprintf(char *fmt, ...);
int readnum(char **p);
void printf_format(char *format, char control);

int main()
{
    miniprintf("%11s decimal: %-10d float: %15.5f hex: %20x\n", "This is", 1234, 1234.345, 54321);
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
                                if (*(p+1) == '-') {
                                        opt.minus = 1;
                                        p++;
                                }
                                if (isdigit(*(p+1)))
                                        opt.min_width = readnum(&p);
                                if (*(p+1) == '.') {
                                        p++;
                                        opt.precision = readnum(&p);
                                }
                                percent = 1;
                        }
                        continue;
                }
                if (percent) {
                        switch (*p) {
                        case 'd':
                        case 'i':
                                ival = va_arg(ap, int);
                                printf_format(format, 'd');
                                printf(format, ival);
                                memset(&opt, 0, sizeof(opt));
                                percent = 0;
                                break;
                        case 'o':
                                ival = va_arg(ap, int);
                                printf_format(format, 'o');
                                printf(format, ival);
                                memset(&opt, 0, sizeof(opt));
                                percent = 0;
                                break;
                        case 'x':
                        case 'X':
                                ival = va_arg(ap, int);
                                printf_format(format, 'x');
                                printf(format, ival);
                                memset(&opt, 0, sizeof(opt));
                                percent = 0;
                                break;
                        case 'f':
                                dval = va_arg(ap, double);
                                printf_format(format, 'f');
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

void printf_format(char *format, char control)
{
        char sztemp[100];
        char szsym[2];
        szsym[0] = control;
        szsym[1] = '\0';
        format[0] = '%';
        format[1] = '\0';
        if (opt.minus != 0) {
                sprintf(sztemp, "%c", '-');
                strcat(format, sztemp);
        }
        if (opt.min_width != 0) {
                sprintf(sztemp, "%d", opt.min_width);
                strcat(format, sztemp);
        }
        if (opt.precision != 0) {
                sprintf(sztemp, ".%d", opt.precision);
                strcat(format, sztemp);
        }
        strcat(format, szsym);
}












