/*                                                            */
/*  This program reads BikeTrip information from a data      */
/*  file into an array and then prints the array              */

#include <stdio.h>
#define FILE_IN "bikeData5000.txt"
#define FILE_OUT "output.txt"

/*  Define structure to represent a BikeTrip  */
typedef struct BikeTrip_struct{
   char membershipType[10];
   int startStationId, endStationId, bikeId,
       duration, startHr, startMin;
}BikeTrip;
//function declarations
void PrintBikeTrip(BikeTrip trip1);
void PrintArray(BikeTrip tripArray[], int arraySize);
void FindMaxDuration(BikeTrip arrayIn[], int arraySize);
int FindMinStartStationId(BikeTrip arrayIn[], int arraySize);
int FindMaxStartStationId(BikeTrip arrayIn[], int arraySize);
int FindCircularTrips(BikeTrip arrayIn[], int arraySize);
int Find0to9MinTrips(BikeTrip arrayIn[], int arraySize);
int FindTripsBikeId(BikeTrip arrayIn[], int arraySize, int bike);
int FindTripsStartStationId(BikeTrip arrayIn[], int arraySize, int station);
int FindTripsEndStationId(BikeTrip arrayIn[], int arraySize, int station);
int TripsInTimeInterval(BikeTrip arrayIn[], int arraySize, int lowDuration, int highDuration);
int FindMinBikeId(BikeTrip arrayIn[], int arraySize);
int FindMaxBikeId(BikeTrip arrayIn[], int arraySize);
int FindMaxHr(BikeTrip arrayIn[], int arraySize);
int FindMinHr(BikeTrip arrayIn[], int arraySize);
int TripsInHr(BikeTrip arrayIn[], int arraySize, int hour);
int TripsInStationPair(BikeTrip arrayIn[], int arraySize, int startStation, int endStation);

