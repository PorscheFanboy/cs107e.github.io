int binky(int x)
{
   return x+2;
}

int winky(int x)
{
   int y = binky(x+1);
   return x+y;
}

void main()
{
   int y = winky(2);
   (void)y;
}

