 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Ahmed Gamal Helmy & Zeyad Abdullah Sayed
 *
 *******************************************************************************/

#include "../../SERVICES/TM4C123.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
/**********

common macros

***********/


#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))  /* Clear a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))    /* Toggle a certain bit in any register */

#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )   /* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )  /* Check if a specific bit is cleared in any register and return true if yes */

#define BAUD_RATE 9600
#define CLOCK_RATE 16000000   /***********  16000000UL ********/ 


/******************   data types   ***************/
typedef unsigned char         uint8;          
typedef signed char           sint8;         
typedef unsigned short        uint16;         
typedef signed short          sint16;         
typedef unsigned long         uint32;        
typedef signed long           sint32;      
typedef unsigned long long    uint64;         
typedef signed long long      sint64;        
typedef float                 float32;
typedef double                float64;





/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
 
 /*
 * Description :
 * Functional responsible for Initialize the UART device 
 */
void UART0_init(uint16  baudRate);
void UART2_init(uint16  baudRate);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
char UART0_recieveByte(void);
char UART2_recieveByte(void);


/*
 * Description :
 * Receive the required string until the stop char symbol through UART from the other UART device.
 */
void UART0_receiveString(char *Str , char stopChar);
void UART2_receiveString(char *Str , char stopChar);


/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART0_sendByte(uint8 data);
void UART2_sendByte(uint8 data);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(char * ptr);
