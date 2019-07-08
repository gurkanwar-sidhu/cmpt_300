#ifndef STATS_H
#define STATS_H

#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>


typedef struct {
	int num_producers;
    int made;
    int eaten;
    double total_delay;
    double min_delay;
    double max_delay;
} stat_t;

stat_t* stats = 0;

void stats_init(int num_producers){

	stats = (stat_t*)malloc(num_producers*(sizeof(stat_t)));
	
	for(int s = 0; s < num_producers; s++){
		stats[s].made = 0;
		stats[s].eaten = 0;
		stats[s].total_delay = 0;
		stats[s].num_producers = num_producers;;
		stats[s].min_delay = 1000000;
		stats[s].max_delay = 0;
	}    
}

void stats_cleanup(void){
	
	free(&stats[0]);
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

	printf("%8s%10s%10s%15s%15s%15s\n", "Factory", "#Made", "#Eaten", "Min Delay[ms]", "Avg Delay[ms]", "Max Delay[ms]");

	double avg_delay[stats[0].num_producers];

	for(int i = 0; i < stats[0].num_producers; i++){
		avg_delay[i] = (stats[i].total_delay)/(stats[i].made);
	}

	for(int j = 0; j < stats[0].num_producers; j++){

		if(stats[j].made != stats[j].eaten){
			printf("ERROR: Mismatch between number made and eaten->");
		}

		else{
			printf("%8d%10d%10d%15f%15f%15f\n", j, stats[j].made, stats[j].eaten, stats[j].min_delay, avg_delay[j], stats[j].max_delay);
		}
	}
}

#endif