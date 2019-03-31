# IndianRail
IndianRail has decided to improve its efficiency by automating not just its trains but also its passengers. 
Each passenger and each train is controlled by a thread. 
You have been hired to write synchronization functions that will guarantee orderly loading of trains. 
You must define a structure struct station, plus several functions described below. 
When a train arrives in the station and has opened its doors, it invokes the function station_load_train(struct station *station, int count) where count indicates how many seats are available on the train. 
The function must not return until the train is satisfactorily loaded (all passengers are in their seats, and either the train is full or all waiting passengers have boarded).
When a passenger arrives in a station, it first invokes the function station_wait_for_train(struct station *station) 
This function must not return until a train is in the station (i.e., a call to station_load_train is in progress) and there are enough free seats on the train for this passenger to sit down. Once this function returns, the passenger robot will move the passenger on board the train and into a seat (you do not need to worry about how this mechanism works). Once the passenger is seated, it will call the function station_on_board(struct station *station) to let the train know that it's on board. Create a file IndianRail.c that contains a declaration for struct station and defines the three functions above, plus the function station_init, which will be invoked to initialize the station object when IndianRail boots.

