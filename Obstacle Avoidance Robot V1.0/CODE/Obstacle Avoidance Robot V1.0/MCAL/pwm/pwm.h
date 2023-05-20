/*
 * pwm.h
 *
 * Created: 5/20/2023 2:28:44 AM
 *  Author: AIO
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "../../MCAL/timers/timer.h"

#define PWM_F             400            //the frequency in Hz
#define PWM_Pin1           pind4
#define PWM_Pin2           pind5
void PWM_duty(uint8_t duty);





#endif /* PWM_H_ */