#include "../../SERVICES/BIT_UTILIES.h"
#include "../../SERVICES/TM4C123.h"
#include "../../SERVICES/STD_TYPES.h"
#include "../../INCLUDE/HAL/SEVEN_SEG.h"
#include "../../INCLUDE/MCAL/GPIO.h"

void GPIO_initPortB() {
SYSCTL_RCGCGPIO_R |= 0x02; 
while ((SYSCTL_PRGPIO_R, & 0x02) == 0);
GPIO_PORTB_CR_R |= 0xFF;
GPIO_PORTB_AMSEL_R &= 0x0; 
GPIO_PORTB_AFSEL_R &= 0x00;	
GPIO_PORTB_PCTL_R &= 0x0; 
GPIO_PORTB_DIR_R |= 0xFF; 
GPIO_PORTB_DEN_R |= 0xFF;
	
void GPIO_PORTB_setPort (unsigned char sevenSegmentValues) {

GPIO_PORTB_DATA_R = sevenSegmentValues;
	
}

unsigned segl, seg2, seg3;
unsigned char seven_segmentArray[10]=(0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x75, 0x27, 0x75, 0x6F); // (0:9)

void setSevenSegment (unsigned char index) {
	
GPIO_PORTB_setPort (seven_segmentArray[index]); 
}



void SplitDistance (double distance) {
int d= (int) distance;

   segl = d % 10;
   d /= 10;

   seg2 = d % 10;
   d /= 10;

   seg3 = d % 10;
	
}
	
void show (int digit, char value) {

   GPIO_PORTB_DATA_R= 0x00; // Turns off LEDs
   GPIO_PORTE_DATA_R= digit; // Selects segment to turn on PE1, PE2, PE3
   GPIO_setSevenSegment (value);


    }


