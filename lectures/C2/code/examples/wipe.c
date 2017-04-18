/* writes zero over all memory locations from start to end.
 * hmmm, how is that going to work out for us?
 */

int main(int argc, char *argv[])
{
    unsigned int *start = 0x0, *end = (unsigned int *)0x100000;

    for (unsigned int *addr = start; addr < end; addr++)
         *addr = 0;
}

  
