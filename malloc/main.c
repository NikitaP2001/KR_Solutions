#include <stdio.h>
#include <string.h>
#include "mem.h"

int main(void)
{
        char *buf = _malloc(sizeof("Hello world!"));
        strcpy(buf, "Hello world!");
        
        puts(buf);
        free(buf);
        
        return 0;
}
