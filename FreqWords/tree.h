
#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *p);
void treescan(struct tnode *p);

extern int s_subword_len;

struct tnode {
  char *word;
  int count;
  struct list_node *plist;
  struct tnode *left;
  struct tnode *right;
};

struct list_node {
        struct tnode *pTreeNode;
        struct list_node *next;
        struct list_node *prev;
};

extern struct list_node tree_list;

void insert_after(struct list_node *pnode, struct tnode *ptree);

void insert_before(struct list_node *pnode, struct tnode *ptree);

struct list_node *alloc_list_node();

void cut_list_node(struct list_node *pnode);

void list_print();
