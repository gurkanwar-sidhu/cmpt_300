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
	int count = 0;
	struct nodeStruct* temp = *headRef;
	printf("\nprinting all nodes: \n");
	if(temp!= NULL){
		printf("next item: %d\n",temp->item);
	}
	while(temp->next != NULL){
		temp = temp->next;
		printf("next item : %d\n",temp->item);
		count++;
		if(count>15){
			break;
		}
	}
	printf("\n\n\n");
}

/*
 * Main()
 */
int main(int argc, char** argv)
{
	printf("Starting tests...\n");
	
	//struct nodeStruct *head = NULL;
	
	printf("Starting prof's tests...\n");
	printf("TESTING :List_insertHead \n");
	struct nodeStruct *headTestInsert = NULL;
	// Create 1 node:
	assert(List_countNodes(headTestInsert) == 0);
	struct nodeStruct* firstNode = List_createNode(0);
	List_insertHead(&headTestInsert, firstNode);
	assert(List_countNodes(headTestInsert) == 1);
	assert(List_findNode(headTestInsert, 0) == firstNode);
	assert(List_findNode(headTestInsert, 1) == NULL);
	printf("TESTING :List_insertHead test passed\n");
	//List_print(&headTestInsert);
	
	// Starting count:
	printf("TESTING :List_count\n");
	struct nodeStruct *headTestCount = NULL;
	//beginning with empty array
	assert(List_countNodes(headTestCount)== 0);
	//adding one element
	struct nodeStruct* aNode = List_createNode(0);
	List_insertHead(&headTestCount, aNode);
	assert(List_countNodes(headTestCount) == 1);
	//deleting one element back to 0
	List_deleteNode(&headTestCount, aNode);
	assert(List_countNodes(headTestCount)== 0);
	printf("TESTING :List_count passed\n");
	

	// Insert tail: 
	printf("TESTING :List_insertTail \n");
	struct nodeStruct *headTestTail = NULL;
	//add to empty list
	firstNode = List_createNode(0);
	List_insertTail(&headTestTail, firstNode);
	assert(headTestTail->item ==0);
	//add another item
	struct nodeStruct* lastNode = List_createNode(-5);
	List_insertTail(&headTestTail, lastNode);
	assert(List_countNodes(headTestTail) == 2);
	assert(List_findNode(headTestTail, 0) == firstNode);
	assert(List_findNode(headTestTail, -5) == lastNode);
	assert(List_findNode(headTestTail, 1) == NULL);
	List_print(&headTestTail);
	// Verify list:
	struct nodeStruct *current = headTestTail;
	assert(current->item == 0);
	assert(current->next != NULL);
	current = current->next;
	assert(current->item == -5);
	assert(current->next == NULL);
	
	printf("TESTING :List_insertTail test passed\n");

	//Testing List_findNode()
	printf("TESTING :List_findNode() \n");
	struct nodeStruct *headTestFind = NULL;
	//find on empty list, return NULL
	assert(List_findNode(headTestFind, 1) == NULL);
	//find with one element
	struct nodeStruct *aNode1 = List_createNode(0);
	List_insertTail(&headTestFind, aNode1);
	assert(List_findNode(headTestFind, 0) == aNode1);
	//find with two elements
	struct nodeStruct *aNode2 = List_createNode(-5);
	List_insertTail(&headTestFind, aNode2);
	assert(List_findNode(headTestFind, -5) == aNode2);
	printf("TESTING :List_findNode() passed \n");
	
	//List_print(&head);
	
	// Sort and verify:
	printf("TESTING : sort");
	//DEMO 1 *******
	struct nodeStruct *headTestSort = NULL;
	assert(List_findNode(headTestSort, 1) == NULL);	
	struct nodeStruct *sNode1 = List_createNode(-5);
	List_insertTail(&headTestSort, sNode1);
	struct nodeStruct *sNode2 = List_createNode(0);
	List_insertTail(&headTestSort, sNode2);
	//assert(List_countNodes(headTestSort) == 2);
	struct nodeStruct *sNode3 = List_createNode(777);
	List_insertTail(&headTestSort, sNode3);
	struct nodeStruct *sNode4 = List_createNode(99);
	List_insertTail(&headTestSort, sNode4);
	struct nodeStruct *sNode5 = List_createNode(1234);
	List_insertTail(&headTestSort, sNode5);
	assert(List_countNodes(headTestSort) == 5);
		
	//DEMO 2 *******
	struct nodeStruct *sNode6 = List_createNode(33);
	List_insertTail(&headTestSort, sNode6);
	struct nodeStruct *sNode7 = List_createNode(6);
	List_insertTail(&headTestSort, sNode7);
	struct nodeStruct *sNode8 = List_createNode(4);
	List_insertTail(&headTestSort, sNode8);
	struct nodeStruct *sNode9 = List_createNode(10);
	List_insertTail(&headTestSort, sNode9);
	struct nodeStruct *sNode0 = List_createNode(3);
	List_insertTail(&headTestSort, sNode0);
	List_print(&headTestSort);
	assert(List_countNodes(headTestSort) == 10);
	List_sort(&headTestSort); 

	List_print(&headTestSort);

	// Delete
	printf("TESTING: List_delete()\n");
	struct nodeStruct *headTestDel = NULL;
	current = headTestDel;
	aNode = List_createNode(-5);
	List_insertHead(&headTestDel, aNode);
	aNode = List_createNode(0);
	List_insertHead(&headTestDel, aNode);
	assert(List_countNodes(headTestDel) == 2); 
	//testing deleting head with 2 element array
	struct nodeStruct *nodeOf0 = List_findNode(headTestDel, 0);
	List_deleteNode(&headTestDel, nodeOf0);
	assert(List_countNodes(headTestDel) == 1);
	assert(List_findNode(headTestDel, 0) == NULL);
	assert(List_findNode(headTestDel, 1) == NULL); 
	current = headTestDel;
	assert(current->item == -5);
	assert(current->next == NULL);
	//deleting head with one 1 element in array
	assert(List_countNodes(headTestDel) == 1);
	struct nodeStruct *onlyNode = List_findNode(headTestDel, -5);
	List_deleteNode(&headTestDel, onlyNode);
	assert(List_countNodes(headTestDel) == 0);
	//deleting third element with 4 elements in array
	struct nodeStruct* fourthNode = List_createNode(-4);
	List_insertHead(&headTestDel, fourthNode);	
	struct nodeStruct* thirdNode = List_createNode(-3);
	List_insertHead(&headTestDel, thirdNode);
	struct nodeStruct* secNode = List_createNode(-2);
	List_insertHead(&headTestDel, secNode);
	struct nodeStruct* first_Node = List_createNode(-1);
	List_insertHead(&headTestDel, first_Node);
	assert(List_countNodes(headTestDel) == 4);
		//deleting third element
	struct nodeStruct *delThirdNode = List_findNode(headTestDel, -3);
	List_deleteNode(&headTestDel, delThirdNode);
	assert(List_countNodes(headTestDel) == 3);
	assert(List_findNode(headTestDel, -3)==NULL);
	//deleting last element with 3 element in array
	assert(List_countNodes(headTestDel) == 3);
	struct nodeStruct *delLastNode = List_findNode(headTestDel, -4);
	List_deleteNode(&headTestDel, delLastNode);
	assert(List_findNode(headTestDel, -4)==NULL);
	assert(List_countNodes(headTestDel) == 2);
	//deleting last element with only 2 elements in array
	assert(List_countNodes(headTestDel) == 2);
	struct nodeStruct *delAgainNode = List_findNode(headTestDel, -2);
	List_deleteNode(&headTestDel, delAgainNode);
	assert(List_findNode(headTestDel, -2)==NULL);
	assert(List_countNodes(headTestDel) == 1);
	struct nodeStruct *currentOnly = headTestDel;
	assert(currentOnly->item == -1);
	//deleting element that does not exist in array
	assert(List_countNodes(headTestDel) == 1);
	struct nodeStruct *randNode = List_createNode(55);
	List_deleteNode(&headTestDel, randNode);
	assert(List_countNodes(headTestDel) == 1);
	struct nodeStruct *curr = headTestDel;
	assert(curr->item == -1);
	//empty list is passed. Do nothing!!!!
	struct nodeStruct *negOneNode = List_findNode(headTestDel, -1);
	List_deleteNode(&headTestDel, negOneNode);
	List_deleteNode(&headTestDel, negOneNode);
	assert(List_countNodes(headTestDel) == 0);


	printf("TESTING: List_delete() passed\n");



	printf("\nExecution finished.\n");
	return 0;
}
