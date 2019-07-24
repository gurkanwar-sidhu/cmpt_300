# Assignment 4: Memory Management- CMPT 300

In this project, I implementED a simple contiguous allocator that supports different allocation techniques that were discussed in class. The allocator used a library that exposes interface to allocate, deallocate and manage memory 


## Design Decisions :

### 1. Initializing contiguous memory allocation:

#### Design Decisions:
1. Calling the initialization function
    * '____size' is the total size of the contiguous block being utilized throughout the project
    * the enum algorithm is deciding which allocation algorithm to use 

2. Enum algorithm(First Fit, Best Fit, Worst Fit):
    * First fit satifies the allocation request in a first come first serve basis as long as size is met
    * Best fit satisfies the allocation request while focusing on mainiting the smallest remainder fragm

### 2. Allocation and Deallocation requests

#### Design Decisions:
1. Kalloc
    * check which algorithm to inact
    * check if any available partitions in contiguous block
    * copy memory from kallocation memory through free list and remove node from free list

2. Kfree
    * check if any partitions from prior kalloc
    * copy contents of pointer to new node
    * delete corresponding allocated node
    * merge any adjacent free chunks in kallocation memory

### 3. Contiguous allocation fragmentation

#### Design Decisions:
1. Storing information in before array
    * loop through allocation list

2. shifting free memory to back
    * shift full free nodes to back whilst moving allocated nodes to front
    * shift allocated memory within the allocated nodes
3. store information in after array
    * same as before array
    * print after array index size

### 4. Information about the current state of memory
    
    *Prints statistics about the contiguous block

### Testing:
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./kallocation

### Project Issues:

    * Difficulty following memory address between two linked list
    *initialization for best and worst fit was rudimentery with priorpartitions but more difficult with contiguous block

## How to run:

    $ make
    $./kallocation

## Author

    Gurkanwar Sidhu - gss28{301290044)


