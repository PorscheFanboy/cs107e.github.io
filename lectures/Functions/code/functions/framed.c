
int binky(int a, int b)
{
	return a * b;
}

int winky(int n)
{
	return n - 99;
}

int dinky(int d)
{
	return binky(d, -d);
}

int pinky(int *ptr)
{
	return winky(*ptr) + *ptr;
}

int tinky()
{
	int arr[100];
	arr[3] = 15;
	return pinky(arr);
}

int main(void)
{
	int x = binky(3, 6);
	return winky(x);
}