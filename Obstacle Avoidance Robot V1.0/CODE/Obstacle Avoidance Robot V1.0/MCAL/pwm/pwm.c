/*
 * pwm.c
 *
 * Created: 5/20/2023 2:28:07 AM
 *  Author: AIO
 */ 


#include "pwm.h"


static volatile uint32_t PWM_count_ON=0;
static volatile uint32_t PWM_count_OFF=0;
static volatile uint8_t PWM_Count=0;
static void PWM_gen();

void PWM_duty(uint8_t duty)
{
	uint32_t temp=0;
	temp=((f32)1/PWM_F)*((f32)duty/100)*1000*1000;
	PWM_count_ON=temp/250;
	temp=((f32)1/PWM_F)*((f32)(100-duty)/100)*1000*1000;
	PWM_count_OFF=temp/250;
	PWM_Count=0;
	TIMER0_OV_SetCallBack(PWM_gen);
	TIMER0_OV_InterruptEnable();
	timer0_set(6);
	TIMER_0_init();
	TIMER_0_start();
}
static void PWM_gen()
{
	PWM_Count++;
	if (PWM_Count==PWM_count_OFF)
	{
		DIO_WRITEPIN(PWM_Pin1,HIGH);
		DIO_WRITEPIN(PWM_Pin2,HIGH);
	}
	else if (PWM_Count==(PWM_count_OFF+PWM_count_ON))
	{
		DIO_WRITEPIN(PWM_Pin1,LOW);
		DIO_WRITEPIN(PWM_Pin2,LOW);
		PWM_Count=0;
	}
	timer0_set(6);
}