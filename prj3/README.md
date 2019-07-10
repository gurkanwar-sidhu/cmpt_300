# Assignment 3: Shell with History - CMPT 300

In this project we safely facilitated a simulation of the production and consumption of candies between factories and kids in C using scheduling and mutual exclusion properties. 


## Additional files
   * discussion.txt used to communicate tasks and workload


## Design Decisions & Project Issues:

### 1. Launching candy factories threads

#### Design Decisions:
1. Creating factory threads
    * Use pthreadd_create in loop to create factory threads
    * store id's for joining later

2. Producing Candies
    * Use while loop in function to keep inserting candies in buffer
    * use mutex lock and semaphore for mutual exclusion and scheduling

### 2. Launching kid threads

#### Design Decisions:
1. Creating kid threads
    * Use loop to create kid threads, (pass in function that eats candies)
    * store id's canceling threads later

2. Consuming Candies
    * Use while loop in function to keep consuming candies in buffer
    * use mutex lock and semaphore for mutual exclusion and scheduling

### 3. Stop factories and kids

#### Design Decisions:
1. Wait for requested time
    * use loop with sleep to wait

2. stop candy factories
    * send stop signal by changing boolean value while loop is depending on
    * join on the thread id's
2. stop kids
    * wait until buffer is empty by sleeping until buffer bbuff_is_empty returns true;
    * cancel kid threads by id

### 4. Print statistics

#### Design Decisions:
1. Create array of structs to hold statistics information for each factory
    * each struct holds candies made eaten, total delay for all candies summed, min and max delays
    * update the min max delay if needed whenever candy is consumed

### 5. Clean up

#### Design Decisions:
1. stats array
    * free stats array instead of each struct, because we decided to dynamically allocate all the space needed instead of allocating each struct one at a time

2. freeing factory and candies structs
    * loop through all_factory array and free each factory
    * free candies immediately after "consumed".



### Testing:

	* tested using sampele output files provided by prof

	* using valgrind command provided by prof:
    valgrind --leak-check=full --show-leak-kinds=all --num-callers=20 ./candykids 8 1 1


### Project Issues:
   * Some trouble understanding how to dynamically allocate a global struct array for stats. TA helped us with that. We ended up allocating entire block instead of allocating each individual struct.
   * Not too many issues. Used stack overflow when confused about dynamic memory allocation and pointers.
   * Occasionally confused by sample output files, but clarified on google groups.
   * merge conflicts resolved with some hassle
   * clarity regularly required regarding correct exact error phrase to use in code.

## How to run tests

	* simply issue commands 'make' 
	* then issue command './candykids' followed by the number of factories and kids you would like to run and for how long
	* ex: the following command: './candykids 2 2 5' creates 2 factories 2 kids and runs for 5 seconds.

## Authors

    Sarbjot Singh - sarbjot-14{301313399}

    Gurkanwar Sidhu - gss28{301290044)



