# Project 1 - CMPT 300

Project involves basic review of C programming, which includes arrays, strings, pointers, memory management, ect. Broken into two parts; string manipulation and linked list.


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

## Linked List Operations

### Design Decisions & Project Issues:

#### Design Decisions:
1. struct nodeStruct* List_createNode(int item);
   * allocate memory for node, initialize item and next

2. void List_insertHead (struct nodeStruct **headRef, struct nodeStruct *node);
   * make new node point to head
   * make head point to new node

3. void List_insertTail (struct nodeStruct **headRef, struct nodeStruct *node);
    * find tail with while loop
     * update tail
    
4. int List_countNodes (struct nodeStruct *head);
   * use while loop to iterate and count nodes until NULL
   * catch edge cases
   
5. struct nodeStruct* List_findNode(struct nodeStruct *head, int item);
   * use while loop to iterate and compare each nodes's item with passes in item
   
6. void List_deleteNode (struct nodeStruct **headRef, struct nodeStruct *node);
     * find node with while loop
     * use tmp pointer to store node to delete
     * update pointers to skip node to delete
     * use temp pointer to free space of tmp pointer
     
7. void List_sort (struct nodeStruct **headRef);
     * For lists that are not empty or only one node long
     * In a nested for loop compare the first node item with the rest
     * Switching item values whenever the item on the left is greater than the right
     * Continue doing so for n^2 - 1 iterations

#### Project Issues:
   * Occasional segmenation faults occured, for example when unintentionally accessing NULL pointer
      * solved using gdb and assertions

### How to Run Tests

To run the test on functions in mystring/mystring.c compile the mystring/Makefile with

'''
make all
'''


## Authors

* **Sarbjot Singh**  - [sarbjot-14](https://github.com/sarbjot-14){301313399}

* **Gurkanwar Sidhu** - [gss28](https://github.com/gurkanwar-sidhu){301290044)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

