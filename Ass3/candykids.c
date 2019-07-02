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
    double time_made;
    double time_eaten;
} candy_t;

typedef struct  {
    int factory_number;
	int made;
	int eaten;
} fact_t;

/*typedef struct {
    int kid_number;
    double time_eaten;
} kid_t;
*/
typedef struct {
    int num_producers;
    int factory_number;
    double delay;
    double min_delay;
    double max_delay;
    candy_t candy;
    fact_t fact;
} stat_t;
//inserting one candy
void insertCandy(int fact_number) {

    candy_t *candy = malloc(sizeof (candy_t)); //check NEED TO FREE EVERY CANDY THEN ARRAY
    candy->factory_number = fact_number; 
	candy->time_made = current_time_in_ms();
    bbuff_blocking_insert(candy);
}


/*void* rand_num_factory(void* a_fact){

    ((fact_t*)a_fact)->factory_sleep = (rand() % 4);
    printf("factory: %d, random_number: %d \n", ((fact_t*)a_fact)->factory_number, ((fact_t*)a_fact)->factory_sleep);
    ((fact_t*)a_fact)->factory_sleep++;
    sleep(1);
    return 0;
}*/

_Bool stop_thread = false;

void* launch_factory(void* a_fact){
	
	//printf("launching factory number %d with thread id  \n",((fact_t*)a_fact)->factory_number);
	int factory_sleep;

    while(!stop_thread){
    
		factory_sleep = (rand() % 4)+1;
		//acquire empty the lock
		sem_wait(&empty);
        printf("\tFactory %d with thread id ships candy and waits %ds\n",((fact_t*)a_fact)->factory_number, factory_sleep);
		//acquire the mutex lock
		pthread_mutex_lock(&mutex);
        insertCandy(((fact_t*)a_fact)->factory_number);
		a_fact->made++;
        //release mutex lock
		pthread_mutex_unlock(&mutex);

		//signal buffer is not empty
		sem_post(&full);
		sleep(factory_sleep);
    }
	printf("Candy-factory %d done\n", ((fact_t*)a_fact)->factory_number);

 return 0;
}

void eatCandy(){

    if(!bbuff_is_empty()){
     candy_t* candy = bbuff_blocking_extract();
     printf("kid ate candy from factory: %d\n", candy->factory_number);
     candy->time_eaten = current_time_in_ms();
     free(candy);
    }
}

int rand_num_kid(){
    int rand_number = (rand() % 2);
    rand_number++;
 return rand_number;
}

void* launch_kid(void* arg){
    int kid_sleep = rand_num_kid();
    printf("launched kid\n");

    while(true){

        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        eatCandy();
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(kid_sleep);
    }
}

int main(int argc, char *argv[]){
	 
        srand(time(0));

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
	stats_init(factories);

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
    pthread_t kid_ID[kids];

    for(int k = 0; k < kids; k++){

        pthread_create(&kid_ID[k], NULL, launch_kid, &kid_ID[k]);
    }
/*
for every kid
		// Spawn thread
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
    while(!bbuff_is_empty()){

        printf("Waiting for all candy to be consumed\n");

        sleep(1);
    }

    printf("stopping kids from eating...\n");
    // While there is still candy in the bounded buffer (check by calling a method in your bounded buffer module), print “Waiting for all candy to be consumed” and sleep for 1 second.

    // 8.  Stop kid threads:
    		
    for(int p = 0; p < kids; p++){
        printf("cancelling kid: %d\n", p);
    pthread_cancel(kid_ID[p]);
    }

    for(int c = 0; c < kids; c++){
        printf("joining thread for kid: %d\n", c);
        pthread_join(kid_ID[c], NULL);
    }
            //For each kid thread, cancel the thread and then join the thread. For example, if a thread ID is stored in daThreadID, you would run:
			// ```cpp pthread_cancel(daThreadId); pthread_join(daThreadId, NULL); ```
   
    // 9.  Print statistics:
			//Call the statistics module to display the statistics

    // 10. Cleanup any allocated memory:
    		//Free any dynamically allocated memory. You may need to call cleanup functions in your statistics and bounded buffer modules if they need to free any memory
	return 0;		
}