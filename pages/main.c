#include <stdio.h>
#include <stdlib.h>

static void print_file(FILE *fp)
{
	int c;

	while ((c = getc(fp)) != EOF)
		putc(c, stdout);
}

int main(int argc, char *argv[])
{
	for (int pages = 1; pages < argc; pages++) {
		FILE *fp = fopen(argv[pages], "r");
		if (fp == NULL) {
			fprintf(stderr, "%s: error opening file %s for reading",
					argv[0], argv[pages]);
			continue;
		}
		printf("Title: %s\nPage: %d\n", argv[pages], pages);
		print_file(fp);
		fclose(fp);
	}

	exit(0);
}
