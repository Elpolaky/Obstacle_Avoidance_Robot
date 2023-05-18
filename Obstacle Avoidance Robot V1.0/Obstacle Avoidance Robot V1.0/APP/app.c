/*
 * app.c
 *
 * Created: 15/05/2023 02:06:40 ص
 *  Author: Genius
 */ 
#include "app.h"


/***********************************************************************************************************************
                                    GLOBAL VARIABLES 
*****************************************************************************************************************************/

uint8_t g_timerFlag  , g_start_stop  , u8_sg_distance = 40; 
uint8_t u8_sg_delay_5_sec , u8_sg_delay_2_sec  , u8_sg_stageFlag ;
static int32_t TIMER_ovf = 0;
 
 
uint8_t button_state = HIGH;
uint8_t u8_sg_default_Rot = right;
 /*****************************************************************************************************************************/
void app_Init(void){
	//Button_INIT(button_0);
	DIO_Init();
	LCD_INIT();
	keypad_init();
	TIMER_2_INT();
	TIMER_2_SetCallBack(TIMER_control);
	
	//start_stage();
}
/*****************************************************************************************************************************/
void TIMER_control(){
	
	if(g_timerFlag == _5_SEC_FLAG){
		
		if (TIMER_ovf < _5_SEC ){
			TIMER_ovf++;
			
			}
			
			else {
			TIMER_ovf = 0 ;
			g_timerFlag = 0 ;
			u8_sg_delay_5_sec = DONE ;
			}
	}
			
	else if (g_timerFlag == _2_SEC_FLAG ){
		
			if (TIMER_ovf < _2_SEC ){
				TIMER_ovf++;
			}
			
			else {
				TIMER_ovf = 0 ;
				g_timerFlag = 0 ;
				u8_sg_delay_2_sec = DONE ;
			}
	
	}
		
		
}

/*****************************************************************************************************************************/
void start_stage (void)
{
	// initializing button and lcd

	// start stage
	LCD_GoTo(FIRST_LINE,COL_3);
	LCD_Write_String("Set Def. Rot.");
	LCD_GoTo(SECOND_LINE,COL_6);
	LCD_Write_String("Right");
	u8_sg_stageFlag++;
}

/*****************************************************************************************************************************/
void CAR_set_rotation_dir(){
	g_timerFlag = _5_SEC_FLAG ;
	
	if (u8_sg_delay_5_sec == NOT_DONE)
	{
	
		Button_read(button_0,&button_state);
		if (button_state==HIGH)
		{
			Button_read(button_0,&button_state);
			
			if (button_state==LOW && u8_sg_default_Rot== right)
			{
				LCD_GoTo(SECOND_LINE,COL_6);
				LCD_Write_String("Left ");
				u8_sg_default_Rot=left;
			}
			else if (button_state==LOW && u8_sg_default_Rot==left)
			{
				LCD_GoTo(SECOND_LINE,COL_6);
				LCD_Write_String("Right");
				u8_sg_default_Rot=right;
			}
		}
	
	}
	
	else if (u8_sg_delay_5_sec == DONE)
	{
		u8_sg_delay_5_sec = NOT_DONE;
		u8_sg_stageFlag ++ ;
	}
}

/*****************************************************************************************************************************/


/*****************************************************************************************************************************/
void CAR_wait_2_sec(){
	g_timerFlag = _2_SEC_FLAG ;
	
	

	if (u8_sg_delay_2_sec == DONE)
	{
		u8_sg_delay_2_sec = NOT_DONE;
		u8_sg_stageFlag ++ ;
	}
}

/*****************************************************************************************************************************/

void CAR_no_obstacle_less_70()
{
	//set timer flag to start the timer
	g_timerFlag = _5_SEC_FLAG ;
	
	//	
	
	while(u8_sg_distance>70)
	{
		
		if(u8_sg_delay_5_sec == NOT_DONE)
		{
			pwm(30);
			Car_Moving_FWD();
			LCD_Clear();
			LCD_GoTo(FIRST_LINE,COL_0);
			LCD_Write_String("Speed:30% Dir: F");
			LCD_GoTo(SECOND_LINE,COL_0);
			LCD_Write_String("Dist.: ");
			LCD_GoTo(SECOND_LINE,COL_9);
			LCD_Write_Number(u8_sg_distance);
			LCD_GoTo(SECOND_LINE,COL_11);
			LCD_Write_String("cm");
		}
		else if(u8_sg_delay_5_sec == DONE)
		{
			pwm(50);
			Car_Moving_FWD();
			LCD_Clear();
			LCD_GoTo(FIRST_LINE,COL_0);
			LCD_Write_String("Speed:50% Dir: F");
			LCD_GoTo(SECOND_LINE,COL_0);
			LCD_Write_String("Dist.: ");
			LCD_GoTo(SECOND_LINE,COL_9);
			LCD_Write_Number(u8_sg_distance);
			LCD_GoTo(SECOND_LINE,COL_11);
			LCD_Write_String("cm");
		}
		else
		{
			// do nothing
		}
		Ultrasonic_GetDistance(&u8_sg_distance);
	}
	u8_sg_delay_5_sec = NOT_DONE ;
}

