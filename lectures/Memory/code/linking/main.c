extern void tricky();

extern int i;
extern int k; 
extern const int m ;

int p = 4;

void main()
{
    i = 10 + k;
    k = 11;
    p = 6;
    tricky();
}
