#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *fp1, *fp2;
	char line1[1000];
	char line2[1000];

	if (argc != 3) {
		fprintf(stderr, "%s: expecting 2 filenames as arguments",
				argv[0]);
		exit(1);
	}

	if ((fp1 = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "%s: error opening file %s for reading",
				argv[0], argv[1]);
		exit(2);
	}

	if ((fp2 = fopen(argv[2], "r")) == NULL) {
		fprintf(stderr, "%s: error opening file %s for reading",
				argv[0], argv[2]);
		exit(2);
	}

	char c1 = 0, c2 = 0;
	int l1p = 0, l2p = 0, line = 1;
	do {
		if (c1 != '\n')
			c1 = getc(fp1);
		if (c2 != '\n')
 			c2 = getc(fp2);

		if (c1 >= 0 && c1 != '\n')
			line1[l1p++] = c1;
		if (c2 >= 0 && c2 != '\n')
			line2[l2p++] = c2;

		if ((c1 == '\n' && c2 == '\n') || c1 < 0 || c2 < 0) {
			line1[l1p] = '\0';
			line2[l2p] = '\0';
			if (strcmp(line1, line2)) {
				printf("line %d:\n%s: %s\n%s: %s\n", line,
						argv[1], line1, argv[2], line2);
				fclose(fp1);
				fclose(fp2);
				exit(0);
			} else {
				line++;
				c1 = 0;
				c2 = 0;
				l1p = 0;
				l2p = 0;
			}
		}
	} while (c1 != EOF && c2 != EOF);
	fclose(fp1);
	fclose(fp2);

	exit(0);
}
