
#ifndef MOTOR_H_
#define MOTOR_H_




/*************************includes*********************************************************************************/
#include "../../MCAL/dio/dio.h"
/******************************************************************************************************************/

/**************************************defines*********************************************************************/
#define motor1_0  pind2
#define motor1_1  pind3
#define motor2_0  pind6
#define motor2_1  pind7
#define motor3_0  pina4
#define motor3_1  pina5
#define motor4_0  pina6
#define motor4_1  pina7


/*******************************************************************************************************************/

/************************************************declarations*******************************************************/
void Car_Moving_BWD(void);
void Car_Motors_init(void);
void Car_Moving_FWD(void);
void Car_Rotating(void);
void Car_Stop(void);




#endif /* MOTOR_H_ */