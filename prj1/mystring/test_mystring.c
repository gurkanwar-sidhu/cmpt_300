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
	char *emptyString = "";

	//TESTING mystrlen()
	//basic string
	assert(mystrlen("cmpt 300") == 8);
	//empty string
	assert(mystrlen(emptyString) == 0);


    //TESTING mystrcpy()
	//copying empty string
	mystrcpy(buffer, "");
	assert(strcmp(buffer,"") == 0 );
	assert(strlen(buffer) == 0);
	char teststr[mystrlen(buffer)];	
	
	//regular string copy
	mystrcpy(buffer, "I am testing my string functions!");
	mystrcpy(teststr, buffer);
	assert(strcmp(buffer, teststr) == 0);

	//TESTING mystrcmp()
	//check: order which words come in dictionary?
	//compare aaa with empty string. should return 1
	assert(mystrcmp("aaa","")==1);
	//compare empty string with empty string. should return 0
	assert(mystrcmp("","")==0);
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
	
	
	
	//TESTING mystrdup()
	//regular duplication
	char *dupStr = mystrdup(buffer);
	assert (!strcmp(buffer, dupStr));// returns 0 meaning it is equal. therefore not 0 is true.
	assert (buffer != dupStr); //pointers are not equal?
	if (dupStr != NULL)
		free (dupStr);
	//empty string duplication
	emptyString = "";
	char *emptyDup = mystrdup(emptyString);
	assert(strcmp(emptyDup, emptyString)==0);	
	
	printf ("\nPassed VERY simple tests, remember to develop more tests.\n");
	
	return 0;
}

