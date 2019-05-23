#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/*struct listStruct {
	struct nodeStruct *head;
	struct nodeStruct *tail;
};*/
/*
 * Allocate memory for a node of type struct nodeStruct and initialize
 * it with the value item. Return a pointer to the new node.
 */
struct nodeStruct* List_createNode(int item){

    struct nodeStruct* newNode = malloc(sizeof(struct nodeStruct));
    newNode->item = item;
    newNode->next = NULL;
    return newNode;
}


/*
 * Insert node at the head of the list.
 */

void List_insertHead (struct nodeStruct **headRef, struct nodeStruct *node){
    
	node->next = *headRef;
	*headRef = node;
}


/*
 * Insert node after the tail of the list.
 */
void List_insertTail (struct nodeStruct **headRef, struct nodeStruct *node){
    
	struct nodeStruct *temp = malloc(sizeof(struct nodeStruct));
	temp = *headRef;

    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = node;
	node->next = NULL;
}


/*
 * Count number of nodes in the list.
 * Return 0 if the list is empty, i.e., head == NULL
 */
int List_countNodes (struct nodeStruct *head){

	int count = 0;
    if(head == NULL){
        return count;
    }
	else{
		struct nodeStruct *temp = malloc(sizeof(struct nodeStruct));
		temp = head;

    	while(temp->next != NULL){
			count++;
        	temp = temp->next;
    	}
    return count;
	}
}


/*
 * Return the first node holding the value item, return NULL if none found
 */
struct nodeStruct* List_findNode(struct nodeStruct *head, int item){

	if(head->item == item){
		return head;
	}

	struct nodeStruct *temp = malloc(sizeof(struct nodeStruct));
	temp = head;

	while( temp->item != item){
		
		if( temp->item == item){
			return temp;
		}
		
		temp = temp->next;
	}

 return NULL;	
}

/*
 * Delete node from the list and free memory allocated to it.
 * This function assumes that node has been properly set to a valid node 
 * in the list. For example, the client code may have found it by calling 
 * List_findNode(). If the list contains only one node, the head of the list 
 * should be set to NULL.
 */
void List_deleteNode (struct nodeStruct **headRef, struct nodeStruct *node);


/*
 * Sort the list in ascending order based on the item field.
 * Any sorting algorithm is fine.
 */
void List_sort (struct nodeStruct **headRef);



