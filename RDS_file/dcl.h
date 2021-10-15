#include <stdio.h>
extern int error;
extern int tokentype;
extern char token[];
extern char *name;
extern char *datatype;
extern char *out;

extern FILE *finput;

void dcl(void);
void dirdcl(void);
int gettoken(void);
