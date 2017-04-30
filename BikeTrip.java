import java.util.Scanner;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.File;

public class BikeTrip{

    private String bikeId;
    private String memberType;
    private String startStation;
    private String endStation;
    private int startMonth;
    private int startDay;
    private int startYr;
    private int startHr;
    private int startMin;
    private int endMonth;
    private int endDay;
    private int endYr;
    private int endHr;
    private int endMin;
    private int startStationId;
    private int endStationId;
    private int duration;

    // constructor
    public BikeTrip(int sstnid, String sstn, int estnid, String estn,
	               int smonth, int sDay, int sYr, int sHr, int sMin,
	               int emonth, int eDay, int eYr, int eHr, int eMin,
				   String bid, String mtyp, int dur) {
        startStationId = sstnid;
        startStation = sstn;
        endStationId = estnid;
        endStation = estn;
        endMonth = emonth;
        endDay = eDay;
        endYr = eYr;
        endHr = eHr;
        endMin = eMin;
        startMonth = smonth;
        startDay = sDay;
        startYr = sYr;
        startHr = sHr;
        startMin = sMin;
		bikeId = bid;
		memberType = mtyp;
        duration = dur;
    }

    //method to add a trip to the array BikeTrip[]
    public static BikeTrip[] addBikeTrip(BikeTrip[] arrayTripsIn, BikeTrip bikeTripToAdd) {
       BikeTrip[] newBikeTrips = new BikeTrip[arrayTripsIn.length + 1];
       System.arraycopy(arrayTripsIn, 0, newBikeTrips, 0, arrayTripsIn.length);
       newBikeTrips[newBikeTrips.length - 1] = bikeTripToAdd;

       return newBikeTrips;
	}

    // method to print one BikeTrip
	public static void PrintTrip(BikeTrip tripIn){
	   System.out.println( tripIn );
	}


	// print functionality
    @Override
	public String toString() {
	    return String.format("Start Date %2d/%2d/%d  Time %2d:%2d\r\n  End Date %2d/%2d/%d  Time %2d:%2d\r\nStart Station Id %d  %s\r\n  End Station Id %d  %s\r\nBike Id %s Membership %s\r\nDuration(ms) %d (minutes) %2.2f\r\n",
	    startMonth, startDay, startYr, startHr, startMin,
	    endMonth, endDay, endYr, endHr, endMin,
		startStationId, startStation, endStationId, endStation, bikeId, memberType, duration, (float)duration/1000/60);
    }
}
