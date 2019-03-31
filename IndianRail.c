#include<pthread.h>
#include <stdio.h>
#include<stdlib.h>

struct station {
	//condition variables
	struct condition *confirm_arrival, *confirm_passengers_seated;
	//shared_variables
	int passengers_waiting;
	int seats_empty;
	int passengers_boarding;
	//lock_variable
	pthread_mutex_t l;
};


void station_wait_for_train(struct station *station)
{
	pthread_mutex_lock(station->l);
	
	station.passengers_waiting = (station.passengers_waiting + 1);
	
	
	while (station.seats_empty==station.passengers_boarding)
	{
		//check 1. train arrived 
		//2. lock is acquired
		station.passengers_boarding = (station.passengers_boardiong + 1);
		station.passengers_waiting = (station.passengers_waiting - 1);
		
		pthread_mutex_unlock(station->l);
	}

}



void station_on_board(struct station *station)
{
	pthread_mutex_lock(station->l);
	
	station.passengers_boarding = (station.passengers_boardiong - 1);
	
	station.seats_empty = (station.seats_empty - 1);
	
	
	if ((station.passengers_boardiong  == 0) || (station.seats_empty == 0))
	//check 1. passengers_seated 
	//2. lock 
	
	pthread_mutex_unlock(station->l);
}


int main()
{

printf("Pass\\n");

}
