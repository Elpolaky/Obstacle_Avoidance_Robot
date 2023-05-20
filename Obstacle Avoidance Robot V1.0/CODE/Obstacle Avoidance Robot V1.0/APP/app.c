
#include "app.h"


/***********************************************************************************************************************
                                    GLOBAL VARIABLES 
*****************************************************************************************************************************/

uint8_t g_timerFlag  , g_start_stop=17 , u8_pwm_flag = _30_ ,g_stop=17;
Uint16_t u8_sg_distance; 
volatile uint8_t u8_sg_delay_5_sec=NOT_DONE , u8_sg_delay_2_sec=NOT_DONE,u8_sg_delay_5_SEC=NOT_DONE  ;
volatile uint8_t u8_sg_stageFlag=0 ,u8_g_stop_flag = 0;
volatile static int32_t TIMER_ovf = 0;

uint8_t button_state = HIGH;
uint8_t u8_sg_default_Rot = right;
 /*****************************************************************************************************************************/
void app_Init(void){
	//Button_INIT(button_0);
	DIO_Init();
	Ultrasonic_init_SW();
	LCD_INIT();
	keypad_init();
	//TIMER_2_INT();
	//TIMER_2_SetCallBack(TIMER_control);
	
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
			
	else if (g_timerFlag == _2_SEC_FLAG )
	{
		
			if (TIMER_ovf < _2_SEC ){
				TIMER_ovf++;
			}
			
			else {
				TIMER_ovf = 0 ;
				g_timerFlag = 0 ;
				u8_sg_delay_2_sec = DONE ;
			}
	}
	else if(g_timerFlag == _5_sec_flag){
		
		if (TIMER_ovf < _5_sec ){
			TIMER_ovf++;
		}
		
		else {
			TIMER_ovf = 0 ;
			g_timerFlag = 0 ;
			u8_sg_delay_5_SEC = DONE ;
		}
	}
			
}

/*****************************************************************************************************************************/
void start_stage (void)
{
	// initializing button and lcd

	// start stage
	LCD_GoTo(FIRST_LINE,COL_2);
	LCD_Write_String("Set Rotation:");
	LCD_GoTo(SECOND_LINE,COL_6);
	LCD_Write_String("Right");
	u8_sg_stageFlag++;
	
}
/*****************************************************************************************************************************/
int stop_stage (void)
{
	keypad_get_value(&g_stop);
	if (g_stop==3)
	{
		u8_g_stop_flag = 1;
		g_start_stop=STOP;
		g_stop=17;
	}
	

}
/*****************************************************************************************************************************/
/*****************************************************************************************************************************/
/*****************************************************************************************************************************/
void CAR_set_rotation_dir(){
	
	uint8_t flag=0;
	static uint8_t flag_Wait=0;
	if (flag_Wait==0)
	{
		g_timerFlag = _5_sec_flag ;
		TIMER_2_INT();
		TIMER_2_SetCallBack(TIMER_control);
		flag_Wait=1;
	}	
	if (u8_sg_delay_5_SEC == NOT_DONE)
	{
		Button_read(button_0,&button_state);
		while(button_state == LOW && u8_sg_delay_5_sec == NOT_DONE )  
		{
			Button_read(button_0,&button_state);
			flag=1;
		}
		if (flag==1)
		{
			if (u8_sg_default_Rot== right)
			{
				LCD_GoTo(SECOND_LINE,COL_6);
				LCD_Write_String("Left ");
				u8_sg_default_Rot=left;
			}
			else if (u8_sg_default_Rot==left)
			{
				LCD_GoTo(SECOND_LINE,COL_6);
				LCD_Write_String("Right");
				u8_sg_default_Rot=right;
			}
			flag=0;
		
		}
		
		//while (button_state == LOW && u8_sg_delay_5_sec == NOT_DONE)
		//{
			//Button_read(button_0,&button_state);
		//}
	}
	
	else if (u8_sg_delay_5_SEC == DONE)
	{
		u8_sg_delay_5_SEC = NOT_DONE;
		u8_sg_stageFlag ++ ;
		TIMER_2_stop();
		flag=0;
		flag_Wait= 0;
		
	}

}

/*****************************************************************************************************************************/

/*****************************************************************************************************************************/