/*****************************************************************************************************************************/

void CAR_no_obstacle_between_30_and_70()
{
	
	while((u8_sg_distance>30) && (u8_sg_distance<=70))
	{
		pwm(30);
		Car_Moving_FWD();
		//LCD_Clear();
		LCD_GoTo(FIRST_LINE,COL_0);
		LCD_Write_String("Speed:30% Dir: F");
		LCD_GoTo(SECOND_LINE,COL_0);
		LCD_Write_String("Dist.: ");
		LCD_GoTo(SECOND_LINE,COL_9);
		LCD_Write_Number(u8_sg_distance);
		LCD_GoTo(SECOND_LINE,COL_11);
		LCD_Write_String("cm");
	
		Ultrasonic_GetDistance(&u8_sg_distance);
	}
}

/*****************************************************************************************************************************/

void CAR_no_obstacle_between_20_and_30()
{

	while((u8_sg_distance>20) && (u8_sg_distance<=30))
	{
		
		Car_Stop();
		LCD_Clear();
		LCD_GoTo(FIRST_LINE,COL_0);
		LCD_Write_String("Speed:30% Dir: S");
		LCD_GoTo(SECOND_LINE,COL_0);
		LCD_Write_String("Dist.: ");
		LCD_GoTo(SECOND_LINE,COL_9);
		LCD_Write_Number(u8_sg_distance);
		LCD_GoTo(SECOND_LINE,COL_11);
		LCD_Write_String("cm");
		
		if(u8_sg_default_Rot == right)
		{
			LCD_Clear();
			LCD_GoTo(FIRST_LINE,COL_0);
			LCD_Write_String("Speed:30% Dir: R");
			rotate_90degree_Right();
			LCD_GoTo(SECOND_LINE,COL_0);
			LCD_Write_String("Dist.: ");
			LCD_GoTo(SECOND_LINE,COL_9);
			LCD_Write_Number(u8_sg_distance);
			LCD_GoTo(SECOND_LINE,COL_11);
			LCD_Write_String("cm");
		}
		else if(u8_sg_default_Rot == left)
		{
			rotate_90degree_Left();
			LCD_Clear();
			LCD_GoTo(FIRST_LINE,COL_0);
			LCD_Write_String("Speed:30% Dir: L");
			LCD_GoTo(FIRST_LINE,COL_0);
			LCD_Write_String("Dist.: ");
			LCD_GoTo(SECOND_LINE,COL_9);
			LCD_Write_Number(u8_sg_distance);
			LCD_GoTo(SECOND_LINE,COL_11);
			LCD_Write_String("cm");
		}
		else
		{
			// DO NOTHING
		}
		Ultrasonic_GetDistance(&u8_sg_distance);
	} //  end of while
	
	
	

}

/*****************************************************************************************************************************/
void CAR_no_obstacle_less_20()
{

	while(u8_sg_distance<=20)
	{
		
		Car_Stop();
		LCD_Clear();
		LCD_GoTo(FIRST_LINE,COL_0);
		LCD_Write_String("Speed:30% Dir: S");
		LCD_GoTo(SECOND_LINE,COL_0);
		LCD_Write_String("Dist.: ");
		LCD_GoTo(SECOND_LINE,COL_9);
		LCD_Write_Number(u8_sg_distance);
		LCD_GoTo(SECOND_LINE,COL_11);
		LCD_Write_String("cm");
		
		Car_Moving_BWD();
		pwm(30);
		LCD_Clear();
		LCD_GoTo(FIRST_LINE,COL_0);
		LCD_Write_String("Speed:30% Dir: B");
		LCD_GoTo(SECOND_LINE,COL_0);
		LCD_Write_String("Dist.: ");
		LCD_GoTo(SECOND_LINE,COL_9);
		LCD_Write_Number(u8_sg_distance);
		LCD_GoTo(SECOND_LINE,COL_11);
		LCD_Write_String("cm");
		
		Ultrasonic_GetDistance(&u8_sg_distance);
	}
}
/*****************************************************************************************************************************/


void app_Start(void){
	
switch(g_start_stop){
	case STOP :

	break;
	
	
	case START :
		Ultrasonic_GetDistance(&u8_sg_distance);
		
		 if (u8_sg_stageFlag == START_PAGE )
		{
			start_stage();
		}
		else if (u8_sg_stageFlag == SET_ROTATION )
		{
			CAR_set_rotation_dir();
		}
		else if ( u8_sg_stageFlag == WAIT_2SEC){
			
			CAR_wait_2_sec();
			
		}else if ( u8_sg_stageFlag == MOVING ){
		
				if ( u8_sg_distance > 70)
				{
					CAR_no_obstacle_less_70();
				}
				else if ((u8_sg_distance>30) && (u8_sg_distance<=70) )
				{
					CAR_no_obstacle_between_30_and_70();
					
				}else if  ((u8_sg_distance>20) && (u8_sg_distance<=30) ){
					
					CAR_no_obstacle_between_20_and_30();
					
				}else if  (u8_sg_distance<=20){
					
					CAR_no_obstacle_between_20_and_30();
				}
				
				
		
		}
		
	

	
	break; // start break


	
}


}

