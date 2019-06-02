# Assignment 2: Shell with History - CMPT 300

In this project we develop a simple UNIX shell. The shell accepts user commands.


## Additional files
   * discussion.txt used to communicate tasks and workload

## String Manipulation Functions

### Design Decisions & Project Issues:

#### Design Decisions:
1. int   mystrlen (const char *s);
    * simple while loop to count letter until reaches '\0'
    
2. char* mystrcpy (char *dst, const  char *src);
    * copy string to tmp array and then transfer tmp array to destination array
    * decided a two stop process would be simpler
    
3. int   mystrcmp (const char *s1,const char *s2);
    * use while loop to see if any letter is more than or less than corresponding letters in other string
    * if both words are same up to a point, but one is longer use mystrlen() to compare words
    
4. char* mystrdup (const char *src);
   * use mystrlen() to find length of string
   * malloc space in new array
   * copy array with mystrcpy()

#### Project Issues:
   * Not too many issues. Used stack overflow when confused about dynamic memory allocation and pointers.  

### How to Run Tests

To run the test on functions in mystring/mystring.c compile the mystring/Makefile with

'''
make all
'''
