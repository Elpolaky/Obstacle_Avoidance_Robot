

#ifndef ICU_H_
#define ICU_H_


#include "../../MCAL/dio/dio.h"
#include "../../MCAL/timers/timer.h"
#include "../../MCAL/exi/exi_interrupt.h"




void Icu_Enable(EN_int_t EXInt );
void Icu_Disable(EN_int_t EXInt);
void Icu_Trigger(EN_int_t EXInt,EN_trig trigger);
void Icu_SetCallback(EN_int_t EXInt,void(*fptr)(void));




#endif /* ICU_H_ */