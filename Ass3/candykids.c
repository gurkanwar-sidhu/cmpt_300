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
#include <time.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <semaphore.h>

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

// mutex locks
pthread_mutex_t mutex;

// the semaphores
sem_t full, empty;

//buffer size
int buffer_size = 10;


//int myCount = 0; //testing

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

double current_time_in_ms(void)
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec * 1000.0 + now.tv_nsec/1000000.0;
}

typedef struct  {
    int factory_number;
    double time_stamp_in_ms;
} candy_t;

typedef struct  {
    int factory_number;
	int made;
	int eaten;
	double min_delay;
	double max_delay;

    double time_stamp_in_ms;
} fact_t;

//inserting one candy
void insertCandy(int fact_number) {

    candy_t *candy = malloc(sizeof (candy_t)); //check NEED TO FREE EVERY CANDY THEN ARRAY
    candy->factory_number = fact_number; 
	candy->time_stamp_in_ms = current_time_in_ms();
    bbuff_blocking_insert(candy);
}

int rand_num_factory(){

    srand(time(0));

    int random_number = (rand() % 4);
    random_number++;//check remove this line of code, i didnt like how when it was 0 seconds it printed too much stuff
    return random_number;
}

_Bool stop_thread = false;

void* launch_factory(void* a_fact){
	
	printf("launching factory number %d with thread id  \n",((fact_t*)a_fact)->factory_number);
	int factory_sleep = rand_num_factory();

    while(!stop_thread){
    
		factory_sleep = rand_num_factory();
		
		//acquire empty the lock
		//sem_wait(&empty);
        printf("\tFactory %d with thread id ships candy and waits %ds\n",((fact_t*)a_fact)->factory_number, factory_sleep);
		//acquire the mutex lock
		pthread_mutex_lock(&mutex);
        insertCandy(((fact_t*)a_fact)->factory_number);
		//release mutex lock
		pthread_mutex_unlock(&mutex);

		//signal buffer is not empty
		//sem_post(&full);
		sleep(factory_sleep);
    }
	printf("Candy-factory %d done\n", ((fact_t*)a_fact)->factory_number);

 return 0;
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
	//create mutex lock
	pthread_mutex_init(&mutex, NULL);

	//intialize semaphores
	sem_init(&full, 0,0);

	sem_init(&empty, 0, buffer_size);

    // 3.  Launch candy-factory threads:
    		//Spawn the requested number of candy-factory threads. To each thread, pass it its factory number: 0 to (number of factories - 1).
			//- Hint: Store the thread IDs in an array because you’ll need to join on them later.
			//- Hint: Don’t pass each thread a reference to the same variable because as you change the variable’s value for the next thread, there’s no guaranty the previous thread will have read the previous value yet. You can use an array to have a different variable for each thread

    pthread_t fact_threadID[factories];
	//int *fact_numbers[factories]; 
	fact_t* all_factories[factories];
	
	//printf("the number is %d\n", *(fact_numbers[1]));
    //pthread_t daThreadID;
    for(int i = 0; i < factories; i++){


        //*(fact_numbers[i]) = i;
		fact_t *fact = malloc(sizeof (fact_t)); //check NEED TO FREE EVERY CANDY THEN ARRAY
    	fact->factory_number = i; 
		all_factories[i] = fact;

		printf("fact_num is %d\n", all_factories[i]->factory_number);
		
        pthread_create(&fact_threadID[i], NULL, launch_factory,all_factories[i] );
    
    }

    
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
for(int s = 0; s < seconds; s++){		
		sleep(1);
		printf("Time %ds:\n", s);
	}		

    // 6.  Stop candy-factory threads:
    		//  Indicate to the factory threads that they are to finish, and then call join for each factory thread. See section on candy-factory threads (below) for more.
	stop_thread = true;

    printf("Stopping candy factories...\n");

	printf("factory number %d\n", factories);
	for(int i = 0; i < factories; i++){
		printf("joining\n");
		pthread_join(fact_threadID[i], NULL);
	}
    

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