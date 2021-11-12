#include <windows.h>
#include "fopen.h"
#include "geterror.h"

int main(void)
{

	for (int i = 0; i < 100; i++) {
		FILE *fp = fopen("fopen.c", "r");

		FILE *fp1 = fopen("fopen.txt", "a");
                
                fseek(fp, 20, 0);
                fseek(fp, 20, SEEK_CUR);                
                
                
		if (fp == NULL || fp1 == NULL)
			return 1;

		char c;
		while ((c = getc(fp)) != EOF)
			putc(c, fp1);                                

		fclose(fp1);
		fclose(fp);
	}
        
      

	return 0;
}
