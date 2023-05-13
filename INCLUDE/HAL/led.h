



#define GPIO_RED_LED 0
#define GPIO_GREEN_LED 1
#define GPIO_BLUE_LED 2


#define GPIO_LED_ON 1
#define GPIO_LED_OFF 0


void led_init();         // led initialization 

void GPIO_setLedValue (unsigned char ledColor, unsigned char ledState);       // to select the led , select its state(on/off)

