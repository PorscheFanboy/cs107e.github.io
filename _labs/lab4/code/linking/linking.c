int n;
int n_init = 1;
const int n_const_init = 2;

static int n_static;
static int n_static_init = 3;
static const int n_static_const;
static const int n_static_const_init = 4;

// const int n_array[10];

static int not_main(int a, int b)
{
    n = a;
    n_init = b;
    n_static += a+b;
    n_static_init += a-b;

    return n + n_init + n_const_init +
    	n_static + n_static_init + n_static_const + n_static_const_init;
}

int main(void)
{
    return not_main(5, 6);
}
