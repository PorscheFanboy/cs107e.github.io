// File: codegen.c
// ---------------
// C examples that demo some interesting properties/transformations
// when C compiler generates ARM instructions


// Part (a): if/else
// This function has a simple if/else. This could be implemented in
// assembly as two distinct code paths and a control flow that
// routes to one arm or the other using branch. Alternatively,
// it could expressed as one combined sequence of conditionally 
// executed instructions. Generate the assembly at optimization
// level -Og. Does it generate using branches or a combined sequence?
// Note there is no ARM arithmetic negate instrution -- what does 
// the compiler use instead?
int abs(int val)
{
    if (val < 0)
        return -val;
    else
        return val;
}

// Part (b): loops
// This function shows a classic for loop that sums the numbers from 
// 1 to n.  First sketch your own arrangement of ARM instructions to
// match the control flow for a C for-loop (i.e. init, followed by test, 
// body, incr). Now look at the generated ARM to see how the compiler 
// arranged it. Use -Og as your optimization level, since generates
// clean assembly that is fairly easy to follow. It may help to print 
// out the list file and annotate  which section corresponds to 
// init/test/body/incr so you can follow the control flow. When
// reading a sequence of assembly instructions, what is a sure
// sign that that original C source was a loop?
int sum(int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += i;
    return sum;
}

// Part (c): arrays and pointers
// Review the generated ARM for the two functions below that sum the
// elements of an array. One accesses the elements using array notation, 
// the other walks a pointer across the array memory. When you compare
// compare the C code, do you suspect that one version will operate more 
// efficiently than the other?  Which one?
// Copy/paste this pair of functions into Compiler Explorer and 
// compare their generated assembly at optimization level -Og. You
// should observe that they are very, very similar -- same number of
// instructions and same arrangement. You have confirmed that an array
// and pointer basically the same thing under the hood!
int sum_array(int arr[], int n)
{
    int total = 0;
    for (int i = 0; i < n; i++)
        total += arr[i];
    return total;
}

int sum_ptr(int *ptr, int n)
{
    int total = 0;
    for (int *cur = ptr; cur < ptr + n; cur++)
        total += *cur; 
    return total;
}

// Part (d): if/else versus switch
// The pair of functions below choose a path from a set of options by
// comparing to compile-time constants. Both functions do the same 
// computation, but one is expressed as if-else, and the other as a switch.
// Are these constructs equivalent? Let's look at the assembly to
// find out!
// Copy and paste both functions into Compiler Explorer as a pair.
// Use optimization at -Og level.
// You should observe that both functions generate near-identical 
// instructions, despite the fairly different expression in C.
// Interesting! 
int choice_if(int n)
{
    if (n == 5) {
        return 99;
    } else if (n == 13) {
        return 197;
    } else {
        return 0;
    }
}

int choice_switch(int n)
{
    switch(n) {
        case  5: return 99;
        case 13: return 197;
        default: return 0;
    }
}

// Follow-up to part (d): this pair of functions adds a few more options
// to the choices and the constants are grouped within a narrow range.
// Copy and paste this pair of functions into Compiler Explorer.
// This time, the generated ARM is quite different. It generated the
// switch as a "jump table" -- an optimization unique to a dense switch 
// statement. Can you and your partner work out how a jump table operates?
int dense_choice_if(int n)
{
    if (n == 100) {
        return 99;
    } else if (n == 102) {
        return 197;
    } else if (n == 105) {
        return 53;
    } else if (n == 107) {
        return 81;
    } else {
        return 0;
    }
}

int dense_choice_switch(int n)
{
    switch(n) {
        case 100: return 1;
        case 102: return 2;
        case 105: return 3;
        case 107: return 4;
        default:  return 0;
    }
}


int gnum; // to fake some "observable" activity

void main()
{
    // make calls to each function so none eliminated as dead code/unreachable
    int nums[] = {5, 2, 100};
    gnum = sum(107) + sum_array(nums, 3) + sum_ptr(nums, 3)
            + choice_if(107) + choice_switch(107)
            + dense_choice_if(107) + dense_choice_switch(107);
}

