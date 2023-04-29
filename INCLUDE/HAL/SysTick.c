#include "..\..\SERVICES\TM4C123.h"
#include "..\..\SERVICES\Bit_Utilies.h"


void delay_1ms(){
	NVIC_ST_CTRL_R = 0x4 ; // Clock Source
	NVIC_ST_RELOAD_R = 16000-1 ;
	NVIC_ST_CURRENT_R = 0 ;
	SET_BIT(NVIC_ST_CTRL_R,0); // enable
	while(GET_BIT(NVIC_ST_CTRL_R,16)==0);
}

void delay_ms(int value){
	int i ;
	for(i = 0 ; i < value ; i++){
	delay_1ms();
	} 
}
