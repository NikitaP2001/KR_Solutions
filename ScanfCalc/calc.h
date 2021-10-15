#pragma once
#include <math.h>

#define SIN 's'
#define COS 'c'
#define POW 'p'
#define EXP 'e'
#define VAR 'v'
#define NUMBER '0'

extern double number;

int ProcessVar(char s[]);
int getop(char s[]);
void clearStack();
void swap();
void duplicate();
void printtop();
void ungetch(int c);
char getch(void);
double pop(void);
void push(double f);
