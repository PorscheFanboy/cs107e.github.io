int i;
int j = 1;
const int k = 3;

static int l;
static int m = 2;
static const int n = 4;

int a[4];

extern int p;

void tricky()
{
   j = i + p;
   i = k + n;

   l = i;
   m = j;
}
