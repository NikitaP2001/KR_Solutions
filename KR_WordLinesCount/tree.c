#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 50

struct tnode *talloc(void);
int s_subword_len = 6;

struct tnode *addtree(struct tnode *p, char *w, int line) {
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = strdup(w);
    p->lines_num = (int *)malloc(LINE_SIZE*sizeof(int));
    p->lines_count = 0;
    p->lines_num[p->lines_count++] = line;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    if (p->lines_num[p->lines_count-1] != line) {
      p->lines_num[p->lines_count++] = line;
    }
  }
  else if (cond < 0)
    p->left = addtree(p->left, w, line);
  else
    p->right = addtree(p->right, w, line);
  return p;
}

void treeprint(struct tnode *p)
{
  if (p != NULL) {
    treeprint(p->left);
    printf("%s", p->word);
    for (int i = 0; i < p->lines_count; i++) {
      printf(" %d", p->lines_num[i]);
    }
    putchar('\n');
    treeprint(p->right);
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
