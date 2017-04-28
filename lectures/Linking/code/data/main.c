void tricky();

extern int i;
extern int k; 
extern const int m ;

void main()
{
    i = 10 + k;
    k = 11;
    tricky();
}
