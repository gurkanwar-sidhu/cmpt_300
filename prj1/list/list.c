#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

		if( temp->item == item){ //check: this one is for last node im assuming?
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
	struct nodeStruct* temp = *headRef;
	//only one item
	if(temp!= NULL){//do nothing if empty list is passed

		if( temp->next == NULL && temp == node ){
			//check: are we sure that it has to be first one?
			*headRef = NULL; //check: not sure if this line is right?
			free(temp);
		
		
		}//deleting head with more than one item in list
		else if(temp == node){
			*headRef = temp->next;
			free(temp);
		}
		else{
			struct nodeStruct* temp_1 = *headRef;
			struct nodeStruct* temp_2 = temp_1->next;
			while(temp_1->next != node && temp_1->next != NULL){
				//printf("Address of node: %p\n", (void *)temp_1);
				//printf("Address of delNode: %p\n", (void *)node);
				//printf("loop: %d\n", temp_1->item);
				//keep updating temp1 until temp->next points to node to delete or it points to NULL
				temp_1= temp_1->next;
			}
			if(temp_1->next == node){
				//make temp_2 the node to free/delete
				temp_2 = temp_1->next;
				//now make temp1 skip over the node to delete (point to what node beside node to delete)
					//this should work when deleting last node too
				temp_1->next = temp_2->next;
				//free the node to delete;
				free(temp_2);
			}
		}
	}

	/*
	//check: this is your loop. see why its wrong :(
	while( temp_2 != node || temp_1->next != NULL || temp_2->next != NULL ){ 


		if(temp_2 == node){
			free(temp_2);
			temp_1->next = temp_2->next; //check: why try to access temp_2 after freeing
			temp_2 = temp_2->next;
		}
		
		temp_1 = temp_2;
		
		if(temp_2->next != NULL){
			temp_2 = temp_2->next;
		}	

	}
*/	
}			


/*
 * Sort the list in ascending order based on the item field.
 * Any sorting algorithm is fine.
 */
void List_sort (struct nodeStruct **headRef){

 struct nodeStruct* head = *headRef;

 if( head != NULL && head->next != NULL ){
	int count = List_countNodes(head);//count for nested for loop
	struct nodeStruct* first;//first node
	struct nodeStruct* second;//second node
	struct nodeStruct* temp;//temporary place holder for node switch

	for(int i = 0; i < count; i++){// runs # of node loops
		int swap_chk = 0;//checks if there was a swap
		first = head;
		second = first->next;
		for(int j = 1; j < count-i-1; j++){//runs from ith position to end of list
			printf("first: %d\n", first->item);
			second = second->next;// compares every node after first node
			printf("second: %d\n", second->item); 
			assert(first != NULL);
			assert(second != NULL);
			if(first->item > second->item){// checks if the prev node is bigger than the next node
				temp = first;//set place holder to node 1
				first = second;// node 1 equals node 2		
				second = temp;// node 2 now equals node 1
				swap_chk = 1;// confirm swap so the loop continues
			}
		 head = head->next;// moves head one node over
		}
		if( swap_chk == 0 ){// confirms all swaps happened and breaks out of loop
			break;
		}
	}
 }
 

 
/*	struct nodeStruct* head = *headRef;

 if( head != NULL && head->next != NULL ){

	struct nodeStruct* first;
	struct nodeStruct* second;
	struct nodeStruct* temp;

	for(first = head; first->next != NULL; first = first->next){//loop for first 
		int swap_chk = 0;
		for(second = first->next; second->next != NULL; second = second->next){

			if(first->item > second->item){
				temp = first;
				first = second;
				second = temp;
				swap_chk = 1;
			}
		}
		if(swap_chk == 0){
			break;
		}
	}
 }*/

 //if(temp->next != NULL) 


}

