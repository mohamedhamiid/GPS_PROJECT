#include "../../INCLUDE/HAL/SEVEN_SEG.h"
#include "../../INCLUDE/HAL/led.h"
#include "../../INCLUDE/HAL/GPS.h"
#include "../../SERVICES/TM4C123.h"
#include "../../INCLUDE/MCAL/uart.h"
#include "../../INCLUDE/MCAL/SysTick.h"
#include "../../SERVICES/Bit_Utilies.h"
#include "../../INCLUDE/MCAL/DIO.h"
#include <float.h>
// Testing
extern char Valid ;
extern char Lat[15];
extern char NorS;
extern char longi[15];
extern char EorW;
extern char speed[15];
//////////////////////////
extern double currentLat ,currentLong ;
double PreviousLong , PrivousLat;

int Distance = 0 , totalDistance =0;

const double x = 30.063468, y = 31.278473;

char flag = 0;

double DistenationDistance=0;

int main(){

	
	led_init();		
	sysTick_Init();
	UART2_init(9600);
	UART0_init(9600);
	GPIO_initPortB();
	GPIO_initPortE();
		

	
	while(1){	
		GPS_read ();
		
		if(flag){
			Distance = GPS_getDistance(currentLong,currentLat,PreviousLong,PrivousLat);
			}
			totalDistance += Distance;
			flag = 1;
			
								
		GPIO_PORTF_DATA_R&=~(0xFFFF);

			
		DistenationDistance =  GPS_getDistance(ToDegree(currentLat),ToDegree(currentLong),x, y); 
		
		
			if(DistenationDistance >10){
			GPIO_setLedValue (GPIO_RED_LED, GPIO_LED_ON);
			}
			 else if(DistenationDistance <=4){
			GPIO_setLedValue (GPIO_GREEN_LED, GPIO_LED_ON);
			}
				 else if ((DistenationDistance <10)&&(DistenationDistance>4)){
			GPIO_setLedValue (GPIO_BLUE_LED, GPIO_LED_ON);
			}

			PreviousLong = currentLong;
			PrivousLat = currentLat;
		}  

}
	
