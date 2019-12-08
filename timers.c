/*
 * timers.c
 *
 *  Created on: Dec 7, 2019
 *      Author: ahmed
 */


#include "timers.h"

static uint8 gu8_timer0Prescaler;
static uint8 gu8_timer1Prescaler;


/*===========================Timer0 Control===============================*/
/**
 * Description:
 * @param control
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer0Init(En_timer0Mode_t mode,En_timer0OC_t OC0,En_timer0perscaler_t prescal, uint8 initialValue, uint8 outputCompare, En_timer0Interrupt_t interruptMask){

    TCCR0 = mode | OC0;

    gu8_timer0Prescaler=prescal;

    TCNT0 = initialValue;

    OCR0 = outputCompare;

    TIMSK|=interruptMask;
}

/**
 * Description:
 * @param value
 */
void timer0Set(uint8 value){

    TCNT0 = value;
}

/**
 * Description:
 * @return
 */
uint8 timer0Read(void){

    return TCNT0;
}

/**
 * Description:
 */
void timer0Start(void){

    TCCR0|=gu8_timer0Prescaler;
}

/**
 * Description:
 */
void timer0Stop(void){

    TCCR0|=T0_NO_CLOCK;

}

/**
 * Description:
 * @param delay
 */
void timer0Delay_ms(uint16 delay){

    uint8 u8_timerModeCheck = GET_BIT(TCCR0,BIT3);

    switch(u8_timerModeCheck)
	{

	    case 0: //Normal Mode

		TCCR0 |= T0_PRESCALER_64;

		uint16 u16_OverflowCounterNM=0; //Count number of overflows

		timer0Set(130); //130 to trick only 125 tricks for 1 overflow

		timer0Start();


		for(u16_OverflowCounterNM=0; u16_OverflowCounterNM<delay; u16_OverflowCounterNM++)
		    {
			while(((TIFR)&(1<<0))==0){};
			SET_BIT(TIFR,BIT0);
			timer0Set(130);
		    }
		timer0Stop();
		break;

	    case 1: //Compare Mode

		TCCR0 |= T0_PRESCALER_64;

		uint16 u16_OverflowCounterCM=0; //Count number of overflows

		uint8  u8_flagCheckCM; //Check overflow

		timer0Set(0); //0 to trick for compared value to check

		timer0Start();

		while(u16_OverflowCounterCM != (delay)) //check delay equal overflow
		    {
			u8_flagCheckCM=0;
			u8_flagCheckCM=GET_BIT(TIFR,BIT1); //store status of TOV0 flag

			if(u8_flagCheckCM==1)//check for overflow
			    {
				u16_OverflowCounterCM++; //increase overflow by 1 everytime
				SET_BIT(TIFR,BIT1);
			    }
		    }
		timer0Stop();
		break;
	}
}

/**
 * Description:
 * @param dutyCycle
 */
void timer0SwPWM(uint8 dutyCycle,uint8 freq){


}


/*===========================Timer1 Control===============================*/
/**
 * Description:
 * @param controlA
 * @param controlB
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer1Init(En_timer1Mode_t mode,En_timer1OC_t OC,En_timer1perscaler_t prescal, uint16 initialValue, uint16 outputCompareA, uint16 outputCompareB, uint16 inputCapture, En_timer1Interrupt_t interruptMask){

    TCCR1 = mode | OC;

    gu8_timer1Prescaler=prescal;

    TCNT1 = initialValue;

    OCR1A = outputCompareA;

    OCR1B = outputCompareB;

    ICR1 = inputCapture;

    TIMSK = interruptMask;


}

/**
 * Description:
 * @param value
 */
void timer1Set(uint16 value){

    TCNT1 = value;
}


/**
 * Description:
 * @return
 */
uint16 timer1Read(void){

    return TCNT1;
}



/**
 * Description:
 */
void timer1Start(void){

    TCCR1 |=gu8_timer1Prescaler;
}

/**
 * Description:
 */
void timer1Stop(void){

    TCCR1 = T1_NO_CLOCK;

}

/**
 * Description:
 * @param delay
 */
void timer1Delay_ms(uint16 delay){

		timer1Init(T1_NORMAL_MODE,T1_OC1_DIS,T1_PRESCALER_64,0,0,0,0,T1_POLLING);


    		uint32 u32_OverflowCounterNM=0; //Count number of overflows

    		timer1Set(65410); //65410 to trick only 125 tricks for 1 overflow

    		timer1Start();

		for(u32_OverflowCounterNM=0; u32_OverflowCounterNM<delay; u32_OverflowCounterNM++)
		    {
			while(((TIFR)&(1<<2))==0){};
			SET_BIT(TIFR,BIT2);
			timer1Set(65410);
		    }
    		timer1Stop();

}

/**
 * Description:
 * @param dutyCycle
 */
void timer1SwPWM(uint8 dutyCycle,uint8 freq){


    
}

