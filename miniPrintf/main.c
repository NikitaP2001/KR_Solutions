#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void miniprintf(char *fmt, ...);

int main()
{
    miniprintf("%s decimal: %d float: %f octal: %o\n", "This is", 1234, 1234.345, 54321);
    return 0;
}

void miniprintf(char *fmt, ...)
{
        va_list ap;
        char *p, *sval;
        int ival;
        double dval;

        va_start(ap, fmt);
        for (p = fmt; *p; p++) {
                if (*p != '%') {
                        putchar(*p);
                        continue;
                }
                switch (*++p) {
                case 'd':
                case 'i':
                        ival = va_arg(ap, int);
                        printf("%d", ival);
                        break;
                case 'o':
                        ival = va_arg(ap, int);
                        printf("%o", ival);
                        break;
                case 'f':
                        dval = va_arg(ap, double);
                        printf("%f", dval);
                        break;
                case 's':
                        for (sval = va_arg(ap, char*); *sval; sval++)
                                putchar(*sval);
                        break;
                default:
                        putchar(*p);
                        break;
                }
        }
        va_end(ap);
}














