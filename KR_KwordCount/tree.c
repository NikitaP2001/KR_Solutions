#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct tnode *talloc(void);
int s_subword_len = 6;

struct tnode *addtree(struct tnode *p, char *w) {
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0)
    p->count++;
  else if (cond < 0)
    p->left = addtree(p->left, w);
  else
    p->right = addtree(p->right, w);
  return p;
}

static char buf[1000];
static int count;

void treeprint(struct tnode *p, char *word)
{
  char wordn[MAXWORD];
  int l_strcmp( char *s1, char *s2, int n);

  if (p != NULL) {
    treeprint(p->left, word);
    if (p->word != 0)
      if (l_strcmp(p->word, word, s_subword_len)) {
        sprintf(wordn,"%s\n", p->word);
        strcat(buf, wordn);
        p->word = 0;
        count++;
      }
    treeprint(p->right, word);
  }

}

void treescan(struct tnode *p)
{
  char wordn[MAXWORD];
  if (p != NULL) {
    if (p->word != 0) {
      count = 0;
      treeprint(p->left, p->word);
      sprintf(wordn,"%s\n", p->word);
      strcat(buf, wordn);
      treeprint(p->right, p->word);
      if (count > 0)
        puts(buf);
      buf[0] = '\0';
    }
    treescan(p->left);
    treescan(p->right);
  }
}

struct tnode *talloc(void)
{
  return (struct tnode *) malloc(sizeof(struct tnode));
}

int l_strcmp(char *s1, char *s2, int n)
{
  while (*s1++ == *s2++ && n > 0) n--;
  return !n;
}
