#include <stdio.h>
#include "calc.h"
#define MAXVAL 100

static int sp = 0;
static double val[MAXVAL];

void push(double f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, cant push %g\n", f);
}

double pop(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

void printtop() {
	double c = pop();
	printf("%8g", c);
	push(c);
}

void duplicate() {
	double c = pop();
	push(c);
	push(c);
}

void swap() {
	double c = pop();
	double b = pop();
	push(c);
	push(b);
}

void clearStack() {
	sp = 0;
}
