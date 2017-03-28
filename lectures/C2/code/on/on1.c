#define FSEL2 0x20200008
#define SET0  0x2020001C

void main()
{
   *(int *)FSEL2 = 1;

   *(int *)SET0 = 1<<20;
}

