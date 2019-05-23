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
/*	
	// Starting count:
	assert(List_countNodes(head) == 0);
	
	//Add a bunch of nodes
	struct nodeStruct* firstNode = List_createNode(0);
	List_insertHead(&head, firstNode);
	List_print(&head);
	struct nodeStruct* lastNode = List_createNode(-5);
	List_insertTail(&head, lastNode);

	struct nodeStruct* lastNode1 = List_createNode(66);
	List_insertTail(&head, lastNode1);

	List_print(&head);

	//Print those nodes
*/

	printf("Starting prof's tests...\n");
	// Create 1 node:
	struct nodeStruct* firstNode = List_createNode(0);
	List_insertHead(&head, firstNode);
	assert(List_countNodes(head) == 1);
	assert(List_findNode(head, 0) == firstNode);
	assert(List_findNode(head, 1) == NULL);

	// Insert tail:
	struct nodeStruct* lastNode = List_createNode(-5);
	List_insertTail(&head, lastNode);
	assert(List_countNodes(head) == 2);
	assert(List_findNode(head, 0) == firstNode);
	assert(List_findNode(head, -5) == lastNode);
	assert(List_findNode(head, 1) == NULL);

	// Verify list:
	struct nodeStruct *current = head;
	assert(current->item == 0);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == -5);
	assert(current->next == NULL);
/*
	// Sort and verify:
	List_sort(&head);
	current = head;
	assert(current->item == -5);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == 0);
	assert(current->next == NULL);

	// Delete
	assert(List_countNodes(head) == 2);
	struct nodeStruct *nodeOf0 = List_findNode(head, 0);
	List_deleteNode(&head, nodeOf0);
	assert(List_countNodes(head) == 1);
	assert(List_findNode(head, 0) == NULL);
	assert(List_findNode(head, 1) == NULL);
	current = head;
	assert(current->item == -5);
	assert(current->next == NULL);
*/



	printf("\nExecution finished.\n");
	return 0;
}
