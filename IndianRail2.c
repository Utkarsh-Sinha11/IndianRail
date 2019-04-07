#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<semaphore.h> 

int allPassangersSeated =0; 
int trainArrived = 0; 
int leftover =0;
struct station
{	
	int noOfSeatsLeft;
	//int passangersId[noOfSeatsLeft];	
	int waitingPassangers;
	int seatedPassangers;
	sem_t lock;	
}S;
  
void station_init()
{
	printf("Enter the train's Capacity: ");
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
	//printf("\n %d\n",S.noOfSeatsLeft);
	
	printf("Enter the No. of Passangers that are willing to board at Station: ");
	scanf("%d",&S.waitingPassangers);
	if(S.waitingPassangers<0)
	{
		printf("Passangers cannot be negative!!\n");
		exit(0);
	}
	if(S.waitingPassangers>S.noOfSeatsLeft)
	{
		leftover = S.waitingPassangers-S.noOfSeatsLeft;
		printf("%d passangers will be left at Station.\n",leftover);
		S.waitingPassangers=S.noOfSeatsLeft;
				
	}
	//printf("\n %d\n",S.waitingPassangers);	
}

void* station_load_train(void *args)
{
	printf("Train has arrived at the station and has opened it doors!!!!!!!!!!!!\n\n ");		
	struct station *p = (struct station *)args;
	trainArrived = 1;
	sleep(2*p->waitingPassangers);
	if(allPassangersSeated ==1 || p->noOfSeatsLeft==0)
	{
		printf("\nSeats Left: %d\n",p->noOfSeatsLeft);
	}
	
	
}
int seatingcounter = 0;
void station_on_board(struct station *st)
{
	seatingcounter++;
	sem_wait(&S.lock);
	allPassangersSeated =0;
	st->noOfSeatsLeft--;
	printf("%d Passangers have seated Successfully\n",seatingcounter);
	allPassangersSeated =1;
	sem_post(&S.lock);
}

void* station_wait_for_train(void *args)
{
	//printf("Passangers thread function\n\n ");		
	struct station *p = (struct station *)args;
	if((trainArrived == 1) && (S.noOfSeatsLeft>0))
	{
		station_on_board(p);	
	}
}



int main()
{	
 //Pass;

	return 0;
}
