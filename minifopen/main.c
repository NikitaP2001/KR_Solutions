#include <windows.h>
#include "fopen.h"

int main(void)
{
	FILE *fp = fopen("fopen.c", "r");
	FILE *fp1 = fopen("fopen.txt", "w");
	if (fp1 == NULL)
		return 1;
	if (fp == NULL)
		return 1;
	
	HANDLE hcons = GetStdHandle(STD_OUTPUT_HANDLE);
	char c;
	while ((c = getc(fp)) != EOF)
		WriteConsole(hcons, &c, 1, NULL, NULL);

	return 0;
}
