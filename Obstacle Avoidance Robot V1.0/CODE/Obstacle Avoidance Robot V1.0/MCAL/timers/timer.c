﻿
#include "timer.h"
#include <math.h>
/*********************************************************************************************************
                                       global variables
*********************************************************************************************************/
 // used in TIME_0_DELAY_MS
static double g_ovfNum  ; 
static double g_time ;


/******************************************************************************************************/
//										 TIMER 0
/**************************************************************************************************/

 static void (*Timer0_OVF_Fptr) (void)=NULLPTR;

/**DESCRIPTION:-
 this function enbles a certain timer mode
 **/

Timer_ErrorStatus TIMER_0_init(){
	Timer_ErrorStatus errorStatus = TIMER_OK;
	
	switch(Timer_cfgArray[TIMER_0].mode){
		
		case NORMAL_MODE :
		clear_bit(TCCR0,WGM00);
		clear_bit(TCCR0,WGM01);
		break;
		
		case PWM_PHASE_CORRECT :
		set_bit(TCCR0,WGM00);
		clear_bit(TCCR0,WGM01);
		break;
		
		case CTC :
		clear_bit(TCCR0,WGM00);
		set_bit(TCCR0,WGM01);
		break;
		
		
		case FAST_PWM :
		set_bit(TCCR0,WGM00);
		set_bit(TCCR0,WGM01);
		break;
		
		default:
		errorStatus = INVALID_MODE ;
		break;
	}
	
	
	return errorStatus;
	
	
}
/*************************************************************************************************************/
/**DESCRIPTION:-
 this function enbles a certain timer prescaler
 **/

Timer_ErrorStatus TIMER_0_start(){
	Timer_ErrorStatus errorStatus = TIMER_OK;
	
	switch(Timer_cfgArray[TIMER_0].prescaler){
		
		case PRECALER_1 :
		set_bit(TCCR0,CS00);
		clear_bit(TCCR0,CS01);
		clear_bit(TCCR0,CS02);
		break;
		
		case PRECALER_8 :
		set_bit(TCCR0,CS01);
		clear_bit(TCCR0,CS00);
		clear_bit(TCCR0,CS02);
		break;
		
		case PRECALER_64 :
		set_bit(TCCR0,CS00);
		set_bit(TCCR0,CS01);
		clear_bit(TCCR0,CS02);
		break;
		
		case PRECALER_256 :
		set_bit(TCCR0,CS02);
		clear_bit(TCCR0,CS01);
		clear_bit(TCCR0,CS00);
		break;
		
		case PRECALER_1024 :
		set_bit(TCCR0,CS00);
		clear_bit(TCCR0,CS01);
		set_bit(TCCR0,CS02);
		break;
		
		default:
		errorStatus= INVALID_PRESCALER;
		break;
	}	
	
	return errorStatus ;
}
/***********************************************************************************************************/
/**DESCRIPTION:-
 this function disables the timer
 **/

void TIMER_0_stop(void){
	
	clear_bit(TCCR0,CS00);
	clear_bit(TCCR0,CS01);
	clear_bit(TCCR0,CS02);
	
}
/**********************************************************************************************************/
/**DESCRIPTION:-
 this function set the offset of the timer counter
 **/

Timer_ErrorStatus TIMER_0_setIntialValue(double a_value){
	Timer_ErrorStatus errorStatus = TIMER_OK;

	if(a_value < TIMR0_MAX_VALUE && a_value >= 0){
		
		TCNT0 = ceil(a_value) ;
	}else{
		errorStatus = INVALID_VALUE;
	}
	return errorStatus ;
}
/******************************************************************************************************/
/**DESCRIPTION:-
takes number of overflow that we want to reach
 **/

Timer_ErrorStatus TIMER_0_OvfNum(double a_overflow){
	Timer_ErrorStatus errorStatus = TIMER_OK;
	double l_num_ovf = 0;
	if (a_overflow > 0)
	{
		
		
		while(l_num_ovf<a_overflow){
			
			while(read_bit(TIFR,TOV0)==0);
			set_bit(TIFR,TOV0);
			l_num_ovf++;
		}
		l_num_ovf = 0;
	}else if (a_overflow <= 0)
	{
		a_overflow = 1 ;
		while(l_num_ovf<a_overflow){
			
			while(read_bit(TIFR,TOV0)==0);
			set_bit(TIFR,TOV0);
			l_num_ovf++;
		}
		l_num_ovf = 0;
	}
		
		else{
			errorStatus = INVALID_OVF;
		}
	
	return errorStatus;
}
/**********************************************************************************************************/
/**DESCRIPTION:-
 this function takes time in ms to make a delay with this time
 **/

