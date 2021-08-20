
#define MAXWORD 100


typedef struct list_node {
        char *word;
        int count;
        struct list_node *next;
        struct list_node *prev;
} t_list;

/*Insert word in the end of list or
* corellate it with existing node in list
*/
void    AddWord(t_list *node, char *word);

void    list_print();

t_list  *AllocNode();
