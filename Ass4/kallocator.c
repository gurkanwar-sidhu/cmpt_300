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
    //printf("aalgorithm test return: %d\n", kallocator.aalgorithm);
    kallocator.size = _size;
    kallocator.memory = malloc((size_t)kallocator.size);

    // Add some other initialization 
    kallocator.a_head = NULL;
    kallocator.f_head->n_ptr = kallocator.memory;
    kallocator.f_head->size = _size;
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
    int algo = kallocator.aalgorithm;
    // Allocate memory from kallocator.memory 
    // ptr = address of allocated memory

 if(algo == 0){ //First Fit

    int count_a = List_countNodes(kallocator.a_head);
    //int count_f = List_countNodes((kallocator.f_head));
    
    if(count_a == 0){ 

        struct nodeStruct* current = kallocator.f_head;
        while(current != NULL){

            if(current->size >= _size){
                struct nodeStruct* new_node = List_createNode(ptr);
                List_insertTail(&(kallocator.a_head), new_node);
                ptr = current->n_ptr;
                kallocator.size -= _size;
                new_node->n_ptr = ptr;
                new_node->size = _size;
                new_node->next = NULL;
                current->n_ptr += _size;
                current->size -= _size;
                break;
            }
         current = current->next;
        }
     return ptr;
    }

    else if(count_a > 0){
    // add meta-data to linked list
        struct nodeStruct* current = kallocator.f_head;
        while(current != NULL){

            if(current->size >= _size){
                struct nodeStruct* new_node = List_createNode(ptr);
                List_insertTail(&(kallocator.a_head), new_node);
                ptr = current->n_ptr;
                kallocator.size -= _size;
                new_node->n_ptr = ptr;
                new_node->size = _size;
                new_node->next = NULL;
                current->n_ptr += _size;
                current->size -= _size;
                break;
            }
         current = current->next;
        }
      return ptr;
    }
 }

 if(algo == 1){ //Best Fit

 }

 if(algo == 2){ // Worst Fit

    int count = List_countNodes((kallocator.a_head));
    // Allocate memory from kallocator.memory 
    // ptr = address of allocated memory
   if(count == 0){ 
        
        struct nodeStruct* new_node = List_createNode(ptr);
        List_insertHead(&(kallocator.a_head), new_node);
        assert(kallocator.size >= _size);
        ptr = kallocator.memory;
        kallocator.size -= _size;
        new_node->n_ptr = ptr;
        new_node->size = _size;
        new_node->next = NULL;
     return ptr;
    }

    else{
        struct nodeStruct* new_node = List_createNode(ptr);
        List_insertTail(&(kallocator.a_head), new_node);
        assert(kallocator.size >= _size);
        ptr = kallocator.memory;
    }  

 }
}

void kfree(void* _ptr) {
    assert(_ptr != NULL);
    int count = List_countNodes((kallocator.f_head));

    if(count == 0){
    
        struct nodeStruct* free_node = List_createNode(_ptr);   
        List_insertHead(&(kallocator.f_head), free_node);
        assert((kallocator.a_head->n_ptr) == _ptr);
        free_node->n_ptr = _ptr;
        free_node->size = kallocator.a_head->size;
    }

    else if(count > 0){ 

        struct nodeStruct* current = kallocator.f_head;

        for(int i = 0; i < count; i++){
            if(((current->n_ptr) == NULL) && ((current->next->n_ptr) == NULL)){
                current->size += current->next->size;
                List_deleteNode(&(kallocator.f_head), current->next);
                i++;
            }
            else{
                current = current->next;
            }
        }

        current = kallocator.a_head;
    
        struct nodeStruct* free_node = List_createNode(_ptr);   
        List_insertTail(&(kallocator.f_head), free_node);  
        free_node->n_ptr = _ptr;
        while(current->n_ptr != free_node){
            current = current->next;
            if(current->next == NULL){
                break;
            }
        }
        free_node->size = current->size;
    }    
}

int compact_allocation(void** _before, void** _after) {
 
    int compacted_size = 0;
    int b_index = 0;
    struct nodeStruct* current = kallocator.a_head;

    while(current != NULL){ //Filling before array
        if(current->n_ptr != NULL){
            _before[b_index] = (current->n_ptr);
            b_index++;
        }
        current = current->next;
    }

/*
    int i = 0;
    current = kallocator.a_head;
    printf("Allocated list pre compaction:\n\n");
    while(current != NULL){
        if(current->n_ptr != NULL){
        printf("p[%d] = %p ; p[%d] size = %d\n", i, current->n_ptr, i, (current->size));
        }
        i++;
        current = current->next;
    }

    i = 0;
    current = kallocator.f_head;
    printf("Freed list pre compaction:\n\n");
    while(current != NULL){
        if(current->n_ptr != NULL){
        printf("p[%d] = %p ; *p[%d] size = %d\n", i, current->n_ptr, i, (current->size));
        }
        i++;
        current = current->next;
    }
*/
    current = kallocator.f_head;

    while(current->next != NULL){// moving null spaces to back
        if(current->n_ptr == NULL){
            current->next->n_ptr -= current->size;
            struct nodeStruct* dummy = current;
            List_deleteNode(&(kallocator.a_head), current);
            List_insertTail(&(kallocator.a_head), dummy);
        }
        current = current->next;
    }
/*
    i = 0;
    current = kallocator.a_head;
    printf("Allocated list mid compaction:\n\n");
    while(current != NULL){
        if(current->n_ptr != NULL){
        printf("p[%d] = %p ; p[%d] size = %d\n", i, current->n_ptr, i, (current->size));
        }
        i++;
        current = current->next;
    }

    i = 0;
    current = kallocator.f_head;
    printf("Freed list mid compaction:\n\n");
    while(current != NULL){
        if(current->n_ptr != NULL){
        printf("p[%d] = %p ; *p[%d] size = %d\n", i, current->n_ptr, i, (current->size));
        }
        i++;
        current = current->next;
    }
*/
    int a_index = 0;
    current = kallocator.f_head;

    while(current != NULL) {//Filing after array
        
        _after[a_index] = (current->n_ptr);
        
        if(((current->n_ptr) == NULL) && ((current->next->n_ptr) == NULL)){//mergin end NULL node
            current->size += current->next->size;
            List_deleteNode(&(kallocator.f_head), current->next);
        }
        
        a_index++;
        current = current->next;
} 

/*
    i = 0;
    current = kallocator.a_head;
    printf("Allocated list post compaction:\n\n");
    while(current != NULL){
        if(current->n_ptr != NULL){
        printf("p[%d] = %p ; p[%d] size = %d\n", i, current->n_ptr, i, (current->size));
        }
        i++;
        current = current->next;
    }

    i = 0;
    current = kallocator.f_head;
    printf("Freed list post compaction:\n\n");
    while(current != NULL){
        if(current->n_ptr != NULL){
        printf("p[%d] = %p ; *p[%d] size = %d\n", i, current->n_ptr, i, (current->size));
        }
        i++;
        current = current->next;
    }
*/
/*
    printf("\n");
    for(int b = 0; b < b_index; b++){
        printf("Pointer stored in before[%d]: %p\n", b, _before[b]);
    }
    printf("\n");

    for (int a = 0; a < a_index; a++)
    {
        printf("Pointer stored in after[%d]: %p\n", a, _after[a]);
    }
    printf("\n");

    assert(b_index = a_index-1);
*/
    compacted_size = a_index;
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
    //available_memory_size = kallocator.size;
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