/*****************************************************************************************************************************/
void CAR_wait_2_sec(){
	
	static uint8_t flag_Wait=0;
	if (flag_Wait==0)
	{
		TIMER_2_INT();
		TIMER_2_SetCallBack(TIMER_control);
		g_timerFlag = _2_SEC_FLAG ;
		flag_Wait=1;
		LCD_Clear();
		LCD_GoTo(1,0);
		LCD_Write_String((uint8_t*)"The Default");
		LCD_GoTo(2,0);
		if (u8_sg_default_Rot==right)
		{
			LCD_Write_String((uint8_t*)"Rotation Right ");
		}
		else
		{
			LCD_Write_String((uint8_t*)"Rotation Left");
		}
		TIMER_2_INT();
		TIMER_2_SetCallBack(TIMER_control);
	}
	
	if (u8_sg_delay_2_sec == DONE)
	{
		TIMER_2_stop();
		u8_sg_delay_2_sec = NOT_DONE;
		u8_sg_stageFlag ++ ;
		flag_Wait=0;
	}
}

/*****************************************************************************************************************************/

void CAR_no_obstacle_less_70()
{
	//set timer flag to start the timer
	g_timerFlag = _5_SEC_FLAG ;
	
	//	
	static uint8_t flag_Wait=0;
	if (flag_Wait==0)
	{
		TIMER_2_INT();
		TIMER_2_SetCallBack(TIMER_control);
		flag_Wait=1;
		LCD_Clear();
	}
	
	while(u8_sg_distance>70 && (u8_g_stop_flag==0))
	{
		Ultrasonic_GetDistance(&u8_sg_distance);
		if(u8_sg_delay_5_sec == NOT_DONE)
		{
			//Ultrasonic_GetDistance(&u8_sg_distance);
			if (u8_pwm_flag == _30_)
			{
				Car_Moving_FWD();
				PWM_duty(30);
				u8_pwm_flag = _50_ ;
			}
			
			
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
			if (u8_pwm_flag == _50_)
			{
				Car_Moving_FWD();
				PWM_duty(50);
				u8_pwm_flag = _30_ ;
			}
			
			//LCD_Clear();
			LCD_GoTo(FIRST_LINE,COL_0);
			LCD_Write_String("Speed:50% Dir: F");
			LCD_GoTo(SECOND_LINE,COL_0);
			LCD_Write_String("Dist.: ");
			LCD_GoTo(SECOND_LINE,COL_9);
			LCD_Write_Number(u8_sg_distance);
			LCD_GoTo(SECOND_LINE,COL_11);
			LCD_Write_String("cm");
			TIMER_2_stop();
		}
		stop_stage();
	}
	u8_sg_delay_5_sec = NOT_DONE ;
	flag_Wait=0;
	u8_pwm_flag = _30_;
}


/*****************************************************************************************************************************/

void CAR_no_obstacle_between_30_and_70()
{
	LCD_Clear();
	while((u8_sg_distance>30) && (u8_sg_distance<=70)&& (u8_g_stop_flag==0))
	{
		LCD_GoTo(FIRST_LINE,COL_0);
		LCD_Write_String("Speed:30% Dir: F");
		LCD_GoTo(SECOND_LINE,COL_0);
		LCD_Write_String("Dist.: ");
		LCD_GoTo(SECOND_LINE,COL_9);
		LCD_Write_Number(u8_sg_distance);
		LCD_GoTo(SECOND_LINE,COL_11);
		LCD_Write_String("cm");
		if (u8_pwm_flag == _30_)
		{
			Car_Moving_FWD();
			PWM_duty(30);
			u8_pwm_flag = _50_ ;
		}
		Car_Moving_FWD();
		Ultrasonic_GetDistance(&u8_sg_distance);
		stop_stage();
	}
	u8_pwm_flag = _30_ ;
}

/*****************************************************************************************************************************/

