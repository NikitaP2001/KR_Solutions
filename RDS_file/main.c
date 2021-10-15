#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "dcl.h"
#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS};

int undcl_main(){
	int type,typeold = 0;
	char temp[MAXTOKEN];
	
	while (gettoken() != EOF){
		strcpy(out, token);
		while ((type = gettoken()) != '\n'){
		
			if (type == PARENS || type == BRACKETS){
				if (typeold == '*'){
					sprintf(temp, "(%s)", out);
					strcpy(out, temp);
				}
				strcat(out, token);
				
			}else if (type == '*') {
				sprintf(temp, "*%s", out);
				strcpy(out, temp);
			} else if (type == NAME){
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else
				printf("Invalid input at %s\n", token);
			
			typeold = type;
			
		}
		printf("%s\n", out);
	}
	return 0;
}

int main(int argc, char *argv[]){
	
	name = (char*)malloc(MAXTOKEN);
	datatype = (char*)malloc(MAXTOKEN);
	out = (char*)malloc(1000);
	int flag_read_stdin = 1;
	char *prog_name = argv[0];

	if (argc > 1)
		flag_read_stdin = 0;
	
	while (argc-- > 1 || flag_read_stdin) {
		if (!flag_read_stdin) {
			finput = fopen(*++argv, "r");
			if (finput == NULL) {
				printf("%s: cannot open file %s for reading",
						prog_name, argv++);
				continue;
			}
		} else
			finput = stdin;

		while (gettoken() != EOF){
			out[0] = '\0';
			error = 0;
			
			strcpy(datatype, token);
			if (!strcmp(token, "const")){
				gettoken();
				if (tokentype == NAME){
					strcat(datatype, " ");
					strcat(datatype, token);
				} else {
					puts("syntax error");
					error = 1;
				}
			}
			
			dcl();
			
			if (tokentype != '\n'){
				puts("syntax error\n");
				while (gettoken() != '\n');
			}
			
			if (out[0] != '\0')
				printf("%s: %s %s\n", name, out, datatype);
			else 
				printf("%s: %s\n", name, datatype);
		}
		if (!flag_read_stdin) {
			fclose(finput);
		} else 
			flag_read_stdin = 0;
	}
	
	free(name); 
	free(datatype);
	free(out);
	
	return 0;	
}
