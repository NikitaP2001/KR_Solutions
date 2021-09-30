#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int miniscanf(char *target, const char *format, ...);

int main()
{
        char buf[100] = "Hi";
        sprintf(buf, "%010d ", -123);
        puts(buf);
        return 0;
}

struct sprintf_flags {
        unsigned int width;
        unsigned int precision;
        unsigned int left_justify       :1;
        unsigned int sign_precedate     :1;
        unsigned int no_sign_blank      :1;
        unsigned int type_presidence    :1;
        unsigned int zero_left_pad      :1;
        unsigned int short_int          :1;
        unsigned int long_int           :1;
        unsigned int long_double        :1;

};

int miniscanf(char *target, const char *format, ...)
{
        struct sprintf_flags flags = {};
        int step = 0, error = 0;
        va_list vl;
        va_start(vl, format);
        target[0] = '\0';

        for (int i = 0, j = 0; format[i] != '\0' && !error; i++) {

                //Read flags
                if (step == 1)
                        switch (format[i]) {
                        case '-':
                                flags.left_justify = 1;
                                break;
                        case '+':
                                flags.sign_precedate = 1;
                                break;
                        case ' ':
                                flags.no_sign_blank = 1;
                                break;
                        case '#':
                                flags.type_presidence = 1;
                                break;
                        case '0':
                                flags.zero_left_pad = 1;
                                break;
                        default:
                                step = 2;
                                break;
                        }

                //Read width
                if (step == 2) {
                        if ('0' <= format[i] && format[i] <= '9')
                                flags.width = flags.width * 10 + format[i] - '0';
                        else if (format[i] == '.')
                                step = 3;
                        else
                                step = 4;
                }

                if (step == 3) {
                        if ('0' <= format[i] && format[i] <= '9')
                                flags.precision = flags.precision * 10 + format[i] - '0';
                        else
                                step = 4;
                }

                if (step == 4) {

                }

                if (format[i] == '%') {
                        step = 1;
                        memset(&flags, 0, sizeof(flags));
                }
        }

        va_end(vl);
        return strlen(target);
}




















