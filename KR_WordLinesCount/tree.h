
#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *p);
void treescan(struct tnode *p);

extern int s_subword_len;

struct tnode {
  char *word;
  int *lines_num;
  int lines_count;
  struct tnode *left;
  struct tnode *right;
};
