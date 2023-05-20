
#include "us.h"


void ultrasonicgetTime(void);
volatile uint8_t Get_Dis=0;

static uint32_t*Disptr;



void Ultrasonic_init_SW(void)
{
	DIO_INITPIN(TRIGGER_PIN,OUTPUT);
}

void Ultrasonic_GetDistance(uint32_t*dis)
{
	if (Get_Dis==0)
	{
		Disptr=dis;
		Icu_SetCallback(ECO_PIN,ultrasonicgetTime);
		Icu_Trigger(ECO_PIN,RISING_EDGE);
		Icu_Enable(ECO_PIN);
		DIO_WRITEPIN(TRIGGER_PIN,HIGH);
		_delay_us(10);
		DIO_WRITEPIN(TRIGGER_PIN,LOW);
		Get_Dis=1;
	}
	else
	{
		//nothing to do
	}
	//Disptr=dis;
	//Icu_SetCallback(ECO_PIN,ultrasonicgetTime);
	//Icu_Trigger(ECO_PIN,RISING_EDGE);
	//Icu_Enable(ECO_PIN);
	//DIO_WRITEPIN(TRIGGER_PIN,HIGH);
	//_delay_us(10);
	//DIO_WRITEPIN(TRIGGER_PIN,LOW);
	//Get_Dis=1;
}


 void ultrasonicgetTime (void)
{
	static uint8_t flag=0;
	static uint32_t T1=0;
	static uint32_t T2=0;
	if (flag==0)
	{
		T1=TCNT1;
		Icu_Trigger(ECO_PIN,FALLING_EDGE);
		flag=1;
	}
	else if (flag==1)
	{
		T2=TCNT1;
		Icu_Disable(ECO_PIN);
		flag=0;
		
		*Disptr=(T2-T1)/58;
		//TCNT1=0;
		Get_Dis=0;
	}
}
