#include <stdlib.h>
#include <string.h>
#include "list.h"

void node_insert_before(t_list);

void node_cut(t_list *node);

void AddWord(t_list *node, char *word) {
    char *w = strdup(word);

    /*Search word in list or insert in end*/
    while (node->next != NULL && strcmp(word, node->word))
        node = node->next;

    node->word = w;
    node->count++;

    t_list *temp = node;

    /*Search new place for node to save right order*/
    while (node->prev != NULL && node->count > node->prev->count)
        node = node->prev;

    node_cut();

    node_insert_before();

}

void    list_print() {

}

t_list  *AllocNode() {
    t_list *node = malloc(sizeof(t_list));
    memset(node, 0, sizeof(t_list));
    return node;
}

void node_cut(t_list *node) {
    if (node->prev != NULL)
        node->prev->next = node->next;

    if (node->next != NULL)
        node-<next->prev = node->prev;
}
