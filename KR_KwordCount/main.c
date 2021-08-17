#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

int getword(char *, int);
int getch();
void ungetch(int);

int main(int argc, char *argv[]) {
  struct tnode *root;
  char word[MAXWORD];

  if (argc > 1)
    s_subword_len = atoi(argv[1]);

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      root = addtree(root, word);
  treescan(root);
  return 0;
}

int getword(char *word, int lim){
  int c, getch(void);
  static int comment = 0, stringConst = 0, controlLine = 0;
  void ungetch(int);
  char *w = word;

  while (isspace(c = getch())){
    if (c == '\n'){
      comment = 0;
      stringConst = 0;
      controlLine = 0;
    }
  };

  if (c != EOF)
    *w++ = c;

  if (!(isalpha(c) || c == '_' )){
    if (*(w-1) == '\n'){
      comment = 0;
      stringConst = 0;
      controlLine = 0;
    }
    if (*(w-1) == '"')
      stringConst ^= 1;
    if (*(w-1) == '#')
      controlLine = 1;
    if (*(w-1) == '/')
      if ((*w = getch()) == '/')
        comment = 1;
      else ungetch(*w);
    *w = '\0';
    return c;
  }

  for ( ; --lim > 0; w++){

    if (*(w-1) == '\n'){
      comment = 0;
      stringConst = 0;
      controlLine = 0;
    }
    if (*(w-1) == '"')
      stringConst ^= 1;
    if (*(w-1) == '#')
      controlLine = 1;
    if (*(w-1) == '/')
      if ((*w = getch()) == '/')
        comment = 1;
      else ungetch(*w);
	
	if (comment || stringConst || controlLine) {
		word[0] = '\0';
		break;
	}
	
    if (!(isalnum(*w = getch()) || *w == '_')){
      ungetch(*w);
      break;
    }
  }
  *w = '\0';
  return word[0];
}

int buf = 0;

int getch(){
  if (buf == 0)
    return getchar();
  else {
    int temp = buf;
    buf = 0;
    return temp;
  }
}

void ungetch(int sym){
  if (buf == 0) 
    buf = sym;
  else puts("Unable to ungetch\n");
}
