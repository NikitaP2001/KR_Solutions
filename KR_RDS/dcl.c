#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "dcl.h"

#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS, CONST, PTRTO};

int error;
int tokentype;
char token[MAXTOKEN];
char *name;
char *datatype;
char *out;

void dcl(void){
	char ptrout[100];
	ptrout[0] = '\0';
	int flag = 0, p = 0;
	
	while((gettoken() == '*' || !strcmp(token, "const") ) && !error){
		if (tokentype == NAME){
			if (flag == 1){
				puts("Incorrect const syntax");
				error = 1;
			}
			ptrout[p++] = CONST;
			flag = 1;
		} else {
			flag = 0;
			ptrout[p++] = PTRTO;
		}
	}

	dirdcl();
	
	p--;
	while(p >= 0){
		strcat(out, (ptrout[p] == CONST) ? " const" : " pointer to");
		p--;
	}
}

void dirdcl(void){
	int type;
	
	if (tokentype == '(' && !error){ 
		dcl();
		if (tokentype != ')'){
			puts("error: missing )\n");
			error = 1;
			return;
		}
	} else if (tokentype == NAME && !error){
		strcpy(name, token);	
	} else {
		puts("error: expected name or (dcl)\n");
		error = 1;
		return;
	}
	
	if ((type=gettoken()) == PARENS || type == BRACKETS && !error)
		do {
			if (type == PARENS)
				strcat(out, " function returning");
			else {
				strcat(out, " array");
				strcat(out, token);
				strcat(out, " of");
			}
		} while ((type=gettoken()) == PARENS || type == BRACKETS && !error);
	else if (type == '(' && !error){
		strcat(out, " function");
		
		do {
			strcat(out, " taking ");
			
			char tempout[MAXTOKEN];
			char *pname = name;
			char *pdatatype = datatype;
			char *pout = out;
			
			name = (char*)malloc(MAXTOKEN);
			datatype = (char*)malloc(MAXTOKEN);
			out = (char*)malloc(1000);
			
			if (gettoken() != NAME)
				error = 1;
			strcpy(datatype, token);
			out[0] = '\0';			
			dcl();
			
			if (out[0] != '\0')
				sprintf(tempout, "%s: %s %s", name, out, datatype);
			else 
				sprintf(tempout, "%s: %s", name, datatype);
			
			strcat(pout, tempout);
			
			free(name); 
			free(datatype);
			free(out);
			name = pname;
			datatype = pdatatype;
			out = pout;
			
			strcat(out, " and");
		} while (tokentype == ',');
		strcat(out, " returning");
		if (tokentype != ')'){
			puts("error: missing )\n");
			error = 1;
			return;
		} else {
			gettoken();
		}
	}
	
}

int gettoken(void){
	int c, getch(void);
	void ungetch(int);
	char *p = token;
	
	if ((c = getch()) == ' ' || c == '\t')
		while ((c = getch()) == ' ' || c == '\t');
	
	if (c == '('){
		if ((c = getch()) == ')'){
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '['){
		for (*p++ = c; (*p++ = getch()) != ']'; );
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)){
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
	
	return 0;
}

char buf;

int getch(void){
	if (buf == 0)
		return getchar();
	else {
		char c = buf;
		buf = 0;
		return c;
	}
}

void ungetch(int sym){
	if (buf == 0)
		buf = sym;
	else 
		puts("Impossible to ungetch");
}