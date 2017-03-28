int i;
static int j;

int k = 1;
static int l = 2;

int a[4];
static int b[4];

int c[4] = {1, 2, 3, 4};
static int d[4] = {5, 6, 7, 8};;

void tricky(int x, int y)
{
   b[0] = j = i+a[0]+x;
   d[0] = l = k+c[0]+y;
}
