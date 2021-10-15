#include <string.h>
#include "calc.h"
#define VAR_NAME_SZ 10	
#define MAX_MEM_SIZE 100

typedef struct VARIABLE {
	char name[VAR_NAME_SZ];
	double val;
}var_t;

struct MEMORY {
	var_t var[MAX_MEM_SIZE];
}mem;

int ProcessVar(char s[]) {
	int i = 0;

	while (i < MAX_MEM_SIZE && strcmp(s, mem.var[i].name))
		i++;

	if (i < MAX_MEM_SIZE)
		push(mem.var[i].val);
	else {
		int j = 0;
		while (j < MAX_MEM_SIZE && strcmp(mem.var[j].name, "")) j++;
		if (j < MAX_MEM_SIZE) {
			strcpy_s(mem.var[j].name, VAR_NAME_SZ, s);
			push(mem.var[j].val = pop());
			return 1;
		}
		else return 0;
	}
	return 1;
}