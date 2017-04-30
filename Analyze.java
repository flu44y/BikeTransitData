import java.util.Scanner;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.File;

public class Analyze{

public static void main(String[] args) throws FileNotFoundException {
    Scanner input = new Scanner(new File("bikeDataJava.txt"));
    input.useDelimiter("-|\n");

    int i = 0;
    BikeTrip[] arrayOfTrips = new BikeTrip[0];
    while(input.hasNext()) {
        int duration = input.nextInt();
        int startMonth = input.nextInt();
        int startDay = input.nextInt();
        int startYr = input.nextInt();
        int startHr = input.nextInt();
        int startMin = input.nextInt();
        int endMonth = input.nextInt();
        int endDay = input.nextInt();
        int endYr = input.nextInt();
        int endHr = input.nextInt();
        int endMin = input.nextInt();
        int startStationId = input.nextInt();
        String startStation = input.next();
        int endStationId = input.nextInt();
        String endStation = input.next();
        String bikeId = input.next();
        String memberType = input.next();

        BikeTrip newBikeTrip = new BikeTrip(startStationId, startStation, endStationId, endStation,
		                                 startMonth, startDay, startYr, startHr, startMin, 
		                                 endMonth, endDay, endYr, endHr, endMin,
										 bikeId, memberType, duration);
        arrayOfTrips = BikeTrip.addBikeTrip(arrayOfTrips, newBikeTrip);
    }
    
    //System.out.println( arrayOfTrips[0] );

	//for( i = 0; i < 3; i++){
	   
    //   System.out.println( arrayOfTrips[i] );
	//}

	//arrayOfTrips[0].PrintTrip( arrayOfTrips[0] );

    
    for (BikeTrip bikeTrip : arrayOfTrips) {
        System.out.println(bikeTrip);
    } 
}
}
