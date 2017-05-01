
int binky(int x)
{
    int y = x + 2;
    return y;
}

char *winky(char *str)
{
    str[1] = 'a';
    int z = binky(9);
    return str + z;
}

void main()
{
    char name[8];
    winky(name);
}