void TIMER_0_DELAY_MS(double a_time_ms){
	 g_time = a_time_ms/1000 ;
	 switch(Timer_cfgArray[TIMER_0].prescaler){
		 case PRECALER_1 :
		 g_ovfNum = ceil (g_time / 0.000032) ;
		 break;
		 case PRECALER_1024 :
		 g_ovfNum = ceil (g_time /  0.032768) ;
		  break;
	 }
	TIMER_0_init();
	TIMER_0_setIntialValue(0);
	TIMER_0_start();
	TIMER_0_OvfNum(g_ovfNum);
	
}

/*
void TIMER_0_pwm(float intial){
	
	uint8_t timer = ceil(intial);
	clear_bit(TCCR0,WGM00);
	clear_bit(TCCR0,WGM01);
	
	TCNT0 =   timer ;     
	            
	set_bit(TCCR0,CS00);
	clear_bit(TCCR0,CS01);
	set_bit(TCCR0,CS02);
	
	while(read_bit(TIFR,TOV0)==0);
	TCCR0 = 0;
	TCNT0 =   0;    
	set_bit(TIFR,TOV0);
	
	
}
*/
/**************************************************************************************************************/
/**DESCRIPTION:-
 this function is PWM using normal mode 
 
 **/
void TIMER_0_pwm(float a_intial){
	
	uint8_t l_timer = ceil(a_intial);
	TIMER_0_init();
	
	TCNT0 =   l_timer ;
	
	TIMER_0_start();
	
	TIMER_0_OvfNum(1);
	TCCR0 = 0;
	TCNT0 =   0;
	set_bit(TIFR,TOV0);
}

void TIMER0_OV_InterruptEnable(void)
{
	set_bit(TIMSK,TOIE0);
}

void TIMER0_OV_InterruptDisable(void)
{
	clear_bit(TIMSK,TOIE0);
}

void TIMER0_OV_SetCallBack(void(*local_fptr)(void))
{
	Timer0_OVF_Fptr=local_fptr;
}

ISR (TIMER0_OVF_vect)
{
	if (Timer0_OVF_Fptr!=NULLPTR)
	Timer0_OVF_Fptr();
}

/*****************************************************************************************/
/****************************************TIMER1*******************************************/

/****************************************************Pointer to Function (Timer_1)************************************************/
static void (*Timer1_OVF_Fptr) (void)=NULLPTR;
/*********************************************************************************************************************************/

void Timer1_Init( Timer_Mode mode,Timer_Prescaler scaler)
{
	switch (mode)
	{
		case NORMAL_MODE:
		clear_bit(TCCR1A,WGM10);
		clear_bit(TCCR1A,WGM11);
		clear_bit(TCCR1B,WGM12);
		clear_bit(TCCR1B,WGM13);
		break;
		case TIMER1_FASTPWM_OCRA_TOP_MODE:
		set_bit(TCCR1A,WGM10);
		set_bit(TCCR1A,WGM11);
		set_bit(TCCR1B,WGM12);
		set_bit(TCCR1B,WGM13);
		break;
	}

	TCCR1B&=0XF8;
	TCCR1B|=scaler;
}

void Timer1_OVF_InterruptEnable(void)
{
	set_bit(TIMSK,TOIE1);
}
void Timer1_OVF_InterruptDisable(void)
{
	clear_bit(TIMSK,TOIE1);
}
void Timer1_OVF_SetCallBack(void(*LocalFptr)(void))
{
	Timer1_OVF_Fptr=LocalFptr;
}


ISR(TIMER1_OVF_vect)
{
	if(Timer1_OVF_Fptr!=NULLPTR)
	{
		Timer1_OVF_Fptr();
	}
}


/*****************************************************************************************/
//										 TIMER2 
/*****************************************************************************************/



