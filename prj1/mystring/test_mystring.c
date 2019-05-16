#include "mystring.h"
#include <assert.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * The following are simple tests to help you.
 * You should develop more extensive tests to try and find bugs.
 */
int main()
{
	const int SIZE = 100;
	char buffer[SIZE];
	printf("\n\n\n\n\n");
	assert(mystrlen("cmpt 300") == 8);
    
	mystrcpy(buffer, "I am testing my string functions!");
	assert(strcmp(buffer, "I am testing my string functions!") == 0);

	//mystrcmp equals and return 0
	assert(mystrcmp ("I love coding", "I love coding") == 0);
	//mystrcmp < and return -1
	assert(mystrcmp ("I love codina", "I love coding") == -1);
	//mystrcmp > and return 1
	assert(mystrcmp ("I love codinz", "I love coding") == 1);
	//mystrcmp < and return -1
	assert(mystrcmp ("aaaaa", "zz") == -1);
	//mystrcmp > and return -1
	assert(mystrcmp ("aa", "zzzzzz") == -1);

	char *dupStr = mystrdup(buffer);
	assert (!strcmp(buffer, dupStr));// returns 0 meaning it is equal. therefore not 0 is true.
	assert (buffer != dupStr); //pointers are not equal?

	if (dupStr != NULL)
		free (dupStr);

	printf ("\nPassed VERY simple tests, remember to develop more tests.\n");
	
	return 0;
}

