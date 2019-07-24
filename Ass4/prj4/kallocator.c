#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "kallocator.h"
//#include "list_sol.c"

struct nodeStruct {
    int size;       //size of ptr
    void* n_ptr;    //pointer to the pointer in list
    struct nodeStruct *next;// points to next node in list
   
};

static _Bool doSinglePassOnSort(struct nodeStruct **headRef);
static void swapElements(struct nodeStruct **previous, struct nodeStruct *nodeA, struct nodeStruct *b);
/*
 * Allocate memory for a node of type struct nodeStruct and initialize
 * it with the value item. Return a pointer to the new node.
 */
struct nodeStruct* List_createNode(void* ptr);

/*
 * Insert node at the head of the list.
 */
void List_insertHead (struct nodeStruct **headRef, struct nodeStruct *node);

/*
 * Insert node after the tail of the list.
 */
void List_insertTail (struct nodeStruct **headRef, struct nodeStruct *node);

/*
 * Count number of nodes in the list.
 * Return 0 if the list is empty, i.e., head == NULL
 */
int List_countNodes (struct nodeStruct *head);

/*
 * Return the first node holding the value item, return NULL if none found
 */
struct nodeStruct* List_findNode(struct nodeStruct *head, void* ptr);

/*
 * Delete node from the list and free memory allocated to it.
 * This function assumes that node has been properly set (by for example
 * calling List_findNode()) to a valid node in the list. If the list contains
 * only node, the head of the list should be set to NULL.
 */
void List_deleteNode (struct nodeStruct **headRef, struct nodeStruct *node);

void List_sort (struct nodeStruct **headRef);

struct KAllocator {
    enum allocation_algorithm aalgorithm;
    int size;
    void* memory;
    // Some other data members you want, 
    // such as lists to record allocated/free memory
    struct nodeStruct *a_head;
    struct nodeStruct *f_head;
};

struct KAllocator kallocator;


void initialize_allocator(int _size, enum allocation_algorithm _aalgorithm) {
    assert(_size > 0);
    kallocator.aalgorithm = _aalgorithm;
    kallocator.size = _size;
    kallocator.memory = malloc((size_t)kallocator.size);
    // Add some other initialization 
    kallocator.a_head = NULL;
    kallocator.f_head = NULL;
}

void destroy_allocator() {
    
    List_sort(&(kallocator.a_head));
    int a_count = List_countNodes((kallocator.a_head));
    int mem_freed = 0;
    if(a_count > 0){
        kallocator.memory = kallocator.a_head->n_ptr;
        mem_freed = 1;
    }
    for(int a = 0; a < a_count; a++){
        List_deleteNode(&(kallocator.a_head), kallocator.a_head);
    }


    List_sort(&(kallocator.f_head));
    int f_count = List_countNodes((kallocator.f_head));
    if(!mem_freed){
        kallocator.memory = kallocator.f_head->n_ptr;
    }
    for(int f = 0; f < f_count; f++){
        List_deleteNode(&(kallocator.f_head), kallocator.f_head);
    }

    free(kallocator.memory);

    // free other dynamic allocated memory to avoid memory leak
}

