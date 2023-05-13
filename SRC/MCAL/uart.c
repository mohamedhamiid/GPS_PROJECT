 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Ahmed Gamal Helmy & Zeyad Abdullah
 *
 *******************************************************************************/


#include "..\..\SERVICES\TM4C123.h"
#include "..\..\SERVICES\Bit_Utilies.h"
#include "../../INCLUDE/MCAL/uart.h"



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


/*
 * Description :
 * Functional responsible for Initialize the UART device 
 */
void UART0_init(uint16  baudRate)
{
	SET_BIT(SYSCTL_RCGCUART_R,0); 	                 /*******  set pin 0 to provide clock ***********/
	while((SYSCTL_PRUART_R & 0x00000001) == 0){}
	SET_BIT(SYSCTL_RCGCGPIO_R,0) ;                   /********   Enable and provide a clock to GPIO Port A in Run mode   *********/
	while((SYSCTL_PRGPIO_R & 0x00000001) == 0){}  	 /*******   wait for GPIO getting ready  ********/
		
		//GPIO_PORTA_LOCK_R |= GPIO_LOCK_KEY;    // 2) unlock GPIO Port F
		//GPIO_PORTA_CR_R |= 0xFF;               // allow changes to PF4-0
		
		CLEAR_BIT(UART0_CTL_R,0);                   /******* disable UART to configure baud rate *************/
		UART0_IBRD_R= 104 ;                        /******** integer reg to store integer value of baudrate **/
		UART0_FBRD_R= 11 ;                        /********* float reg to store the fraction of baudrate *****/
		UART0_LCRH_R=0x00000070;                 /********** 8bit, no parity bits,one stop, fifo   ***********/
		UART0_CTL_R |= 0x00000301;   					 /************ enable UART,TX,RX  ******************************/
		
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
	SET_BIT(SYSCTL_RCGCUART_R,2);    							/*************  set pin 2 to provide clock ***********************************/
	SET_BIT(SYSCTL_RCGCGPIO_R,3) ;                /*************  Enable and provide a clock to GPIO Port D in Run mode   *****/
	while((SYSCTL_PRGPIO_R & (0x01<<3)) == 0){}  	/*********** *  wait for GPIO portD getting ready  *************************/
	  GPIO_PORTD_LOCK_R |= GPIO_LOCK_KEY;    // 2) unlock GPIO Port F
		GPIO_PORTD_CR_R |= 0xFF;               // allow changes to PF4-0
		CLEAR_BIT(UART2_CTL_R,0);                /******* disable UART2 to configure baud rate *************/
		UART2_IBRD_R=104;                        /******* integer reg to store integer value of baudrate **/
		UART2_FBRD_R=11 ;                        /******* float reg to store the fraction of baudrate ****/
		UART2_LCRH_R=0x00000070;                 /******* 8bit, no parity bits,one stop, fifo   *********/
		UART2_CTL_R |= 0x00000301;   						 /******* enable UART,TX,RX  ***************************/
		
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





/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */

/**********   function to recieve byte UART0******/
char UART0_recieveByte(void){
	while (     BIT_IS_SET(UART0_FR_R,4)  ){}  /**********  check until RXFE =0  **************/
		return (uint8)UART0_DR_R&0xFF;          /********      return the value    **************/
		
}

/**********   function to recieve byte UART2****/
char UART2_recieveByte(void){
	while (  BIT_IS_SET(UART2_FR_R,4)   ){}  /**********  check until RXFE =0  **************/
		return (uint8)UART2_DR_R&0xFF;        /*********    return the value    **************/
		
}





/*
 * Description :
 * Receive the required string until the stop char symbol through UART from the other UART device.
 */

/**********   function to recieve string UART0***********/
void UART0_receiveString(char *Str , char stopChar)
{

	uint8 i = 0;

	/* Receive the first byte */
	Str[i] =  UART0_recieveByte();
	UART0_sendByte(Str[i]);
	/* Receive the whole string until the stop char */
	while(Str[i] != stopChar)
	{
		i++;
		Str[i] =  UART0_recieveByte();
		if(Str[i]!=',')
		UART0_sendByte(Str[i]);
	}

	/* After receiving the whole string plus the stop char, replace the stop char with '\0' */
	Str[i] = '\0';
}



/**********   function to recieve string UART2***********/
void UART2_receiveString(char *Str , char stopChar)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] =  UART2_recieveByte();

	/* Receive the whole string until the stop char */
	while(Str[i] != stopChar)
	{
		i++;
		Str[i] =  UART2_recieveByte();
	}

	/* After receiving the whole string plus the stop char, replace the stop char with '\0' */
	Str[i] = '\0';
}





/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */

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



/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(char * ptr){
while(*ptr != NULL){
	UART0_sendByte(*ptr);
	ptr++;
}
}
