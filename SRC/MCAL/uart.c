#include "uart.h"


void UART0_init(uint16  baudRate)
{
	double x=CLOCK_RATE/(16.0*baudRate);  /************  configure BD RATE  ********************/
	SET_BIT(SYSCTL_RCGCUART_R,0);    							/*************  set pin 0 to provide clock ***********/
	SET_BIT(SYSCTL_RCGCGPIO_R,0) ;                /**************   Enable and provide a clock to GPIO Port A in Run mode   ***************/
	while((SYSCTL_PRGPIO_R & 0x00000001) == 0){}  	   /***********   wait for GPIO getting ready  *************/
	CLEAR_BIT(UART0_CTL_R,0);                     /******* disable UART to configure baud rate ***********/
		UART0_IBRD_R=(int)x;                        /******integer reg to store integer value of baudrate **********/
		UART0_FBRD_R=(int) ((x-UART0_IBRD_R)*64+0.5 );   /*********** float reg to store the fraction of baudrate **********/
		UART0_LCRH_R=0x00000070;                       /***********       8bit, no parity bits,one stop, fifo   *********/
		UART0_CTL_R |= 0x00000301;   										 /*************** enable UART,TX,RX  *************/
		
		/*********   digital enable  **************/
		SET_BIT(GPIO_PORTA_DEN_R,0);
		SET_BIT(GPIO_PORTA_DEN_R,1);
		
		/**********     enable digital pins     ***********/
		SET_BIT(GPIO_PORTA_AFSEL_R,0);
		SET_BIT(GPIO_PORTA_AFSEL_R,1);
		/*************     disable analog   ***********/
		CLEAR_BIT(GPIO_PORTA_AMSEL_R,0);
		CLEAR_BIT(GPIO_PORTA_AMSEL_R,1);
		
		
		/**********  PCTL    *********************/
		GPIO_PORTA_PCTL_R |= 0x00000011;
}




/********************    UART2 *********************/
/********************  RX---->PD6  ********   TX-------->PD7  **************************/
void UART2_init(uint16  baudRate)
{
	double x=CLOCK_RATE/(16.0*baudRate);  /************  configure BD RATE  ********************/
	SET_BIT(SYSCTL_RCGCUART_R,2);    							/*************  set pin 2 to provide clock ***********/
	SET_BIT(SYSCTL_RCGCGPIO_R,3) ;                /**************   Enable and provide a clock to GPIO Port D in Run mode   ***************/
	while((SYSCTL_PRGPIO_R & (0x01<<3)) == 0){}  	   /***********   wait for GPIO portD getting ready  *************/
	CLEAR_BIT(UART2_CTL_R,0);                     /******* disable UART2 to configure baud rate ***********/
		UART2_IBRD_R=(int)x;                        /******integer reg to store integer value of baudrate **********/
		UART2_FBRD_R=(int) ((x-UART0_IBRD_R)*64+0.5 ) ;   /*********** float reg to store the fraction of baudrate **********/
		UART2_LCRH_R=0x00000070;                       /***********       8bit, no parity bits,one stop, fifo   *********/
		UART2_CTL_R |= 0x00000301;   										 /*************** enable UART,TX,RX  *************/
		
		/*********   digital enable  **************/
		SET_BIT(GPIO_PORTD_DEN_R,6);
		SET_BIT(GPIO_PORTD_DEN_R,7);
		
		/**********     enable digital pins     ***********/
		SET_BIT(GPIO_PORTD_AFSEL_R,6);
		SET_BIT(GPIO_PORTD_AFSEL_R,7);
		/*************     disable analog   ***********/
		CLEAR_BIT(GPIO_PORTD_AMSEL_R,6);
		CLEAR_BIT(GPIO_PORTD_AMSEL_R,7);
		
		/**********  PCTL    *********************/
		GPIO_PORTD_PCTL_R |= 0x11000000;
}







/**********   function to recieve byte UART0******/
uint8 UART0_recieveByte(void){
	while (     BIT_IS_SET(UART0_FR_R,4)  ){}  /**********  check until RXFE =0  **************/
		return (uint8)UART0_DR_R&0xFF;   /********      return the value    ****************/
		
}

/**********   function to recieve byte UART2****/
uint8 UART2_recieveByte(void){
	while (  BIT_IS_SET(UART2_FR_R,4)   ){}  /**********  check until RXFE =0  **************/
		return (uint8)UART2_DR_R&0xFF;   /********      return the value    ****************/
		
}






/**********   function to recieve string UART0***********/
void UART0_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] =  UART0_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] =  UART0_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}



/**********   function to recieve string UART2***********/
void UART2_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] =  UART2_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] =  UART2_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}


/**********   function to send byte UART0****/

void UART0_sendByte(uint8 data)
{
	while(BIT_IS_SET(UART0_FR_R,5));	/**********  check until TXFF =0  **************/
	UART0_DR_R=data;
}
/**********   function to send byte UART2****/

void UART2_sendByte(uint8 data)
{
	while(BIT_IS_SET(UART2_FR_R,5));	/**********  check until TXFF =0  **************/
	UART2_DR_R=data;
}