

#ifndef US_H_
#define US_H_



#include "../../MCAL/dio/dio.h"
#include "../../MCAL/timers/timer.h"
#include "../../HAL/icu/icu.h"
#include "../../HAL/lcd/lcd.h"

#define  ECO_PIN         EXT_INT_0
#define  TRIGGER_PIN      pinb0

void Ultrasonic_init_SW(void);

void Ultrasonic_GetDistance(uint32_t*dis);











#endif /* US_H_ */