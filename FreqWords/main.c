#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

int getword(char *, int);
int isnoise(const char *word);
int getch();
void ungetch(int);

const char *noise_words[];

int main(int argc, char *argv[]) {
  t_list *first;
  char word[MAXWORD];

  first = AllocNode();
  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]) && !isnoise(word)) {
        AddWord(first, word);
        first = goto_start(first);
    }
  list_print(first);

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

const char *noise_words[] = {
        "the",
        "and",
        "a",
        "then",
        "when",
        "is",
        "of",
        "to",
        "that",
        "in"
};

int isnoise(const char *word)
{
        for (int i = 0; i < sizeof(noise_words) / sizeof(char *); i++)
        {
                if (!strcasecmp(word, noise_words[i]))
                        return 1;
        }
        return 0;
}











