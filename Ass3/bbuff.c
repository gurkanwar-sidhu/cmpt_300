#ifndef BBUFF_H
#define BBUFF_H

#define BUFFER_SIZE 10

// check : for testing delete these:
#include <stdio.h> 
#include <stdlib.h> 
typedef struct  {
    int factory_number;
    double time_stamp_in_ms;
} candy_t;
//delete these ^^^

void* theBuffer[BUFFER_SIZE]; 
int front;
int size;
void bbuff_init(void){

    front= 0;
    size=0;
}
void bbuff_blocking_insert(void* item){
    
    theBuffer[size] = item;
    size++;
    //print all for testing
    int itr = 0;
    candy_t *candy;
    while(itr != size){
        candy  = theBuffer[itr];
        printf("print %d\n", candy->factory_number );
        itr++;
    }
    printf("insert\n\n");
}
void* bbuff_blocking_extract(void);
_Bool bbuff_is_empty(void);


#endif