//check: remember to delete this function from header file**********************
void List_Sarbsort (struct nodeStruct **headRef){
	//DEMO 1******
	/*
	struct nodeStruct* head = *headRef;
	if( head != NULL && head->next != NULL ){
		//int count = List_countNodes(head);
		struct nodeStruct* first = head;//first node
		struct nodeStruct* prevFirst = NULL;//first node
		struct nodeStruct* second = first->next;//second node
		struct nodeStruct* prevSecond = first;//first node
		struct nodeStruct* temp;//temporary place holder for node switch

		while(second != NULL){// runs # of node loops
			printf("comparing first %d and second %d\n", first->item,  second->item);
		
				if(first->item > second->item){ //keeping first the same for now. will have to update once we use second for loop
					printf("swiiiiiiiitch\n");
					
					temp = second->next;
					second->next = first->next; //step 1, make second point to what first was pointing to
					first->next = temp; //step 2, make first point to what second was pointing to
					temp = second->next; 
					prevSecond->next = first; //step 3. prev of second now points to first
					//step 4, make prevFirst point to second
					if(prevFirst ==NULL){ //this is for only the first iteration. when prevFirst is NULL. cause its before head
						*headRef = second;
						//printf("this should be 4 : %d\n", head->item);
						
					}
					else{
						prevFirst->next = second; //step 4  regular case
					}
					//update first and seconds
					temp = second;
					second = first;
					first = temp;
					
					

				}

				//update prevSecond
				prevSecond = second;
				second = second->next;
				
			
			
		}
	}
	printf("\n\n");	
	*/
	// DEMO 1 ENDED

	//DEMO 2****** use demo 33333333
	
	struct nodeStruct* head = *headRef;
	if( head != NULL && head->next != NULL ){
		//int count = List_countNodes(head);
		struct nodeStruct* first = head;//first node
		struct nodeStruct* prevFirst = NULL;//first node
		struct nodeStruct* second = first->next;//second node
		struct nodeStruct* prevSecond = first;//first node
		struct nodeStruct* temp;//temporary place holder for node switch

		while(second != NULL){// runs # of node loops
			printf("comparing first %d and second %d\n", first->item,  second->item);
		
				if(first->item > second->item){ //keeping first the same for now. will have to update once we use second for loop
					if(first->next == second){
						printf("THIS IS THE SPECIAL CASE SWITCH THEY ARE BESIDE EACH OTHER\n");

						first->next = second->next;
						second->next= first;
						

					}
					else{
						printf("swiiiiiiiitch\n");
						
						temp = second->next;
						second->next = first->next; //step 1, make second point to what first was pointing to
						first->next = temp; //step 2, make first point to what second was pointing to
						temp = second->next; 
						prevSecond->next = first; //step 3. prev of second now points to first
					}	
						//step 4, make prevFirst point to second
						if(prevFirst ==NULL){ //this is for only the first iteration. when prevFirst is NULL. cause its before head
							*headRef = second;
							//printf("this should be 4 : %d\n", head->item);
							
						}
						else{
							prevFirst->next = second; //step 4  regular case
						}
						
					//update first and seconds
					temp = second;
					second = first;
					first = temp;
					
					
					
					

				}

				//update prevSecond
				prevSecond = second;
				second = second->next;
				
			
			
		}
	}
	printf("\n\n");	
	
	//DEMO 2 ENDED
}


void List_SarbsortDemo3 (struct nodeStruct **headRef){

	struct nodeStruct* head = *headRef;
	if( head != NULL && head->next != NULL ){
		//int count = List_countNodes(head);
		struct nodeStruct* first = head;//first node
		struct nodeStruct* prevFirst = NULL;//first node
		struct nodeStruct* second = first->next;//second node
		struct nodeStruct* prevSecond = first;//first node
		struct nodeStruct* temp;//temporary place holder for node switch

		while(second!= NULL){
			while(second != NULL){// runs # of node loops
				printf("comparing first %d and second %d\n", first->item,  second->item);
				if(first->item > second->item){ //keeping first the same for now. will have to update once we use second for loop
					if(first->next == second){
						printf("THIS IS THE SPECIAL CASE SWITCH THEY ARE BESIDE EACH OTHER\n");
						first->next = second->next;
						second->next= first;
					}
					else{
						printf("swiiiiiiiitch\n");
						temp = second->next;
						second->next = first->next; //step 1, make second point to what first was pointing to
						first->next = temp; //step 2, make first point to what second was pointing to
						temp = second->next; 
						prevSecond->next = first; //step 3. prev of second now points to first
					}	
						//step 4, make prevFirst point to second
						if(prevFirst ==NULL){ //this is for only the first iteration. when prevFirst is NULL. cause its before head
							*headRef = second;
							//printf("this should be 4 : %d\n", head->item);
						}
						else{
							prevFirst->next = second; //step 4  regular case
						}
						
					//update first and seconds
					temp = second;
					second = first;
					first = temp;
				}

				//update prevSecond
				prevSecond = second;
				second = second->next;
				
			}			
			prevFirst = first;
			first = first ->next;
			prevSecond = first;
			second = first->next;
		
		}	
	}
	printf("\n\n");	
}