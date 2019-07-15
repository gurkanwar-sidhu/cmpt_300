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
}

void destroy_allocator() {
    free(kallocator.memory);

    // free other dynamic allocated memory to avoid memory leak
}

void* kalloc(int _size) {
    void* ptr = NULL;
    
    // Allocate memory from kallocator.memory 
    // ptr = address of allocated memory
   if(kallocator.a_head == NULL){ 
    
        struct nodeStruct* new_node = List_createNode(&ptr);
        List_insertHead(&(kallocator.a_head), new_node);
        ptr = kallocator.memory;
        kallocator.size -= _size;
        new_node->n_ptr = &ptr;
        new_node->size = sizeof(ptr);
    }

    else if(kallocator.a_head != NULL){
        int count = List_countNodes((kallocator.a_head));
        /*struct nodeStruct* current = kallocator.head;
        while(count > 0){
            current = current->next;
            count--;
        }*/
    // add meta-data to linked list
        struct nodeStruct* new_node = List_createNode(&ptr);
        List_insertTail(&(kallocator.a_head), new_node);
        ptr = kallocator.memory + (count*_size);
        kallocator.size -= _size;
        new_node->n_ptr = &ptr;
        new_node->size = sizeof(ptr);
    }
    
 return ptr;
}

void kfree(void* _ptr) {
    assert(_ptr != NULL);

    
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
    int free_size = 0;
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



