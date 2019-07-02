//need to track a number of values for each candy-factory. It is suggested you create a struct
//with all required fields, and then build an array of such structs (one element for each
//candy-factory). The stats_init() function can initialize your data storage and get it ready
//to process produced and consumed events (via the respective functions). The stats_cleanup()
//function is used to free any dynamically allocated memory. This function should be called just
//before main() terminates.
/*
1. Count the number of candies each factory creates. Called from the candy-factory thread.

2. Count the number of candies that were consumed from each factory.

3. For each factory, the min, max, and average delays for how long it took from the moment the
candy was produced (dynamically allocated) until consumed (eaten by the kid). This will be done
by the factory thread calling the stats code when a candy is created, and the kid thread calling
the stats code when an item is consumed.
*/

void stats_init(int num_producers){
    // struct definition
    // intialize the stat struct array here
}
void stats_cleanup(void);
void stats_record_produced(int factory_number);
void stats_record_consumed(int factory_number, double delay_in_ms);
void stats_display(void);