Timer_ErrorStatus TIMER_2_init(){
	Timer_ErrorStatus errorStatus = TIMER_OK;
	
	switch(Timer_cfgArray[TIMER_2].mode){
		
		case NORMAL_MODE :
		clear_bit(TCCR2,WGM20);
		clear_bit(TCCR2,WGM21);
		break;
		
		case PWM_PHASE_CORRECT :
		set_bit(TCCR2,WGM20);
		clear_bit(TCCR2,WGM21);
		break;
		
		case CTC :
		clear_bit(TCCR2,WGM20);
		set_bit(TCCR2,WGM21);
		break;
		
		
		case FAST_PWM :
		set_bit(TCCR2,WGM20);
		set_bit(TCCR2,WGM21);
		break;
		
		default:
		errorStatus = INVALID_MODE ;
		break;
	}
	
	
	return errorStatus;
	
	
}



void TIMER_2_stop(void){
	
	clear_bit(TCCR2,CS20);
	clear_bit(TCCR2,CS21);
	clear_bit(TCCR2,CS22);
	
}



Timer_ErrorStatus TIMER_2_setIntialValue(uint8_t a_value){
	Timer_ErrorStatus errorStatus = TIMER_OK;

	if(a_value < TIMR2_MAX_VALUE && a_value >= 0){
		
		TCNT2 = a_value ;
		}else{
		errorStatus = INVALID_VALUE;
	}
	return errorStatus ;
}



Timer_ErrorStatus TIMER_2_start(){
	Timer_ErrorStatus errorStatus = TIMER_OK;
	
	switch(Timer_cfgArray[TIMER_2].prescaler){
		
		case PRECALER_1 :
		set_bit(TCCR2,CS20);
		clear_bit(TCCR2,CS21);
		clear_bit(TCCR2,CS22);
		break;
		
		case PRECALER_8 :
		set_bit(TCCR2,CS21);
		clear_bit(TCCR2,CS20);
		clear_bit(TCCR2,CS22);
		break;
		
		case PRECALER_32 :
		set_bit(TCCR2,CS20);
		set_bit(TCCR2,CS21);
		clear_bit(TCCR2,CS22);
		break;
		
		case PRECALER_64 :
		set_bit(TCCR2,CS22);
		clear_bit(TCCR2,CS21);
		clear_bit(TCCR2,CS20);
		break;
		
		case PRECALER_128 :
		set_bit(TCCR2,CS20);
		clear_bit(TCCR2,CS21);
		set_bit(TCCR2,CS22);
		break;
		
		case PRECALER_256 :
		set_bit(TCCR2,CS22);
		clear_bit(TCCR2,CS20);
		set_bit(TCCR2,CS21);
		break;
			
		case PRECALER_1024 :
		set_bit(TCCR2,CS20);
		set_bit(TCCR2,CS21);
		set_bit(TCCR2,CS22);
		break;
		
		
		default:
		errorStatus= INVALID_PRESCALER;
		break;
	}
	
	return errorStatus ;
}



Timer_ErrorStatus TIMER_2_OvfNum(double overflow){
	Timer_ErrorStatus errorStatus = TIMER_OK;
	double num_ovf = 0;
	if (overflow > 0)
	{
		
		while(num_ovf<overflow){
			
			while(read_bit(TIFR,TOV2)==0);
			set_bit(TIFR,TOV2);
			num_ovf++;
		}
		num_ovf = 0;
	}else if (overflow <= 0)
	{
		overflow = 1 ;
		while(num_ovf<overflow){
			
			while(read_bit(TIFR,TOV2)==0);
			set_bit(TIFR,TOV2);
			num_ovf++;
		}
		num_ovf = 0;
	}
	
	else{
		errorStatus = INVALID_OVF;
	}
	
	return errorStatus;
}



void TIMER_2_DELAY_MS(double time_ms){
	double ovfNum2  ;
	double t2 ;
	t2 = time_ms/1000 ;
	ovfNum2 = ceil (t2 / 0.000256) ;
	TIMER_2_init(NORMAL_MODE);
	TIMER_2_setIntialValue(0);
	TIMER_2_start(PRECALER_1);
	TIMER_2_OvfNum(ovfNum2);
	
}







void TIMER_2_INT(){
	sei();
	set_bit(TIMSK,TOIE2);
	TIMER_2_init();
	TIMER_2_setIntialValue(0);
	TIMER_2_start();
	
	
	
}


static void (*ptrf_TIMER_2)(void)=NULL;

void TIMER_2_SetCallBack(void(*ptrf)(void)){
	
	ptrf_TIMER_2 = ptrf;
	
}

ISR(TIMER2_OVF){
	
	
	ptrf_TIMER_2();
	
	
}