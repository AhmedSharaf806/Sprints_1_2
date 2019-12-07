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

int main(){

    Led_Init(1);
    Led_Init(2);
    Led_Init(3);

    while(1)
	{
	    Led_On(1);
	    SwDelay_ms(1000);
	    Led_On(3);
	    Led_Off(1);
	    SwDelay_ms(1000);
	    Led_On(2);
	    SwDelay_ms(1000);
	    Led_Off(2);
	    Led_Off(3);
	}
}
