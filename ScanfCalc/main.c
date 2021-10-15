#include <stdio.h>
#include <math.h>
#include "calc.h"
#define MAXOP 100

double number;

void main() {
	int type;
	double op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(number);
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error zero devision\n");
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				push((int)(pop()) % (int)(op2));
			else
				printf("error zero devision\n");
			break;
		case SIN:
			push(sin(pop()));
			break;
		case COS:
			push(cos(pop()));
			break;
		case POW:
			push(pow(pop(), pop()));
			break;
		case EXP:
			push(exp(pop()));
			break;
		case VAR:
			if (!ProcessVar(s))
				printf("No memory to add %s", s);
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command\n");
			break;
		}
	}
}
