/*
 * carControl.c
 *
 * Created: 5/17/2023 12:53:49 PM
 *  Author: moham
 */ 

#include "carControl.h"
/***********************************************************************************************************************
                                    GLOBAL VARIABLES 
*****************************************************************************************************************************/
// used in rotate_90degree_calculation
float rotation_per_circle;
float time_rotation_state ;
// used in pwm
float g_time1;
float g_speed;
float g_time2;








/**DESCRIPTION:-
  this function is used to make pwm in pin pinb0
  **/
void pwm(float a_speed){
	 g_speed= a_speed/100;
	g_time1=  (g_speed * 256);
	 g_time2=256-g_time1;
	TIMER_0_pwm(g_time1);
	DIO_WRITEPIN(pinb0,HIGH);
	
	TIMER_0_pwm(g_time2);
	DIO_WRITEPIN(pinb0,LOW);
	
}

/*****************************************************************************************************
**DESCRIPTION:-
this function calculates the time nedded of rotation to turn the car 90 degree*/

void rotate_90degree_calculation (void)
{
	//1-Rotation of wheels needed to make a circular path calculations:
	//(1.1)-the circumference of the circle of that the wheels make.
	//circle_circumference= PI*distance_between_wheels;
	//(1.2) the circumference of the wheel.
	//wheel_circumference= PI*wheel_diameter;
	//(1.3) total rotations needed for one circular path.
	//rotation_per_circle = circle_circumference/wheel_circumference;
	rotation_per_circle = ((PI*distance_between_wheels)/(PI*wheel_diameter));
	//2- Calculate the rotation of each wheel to rotate 90 degrees:
	//(2.1)  rotation per wheel= rotation_per_circle/0.25
	//(2.2) time needed for car to turn 90 degree= (rotation per wheel/maximum speed percentage)*60) in sec
	time_rotation_state= ((rotation_per_circle*0.25)/(max_speed*0.1))*60;
	
	
}


/*******************************************************************************************************************************************
**DESCRIPTION:-
this function makes the car stop for another 0.5 sec then rotate 90 degree to the right then stop for another 0.5 sec
LED four is the indicator of rotating phase*/

void rotate_90degree_state (void)
{
	DIO_WRITEPIN(pinc0,LOW);
	rotate_90degree_calculation();
	mode_ovf= time_rotation_state/ 0.000256 ;  // 3.75 seconds for simulation test
	//mode_ovf= 15625 ;
	// Rotation state
	Car_Rotating();
	
	DIO_WRITEPIN(pinc3,HIGH);
	pwm(10);

}
/*************************************************************************************************************************************************/
