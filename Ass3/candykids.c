//Main application holding factory thread, kid thread, and main() function. Plus some other helper functions, and some #defined constants.
#include <stdio.h> 
#include <stdlib.h>  // for strtol
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/limits.h>
#include <errno.h>
#include <signal.h>

#include "bbuff.h"
#include "stats.h"

		 

/*
# Factories: Number of candy-factory threads to spawn.
# Kids: Number of kid threads to spawn.
# Seconds: Number of seconds to allow the factory threads to run for.
*/
int factories = 0;
int kids = 0;
int seconds = 0;

int myCount = 0; //testing
//factory_number: tracks which factory thread produced the candy item
// time_stamp_in_ms: tracks when the item was created. You can get the current number of milliseconds using the following function
//check: must be linked through -lrt flag, What is -lrt flag?

//function to make printing easyier
//if need to print numbers, first turn into string, 
char sprintString[100]; 
void myPrint(char* buff){
	write(STDOUT_FILENO, buff, strlen(buff));
	write(STDOUT_FILENO, "\n", strlen("\n"));
	sprintString[0] = '\0';
}

typedef struct  {
    int factory_number;
    double time_stamp_in_ms;
} candy_t;

//inserting one candy
void insertCandy() {
    candy_t *candy = malloc(sizeof (candy_t)); //check NEED TO FREE EVERY CANDY THEN ARRAY
    candy->factory_number = myCount; //check fix these two, with actual factory number and time
    candy->time_stamp_in_ms = 55;
    bbuff_blocking_insert(candy);
}

int main(int argc, char *argv[]){
	 // 1.  Extract arguments:
			 //Process the arguments passed on the command line. All arguments must be greater than 0. If any argument is 0 or less, display an error and exit the program.
	if(argc < 4){
		myPrint("missing variables");
		exit(0);
	}		
	factories = atoi(argv[1]);
	kids = atoi(argv[2]);
	seconds = atoi(argv[3]); 
	if(factories <1 || kids <1 || seconds < 1){
		myPrint("variables is less than 0");
		exit(0);
	}
	sprintf(sprintString, "factories: %d, kids: %d, seconds: %d", factories,kids, seconds);
	myPrint(sprintString);

    // 2.  Initialize modules:
    		// Do any module initialization. You will have at least two modules: bounded buffer, and statistics. If no initialization is required by your implementation, you may skip this step.
    bbuff_init(); //check: idk if this is right
    // 3.  Launch candy-factory threads:
    		//Spawn the requested number of candy-factory threads. To each thread, pass it its factory number: 0 to (number of factories - 1).
			//- Hint: Store the thread IDs in an array because you’ll need to join on them later.
			//- Hint: Don’t pass each thread a reference to the same variable because as you change the variable’s value for the next thread, there’s no guaranty the previous thread will have read the previous value yet. You can use an array to have a different variable for each thread
	/* 
	for every factory	
		// Spawn thread
		pthread_id daThreadId;
		pthread_create(&daThreadId, ...)
		//ask call dathread_function(void* arg)???? Inserting the candies
		// Wait
		sleep(...)

		// Tell thread to stop itself, and then wait until it's done.
		stop_thread = true;
		pthread_join(daThreadID, NULL)
*/


	//check: i am not gonna do worry about threads right now. just gonna try to perfect the buffer. inserting deleting
		//add a candies to the buffer
	for(int i =0; i < 10; i++){ //testing...
		myCount++;
		insertCandy();
		/* 
		if(i%3 ==0 && i>0){
			myPrint("extracting");
			candy_t *ret_candy = bbuff_blocking_extract();
			sprintf(sprintString, "returned candy is %d", ret_candy->factory_number);
			myPrint(sprintString);
		}
		*/
	}
	myPrint("extracting");
	candy_t *ret_candy = bbuff_blocking_extract();
	sprintf(sprintString, "returned candy is %d", ret_candy->factory_number);
	myPrint(sprintString);

	myPrint("extracting");
	ret_candy = bbuff_blocking_extract();
	sprintf(sprintString, "returned candy is %d", ret_candy->factory_number);
	myPrint(sprintString);

	myPrint("extracting");
	ret_candy = bbuff_blocking_extract();
	sprintf(sprintString, "returned candy is %d", ret_candy->factory_number);
	myPrint(sprintString);
	myCount++;
	insertCandy();
	myCount++;
	insertCandy();
	

	myCount++;
	insertCandy();
	myCount++;
	insertCandy();
	myCount++;
	insertCandy();


    // 4.  Launch kid threads:
    		// Spawn the requested number of kid threads

/*
for every kid
		// Spawn thread
		pthread_id daThreadId;
		pthread_create(&daThreadId, ...)
		//ask call dathread_function(void* arg)???? Eat candies??
		// Wait
		sleep(...)

		// Tell thread to stop itself, and then wait until it's done.
		stop_thread = true;
		pthread_join(daThreadID, NULL)
		
dathread_function
Loop forever
Extract a candy item from the bounded buffer.
This will block until there is a candy item to extract.
Process the item. Initially you may just want to printf() it to the screen; in the next section, you must add a statistics module that will track what candies have been eaten.
Sleep for either 0 or 1 seconds (randomly selected). The kid threads are canceled from main() using pthread_cancel(). When this occurs, it is likely that the kid thread will be waiting on the semaphore in the bounded buffer. This should not cause problems.
 */
    // 5.  Wait for requested time:
    		// In a loop, call sleep(1). Loop as many times as the “# Seconds” command line argument. Print the number of seconds running each time, such as “Time 3s” after the 3rd sleep. This shows time ticking away as your program executes.

    // 6.  Stop candy-factory threads:
    		//  Indicate to the factory threads that they are to finish, and then call join for each factory thread. See section on candy-factory threads (below) for more.

    // 7.  Wait until no more candy:
    		// While there is still candy in the bounded buffer (check by calling a method in your bounded buffer module), print “Waiting for all candy to be consumed” and sleep for 1 second.

    // 8.  Stop kid threads:
    		//  For each kid thread, cancel the thread and then join the thread. For example, if a thread ID is stored in daThreadID, you would run:
			// ```cpp pthread_cancel(daThreadId); pthread_join(daThreadId, NULL); ```
   
    // 9.  Print statistics:
			//Call the statistics module to display the statistics

    // 10. Cleanup any allocated memory:
    		//Free any dynamically allocated memory. You may need to call cleanup functions in your statistics and bounded buffer modules if they need to free any memory
	return 0;		
}