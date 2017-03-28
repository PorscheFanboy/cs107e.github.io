#include <stdio.h>

int main()
{
    char *cs107e = "cs107e";

    for( char *s = cs107e; *s; s++ )
        putchar( *s );
    putchar('\n');
}

