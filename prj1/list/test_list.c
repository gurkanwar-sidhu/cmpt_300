// Sample test routine for the list module.
#include <stdio.h>
#include "list.h"
#include <stdbool.h>
#include <string.h>
#include <assert.h>

/*
 * print all for personal debugging
 */
void List_print (struct nodeStruct **headRef){
	struct nodeStruct* temp = *headRef;
	printf("\nprinting all nodes: \n");
	if(temp!= NULL){
		printf("next item: %d\n",temp->item);
	}
	while(temp->next != NULL){
		temp = temp->next;
		printf("next item : %d\n",temp->item);
	}
	printf("\n\n\n");
}

/*
 * Main()
 */
int main(int argc, char** argv)
{
	printf("Starting tests...\n");
	
	struct nodeStruct *head = NULL;
	
	// Starting count:
	assert(List_countNodes(head) == 0);
/*	
	//Add a bunch of nodes
	struct nodeStruct* firstNode = List_createNode(0);
	List_insertHead(&head, firstNode);
	List_print(&head);
	struct nodeStruct* lastNode = List_createNode(-5);
	List_insertTail(&head, lastNode);

	struct nodeStruct* lastNode1 = List_createNode(66);
	List_insertTail(&head, lastNode1);

	List_print(&head);
*/
	//Print those nodes


	printf("Starting prof's tests...\n");
	// Create 1 node:
	struct nodeStruct* firstNode = List_createNode(0);
	List_insertHead(&head, firstNode);
	assert(List_countNodes(head) == 1);
	assert(List_findNode(head, 0) == firstNode);
	assert(List_findNode(head, 1) == NULL);
	printf("TESTING :List_insertHead test passed\n");
	List_print(&head);

	// Insert tail:
	struct nodeStruct* lastNode = List_createNode(-5);
	List_insertTail(&head, lastNode);
	assert(List_countNodes(head) == 2);
	assert(List_findNode(head, 0) == firstNode);
	assert(List_findNode(head, -5) == lastNode);
	assert(List_findNode(head, 1) == NULL);
	printf("TESTING :List_insertTail test passed\n");
	List_print(&head);
	// Verify list:
	struct nodeStruct *current = head;
	assert(current->item == 0);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == -5);
	assert(current->next == NULL);
	
	printf("list verified\n");
	
	//List_print(&head);
	/*
	// Sort and verify:
	printf("TESTING : sort");
	List_sort(&head);
	current = head;
	assert(current->item == -5);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == 0);
	assert(current->next == NULL);
	List_print(&head);
	*/

	// Delete
	printf("TESTING: List_delete()\n");
	List_print(&head);
	assert(List_countNodes(head) == 2); 
	//testing deleting head with 2 element array
	struct nodeStruct *nodeOf0 = List_findNode(head, 0);
	List_deleteNode(&head, nodeOf0);
	assert(List_countNodes(head) == 1);
	assert(List_findNode(head, 0) == NULL);
	assert(List_findNode(head, 1) == NULL); //check: because there is no 1 at this point ?
	current = head;
	assert(current->item == -5);
	assert(current->next == NULL);
	
	List_print(&head);
	//deleting head with one 1 element in array
	struct nodeStruct *onlyNode = List_findNode(head, -5);
	List_deleteNode(&head, onlyNode);
	printf("size is %d\n",List_countNodes(head) );
	assert(List_countNodes(head) == 0);
	//deleting second element with 4 elements in array
	//deleting last element with 4 element in array
	//deleting last element with only 2 elements in array
	//deleting element that does not exist
	//check: what happens if sent empty list? head is null? 

	printf("TESTING: List_delete() passed\n");



	printf("\nExecution finished.\n");
	return 0;
}
