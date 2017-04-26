#include "assert.h"
#include <string.h>

size_t strlen(const char *str)
{
    const char *start = str;
    while (*str != '\0') 
        str++;
    return str - start;
}

char *strcpy(char *dst, const char *src)
{
    // Your turn -- implement strcpy!
    return NULL;
}


int atoi(const char *str)
{
    // Convert string of digits to numeric value
    return 0;
}


// --------  unit tests from here down -------------------


void test_strlen(void)
{
    char *literal = "apple";
    char stack[] = "banana";

    assert(strlen("cherry") == 6);
    assert(strlen("") ==  0);
    assert(strlen(stack) + 1 == sizeof(stack));
    assert(strlen(literal + 1) == strlen(literal) - 1); 
}

void test_strcpy(const char *orig)
{
    int len = strlen(orig);
    char buf[len + 1]; // + one for terminator

    char *copy = strcpy(buf, orig);  
    for (int i = 0; i <= len; i++)
        assert(copy[i] == orig[i]);
}

void test_atoi(void)
{
    assert(atoi("8") == 8);
    assert(atoi("127") == 127);
    assert(atoi("00010") == 10);
}

int bogus_strlen_calls(const char *s)
{
    char uninitialized[10];
    char ch = 'A';
    int total = strlen(s);

    // what "should" happen on these calls? what *does* happen?
    total += strlen(uninitialized); // bogus #1
    total += strlen(NULL);          // bogus #2
    total += strlen(&ch);           // bogus #3
    return total;
}

int use_stack(void)
{
    const char *s = "Stanford University";
    char buf[25];
    strcpy(buf, s);
    return strlen(buf);
}

int stress_test_strlen(void)
{
    int first = bogus_strlen_calls("Omar");
    int second = bogus_strlen_calls("Anna");
    assert(first == second);

    // same test as above repeated with unrelated call inserted
    // why does it fail this time, yet passed before?
    int third = bogus_strlen_calls("Omar");
    int val = use_stack();
    int fourth = bogus_strlen_calls("Anna");
    assert(third == fourth);
    return val;
}

int sketchy_strcpy_call(const char *orig)
{
    // what "should" happen if orig is longer than 10? what *does* happen?
    char copy[10];
    strcpy(copy, orig);
    return strlen(copy);
}

void stress_test_strcpy(void)
{
    assert(sketchy_strcpy_call("Michelle") == 8);   // not-so-sketchy
    assert(sketchy_strcpy_call("John Jacob Jingleheimer Schmidt") == 31); // very sketchy
    assert(sketchy_strcpy_call("Will") == 4);        // not-so-sketchy
}


void main(void)
{
    test_strlen();
    // test_strcpy("Isabel");
    // stress_test_strlen();
    // stress_test_strcpy();
    // test_atoi();
}

