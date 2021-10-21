#include <windows.h>
#include "fopen.h"

int main(void)
{
	HANDLE hcons = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < 100; i++) {
		FILE *fp = fopen("fopen.c", "r");
		FILE *fp1 = fopen("fopen.txt", "a");
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
