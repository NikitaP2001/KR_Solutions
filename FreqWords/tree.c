#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_SIZE 50

struct tnode *talloc(void);
int s_subword_len = 6;
struct list_node tree_list; 

struct tnode *addtree(struct tnode *p, char *w) {
  int cond;

  if (p == NULL) {
    p = talloc();
    p->word = strdup(w);
    p->count = 0;
    p->left = p->right = NULL;

    struct list_node *plist = &tree_list;
    if (plist->pTreeNode == NULL) {
        plist->pTreeNode = p;
        p->plist = plist;
    }
    while (plist->next != NULL)
            plist = plist->next;
    insert_after(plist, p); 
  } else if ((cond = strcmp(w, p->word)) == 0) {
          p->count++;
          struct list_node *plist = p->plist;
          while (p->plist->prev != NULL && p->plist->prev->pTreeNode->count < p->count)
                  p->plist = p->plist->prev;
          insert_before(p->plist, p);
          p->plist = p->plist->prev;
          cut_list_node(plist);
  }
  else if (cond < 0)
    p->left = addtree(p->left, w);
  else
    p->right = addtree(p->right, w);
  return p;
}

void list_print()
{
        struct list_node *plist = &tree_list;
        while (plist->next != NULL) {
                printf("%d %s\n", plist->pTreeNode->count, plist->pTreeNode->word);
                plist = plist->next;
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

void insert_after(struct list_node *pnode, struct tnode *ptree)
{
        struct list_node *temp = pnode->next;
        pnode->next = alloc_list_node();
        pnode->next->next = temp;

        pnode->next->pTreeNode = ptree;
}

void insert_before(struct list_node *pnode, struct tnode *ptree)
{
        struct list_node *temp = pnode->prev;
        pnode->prev = alloc_list_node();
        pnode->prev->prev = temp;

        pnode->prev->pTreeNode = ptree;
}

struct list_node *alloc_list_node()
{
        struct list_node *pnode = malloc(sizeof(struct list_node));
}

void cut_list_node(struct list_node *pnode)
{
        pnode->prev->next = pnode->next;
        pnode->next->prev = pnode->prev;
        free(pnode);
}
