// File: codegen.c
// ---------------
// C examples that demo some interesting properties/transformations
// when C compiler generates ARM instructions


// Part (a): if/else versus switch
// The pair of functions below choose a path from a set of options by
// comparing to compile-time constants. Both functions do the same 
// computation, but one is expressed as if-else, and the other as a switch.
// Are these constructs equivalent? Let's look at the assembly to
// find out!
// A convenient way to view the generated assembly is to copy 
// and paste both functions into Compiler Explorer as a pair.
// First try with optimization at -Og level, then switch to -O2 to see more
// aggressive use of conditional instructions. 
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

// Follow-up to part (a): this pair of functions adds a few more options
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

// Part (b): loops
// This function counts the number of on bits in its argument 
// using an ordinary for loop. The C language semantics dictate that
// both for and while loops are pre-tested (i.e. the test expression 
// is evaluated before the first and every subsequent iteration). First
// sketch your own arrangement of ARM instructions to match the control
// flow for a C for-loop (i.e. init, followed by test, body, incr).
// Now look at the generated ARM to see how the compiler arranged it.
// It may help to print out the listing and annotate which section
// corresponds to init/test/body/incr. The compiler's arrangement
// makes a special case out of the first iteration so as to streamline
// each subsequent loop iteration to need only one branch, not two. I
// In many architectures (ARM included), branch instructions are more
// costly than others, so the compiler is eager to minimize their use.
int count_on_bits(int n)
{
    int count = 0;
    for (int i = 0; i < 31; i++)
        if (n & (1 << i)) count++;
    return count;
}

// Part (c): arrays and pointers
// Review the generated ARM for the two strlen functions below.
// One accesses the chars using array notation, the other walks a pointer
// down the string. When you look at the two, do you suspect that
// one formulation is more efficient than the other?  Which one?
// Copy/paste this pair into Compiler Explorer and compare their 
// generated assembly at -Og and and again at -02. What do you
// observe?  Now review the code and consider in terms of readability--
// which would you rather be in charge of maintaining and why?
int strlen_arr(const char str[])
{
    int n;
    for (n = 0; str[n] != '\0'; n++) ;
    return n;
}

int strlen_ptr(const char *str)
{
    const char *cur = str;
    while (*cur) 
        cur++;
    return cur-str;
}

// Part (d): GPIO pointers/bits
// Look at the generated ARM for this function and compare to
// the hand-written ARM from your larson scanner. Despite the C
// showing several uses of the div/mod operators, the generated ARM
// doesn't contain any references to a (non-existent) ARM divide.
// Why not?
// For set_pin_on, the "pin" argument is expected to
// be a number from 0 to 54. Remember there are two separate SET registers--
// how does this code handle (or not) switching between SET0 and SET1?
// Are all pins from 0 to 54 correctly set?  Now trace through
// to understand the consequence if the function is called with a 
// pin number completely outside the valid range, such as -1 or 150. 
// Hmmm... might it be better for the function to ignore/halt on invalid 
// request than blunder on and cause unknown havoc?
// Although such a call is in fact client error, anticipating
// that possibility and writing your code defensively can preempt future 
// heartache and headache!

#define GPIO_SET  ((unsigned int *)0x2020001C)
#define WORD_SIZE 32

void set_pin_on(int pin)
{
     int index = pin/WORD_SIZE;
     int pos = pin%WORD_SIZE;
     GPIO_SET[index] = 1 << pos;
}


int gnum; // to fake some "observable" activity

void main()
{
    // make calls to each function so none eliminated as dead code/unreachable
    gnum = choice_if(107) + choice_switch(107) +
            dense_choice_if(107) + dense_choice_switch(107) +
            count_on_bits(107) + strlen_ptr("Stanford)" + strlen_arr("University"));
}
