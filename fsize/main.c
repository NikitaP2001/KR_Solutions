#include <windows.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
        int len = strlen(argv[1]);
        
        while (argv[1][--len] != '\\' && argv[1][len] != ':')
                argv[1][len] = '\0';
        
        HANDLE hDir = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, 
         NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_BACKUP_SEMANTICS, NULL);
        if (hDir == NULL)
                printf("Error opening directory %s", argv[1]);
        
        
}