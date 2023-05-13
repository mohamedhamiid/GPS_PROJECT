/**********************
*	
*	file name : main.c
*
**********************/

/* Includes of other files */

#include "../../INCLUDE/HAL/SEVEN_SEG.h"
#include "../../INCLUDE/HAL/led.h"
#include "../../INCLUDE/HAL/GPS.h"
#include "../../SERVICES/TM4C123.h"
#include "../../INCLUDE/MCAL/uart.h"
#include "../../INCLUDE/MCAL/SysTick.h"
#include "../../SERVICES/Bit_Utilies.h"
#include "../../INCLUDE/MCAL/DIO.h"
#include <float.h>

/************************************/

/* externed variables with GPS file 
that has the values we get from the 
GPS module to calculate Distance*/

extern char Valid ;
extern char Lat[15];
extern char NorS;
extern char longi[15];
extern char EorW;
extern char speed[15];

/************************************/

extern double currentLong ,currentLat ;
double PreviousLong , PrivousLat;

/************************************/

int Distance = 0 , totalDistance =0;  

const double x = 30.063468, y = 31.278473;  // here are the longtitude and the latitude of the desired location we want to go there

char flag = 0;

double DistenationDistance=0;

int main(){

	
	led_init();		// the led initialisation of ports and pins
	UART2_init(9600);  // UART initialisation 
	
	while(1){	

		GPS_read ();   // here we are reading from the GPS module 
		
		if(flag){
			Distance = GPS_getDistance(currentLong,currentLat,PreviousLong,PrivousLat);  // Flag to not start the calculation of Distance if i didn't move 
			}
			totalDistance += Distance;  // the summation of the distance 
			flag = 1;
			
								
		GPIO_PORTF_DATA_R&=~(0xFFFF);  // turn off leds 

		
		
		/* calculate the difference between my location and the final location we want to go */

		DistenationDistance =  GPS_getDistance(ToDegree(currentLat),ToDegree(currentLong),x, y);   
		
		/*the indication leds*/

			if(DistenationDistance >10){
			GPIO_setLedValue (GPIO_RED_LED, GPIO_LED_ON);  // Red Led if we are far from Location
			}
			else if(DistenationDistance <=4){
			GPIO_setLedValue (GPIO_GREEN_LED, GPIO_LED_ON); // Freen Led if we arrived to Location
			}
			else if ((DistenationDistance <10)&&(DistenationDistance>4)){
			GPIO_setLedValue (GPIO_BLUE_LED, GPIO_LED_ON); // Blue Led if we get closer to Location 
			}

			/* to start the next while loop with my current Location */
			PreviousLong = currentLong; 
			PrivousLat = currentLat;
	}  

}
	
