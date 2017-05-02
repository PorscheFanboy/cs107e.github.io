#include "malloc.h"
#include "printf.h"

static size_t strlen(const char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++) ;
    return i;
}

static char *strndup(const char *src, int n)
{
    char *copy = malloc(n + 1);
    for (int i = 0; i < n; i++)
        copy[i] = src[i]; 
    copy[n] = '\0';
    return copy;   
}

static int isspace(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n';
}

static char** tokenize(const char *line, char *array[], int* ntokens_ptr, int max)
{
    int ntokens = 0;

    while (*line != '\0' && ntokens < max) {
        while (isspace(*line)) line++;  // skip past spaces
        if (*line == '\0') break; // no more non-white chars
        const char *start = line;
        while (*line != '\0' && !isspace(*line)) line++; // advance to next space/null
        int nchars = line - start;
        array[ntokens++] = strndup(start, nchars);   // make heap-copy, add to array
    }
    *ntokens_ptr = ntokens; // update passed reference of ntokens
    return array;
}

void main(void)
{
    printf_init();
    malloc_init();

    char *str = "Leland Stanford Junior University Established 1891";
    int max = strlen(str); // number of tokens is at most length of string
    
    char *array[max];   // make stack array to hold strings.
    int ntokens = 0;

    char **arr_ptr = tokenize(str, array, &ntokens, max);
    for (int i = 0; i < ntokens; i++)
        printf("[%d] = %s\n", i, arr_ptr[i]);
}
