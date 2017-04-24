#include "assert.h"
#include <string.h>

size_t strlen(const char *str)
{
}

char *strcpy(char *dst, const char *src)
{
}


void use_stack(void)
{
	char arr[27];
	for (int i = 0; i < sizeof(arr); i++)
		arr[i] = 'A' + i;
	arr[26] = '\0';
	assert(strlen(arr) == sizeof(arr) -1);
}


int test_strlen(const char *s)
{
	const char *literal = "Stanford";
	char stack[] = "University";
	char uninitialized[10];
	char ch = 'A';

	int total =  strlen(s);
	total += strlen(literal);
	total += strlen(stack);
	total += strlen(uninitialized);
	total += strlen(NULL);
	total += strlen(&ch);
	return total;
}

int test_strcpy(const char *s)
{
	char copy[strlen(s)+1];
	strcpy(copy, s); 
	assert(strlen(s) == strlen(copy));
	return 107;
}

int main(void)
{
	int first = test_strlen("Omar");
	// use_stack();  // what happens if we uncomment this line?
	int second = test_strlen("Anna");
	assert(first == second);

	int third = test_strcpy("Michelle");
	int fourth = test_strcpy("John Jacob Jingleheimer Schmidt");
	int fifth = test_strcpy("Will");
	return third + fourth + fifth;
}

