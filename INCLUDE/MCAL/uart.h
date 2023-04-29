#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
/**********

common macros

***********/

#define SET_BIT(REG,BIT) (REG|=(1<<BIT))    /* Set a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))  /* Clear a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))    /* Toggle a certain bit in any register */
#define GET_BIT(REG,BIT) ( ( REG & (1<<BIT) ) >> BIT )   /* Get bit value */

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





/**************     prototypes     *****************/
void UART0_init(uint16  baudRate);
void UART2_init(uint16  baudRate);

uint8 UART0_recieveByte(void);
uint8 UART2_recieveByte(void);

void UART0_receiveString(uint8 *Str);
void UART2_receiveString(uint8 *Str);

void UART0_sendByte(uint8 data);
void UART2_sendByte(uint8 data);