
#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *p, char *word);
void treescan(struct tnode *p);

extern int s_subword_len;

struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};
