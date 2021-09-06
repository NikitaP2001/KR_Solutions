#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ERRMSG \
"Invalid program name. Expects to be \
tolower.exe OR toupper.exe"

int main(int argc, char *argv[])
{
        char c;
        char *pname = argv[0];
        pname += strlen(argv[0]);
        while (*pname != '\\')
                pname--;
        pname++;

        puts(argv[0]);
        if (strcmp(pname, "toupper.exe") == 0) {
                while ((c = getchar()) >= 0)
                        putchar(toupper(c));
        } else if (strcmp(pname, "tolower.exe") == 0) {
                while ((c = getchar()) >= 0)
                        putchar(tolower(c));
        } else
                puts(ERRMSG);
        return 0;
}
