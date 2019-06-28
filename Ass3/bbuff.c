#ifndef BBUFF_H
#define BBUFF_H

#define BUFFER_SIZE 10
#include <stdbool.h>
// check : for testing delete these:
#include <stdio.h> 
#include <stdlib.h> 

//delete these ^^^

typedef struct  {
    int factory_number;
    double time_stamp_in_ms;
} candy_t;

void* theBuffer[BUFFER_SIZE]; 
int front;
int size;
int tail;
void bbuff_init(void){

    front= 0;
    size=0;
   
}
void bbuff_blocking_insert(void* item){
    if(size == 10){
        printf("toooo big");
    }
    printf("inserting in %d\n", (front+size)%10);
    theBuffer[(front+size)%10] = item;
    
    size++;
    //print all for testing
    int itr = front;
    int tempSize= 0;
    candy_t *candy;
    if(size!=0){
        while(tempSize <size){
        itr = itr%10;
        candy  = theBuffer[itr];
        printf("print %d\n", candy->factory_number );
        
        if(candy->factory_number ==13){
            break;
        }
        itr++;
        tempSize++;
 
        
        }
    }
    
    //printf("insert\n\n");
}
void* bbuff_blocking_extract(void){
    candy_t *candy = theBuffer[front];
    front++;
    front = front % 10;
    size--;
    return candy;
}
_Bool bbuff_is_empty(void){
    if(size ==0){
        return true;
    }
    else{
        return false;
    }
}


#endif
