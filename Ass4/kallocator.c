#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "kallocator.h"
#include "list_sol.c"

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
    int a_count = List_countNodes((kallocator.a_head));
    for(int a = 0; a < a_count; a++){
        List_deleteNode(&(kallocator.a_head), kallocator.a_head);
    }

    int f_count = List_countNodes((kallocator.f_head));
    for(int f = 0; f < f_count; f++){
        List_deleteNode(&(kallocator.f_head), kallocator.f_head);
    }

    free(kallocator.memory);

    // free other dynamic allocated memory to avoid memory leak
}

void* kalloc(int _size) {
    void* ptr = NULL;
    int count = List_countNodes((kallocator.a_head));

    // Allocate memory from kallocator.memory 
    // ptr = address of allocated memory
   if(count == 0){ 
        
        //printf("count should be 0 only appears once.\n");
        struct nodeStruct* new_node = List_createNode(ptr);
        List_insertHead(&(kallocator.a_head), new_node);
        ptr = kallocator.memory;
        kallocator.size -= _size;
        new_node->n_ptr = ptr;
        new_node->size = sizeof(ptr);
        new_node->next = NULL;
    //printf("head pointing to: %p\n", (kallocator.a_head->n_ptr));

    }

    else {//if(kallocator.a_head != NULL){
    // add meta-data to linked list
        //count = List_countNodes((kallocator.a_head));
        //printf("count: %d, should be more than 0 incrementing\n", count);
        struct nodeStruct* new_node = List_createNode(ptr);
        List_insertTail(&(kallocator.a_head), new_node);
        ptr = kallocator.memory + (count*_size);
        kallocator.size -= _size;
        new_node->n_ptr = ptr;
        new_node->size = sizeof(ptr);
        new_node->next = NULL;
   // printf("head pointing to: %p\n", (kallocator.a_head->n_ptr));
    }
    
 return ptr;
}

void kfree(void* _ptr) {
    assert(_ptr != NULL);
    int count = List_countNodes((kallocator.f_head));

    if(count == 0){
    
        struct nodeStruct* free_node = List_createNode(_ptr);   
        List_insertHead(&(kallocator.f_head), free_node);
        assert((kallocator.a_head->n_ptr) == _ptr);
        //printf("a:%p, p:%p\n", *(kallocator.a_head->n_ptr), _ptr);
        free_node->n_ptr = _ptr;
        free_node->size = sizeof(_ptr);
        //free(_ptr);
    }

    //count = List_countNodes((kallocator.f_head));
    else if(count > 0){ //if(kallocator.f_head != NULL){

    struct nodeStruct* current = kallocator.a_head;

    for(int i = 0; i < count; i++){
        if(((current->n_ptr) == NULL) && ((current->next->n_ptr) == NULL)){
            //current = current->next;
            //if(*(current->n_ptr) == NULL){
                current->size += current->next->size;
                List_deleteNode(&(kallocator.a_head), current->next);
                i++;
            //}
        }
        else{
            current = current->next;
        }
    }
        //printf("check access.\n");
        struct nodeStruct* free_node = List_createNode(_ptr);   
        List_insertTail(&(kallocator.f_head), free_node);  
        free_node->n_ptr = _ptr;
        free_node->size = sizeof(_ptr);
        //free(_ptr);
    }
    //free(_ptr);
    
}

int compact_allocation(void** _before, void** _after) {
    int compacted_size = 0;

    // compact allocated memory
    // update _before, _after and compacted_size

    return compacted_size;
}

int available_memory() {
    int available_memory_size = 0;
    int allocated_memory = 0;
    int count = List_countNodes((kallocator.a_head));
    struct nodeStruct* current = kallocator.a_head;
    
    while(count > 0){
        allocated_memory += current->size;
        current = current->next;
        count--;
    }

    available_memory_size = 100 - allocated_memory;
    // Calculate available memory size
    return available_memory_size;
}

void print_statistics() {
    int allocated_size = 0;
    int allocated_chunks = 0;
    int free_size = available_memory();
    int free_chunks = 0;
    int smallest_free_chunk_size = kallocator.size;
    int largest_free_chunk_size = 0;

    // Calculate the statistics

    printf("Allocated size = %d\n", allocated_size);
    printf("Allocated chunks = %d\n", allocated_chunks);
    printf("Free size = %d\n", free_size);
    printf("Free chunks = %d\n", free_chunks);
    printf("Largest free chunk size = %d\n", largest_free_chunk_size);
    printf("Smallest free chunk size = %d\n", smallest_free_chunk_size);
}



