/*
 * keypad.h
 *
 * Created: 5/9/2023 9:49:45 PM
 *  Author: Nada
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
//********************INCLUDES***********************

#include "../../SERVICES/std_types.h"
#include "keypad_config.h"
#include "../../MCAL/memorymap.h"
#include "../../MCAL/dio/dio.h"



//******************FUNCTIONS DECLEARATION************
void keypad_init (void);
void keypad_get_value  (uint8_t *value);






#endif /* KEYPAD_H_ */