/*
 * app.h
 *
 * Created: 15/05/2023 02:06:30 ص
 *  Author: Genius
 */ 


#ifndef APP_H_
#define APP_H_


/*****************************************************************************************************************************************************************
*									Includes																				 *
******************************************************************************************************************************************************************/
#include "../MCAL/dio/dio.h"
#include "../HAL/button/button.h"
#include "../MCAL/exi/exi_interrupt.h"
#include "../HAL/motor/motor.h"
#include "../MCAL/timers/timer.h"
#include "../HAL/ultrasonic/us.h"
#include "../HAL/car control/carControl.h"
#include "../HAL/keypad/keypad.h"
#include "../HAL/car control/carControl.h"
#include "../MCAL/pwm/pwm.h"
/*****************************************************************************************************************************************************************
*									defines																			 *
******************************************************************************************************************************************************************/

#define  _5_SEC  153
#define  _5_sec  30
#define  _2_SEC  10

#define button_0  pinc4

#define   left   1
#define   right  2


typedef enum {
	_5_SEC_FLAG = 1,
	_2_SEC_FLAG,
	_5_sec_flag
	
}TIME_FLAG;

typedef enum {
	NOT_DONE,
	DONE,
	
}TIME_STATE;


typedef enum {
	_30_ = 1,
	_50_,
	
}PWN_STATE;

typedef enum {
	START,
	STOP
}CAR_STATE;


typedef enum {
	START_PAGE,
	SET_ROTATION,
	WAIT_2SEC,
	MOVING,
}CAR_STAGES;

int stop_stage (void);
void start_stage (void);
void TIMER_control();
void CAR_no_obstacle_between_20_and_30();
void CAR_no_obstacle_between_30_and_70();
void CAR_wait_2_sec();
void CAR_no_obstacle_less_70();
void CAR_set_rotation_dir();
void app_Start(void);
void app_Init(void);
void check_start_stop (void);
void CAR_no_obstacle_less_20();
#endif /* APP_H_ */