#include "malloc.h"
#include "list.h"
#include "printf.h"

static size_t strlen(const char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++) ;
    return i;
}

static char *strdup(const char *src)
{
    int len = strlen(src);
    char *copy = malloc(len + 1);
    for (int i = 0; i <= len; i++)
        copy[i] = src[i]; 
    return copy;   
}

static int isspace(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n';
}

static List *tokenize(const char *line)
{
    List *tokens = NULL;

    char tmp[strlen(line)+1];   // tmp buffer on stack

    while (*line != '\0') {
        while (isspace(*line)) line++;  // skip past spaces
        char *dst = tmp;
        while (*line != '\0' && !isspace(*line)) { // gather to next space/null
            *dst++ = *line++;
        }
        *dst = '\0';
        if (!*tmp) break;
        tokens = cons(strdup(tmp), tokens);
    }
    return reverse(tokens);
}


void main(void)
{
    printf_init();
    malloc_init();

    List *tokens = tokenize("Leland Stanford Junior University Established 1891");

    for( List *t = tokens; t; t = t->cdr )
        printf("%s\n", (char*)t->car );

    freelist(tokens, free);
}
