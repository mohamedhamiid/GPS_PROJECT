#include "../../INCLUDE/HAL/GPS.h"
#include "../../INCLUDE/MCAL/UART.h"
#include "../../SERVICES/TM4C123.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>




char GPS_logHeader[]="$GPRMC,";   

char GPS[80]; //contain the characters which recived from GPS module

char GPS_formated[12][20];  // same of GPS array but devide log to sections (fields)

char * token ; //pointer to point on character of each field 

float currentLong , currentLat , speed ,finalLat=1052.563787 ;

int i;

const double EARTH_RADIUS = 6371000;
const double long_final,lat_final;


/*******************Functions to convert the values of angle********************/

float GPS_converToDeg (float angle){
	
int degree = (int)angle / 100 ;
float minutes = angle - (float)degree*100;
return(degree+ (minutes/60));

}


float GPS_convertToRad(float degValue){

return degValue*PI/180;

}

////////////////////////////////////////////////////////////////////////////////////




//**************************Get distance*****************************************//
//  using Haversine formula: a = sin²(?f/2) + cos f1 · cos f2 · sin²(??/2)       //
//  c = 2 * atan2(sqrt(a), sqrt(1 - a))                                          //
// distance = Earth radius *c                                                    //
//*******************************************************************************//

float GPS_getDistance(float currentLong,float currentLat,float destinationLong,float destinationLat){

	/*Convert each parameter to RAD*/
  float currentLongRad =GPS_convertToRad(GPS_converToDeg(currentLong));
	float currentLatRad =GPS_convertToRad(GPS_converToDeg(currentLat));
	float destinationLongRad =GPS_convertToRad(GPS_converToDeg(destinationLong));
	float destinationLatRad =GPS_convertToRad(GPS_converToDeg(destinationLat));

  /*Get the difference */
	
	float deltaLong=destinationLongRad-currentLongRad;
  float deltaLat=destinationLatRad-currentLatRad;
   
	 float a = pow(sin(deltaLat/2),2)+cos(currentLatRad)*cos(destinationLatRad)*pow(sin(deltaLong/2),2); 
   double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	 return EARTH_RADIUS * c ;


}

/*************to get char's from GPS using UART*********/
void GPS_read (){

  char c0,c1,c2,c3,c4,c5,c6,c7;
	
   c0=UART_getChar();
    if(c0=='$'){
           c1=UART_getChar();
			
        if(c1=='G'){
              c2=UART_getChar();
					
            if(c2=='P'){
                  c3=UART_getChar();
							
                if(c3=='R'){
                      c4=UART_getChar();
									
                    if(c4=='M'){
                          c5=UART_getChar();
											
                        if(c5=='C'){
                              c6=UART_getChar();
													
                            if(c6==','){
                                  c7=UART_getChar();
				  strcpy(GPS, "");
				  i = 0;
       				  while(c7!='*'){
        			  GPS[i]=c7;
        			  c7=UART_getChar();
        			  i++;
																																																																	
		                 }
				}}}}}}}

}





void GPS_format(){

char indexOfTokenStrings = 0 ;
	
	token = strtok(GPS , ",");  //strtok() devide the string to sections 
	do{
		
		strcpy (GPS_formated[indexOfTokenStrings],token);  //strcpy() copy the token to the place you want in array
		token = strtok(NULL , ",");
		indexOfTokenStrings++;
		
	}while(token!=NULL);
	

	if(strcmp(GPS_formated[1],"A")==0){	//Valid
		
		if(strcmp(GPS_formated[3],"N")==0)
			currentLat = atof(GPS_formated[2]); //atof ()  convert string to float
		else
			currentLat = -atof(GPS_formated[2]);
		
		if(strcmp(GPS_formated[5],"E")==0)
			currentLong = atof(GPS_formated[4]);
		else
			currentLong = -atof(GPS_formated[4]);
	}






}