void* kalloc(int _size) {
    void* ptr = NULL;
    int algo = kallocator.aalgorithm;
    // Allocate memory from kallocator.memory 
    // ptr = address of allocated memory

 if(algo == 0){ //First Fit

    int count_a = List_countNodes(kallocator.a_head);
    int count_f = List_countNodes((kallocator.f_head));
    
    if(count_f == 0){ 
        struct nodeStruct* new_node = List_createNode(ptr);

        if(kallocator.size >= _size){
                
            if(count_a == 0){
                List_insertHead(&(kallocator.a_head), new_node);
            }
            else if(count_a > 0){
            List_insertTail(&(kallocator.a_head), new_node);
            }
            ptr = kallocator.memory;
            new_node->n_ptr = ptr;
            new_node->size = _size;
            new_node->next = NULL;
            kallocator.memory += _size;
            kallocator.size -= _size;
        }
     return ptr;
    }

    else if(count_f > 0){
    // add meta-data to linked list
        List_sort(&(kallocator.f_head));
        struct nodeStruct* current = kallocator.f_head;
        while(current != NULL){
            if(current->size >= _size){
                struct nodeStruct* new_node = List_createNode(ptr);
                if(count_a == 0){
                    List_insertHead(&(kallocator.a_head), new_node);
                }
                else if(count_a > 0){
                    List_insertTail(&(kallocator.a_head), new_node);
                }                
                ptr = current->n_ptr;
                kallocator.memory += current->size;
                kallocator.size -= _size;
                new_node->n_ptr = ptr;
                new_node->size = _size;
                new_node->next = NULL;
                List_deleteNode(&(kallocator.f_head), current);
                return ptr;
            }

         current = current->next;
        }
      if(kallocator.size > _size){
          /*List_sort(&(kallocator.a_head));
          struct nodeStruct* current_a = kallocator.a_head;
          for(int i = 0; i < count_a; i++){
            current_a = current_a->next;
          }
          if(current->n_ptr > current_a->n_ptr){
            if(current->n_ptr+current->size < kallocator.memory);
          }
          */
        struct nodeStruct* new_node = List_createNode(ptr);
            if(count_a == 0){
                List_insertHead(&(kallocator.a_head), new_node);
            }
            else if(count_a > 0){
                List_insertTail(&(kallocator.a_head), new_node);
            }
            ptr = kallocator.memory;
            new_node->n_ptr = ptr;
            new_node->size = _size;
            new_node->next = NULL;
            kallocator.memory += _size;
            kallocator.size -= _size;
        return ptr;
      }
    }
  return NULL;
 }

 if(algo == 1){ //Best Fit

    int count_a = List_countNodes((kallocator.a_head));
    int count_f = List_countNodes(kallocator.f_head);
    // Allocate memory from kallocator.memory 
    // ptr = address of allocated memory
   if(count_f == 0){ 
        
        struct nodeStruct* new_node = List_createNode(ptr);
        
        if(count_a == 0){
            List_insertHead(&(kallocator.a_head), new_node);
        }
        
        else if(count_a > 0){
            List_insertTail(&(kallocator.a_head), new_node);
        }    

        assert(kallocator.size >= _size);
        ptr = kallocator.memory;
        new_node->n_ptr = ptr;
        new_node->size = _size;
        new_node->next = NULL;
        kallocator.memory += _size;
        kallocator.size -= _size;

     return ptr;
    }

    else if(count_f > 0){
        List_sort(&(kallocator.f_head));
        struct nodeStruct* new_node = List_createNode(ptr);
        if(count_a == 0){
            List_insertHead(&(kallocator.a_head), new_node);
        }
        else if(count_a > 0){
            List_insertTail(&(kallocator.a_head), new_node);
        }
        struct nodeStruct* current = kallocator.f_head;
        struct nodeStruct* min = kallocator.f_head;
        while(current != NULL){
            if(min->size > current->size){
                min = current;
            }
            current = current->next;
        }
        assert(kallocator.size >= _size);
        if(min->size >= _size){
        ptr = min;
        kallocator.size -= _size;
        kallocator.memory += min->size;
        new_node->n_ptr = ptr;
        new_node->size = _size;
        new_node->next = NULL;
        List_deleteNode(&(kallocator.f_head), min);
         return ptr;
        }
        else if(min->size < _size){
        assert(kallocator.size >= _size);
        ptr = kallocator.memory;
        new_node->n_ptr = ptr;
        new_node->size = _size;
        new_node->next = NULL;
        kallocator.memory += _size;
        kallocator.size -= _size;
         return ptr;
        }
    }
        
  return NULL;
 }

 if(algo == 2){ // Worst Fit

    int count_a = List_countNodes((kallocator.a_head));
    int count_f = List_countNodes(kallocator.f_head);
    // Allocate memory from kallocator.memory 
    // ptr = address of allocated memory
   if(count_f == 0){ 
        
        struct nodeStruct* new_node = List_createNode(ptr);
        if(count_a == 0){
            List_insertHead(&(kallocator.a_head), new_node);
        }
        else if(count_a > 0){
            List_insertTail(&(kallocator.a_head), new_node);
        }
        
        assert(kallocator.size >= _size);
        ptr = kallocator.memory;
        new_node->n_ptr = ptr;
        new_node->size = _size;
        new_node->next = NULL;
        kallocator.memory += _size;
        kallocator.size -= _size;

     return ptr;
    }

    else if(count_f > 0){
        List_sort(&(kallocator.f_head));
        struct nodeStruct* new_node = List_createNode(ptr);
        if(count_a == 0){
            List_insertHead(&(kallocator.a_head), new_node);
        }
        else if(count_a > 0){
            List_insertTail(&(kallocator.a_head), new_node);
        }
        struct nodeStruct* current = kallocator.f_head;
        struct nodeStruct* max = kallocator.f_head;
        while(current != NULL){
            if(max->size < current->size){
                max = current;
            }
            current = current->next;
        }
        assert(kallocator.size >= _size);
        if(max->size >= _size){
        ptr = max;
        kallocator.size -= _size;
        kallocator.memory += max->size;
        new_node->n_ptr = ptr;
        new_node->size = _size;
        new_node->next = NULL;
        List_deleteNode(&(kallocator.f_head), max);
     return ptr;
        }
        else if(max->size < _size){
        assert(kallocator.size >= _size);
        ptr = kallocator.memory;
        new_node->n_ptr = ptr;
        new_node->size = _size;
        new_node->next = NULL;
        kallocator.memory += _size;
        kallocator.size -= _size;
         return ptr;
        }
        }
    }  

 
 return NULL;
}

