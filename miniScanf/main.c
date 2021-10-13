#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int miniscanf(char *target, const char *format, ...);

int main()
{
        char buf[100] = "Hi";
        miniscanf(buf, "%010.15hs ", "");
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

/*
In debugging purposes */
static void dump_flags(struct sprintf_flags *flg) {
        if (flg->left_justify)
                puts("flag left justify: -");
        if (flg->sign_precedate)
                puts("flag sign precedate: +");
        if (flg->no_sign_blank)
                puts("flag not sign blank: (space)");
        if (flg->type_presidence)
                puts("flag type presidence: #");
        if (flg->zero_left_pad)
                puts("flag zero left pad: 0");
        if (flg->width != 0)
                printf("width:%d\n", flg->width);
        if (flg->precision != 0)
                printf("width:%d\n", flg->precision);
        if (flg->short_int)
                puts("short int: h");
        if (flg->long_int)
                puts("long int: l");
        if (flg->long_double)
                puts("long double: L");
}

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
                        step = 5;
                        switch (format[i]) {
                        case 'h':
                                flags.short_int = 1;
                                continue;
                        case 'L':
                                flags.long_double = 1;
                                continue;
                        case 'l':
                                flags.long_int = 1;
                                continue;
                        }
                }

                if (step == 5) {
                        dump_flags(&flags);
                }

                if (format[i] == '%') {
                        step = 1;
                        memset(&flags, 0, sizeof(flags));
                }
        }

        va_end(vl);
        return strlen(target);
}




















