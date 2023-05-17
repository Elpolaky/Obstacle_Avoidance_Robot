
#ifndef TIMER_H_
#define TIMER_H_





/*****************************************************************************************************************************************************************
*									Includes																				 *
******************************************************************************************************************************************************************/
#include "../../SERVICES/std_types.h"
#include "../../SERVICES/utiles.h"
#include "../memorymap.h"
#include "../exi/exi_interrupt.h"



/***********************************************************************************************************************
                                    GLOBAL VARIABLES AND DEFINES
******************************************************************************************************************************/

#define TIMR0_MAX_VALUE		256
#define TIMR2_MAX_VALUE		256

#define TIMER_NUM			 3 
extern uint8_t car_mode ;
extern  int32_t mode_ovf ;

/*****************************************************************************************************************************************************************
*									Typedefs																				 *
******************************************************************************************************************************************************************/
typedef enum {
	TIMER_0,
	TIMER_1,
	TIMER_2
	
	}TIMERS;

typedef enum {
	INVALID_PRESCALER,
	INVALID_MODE,
	INVALID_OVF,
	INVALID_VALUE,
	TIMER_OK
	}Timer_ErrorStatus;

typedef enum {
	NORMAL_MODE,
	FAST_PWM,
	CTC,
	TIMER1_FASTPWM_OCRA_TOP_MODE,
	PWM_PHASE_CORRECT
	
	}Timer_Mode;
	
typedef enum{
	PRECALER_1,
	PRECALER_8,
	PRECALER_64,
	PRECALER_32, // ONLY FOR TIMER_2
	PRECALER_128, // ONLY FOR TIMER_2
	PRECALER_256,
	PRECALER_1024,
	}Timer_Prescaler;

typedef struct {
	
	Timer_Mode		 mode ;
	Timer_Prescaler prescaler ;
	
	
}TIMER_cfg;

extern const TIMER_cfg Timer_cfgArray[TIMER_NUM] ;

/*****************************************************************************************************************************************************************
*									Functions declarations																				 *
******************************************************************************************************************************************************************/

/********************************** TIMER_0_ ******************************************/
Timer_ErrorStatus TIMER_0_init();
Timer_ErrorStatus TIMER_0_start();
void TIMER_0_stop(void);
Timer_ErrorStatus TIMER_0_setIntialValue(double a_value);
Timer_ErrorStatus TIMER_0_OvfNum(double a_overflow);
void TIMER_0_DELAY_MS(double a_time_ms);

void TIMER_0_pwm(float a_intial);


/********************************** TIMER_1_ ******************************************/
void Timer1_Init( Timer_Mode mode,Timer_Prescaler scaler);
void Timer1_OVF_InterruptEnable(void);
void Timer1_OVF_InterruptDisable(void);
void Timer1_OVF_SetCallBack(void(*LocalFptr)(void));
#define TIMER1_STOP()       TCCR1B&=0XF8


/********************************** TIMER_2_ ******************************************/
Timer_ErrorStatus TIMER_2_init(Timer_Mode a_mode);
Timer_ErrorStatus TIMER_2_start(Timer_Prescaler a_prescaler);
void TIMER_2_stop(void);
Timer_ErrorStatus TIMER_2_setIntialValue(uint8_t a_value);
Timer_ErrorStatus TIMER_2_OvfNum(double overflow);
void TIMER_2_DELAY_MS(double _delay);

void TIMER_2_INT();







#endif /* TIMER_H_ */