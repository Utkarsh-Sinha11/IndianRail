#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<semaphore.h> 
 
int allPassengerSeated =0; 
int trainArrived = 0; 
int leftover =0;
int seatingcounter = 0;

struct station
{	
	int noOfSeatsLeft;	
	int waitingPassenger;
	int seatedPassenger;
	sem_t lock;	
}S;
  
void station_init()
{
	seatingcounter = 0;
	leftover =0;
	printf("\nEnter the train's Capacity: ");
	scanf("%d",&S.noOfSeatsLeft);
	if(S.noOfSeatsLeft==0)
	{
		printf("Train is already FULL!!!\n");
		exit(0);
	}
	if(S.noOfSeatsLeft<0)
	{
		printf("Seats cannot be negative!!\n");
		exit(0);
	}
	
	
	printf("Enter the No. of Passenger that are willing to board at Station: ");
	scanf("%d",&S.waitingPassenger);
	if(S.waitingPassenger<0)
	{
		printf("Passenger cannot be negative!!\n");
		exit(0);
	}
	if(S.waitingPassenger>S.noOfSeatsLeft)
	{
		leftover = S.waitingPassenger-S.noOfSeatsLeft;
		printf("\n\n%d Passenger will be left at Station.\n\n",leftover);
		S.waitingPassenger=S.noOfSeatsLeft;
				
	}
	
}

void* station_load_train(void *args)
{
	
	printf("Train has arrived at the station and has opened it's doors!!!!!!!!!!!!\n\n ");		
	struct station *p = (struct station *)args;
	trainArrived = 1;
	sleep(10);
	if(p->noOfSeatsLeft<0)
	{
		printf("\nSeats Left: 0\n");	
	}
	if(allPassengerSeated ==1 || p->noOfSeatsLeft==0)
	{
		printf("\nSeats Left: %d\n",p->noOfSeatsLeft);
		printf("\nTrain Has Departed..\n");
	}
	if(leftover>0)
	{
			
		printf("\nLeftover Passengers = %d\n",leftover);
		
	}
	
}

void station_on_board(struct station *st)
{
	seatingcounter++;
	sem_wait(&S.lock);
	allPassengerSeated =0;
	st->noOfSeatsLeft--;
	printf("%d Passenger have seated Successfully\n",seatingcounter);
	allPassengerSeated =1;
	sem_post(&S.lock);
}

void* station_wait_for_train(void *args)
{		
	struct station *p = (struct station *)args;
	if((trainArrived == 1) && (p->noOfSeatsLeft>0))
	{
		station_on_board(p);	
	}
}



int main()
{	
	int i =0,arr=0;
	printf("\t\t\t\t\t\t\t\tIndian Railways is Booting.\n");

	for( i =0 ; i<10;i++)
	{
		printf("..\n");	
		sleep(1);
	}printf("\n\n");
	
	while(1)
	{
	printf("\nTo Exit, PRESS CTRL + C\n");
	station_init();
	
	//creating Train thread and Passenger threads

	pthread_t train, Passenger[allwaiting+1];

    	// initialize the semaphores 
   	 sem_init(&S.lock, 0, 1);
	
  	 pthread_create(&train, NULL, station_load_train, &S);
	 sleep(5);
    	for (i = 0 ;i <allwaiting; i++) 
	{ 
        pthread_create(&Passenger[i], NULL, station_wait_for_train, &S); 
  	printf("Passanger %d is arrived at Station\n", i + 1); 
    	} 
	
	for (i = 0; i < allwaiting; i++)
	{
  
        pthread_join(Passenger[i], NULL);
	
	}
	
	pthread_join(train, NULL);
	
	}	
	return 0;
}
