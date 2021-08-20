
#define MAXWORD 100


typedef struct list_node {
        char *word;
        int count;
        struct list_node *next;
        struct list_node *prev;
} t_list;

void    AddWord(t_list *first, char *word);
void    list_print();
t_list  *AllocNode();
