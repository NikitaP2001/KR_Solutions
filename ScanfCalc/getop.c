#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "calc.h"

#define INPUT_MAX_SIZE 500

static int getline(char *lineptr, int maxline)
{
	int i = 0;
	char c;

	while ((c = getchar()) != '\n' && c > 0 && i < maxline)
		lineptr[i++] = c;

	lineptr[i] = '\0';
	return i;
}

static int issymbol(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int getop(char s[])
{
	static char inputline[INPUT_MAX_SIZE];
	static int len = 0, pos = 0;

	if (pos == 0)
		len = getline(inputline, INPUT_MAX_SIZE);

	if (len == 0)
		return EOF;

	while (pos < len && isspace(inputline[pos]))
		pos++;

	if (pos >= len) {
		pos = 0;
		return '\n';
	}

	sscanf(&inputline[pos], "%100s", s);
	int wordlen = strlen(s);

	if (sscanf(s, "%lf", &number) > 0) {
		pos += wordlen;
		return NUMBER;
	} else if (issymbol(s[0])) {
		pos += wordlen;
		if (!strcmp(s, "sin")) return SIN;
		if (!strcmp(s, "cos")) return COS;
		if (!strcmp(s, "pow")) return POW;
		if (!strcmp(s, "exp")) return EXP;
		return VAR;
	}

	
	pos += 1;
	return s[0];
}
