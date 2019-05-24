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
    
	struct nodeStruct *temp = *headRef;

	if(temp == NULL){
		*headRef = node;
	}

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

	
    if(head == NULL){
        return 0;
    }

	if(head->next == NULL){
		return 1;
	}
	
	int count = 1;
	struct nodeStruct *temp = head;

    while(temp->next != NULL){
		count++;
        temp = temp->next;
    }
 return count;
}


/*
 * Return the first node holding the value item, return NULL if none found
 */
struct nodeStruct* List_findNode(struct nodeStruct *head, int item){

	if(head->item == item){
		return head;
	}

	struct nodeStruct *temp = head;

	while( temp->next != NULL){
		
		if( temp->item == item){
			return temp;
		}
		
		temp = temp->next;
	}

	if( temp->item == item){
			return temp;
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
void List_deleteNode (struct nodeStruct **headRef, struct nodeStruct *node){

	struct nodeStruct* temp = *headRef;

	if( temp->next == NULL ){
		free(temp);
	}

	struct nodeStruct* temp_1 = *headRef;
	struct nodeStruct* temp_2 = temp_1->next;

	while( temp_2 != node || temp_1->next != NULL || temp_2->next != NULL ){

		if(temp_2 == node){
			free(temp_2);
			temp_1->next = temp_2->next;
			temp_2 = temp_2->next;
		}
		
		temp_1 = temp_2;
		
		if(temp_2->next != NULL){
			temp_2 = temp_2->next;
		}	
	}
}			


/*
 * Sort the list in ascending order based on the item field.
 * Any sorting algorithm is fine.
 */
void List_sort (struct nodeStruct **headRef){

 if( *headRef != NULL ){

	struct nodeStruct* first;
	struct nodeStruct* second;
	int temp;

	for(first = *headRef; first->next != NULL; first = first->next){
	
		for(second = first->next; second != NULL; second = second->next){

			if(first->item > second->item){
				temp = first->item;
				first->item = second->item;		
				second->item = temp;
			}
		}
	}
 }
 
}