void kfree(void* _ptr) {
    assert(_ptr != NULL);

    int count_f = List_countNodes((kallocator.f_head));
    if(count_f == 0){
       struct nodeStruct* free_node = List_createNode(_ptr);   
       struct nodeStruct* current = List_findNode(kallocator.a_head, _ptr);
        assert(current->n_ptr == _ptr); 
        free_node->size = current->size; 
        List_insertHead(&(kallocator.f_head), free_node);
        kallocator.size += current->size;
        List_deleteNode(&(kallocator.a_head), current);
    }
    

    else if(count_f > 0){ 
        struct nodeStruct* current = kallocator.f_head;
        struct nodeStruct* free_node = List_createNode(_ptr);
        if(_ptr > current->n_ptr){
            List_insertTail(&(kallocator.f_head), free_node);
        }
       else if(_ptr < current->n_ptr){
        List_insertHead(&(kallocator.f_head), free_node);
       }
       current = List_findNode(kallocator.a_head, _ptr);
       assert(current->n_ptr == _ptr);
       free_node->size = current->size;
       kallocator.size += current->size;
        List_deleteNode(&(kallocator.a_head), current);
    }

     List_sort(&(kallocator.f_head));
       struct nodeStruct* current_f = kallocator.f_head;
       while(current_f->next != NULL){
        if((current_f->n_ptr + current_f->size) == (current_f->next->n_ptr)){
            current_f->size += current_f->next->size;
            List_deleteNode(&(kallocator.f_head), current_f->next);
        }
        if(current_f->next == NULL){
                break;
        }
        current_f = current_f->next;
       }
}

int compact_allocation(void** _before, void** _after) {
 
    int compacted_size = 0;
    int b_index = 0;
    List_sort(&(kallocator.a_head));
    struct nodeStruct* current = kallocator.a_head;

    while(current != NULL){ //Filling before array
        if(current->n_ptr != NULL){
            _before[b_index] = (current->n_ptr);
            b_index++;
        }
        current = current->next;
    }

    List_sort(&(kallocator.f_head));

    struct nodeStruct* current_a = kallocator.a_head;
    struct nodeStruct* current_f = kallocator.f_head;
    while(current_a != NULL){
        if(current_f->n_ptr < current_a->n_ptr){//if free space infront of allocated space
            while((current_f->n_ptr + current_f->size) != (current_f->next->n_ptr)){//while free space is moved next to empty space
                current_a->n_ptr -= current_f->size;//switch allocated & empty space
                current_f->n_ptr = current_a->n_ptr + current_a->size;
                current_a = current_a->next;//go to next allocated space
            }
            if((current_f->n_ptr + current_f->size) == (current_f->next->n_ptr)){//if 2 adacent empty spaces
                current_f->size += current_f->next->size;//merge them
                List_deleteNode(&(kallocator.f_head), current_f->next);
            }
        }
        else{
            current_a = current_a->next;
        }
    }

    current = kallocator.a_head;
    int size_diff = 0;
    while(current->next != NULL){
        if(current->n_ptr+current->size < current->next->n_ptr){
            size_diff = current->next->n_ptr - (current->n_ptr+current->size);
            current->next->n_ptr -= size_diff;
        }
     current = current->next;
    }

    size_diff = kallocator.f_head->n_ptr - current->n_ptr + current->size;

    kallocator.f_head->n_ptr = current->n_ptr + current->size;
    kallocator.f_head->size += size_diff;

    int a_index = 0;
    current = kallocator.a_head;
    while(current != NULL) {//Filing after array
        
        _after[a_index] = (current->n_ptr);        
        a_index++;
        current = current->next;
    } 

    assert(b_index = a_index);

    compacted_size = a_index;
    // compact allocated memory
    // update _before, _after and compacted_size

 return compacted_size;
}

