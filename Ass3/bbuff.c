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
        printf("toooo big\n");
    }
    else{
        printf("inside buff : inserting in %d\n", (front+size)%10);
        
        theBuffer[(front+size)%10] = item;
        
        size++;
        //print all for testing
        int itr = front;
        int tempSize= 0;
        candy_t *candy= theBuffer[itr];
        if(size!=0){
            if(size==9){ //easier for testing, only print all if buffer is full
                 while(tempSize <size){
                    itr = itr%10;
                    candy  = theBuffer[itr];
                    //printf("tempSize %d and size %d\n", tempSize, size);
                    printf("inside buffer print %d  ", candy->factory_number );
                    
                    
                    itr++;
                    tempSize++;
                }
            }
           
        }
    
 
        
        
    }
    //printf("size is %d\n\n", size);
    //printf("insert\n\n");
}
void* bbuff_blocking_extract(void){
    printf("size is %d\n",size);
    if(size==0){
        printf("nothing to extract\n");
    }
    else{
        candy_t *candy = theBuffer[front];
        front++;
        front = front % 10;
        size--;
        return candy;
    }
    return NULL;
    
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
