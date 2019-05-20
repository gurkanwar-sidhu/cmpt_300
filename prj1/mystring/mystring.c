#include "mystring.h"
#include <stdio.h>
#include <stdlib.h>

/*
 *   Implement the following functions: 
 * 
 *   You are NOT allowed to use any standard string functions such as 
 *   strlen, strcpy or strcmp or any other string function.
 */

/*
 *  mystrlen() calculates the length of the string s, 
 *  not including the terminating character '\0'.
 *  Returns: length of s.
 */
int mystrlen (const char *s) //fix: empty strings?
{
	char temp;
	temp = s[0];
	int count = 0;
	
	while(temp != '\0'){
		count++;
		temp = s[count];
	}
	return count;
}

/*
 *  mystrcpy()  copies the string pointed to by src (including the terminating 
 *  character '\0') to the array pointed to by dst.
 *  Returns: a  pointer to the destination string dst.
 */
char  *mystrcpy (char *dst, const char *src)
{
		//find length of src string
	int count =0;
	char tmp = src[0];
	while(tmp != '\0'){
		count++;
		tmp = src[count];
		//printf("count is %d and char is %c\n", count, tmp);
	}
	//printf("length of string is %d", count);

		//copy over chars to dst
		
	for(int i =0 ; i<count+1 ; i++){
		//printf("copying over %c\n", src[i]);
		dst[i] = src[i];
	}

	//printf("string is %s\n", dst);
	//printf("string is %s\n", src);

	//printf("\n\n\n");
	return NULL;
}

/*
 * mystrcmp() compares two strings alphabetically
 * Returns: 
 * 	-1 if s1  < s2
 *  	0 if s1 == s2
 *  	1 if s1 > s2
 */
int mystrcmp(const char *s1, const char *s2)
{
	int itr =0;
	char tmpS1 = s1[0];
	char tmpS2 = s2[0];
	//printf("first letter %c", tmpS1);
	while( tmpS1 != '\0' && tmpS2 != '\0'){
		if(tmpS1 != tmpS2){ //if letter are different
			if(tmpS1 < tmpS2){
				return -1;
			}
			else if(tmpS1 > tmpS2){
				return 1;
			}
		}
		//printf("tmpS1: %c and tmpS2 %c\n", tmpS1, tmpS2);
		itr++;
		tmpS1 = s1[itr];
		tmpS2 = s2[itr]; 
	}

	if(tmpS1 < tmpS2){ //if one word is longer than the other
		return -1;
	}
	else if(tmpS1 > tmpS2){
		return 1;
	}
	else if(tmpS1 == tmpS2){
		return 0;
	}

	return 0;
}

/*
 * mystrdup() creates a duplicate of the string pointed to by s. 
 * The space for the new string is obtained using malloc.  
 * If the new string can not be created, a null pointer is returned.
 * Returns:  a pointer to a new string (the duplicate) 
 	     or null If the new string could not be created for 
	     any reason such as insufficient memory.
 */
char *mystrdup(const char *s1)
{
	
		//find how big s1 is
	int count =0;
	char tmp = s1[0];
	while(tmp != '\0'){
		count++;
		tmp = s1[count];
		//printf("count is %d and char is %c\n", count, tmp);
	}

		//malloc space in new pointer
	char* strDup = (char*) malloc(count+1 *sizeof(char));
	if(strDup == NULL){
		return 	NULL; 
	}
		//copy string over 
	//printf("\n\n\n");	
	for(int i =0 ; i< count+1 ; i++){
		strDup[i] = s1[i];
		
		//printf(" %c", strDup[i]);
	}	

	return strDup;
}

