#ifndef STATS_H
#define STATS_H

#include <stdbool.h>
// check : for testing delete these:
#include <stdio.h> 
#include <stdlib.h> 


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
typedef struct {
	int num_producers;
    int made;
    int eaten;
    double total_delay;
    double min_delay;
    double max_delay;
} stat_t;

stat_t* stats;

void stats_init(int num_producers){

	stats = malloc(num_producers*(sizeof(stat_t)));
	for(int s = 0; s < num_producers; s++){

	stats[s].num_producers = num_producers;;
	stats[s].min_delay = 1000000;
	stats[s].max_delay = 0;
	 }       // int prod_time_arr : store time produced. only need size 10 because at no point will we need to keep track of produced time of more than 10 candies
}

void stats_cleanup(void){

}

void stats_record_produced(int factory_number){
		
		stats[factory_number].made++;
}

void stats_record_consumed(int factory_number, double delay_in_ms){
	
	stats[factory_number].eaten++;
	
	stats[factory_number].total_delay += delay_in_ms;
	
	if(delay_in_ms < stats[factory_number].min_delay){
		stats[factory_number].min_delay = delay_in_ms;
	}

	if(delay_in_ms > stats[factory_number].max_delay){
		stats[factory_number].max_delay = delay_in_ms;
	}
}

void stats_display(void){

	printf("Statistics:\n");

	printf("%8s%10s%10s%10s%10s%10s\n", "Factory", "#Made", "#Eaten", "Min Delay[ms]", "Average Delay[ms]", "Max Delay[ms]");

	double avg_delay[stats[0].num_producers];

	for(int i = 0; i < stats[0].num_producers; i++){
		avg_delay[i] = (stats[i].total_delay)/(stats[i].made);
	}

	for(int j = 0; j < stats[0].num_producers; j++){
		printf("%8d%10d%10d%10f%10f%10f\n", j, stats[j].made, stats[j].eaten, stats[j].min_delay, avg_delay[j], stats[j].max_delay);
	}
}

#endif