void CAR_no_obstacle_between_20_and_30()
{
	
	Car_Stop();
	LCD_Clear();
	while((u8_sg_distance>20) && (u8_sg_distance<=30)&& (u8_g_stop_flag==0))
	{
		
		
		if(u8_sg_default_Rot == right )
		{
			Ultrasonic_GetDistance(&u8_sg_distance);
			LCD_GoTo(FIRST_LINE,COL_0);
			LCD_Write_String("Speed:30% Dir: R");
			
			LCD_GoTo(SECOND_LINE,COL_0);
			LCD_Write_String("Dist.: ");
			LCD_GoTo(SECOND_LINE,COL_9);
			LCD_Write_Number(u8_sg_distance);
			LCD_GoTo(SECOND_LINE,COL_11);
			LCD_Write_String("cm");
			
			if (u8_pwm_flag == _30_)
			{
				PWM_duty(30);
				rotate_90degree_Right();
				u8_pwm_flag = _50_ ;
			}
			Car_Stop();
		
		}
		else if(u8_sg_default_Rot == left )
		{
			Ultrasonic_GetDistance(&u8_sg_distance);
			
			//LCD_Clear();
			LCD_GoTo(FIRST_LINE,COL_0);
			LCD_Write_String("Speed:30% Dir: L");
			LCD_GoTo(FIRST_LINE,COL_0);
			LCD_Write_String("Dist.: ");
			LCD_GoTo(SECOND_LINE,COL_9);
			LCD_Write_Number(u8_sg_distance);
			LCD_GoTo(SECOND_LINE,COL_11);
			LCD_Write_String("cm");
			if (u8_pwm_flag == _30_)
			{
				
				PWM_duty(30);
				rotate_90degree_Left();
				u8_pwm_flag = _50_ ;
			}
			Car_Stop();
			
		}
		else
		{
			// DO NOTHING
		}
		Ultrasonic_GetDistance(&u8_sg_distance);
		stop_stage();
	} //  end of while
	
	
	u8_pwm_flag = _30_ ;

}

/*****************************************************************************************************************************/
void CAR_no_obstacle_less_20()
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
		_delay_ms(1000);
		LCD_Clear();
	while(u8_sg_distance<=20 && (u8_g_stop_flag==0))
	{
		
		if (u8_pwm_flag == _30_)
		{
			Car_Moving_BWD();
			PWM_duty(30);
			u8_pwm_flag = _50_ ;
		}
		LCD_GoTo(FIRST_LINE,COL_0);
		LCD_Write_String("Speed:30% Dir: B");
		LCD_GoTo(SECOND_LINE,COL_0);
		LCD_Write_String("Dist.: ");
		LCD_GoTo(SECOND_LINE,COL_9);
		LCD_Write_Number(u8_sg_distance);
		LCD_GoTo(SECOND_LINE,COL_11);
		LCD_Write_String("cm");
		
		Ultrasonic_GetDistance(&u8_sg_distance);
		stop_stage();
	}
	
	u8_pwm_flag = _30_ ;
}
/*****************************************************************************************************************************/



void app_Start(void){
 

 while(1)
	{
			 if (g_start_stop==START)
			 {
				 keypad_get_value(&g_start_stop);
				 if (u8_sg_stageFlag == START_PAGE )
				 {
					 start_stage();
				 }
				 else if (u8_sg_stageFlag == SET_ROTATION )
				 {
					 CAR_set_rotation_dir();
				 }
				 else if ( u8_sg_stageFlag == WAIT_2SEC)
				 {
					 
					 CAR_wait_2_sec();
				 }
				 while(u8_sg_stageFlag == MOVING && u8_g_stop_flag==0)
				 {
					 Ultrasonic_GetDistance(&u8_sg_distance);
					 if ( u8_sg_distance > 70)
					 {
						 CAR_no_obstacle_less_70();
					 }
					 else if ((u8_sg_distance>30) && (u8_sg_distance<=70) )
					 {
						 CAR_no_obstacle_between_30_and_70();
						 
					 }
					 else if  ((u8_sg_distance>20) && (u8_sg_distance<=30) )
					 {
						 
						 CAR_no_obstacle_between_20_and_30();
						 
					 }
					 else if  (u8_sg_distance<=20)
					 {
						 
						 CAR_no_obstacle_less_20();
					 }
					       stop_stage();
				 }
			 }
			 else if (u8_g_stop_flag==1)
			 {
				 LCD_Clear();
				 Car_Stop();
				 PWM_duty(0);
				 TIMER_2_stop();
				 u8_sg_default_Rot = right ;
				  u8_g_stop_flag=0;
				 u8_sg_stageFlag =START_PAGE;
			 }
				   
			 else keypad_get_value(&g_start_stop);
				   
				   
			 }

}

