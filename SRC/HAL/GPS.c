#include "../../INCLUDE/HAL/GPS.h"
#include "../../INCLUDE/MCAL/uart.h"
#include "../../SERVICES/TM4C123.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

/********** Globlal variables to store the needed values from GPS **************/
char Valid ;
char Lat[15];
char NorS;
char longi[15];
char EorW;
char speed[15];
/***************** The log header that we want to recieve **********************/
char GPS_logName[]="$GPRMC,";  
/******** Globlal variables to store the needed values from GPS ****************/
/********************** after converting to Double *****************************/
double currentLat=0 ,currentLong=0 ;

char recievedChar ;
char counter = 0 ;

/**************** Calculate Distance Functions ********************/

//  function to Convert GPS values to Degree
double ToDegree(double value) {
    double result=0;
    int degree = (int)value / 100;
    double minutes = value-(double)degree*100;
    result = degree+ (minutes/60);

    return result;


}

//  function to Convert Degree to Rad
double degToRad(double degree) {
    return degree * (PI / 180.0);
}


// function to calculate distance between two locations using longitude and latitude in Radians
double GPS_getDistance(double currentLat,double currentLong,double previousLat,double previousLong){
    double lat1 = degToRad(currentLat);
    double long1 = degToRad(currentLong);
    double lat2 = degToRad(previousLat);
    double long2 = degToRad(previousLong);
    double latdiff = lat2 - lat1;
    double longdiff = long2 - long1;

    double a= pow(sin(latdiff/2),2)+cos(lat1)*cos(lat2)*pow(sin(longdiff/2),2); // Haversine formula: a = sin²(Δφ/2) + cos φ1 ⋅ cos φ2 ⋅ sin²(Δλ/2)
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return 6371000*c;   //in meters
}
/****************************************************************************/

/******************************** GPS_read **********************************/
/* @breif It read the logs from GPS module, then it check log names till it */
/* find the correct one, then it store the needed info from the log :       */
/* latitude , longitude , north or south , east or west and speed           */
/* this done by counter tracing the ',' character and based on counter we   */
/* we choose what to store. Storing is done in global variables             */
/* @parameters void                                                         */
/* @return     void                                                         */
/****************************************************************************/
void GPS_read (){
	
	char counter=0;
 	char recievedChar ;
	char i = 0 ;
	char flag = 1;
	
	do{
		
		while(UART2_recieveByte()!=GPS_logName[i]){i=0;}
		i++;
	}while(i!=7);
	// Here I make sure that I recieved the correct log
	

	while(1){
					if(flag){
		recievedChar = UART2_recieveByte();
				if(recievedChar==',')
					{
						counter++;
					}
				}
					switch(counter){
						
						case 1 : Valid = UART2_recieveByte();break;
						case 2 : UART2_receiveString( Lat , ',');counter++;flag=0;break;
						case 3 : NorS = UART2_recieveByte();flag=1;break;
						case 4 : UART2_receiveString( longi , ',');counter++;flag=0;break;
						case 5 : EorW = UART2_recieveByte();flag=1;break;
						case 6 : UART2_receiveString( speed , ',');counter++;flag=0;break;

						}
					if(counter==7) break;
	}
	
	if(Valid=='A'){	//Valid
		
			currentLat = atof(Lat); // atof ()  convert character array to double
	
			currentLong = atof(longi);
}

}
