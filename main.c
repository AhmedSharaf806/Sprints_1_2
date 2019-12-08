/*
 * main.c
 *
 *  Created on: Dec 3, 2019
 *      Author: ahmed
 */

#include "led.h"
#include "gpio.h"
#include "softwareDelay.h"
#include "pushButton.h"
#include "timers.h"

enum state{
    Go,
    Stop,
    Ready
}state;
int main(){

    Led_Init(0);
    Led_Init(1);
    Led_Init(2);

    timer0Init(T0_COMP_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,125,T0_COMP_MODE);

    uint8 i;
    while(1)
	{
	    static uint8 u8_State=Go;
	    switch(u8_State)
	    {
		case Go:
		    Led_Off(1);
		    Led_Off(2);
		    Led_On(0);
		    u8_State=Stop;
		    timer0Delay_ms(1000);
		    break;
		case Stop:
		    Led_On(1);
		    Led_Off(0);
		    Led_Off(2);
		    u8_State=Ready;
		    timer0Delay_ms(1000);
		    break;
		case Ready:
		    Led_On(2);
		    Led_Off(0);
		    Led_Off(1);
		    u8_State=Go;
		    timer0Delay_ms(1000);
		    break;
	    }
	}
}
