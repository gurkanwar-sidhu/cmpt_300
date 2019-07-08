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
} fact_t;

//inserting one candy
void insertCandy(int fact_number) {

    candy_t *candy = malloc(sizeof (candy_t)); //check NEED TO FREE EVERY CANDY THEN ARRAY
    candy->factory_number = fact_number; 
	candy->time_made = current_time_in_ms();
    bbuff_blocking_insert(candy);
    stats_record_produced(fact_number);
}


int rand_num_factory(){
    int factory_sleep = (rand() % 4);
 return factory_sleep;
}

_Bool stop_thread = false;

void* launch_factory(void* a_fact){
	
	int factory_sleep;

    while(!stop_thread){
    
		factory_sleep = rand_num_factory();
		//acquire empty the lock
		sem_wait(&empty);
        printf("\tFactory %d ships candy and waits %ds\n", ((fact_t*)a_fact)->factory_number, factory_sleep);
		//acquire the mutex lock
		pthread_mutex_lock(&mutex);
        insertCandy(((fact_t*)a_fact)->factory_number);
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
     candy->time_eaten = current_time_in_ms();
     double delay = candy->time_eaten - candy->time_made;
     stats_record_consumed(candy->factory_number, delay);
     free(candy);
    }
}

int rand_num_kid(){
    int rand_number = (rand() % 2);
 return rand_number;
}

void* launch_kid(void* arg){
    
    while(true){

        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        eatCandy();
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(rand_num_kid());
    }
}

int main(int argc, char *argv[]){
	 
    srand(time(0));//seed the time for random number generator for both kids and factories

// 1.  Extract arguments:
	if(argc < 4){
		printf("Invalid command line.\n");
		exit(0);
	}	

	factories = atoi(argv[1]);//pass in # of factories

    if(factories < 1){
        printf("Error: All arguments must be positive.\n");
        exit(0);
    }

	kids = atoi(argv[2]);//pass in # of kids

    if(kids < 1){
        printf("Error: All arguments must be positive.\n");
        exit(0);
    }

	seconds = atoi(argv[3]);//pass in time(s) to run program concurrently

	if(seconds < 1){
        printf("Error: All arguments must be positive.\n");
        exit(0);
	}

// 2.  Initialize modules:		
    bbuff_init(); 
	
    stats_init(factories);

    //create mutex lock
	pthread_mutex_init(&mutex, NULL);

	//intialize semaphores
	sem_init(&full, 0,0);
	sem_init(&empty, 0, buffer_size);

// 3.  Launch candy-factory threads:
    pthread_t fact_threadID[factories];
	
    fact_t* all_factories[factories];
    	
    for(int i = 0; i < factories; i++){

		fact_t* fact = malloc(sizeof(fact_t)); 
    	fact->factory_number = i; 
		all_factories[i] = fact;
        pthread_create(&fact_threadID[i], NULL, launch_factory, all_factories[i]);
    }
	// 4.  Launch kid threads:
    pthread_t kid_ID[kids];

    for(int k = 0; k < kids; k++){

        pthread_create(&kid_ID[k], NULL, launch_kid, &kid_ID[k]);
    }

// 5.  Wait for requested time:
    for(int s = 0; s < seconds; s++){		
		
        printf("Time %ds:\n", s);
        sleep(1);
	}		

// 6.  Stop candy-factory threads:
	stop_thread = true;

    printf("Stopping candy factories...\n");
    
	for(int i = 0; i < factories; i++){

		pthread_join(fact_threadID[i], NULL);
	}


// 7.  Wait until no more candy:
    while(!bbuff_is_empty()){
        sleep(1);
        printf("Waiting for all candy to be consumed.\n");
    }

// 8.  Stop kid threads:		
    for(int p = 0; p < kids; p++){

        pthread_cancel(kid_ID[p]);
    }

    printf("Stopping kids.\n");

    for(int c = 0; c < kids; c++){

        pthread_join(kid_ID[c], NULL);
    }
   
// 9.  Print statistics:
    stats_display();
    
// 10. Cleanup any allocated memory:

    stats_cleanup();

    for(int y = 0; y < factories; y++){
        free(all_factories[y]);
    }

 return 0;		
}