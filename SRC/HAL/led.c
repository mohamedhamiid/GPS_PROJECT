#include "../../SERVICES/BIT_UTILIES.h"
#include "../../SERVICES/TM4C123.h"
#include "../../INCLUDE/HAL/led.h"

void led_init(){
    SYSCTL_RCGCGPIO_R|=0x20;
    while((SYSCTL_PRGPIO_R & 0x20)==0);
    GPIO_PORTF_LOCK_R=0x4C4F434B;
    GPIO_PORTF_CR_R |=0x0E;
    GPIO_PORTF_AFSEL_R&=~0x0E;
    GPIO_PORTF_AMSEL_R&=~0x0E;
    GPIO_PORTF_DEN_R|=0x0E;
    GPIO_PORTF_PCTL_R&=~0x0000FFF0;
    GPIO_PORTF_DIR_R|=0x0E;
}

void GPIO_setLedValue (unsigned char ledColor,unsigned char ledState) { // two parameters one to select led second to on/off
    switch (ledColor) {
       case GPIO_RED_LED: switch (ledState)

			 {case GPIO_LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R,1); break; //turn red led off	
			   case GPIO_LED_ON: SET_BIT(GPIO_PORTF_DATA_R,1); break; ////turn red led on
			default: break;
      } break;

     case GPIO_BLUE_LED: switch(ledState)

			{case GPIO_LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R,2); break; //turn blue led off
				case GPIO_LED_ON: SET_BIT(GPIO_PORTF_DATA_R,2); break;//turn blue led on
				default: break;
       } break;

			case GPIO_GREEN_LED: switch(ledState)

			{case GPIO_LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R,3); break; //turn green led off
			case GPIO_LED_ON: SET_BIT(GPIO_PORTF_DATA_R,3); break; //turn green led on
			default: break;
		} break;

default: break;
	}
}
