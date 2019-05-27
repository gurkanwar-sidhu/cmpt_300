#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


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
		node->next = NULL;
	}
	
	else{
		
		while(temp->next != NULL){
	        temp = temp->next;
		}
		temp->next = node;
		node->next = NULL;
	}    
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
	if(head==NULL){ //for empty list
		return NULL;
	}
	else{
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
	struct nodeStruct* temp = *headRef;//only one item
	if(temp!= NULL){//do nothing if empty list is passed

		if( temp->next == NULL && temp == node ){//single node case
			*headRef = NULL; 
			free(temp);		
		}
		
		else if(temp == node){//deleting head with more than one item in list
			*headRef = temp->next;
			free(temp);
		}
		
		else{
			struct nodeStruct* temp_1 = *headRef;
			struct nodeStruct* temp_2 = temp_1->next;
			while(temp_1->next != node && temp_1->next != NULL){//loop till node found or tail reached
				temp_1= temp_1->next;
			}
			if(temp_1->next == node){//make temp_2 the node to free
				temp_2 = temp_1->next;//keep list intact
				temp_1->next = temp_2->next;
				free(temp_2);//free the node to delete;
			}
		}
	}
}			


/*
 * Sort the list in ascending order based on the item field.
 * Any sorting algorithm is fine.
 */
void List_sort (struct nodeStruct **headRef){
//Sort through switching nodes>
/*	struct nodeStruct* head = *headRef;
	
	if( head != NULL && head->next != NULL ){
		
		struct nodeStruct* first = head; //first node
		struct nodeStruct* prevFirst = NULL;//previous node
		struct nodeStruct* second = first->next; //second node
		struct nodeStruct* prevSecond = first; //joining node
		struct nodeStruct* temp; //temp place holder for switch
		
		while(second!= NULL){ //runs # of node loops

			while(second != NULL){//runs # of nodes-1 loops 

				if(first->item > second->item){//check for item order
					if(first->next == second){
						first->next = second->next;
						second->next= first;
					}
					else{
						temp = second->next;
						second->next = first->next; //step 1, make second point to what first was pointing to
						first->next = temp; //step 2, make first point to what second was pointing to
						temp = second->next; 
						prevSecond->next = first; //step 3. prev of second now points to first
					}	
						//step 4, make prevFirst point to second
					if(prevFirst ==NULL){ //first iteration step
						*headRef = second;
					}
					else{
						prevFirst->next = second;//regular case
					}
					temp = second;
					second = first;//switch first
					first = temp;//switch second
				}
				prevSecond = second;//update prevSecond
				second = second->next;	
			}			
			prevFirst = first;// increment previous node
			first = first ->next;// increment first node
			prevSecond = first;// increment joining node
			second = first->next;// increment second node
		}	
	}
//end<
*/
//Sort through switching values>

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
//end<
}
