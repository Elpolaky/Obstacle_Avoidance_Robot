
#include "icu.h"

static void Icu_TimerOVF(void);
static uint8_t count_OVF=0;

void Icu_Enable(EN_int_t EXInt )
{
	EXI_Enable(EXInt);
	TCNT1=0;
	Timer1_OVF_SetCallBack(Icu_TimerOVF);
	Timer1_OVF_InterruptEnable();
	Timer1_Init(NORMAL_MODE,PRECALER_8);
}
void Icu_Disable(EN_int_t EXInt)
{
	EXI_Disable(EXInt);
	count_OVF=0;
	TIMER1_STOP();
}
void Icu_Trigger(EN_int_t EXInt,EN_trig trigger)
{
	EXI_Trigger(EXInt,trigger);
}

void Icu_SetCallback(EN_int_t EXInt,void(*fptr)(void))
{
	EXI_SetCallBack(EXInt,fptr);
}

static void Icu_TimerOVF(void)
{
	count_OVF++;
}



