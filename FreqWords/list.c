#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

void node_insert_before(t_list *node_prev, t_list *node_next);

void node_cut(t_list *node);

void AddWord(t_list *node, char *word) {

    /*Search word in list or insert in end*/
    while (node->next != NULL && strcmp(word, node->word))
        node = node->next;

    if (node->next == NULL) {
        node->next = AllocNode();
        node->next->prev = node;
    }

    if (node->word == NULL) {
        node->word = strdup(word);
    }
    node->count++;

    t_list *temp = node;

    /*Search new place for node to save right order*/
    while (node->prev != NULL && temp->count > node->prev->count)
        node = node->prev;

    if (temp != node) {
        node_cut(temp);

        node_insert_before(temp, node);
    }

}

void list_print(t_list *node_start) {
    while (node_start != NULL && node_start->word != NULL) {
        printf("%d %s\n", node_start->count, node_start->word);
        node_start = node_start->next;
    }
}

t_list  *AllocNode() {
    t_list *node = malloc(sizeof(t_list));
    memset(node, 0, sizeof(t_list));
    return node;
}

void node_insert_before(t_list *node_prev, t_list *node_next) {
    if (node_next->prev != NULL)
        node_next->prev->next = node_prev;

    node_prev->prev = node_next->prev;
    node_prev->next = node_next;

    node_next->prev = node_prev;
}

void node_cut(t_list *node) {
    if (node->prev != NULL)
        node->prev->next = node->next;


    if (node->next != NULL)
        node->next->prev = node->prev;
}















