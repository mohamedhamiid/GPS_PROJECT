#include "../../SERVICES/BIT_UTILIES.h"
#include "../../SERVICES/TM4C123.h"
#include "../../SERVICES/STD_TYPES.h"
#include "../../INCLUDE/HAL/LED.h"

void led_init(){
    SYSCTL_RCGCGPIO_R|=0x20;
    while((SYSCTL_PRGPIO_R & 0x20)==0);
    GPIO_PORTF_LOCK_REG=0x4C4F434B;
    GPIO_PORTF_CR_REG|=0x0E;
    GPIO_PORTF_AFSEL_REG&=~0x0E;
    GPIO_PORTF_AMSEL_REG&=~0x0E;
    GPIO_PORTF_DEN_REG|=0x0E;
    GPIO_PORTF_PCTL_REG&=~0x0000FFF0;
    GPIO_PORTF_DIR_REG|=0x0E;
}

void GPIO_setLedValue (unsigned char ledColor,unsigned char ledState) { // two parameters one to select led second to on/off
    switch (ledColor) {
       case GPIO_RED_LED: switch (ledState)

			 {case GPIO_LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R,1); break; 
			   case GPIO_LED_ON: SET_BIT(GPIO_PORTF_DATA_R,1); break;
			default: break;
      } break;

     case GPIO_BLUE_LED: switch(ledState)

			{case GPIO_LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R,2); break; 
				case GPIO_LED_ON: SET_BIT(GPIO_PORTF_DATA_R,2); break;
				default: break:
       } break;

			case GPIO_GREEN_LED: switch(ledState)

			{case GPIO_LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R,3); break; 
			case GPIO_LED_ON: SET_BIT(GPIO_PORTF_DATA_R,3); break; 
			default: break:
		} break;

default: break;
	}
}