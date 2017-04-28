// uninitialized global and static variables
int i;
static int j;

// initialized global and static variables
int k = 1;
static int l = 2;

// initialized global and static const variables
const int m = 3;
static const int n = 4;

void tricky()
{
   i = k + n;
   j = i + 2;

   k = i;
   l = j;
}
