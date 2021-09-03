#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 100
#define MAXLINE 1000

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *name);
int define(char *line);

char *nextword(char *line, char *word);
int getline(char *line);

struct nlist {
        struct nlist *next;
        char *name;
        char *defn;
};

static struct nlist *hashtab[HASHSIZE];

int main()
{
        char line[MAXLINE];
        while (getline(line) >= 0) {
                if (line[0] == '#') {
                        //define(line);
                        puts(line);
                }

        }
}

int getline(char *line)
{
        char c;
        int p = 0;;
        while ((c = getchar()) >= 0 && c != '\n' && p < MAXLINE)
                line[p++] = c;
        line[p] = '\0';
        return c;
}

char *nextword(char *line, char *word)
{
        int ipw = 0;
        int ipl = 0;

        while (line[ipl] == ' ' && line[ipl] != '\0')
                ipl++;
        char c = word[ipw++] = line[ipl++];
        if (isalpha(c) || c == '_')
                while ((isalpha(line[ipl]) || line[ipl] == '_') && ipw < MAXWORD)
                        word[ipw++] = line[ipl++];
        word[ipw] = '\0';
        return line + ipl;
}

int define(char *line)
{
        char *lp = line;
        char name[MAXWORD];
        char word[MAXWORD];

        lp = nextword(lp, name);

        if (!(isalpha(name[0]) || name[0] == '_'))
                return 1;

        nextword(lp, word);
        if (word[0] == '\0')
                return 2;

        install(name, lp);

        return 0;
}

unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void *) np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *name)
{
    struct nlist *np,*prev;
    unsigned hashval;
    if ((np = lookup(name)) != NULL) {
        hashval = hash(name);
        hashtab[hashval] = NULL;
        while (np != NULL) {
            prev = np;
            np = np->next;
            free((void *) prev->defn);
            free((void *) prev->name);
            free((void *) prev);
        }
    }
}














