#include "malloc.h"
#include "printf.h"
#include "strings.h"
#include "uart.h"


static char *strndup(const char *src, int n)
{
    // TODO fill this in
    return "";
}

static int isspace(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n';
}

static int tokenize(const char *line, char *array[],  int max)
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
    return ntokens;
}

void main(void)
{
    uart_init();

    char *str = "Leland Stanford Junior University Established 1891";
    int max = strlen(str); // number of tokens is at most length of string
    
    char *array[max];   // declare stack array to hold strings

    int ntokens = tokenize(str, array, max);
    for (int i = 0; i < ntokens; i++)
        printf("[%d] = %s\n", i, array[i]);
    printf("\04");
}