//main
int main(void)
{
   /*  Declare variables */
   int k=0, i=0, elements;
   BikeTrip tripArray[5010];

   /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
   // Students do not need to edit sections that 
   // create the input and output file streams
   FILE *inputFileStream, *outputFileStream;
   /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
   //  Open the input file stream to scan data into the array 
   inputFileStream = fopen(FILE_IN,"r");
   if (inputFileStream == NULL){
       printf("Error opening data file. \n");}
   else{
	  while (fscanf(inputFileStream, "%s %d %d %d %d %d %d",
		    tripArray[k].membershipType,&tripArray[k].startStationId,
			&tripArray[k].endStationId, &tripArray[k].bikeId, &tripArray[k].duration,
			&tripArray[k].startHr, &tripArray[k].startMin) == 7){k++;}
	  elements = k;
	}
   fclose(inputFileStream);
   /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
   //  Open the output file stream to write to output.txt        
   outputFileStream = fopen(FILE_OUT,"w");
   if (outputFileStream == NULL){
       printf("Error opening data file. \n");}
   /*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
   
   FindMaxDuration( tripArray, elements);
   int numCircularTrips = FindCircularTrips( tripArray, elements);
   int minStation = FindMinStartStationId( tripArray, elements);
   int maxStation = FindMaxStartStationId( tripArray, elements);
   int trips0to9Mins = Find0to9MinTrips(tripArray, elements);
   int trips0_9 = TripsInTimeInterval( tripArray, elements, 0, 540000);
   int minBikeId = FindMinBikeId( tripArray, elements );
   int maxBikeId = FindMaxBikeId( tripArray, elements );
   int tripsBike116 = FindTripsBikeId( tripArray, elements, 116);
   int maxStartHr = FindMaxHr( tripArray, elements );
   int minStartHr = FindMinHr( tripArray, elements );
   int tripsInHr17 = TripsInHr( tripArray, elements, 17);

   for( i = 0; i < elements; i++){
      if( FindTripsEndStationId(tripArray, elements, tripArray[i].endStationId) > 70 ){
         fprintf(outputFileStream, "endStationId = %d, trips = %d\n", tripArray[i].endStationId,
	             FindTripsEndStationId(tripArray, elements, tripArray[i].endStationId) );
      }
   }

   for( i = 0; i < elements; i++){
      if( FindTripsStartStationId(tripArray, elements, tripArray[i].startStationId) > 70 ){
         fprintf(outputFileStream, "startStationId = %d, trips = %d\n", tripArray[i].startStationId,
	             FindTripsStartStationId(tripArray, elements, tripArray[i].startStationId) );
      }
   }

   for( i = 0; i < elements; i++){
      if( FindTripsBikeId(tripArray, elements, tripArray[i].bikeId) == 12 ){
         fprintf(outputFileStream, "bikeId = %d, trips = %d\n", tripArray[i].bikeId,
	             FindTripsBikeId(tripArray, elements, tripArray[i].bikeId) );
      }
   }

   for( i = 0; i < 24; i++){
      fprintf(outputFileStream, " startHr = %d, trips = %d\n", i, TripsInHr(tripArray, elements, i) );
   }

   fprintf(outputFileStream, "From station %d to station %d, trips = %d\n", 31200, 31201, 
	             TripsInStationPair(tripArray, elements, 31200, 31201) );


   fprintf(outputFileStream, "\n tripsBike116 = %d\n", tripsBike116);
   fprintf(outputFileStream, "\n tripsinHr17 = %d\n", tripsInHr17);
   fprintf(outputFileStream, "\n minStartHr = %d, maxStartHr = %d\n", minStartHr, maxStartHr);
   fprintf(outputFileStream, "\n minStartHr = %d, maxStartHr = %d\n", minStartHr, maxStartHr);
   fprintf(outputFileStream, "\n minBikeId = %d, maxBikeId = %d\n", minBikeId, maxBikeId);
   fprintf(outputFileStream, "\n trips0_9 = %d\n", trips0_9);
   fprintf(outputFileStream, "\n trips0to9Mins = %d\n", trips0to9Mins);
   fprintf(outputFileStream, "\n numCircularTrips = %d\n", numCircularTrips);
   fprintf(outputFileStream, "\n minStation = %d, maxStation = %d\n", minStation, maxStation);
   //PrintArray( tripArray, elements );

   return 0;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the count of trips between 2 stations
int TripsInStationPair(BikeTrip arrayIn[], int arraySize,
                          int startStation, int endStation){
   int k;
   int count = 0;
   for (k = 0; k < arraySize; k++ ){
      if( (arrayIn[k].startStationId == startStation) &&
	      (arrayIn[k].endStationId == endStation) ){
         count++;
	  }
   }
   //printf("count of trips for bikeId %d: %d", bike, count);
   return count;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the count of trips for an endStationId 
int FindTripsEndStationId(BikeTrip arrayIn[], int arraySize, int station){
   int k;
   int count = 0;
   for (k = 0; k < arraySize; k++ ){
      if( arrayIn[k].endStationId == station ){
         count++;
	  }
   }
   //printf("count of trips for bikeId %d: %d", bike, count);
   return count;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the count of trips for a startStationId 
int FindTripsStartStationId(BikeTrip arrayIn[], int arraySize, int station){
   int k;
   int count = 0;
   for (k = 0; k < arraySize; k++ ){
      if( arrayIn[k].startStationId == station ){
         count++;
	  }
   }
   //printf("count of trips for bikeId %d: %d", bike, count);
   return count;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the count of trips for a bikeId
int FindTripsBikeId(BikeTrip arrayIn[], int arraySize, int bike){
   int k;
   int count = 0;
   for (k = 0; k < arraySize; k++ ){
      if( arrayIn[k].bikeId == bike ){
         count++;
	  }
   }
   //printf("count of trips for bikeId %d: %d", bike, count);
   return count;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the count of trips started for an hour 
int TripsInHr(BikeTrip arrayIn[], int arraySize, int hour){
   int k;
   int count = 0;
   for (k = 0; k < arraySize; k++ ){
      if( arrayIn[k].startHr == hour ){
         count++;
	  }
   }
   //printf("count of trips start in hour %d: %d", hour, count);
   return count;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the count of trips in a duration interval
int TripsInTimeInterval(BikeTrip arrayIn[], int arraySize, int lowDuration, int highDuration){
   int k;
   int count = 0;
   printf("\n");
   for (k = 0; k < arraySize; k++ ){
      if( (arrayIn[k].duration >= lowDuration ) && (arrayIn[k].duration <= highDuration ) ){
         count++;
         //PrintBikeTrip(arrayIn[k]);
	  }
   }
   printf("time interval: %d to %d count: %d", lowDuration, highDuration, count);
   return count;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the count of trips 0 to 9 minutes
int Find0to9MinTrips(BikeTrip arrayIn[], int arraySize){
   int k;
   int count0to9Mins = 0;
   printf("\n");
   for (k = 0; k < arraySize; k++ ){
      if( (arrayIn[k].duration >= 0 ) && (arrayIn[k].duration <= 540000 ) ){
         count0to9Mins++;
         PrintBikeTrip(arrayIn[k]);
	  }
   }
   return count0to9Mins;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the count of 1 degree trips
//  when a bike was returned to the same station it came from
int FindCircularTrips(BikeTrip arrayIn[], int arraySize){
   int k;
   int count = 0;
   printf("\n");
   for (k = 0; k < arraySize; k++ ){
      if( arrayIn[k].startStationId == arrayIn[k].endStationId ){
         count++;
         //PrintBikeTrip(arrayIn[k]);
	  }
   }
   return count;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the max startHr 
int FindMaxHr(BikeTrip arrayIn[], int arraySize){
   int k;
   int maxHr = arrayIn[0].startHr;
   printf("\n");
   for (k = 1; k < arraySize; k++ ){
      if( arrayIn[k].startHr > maxHr){
	     maxHr = arrayIn[k].startHr;
         PrintBikeTrip(arrayIn[k]);
	  }
   }
   return maxHr;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the min startHr 
int FindMinHr(BikeTrip arrayIn[], int arraySize){
   int k;
   int minHr = arrayIn[0].startHr;
   printf("\n");
   for (k = 1; k < arraySize; k++ ){
      if( arrayIn[k].startHr < minHr){
	     minHr = arrayIn[k].startHr;
         PrintBikeTrip(arrayIn[k]);
	  }
   }
   return minHr;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the max bikeId 
int FindMaxBikeId(BikeTrip arrayIn[], int arraySize){
   int k;
   int maxBikeId = arrayIn[0].bikeId;
   printf("\n");
   for (k = 1; k < arraySize; k++ ){
      if( arrayIn[k].bikeId > maxBikeId){
	     maxBikeId = arrayIn[k].bikeId;
         PrintBikeTrip(arrayIn[k]);
	  }
   }
   return maxBikeId;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the min bikeId 
int FindMinBikeId(BikeTrip arrayIn[], int arraySize){
   int k;
   int minBikeId = arrayIn[0].bikeId;
   printf("\n");
   for (k = 1; k < arraySize; k++ ){
      if( arrayIn[k].bikeId < minBikeId){
	     minBikeId = arrayIn[k].bikeId;
         PrintBikeTrip(arrayIn[k]);
	  }
   }
   return minBikeId;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the min startStationId 
int FindMinStartStationId(BikeTrip arrayIn[], int arraySize){
   int k;
   int minStartStationId = arrayIn[0].startStationId;
   printf("\n");
   for (k = 1; k < arraySize; k++ ){
      if( arrayIn[k].startStationId < minStartStationId){
	     minStartStationId = arrayIn[k].startStationId;
         PrintBikeTrip(arrayIn[k]);
	  }
   }
   return minStartStationId;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function returns the max startStationId 
int FindMaxStartStationId(BikeTrip arrayIn[], int arraySize){
   int k;
   int maxStartStationId = arrayIn[0].startStationId;
   printf("\n");
   for (k = 1; k < arraySize; k++ ){
      if( arrayIn[k].startStationId > maxStartStationId){
	     maxStartStationId = arrayIn[k].startStationId;
         PrintBikeTrip(arrayIn[k]);
	  }
   }
   return maxStartStationId;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function prints the longest trip
void FindMaxDuration(BikeTrip arrayIn[], int arraySize){
   int maxDuration = 0;
   int k;
   maxDuration = arrayIn[0].duration;
   for (k = 1; k < arraySize; k++ ){
      if( arrayIn[k].duration > maxDuration){
	     maxDuration = arrayIn[k].duration;
         PrintBikeTrip(arrayIn[k]);
	  }
   }
   return;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
//  This function prints the array
void PrintArray(BikeTrip tripArray[], int arraySize){
   printf("bikeId membershipType startStationId endStationId startHr startMin duration(ms) minutes \n"); 
   int k;
   for (k = 0; k < arraySize; k++ ){
      PrintBikeTrip(tripArray[k]);
   }
   return;
}

/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/
/*  This function prints one BikeTrip struct           */

void PrintBikeTrip(BikeTrip t){

   printf("%6d %11s %15d %12d %7d %8d %10d %6d\n",
            t.bikeId, t.membershipType,t.startStationId,t.endStationId, 
			t.startHr, t.startMin, t.duration, t.duration/1000/60);
   return;
}
/*––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/