int available_memory() {
    int available_memory_size = 0;
    // Calculate available memory size
    available_memory_size = kallocator.size;
 return available_memory_size;
}

void print_statistics() {
    
    int allocated_size = 0;
    int allocated_chunks = 0;

    struct nodeStruct* current = kallocator.a_head;
    while(current != NULL){
        if((current->n_ptr != NULL) && (current->size > 0)){
            allocated_size += current->size;
        }
        if(current->n_ptr != NULL){
            allocated_chunks++;
        }
     current = current->next;
    }

    int free_size = available_memory();
    int free_chunks = List_countNodes(kallocator.f_head);
    int smallest_free_chunk_size = kallocator.size;
    int largest_free_chunk_size = 0;
    if(free_chunks == 0){
        largest_free_chunk_size = smallest_free_chunk_size;
    }
    current = kallocator.f_head;
    while(current != NULL){
        if(smallest_free_chunk_size > current->size){
            smallest_free_chunk_size = current->size;
        }
        if(largest_free_chunk_size < current->size){
            largest_free_chunk_size = current->size;
        }
     current = current->next;
    }

    // Calculate the statistics

    printf("Allocated size = %d\n", allocated_size);
    printf("Allocated chunks = %d\n", allocated_chunks);
    printf("Free size = %d\n", free_size);
    printf("Free chunks = %d\n", free_chunks);
    printf("Largest free chunk size = %d\n", largest_free_chunk_size);
    printf("Smallest free chunk size = %d\n", smallest_free_chunk_size);
}

struct nodeStruct* List_createNode(void* ptr){
    struct nodeStruct *pNode = malloc(sizeof(struct nodeStruct));
    if (pNode != NULL) {
        pNode->n_ptr = ptr;
    }
    return pNode;
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
    node->next = NULL;

    // Handle empty list
    if (*headRef == NULL) {
        *headRef = node;
    }
    else {
        // Find the tail and insert node
        struct nodeStruct *current = *headRef;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }
}

/*
 * Count number of nodes in the list.
 * Return 0 if the list is empty, i.e., head == NULL
 */
int List_countNodes (struct nodeStruct *head){
    int count = 0;
    struct nodeStruct *current = head;
    while (current != NULL) {
        current = current->next;
        count++;
    }
    return count;
}

/*
 * Return the first node holding the value item, return NULL if none found
 */
struct nodeStruct* List_findNode(struct nodeStruct *head, void* ptr){
    struct nodeStruct *current = head;
    while (current != NULL) {
        if (current->n_ptr == ptr) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/*
 * Delete node from the list and free memory allocated to it.
 * This function assumes that node has been properly set (by for example
 * calling List_findNode()) to a valid node in the list. If the list contains
 * only node, the head of the list should be set to NULL.
 */
void List_deleteNode (struct nodeStruct **headRef, struct nodeStruct *node){
    assert(headRef != NULL);
    assert(*headRef != NULL);

    // Is it the first element?
    if (*headRef == node) {
        *headRef = node->next;
    }
    else {
        // Find the previous node:
        struct nodeStruct *previous = *headRef;
        while (previous->next != node) {
            previous = previous->next;
            assert(previous != NULL);
        }

        // Unlink node:
        assert(previous->next == node);
        previous->next = node->next;
    }

    // Free memory:
    free(node);
}

void List_sort (struct nodeStruct **headRef)
{
    while (doSinglePassOnSort(headRef)) {
        // Do nothing: work done in loop condition.
    }
}
static _Bool doSinglePassOnSort(struct nodeStruct **headRef)
{
    _Bool didSwap = false;
    while (*headRef != NULL) {
        struct nodeStruct *nodeA = *headRef;
        // If we don't have 2 remaining elements, nothing to swap.
        if (nodeA->next == NULL) {
            break;
        }
        struct nodeStruct *nodeB = nodeA->next;

        // Swap needed?
        if (nodeA->n_ptr > nodeB->n_ptr){
            swapElements(headRef, nodeA, nodeB);
            didSwap = true;
        }

        // Advance to next elements
        headRef = &((*headRef)->next);
    }
    return didSwap;
}
static void swapElements(struct nodeStruct **previous,
        struct nodeStruct *nodeA,
        struct nodeStruct *nodeB)
{
    *previous = nodeB;
    nodeA->next = nodeB->next;
    nodeB->next = nodeA;
}


