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

/*****************************************************************************************************************************************************************
*									defines																			 *
******************************************************************************************************************************************************************/

#define  _5_SEC  153
#define  _2_SEC  62

#define button_0  pinc0

#define   left   1
#define   right  2


typedef enum {
	_5_SEC_FLAG = 1,
	_2_SEC_FLAG,
	
}TIME_FLAG;

typedef enum {
	NOT_DONE,
	DONE,
	
}TIME_STATE;


typedef enum {
	STOP,
	START,
	
}CAR_STATE;


typedef enum {
	START_PAGE,
	SET_ROTATION,
	WAIT_2SEC,
	MOVING,
	
}CAR_STAGES;


void start_stage (void);
void TIMER_control();
void CAR_no_obstacle_between_30_and_70();
void CAR_wait_2_sec();
void CAR_no_obstacle_less_70();
void CAR_set_rotation_dir();
void app_Start(void);
void app_Init(void);
#endif /* APP_H_ */