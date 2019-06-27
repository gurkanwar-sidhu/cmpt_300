//Main application holding factory thread, kid thread, and main() function. Plus some other helper functions, and some #defined constants.

/*
# Factories: Number of candy-factory threads to spawn.
# Kids: Number of kid threads to spawn.
# Seconds: Number of seconds to allow the factory threads to run for.
*/
//check: read Assignment page thoroughly, large assigmet but very focused hints given throughout
//check: message each other before pushing and pulling

typedef struct  {
    int factory_number;
    double time_stamp_in_ms;
} candy_t;

//factory_number: tracks which factory thread produced the candy item
// time_stamp_in_ms: tracks when the item was created. You can get the current number of milliseconds using the following function
//check: must be linked through -lrt flag, What is -lrt flag?


int main(){
	 // 1.  Extract arguments:
			 //Process the arguments passed on the command line. All arguments must be greater than 0. If any argument is 0 or less, display an error and exit the program.
    
    // 2.  Initialize modules:
    		// Do any module initialization. You will have at least two modules: bounded buffer, and statistics. If no initialization is required by your implementation, you may skip this step.
    
    // 3.  Launch candy-factory threads:
    		//Spawn the requested number of candy-factory threads. To each thread, pass it its factory number: 0 to (number of factories - 1).
			//- Hint: Store the thread IDs in an array because you’ll need to join on them later.
			//- Hint: Don’t pass each thread a reference to the same variable because as you change the variable’s value for the next thread, there’s no guaranty the previous thread will have read the previous value yet. You can use an array to have a different variable for each thread

    // 4.  Launch kid threads:
    		// Spawn the requested number of kid threads

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