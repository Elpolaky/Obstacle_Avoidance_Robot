/*
 * keypad.h
 *
 * Created: 5/9/2023 9:50:33 PM
 *  Author: Nada
 */ 

#include "keypad.h"


//*******************************************************************************************
uint8_t counter=0;

uint8_t button_value [keypad_rows_num ][keypad_columns_num]=
{
	{0,1},
	{2,3}

};

//********************************************************************************************************
/*Description:
This function is used to initialize the rows pin by assigning low voltage to it
note* the columns pins arealready initialized as inputs and rows pins as outputs in the Dio init array
*/
void keypad_init (void)
{ 

		
		// rows initialization value
		DIO_write(row1,keypad_port,LOW);
		DIO_write(row2,keypad_port,LOW);
		//DIO_write(row3,keypad_port,LOW);
		//DIO_write(row4,keypad_port,LOW);
}
//********************************************************************************************************
/*Description:
This function is used to get the value of the pressed key
*/
keypad_get_value  (uint8_t *value)
{
	uint8_t row_c=0,column_c=0;
	uint8_t row_pin,column_pin;
	uint8_t state=0;
	uint8_t key_unpressed=0;
	for (row_c=0;row_c<keypad_rows_num;row_c++)
	{
		
		DIO_write(row1,keypad_port,LOW);
		DIO_write(row2,keypad_port,LOW);
		//DIO_write(row3,keypad_port,LOW);
		//DIO_write(row4,keypad_port,LOW);
		row_pin=row_c+2;
		DIO_write(row_pin,keypad_port,HIGH);
		
		
		for(column_c=0;column_c<keypad_columns_num;column_c++)
		{
			column_pin=column_c+5;
			DIO_read(column_pin,keypad_port,&state);
			if (state==HIGH) {
			if (counter==0) 
			{
				*value=button_value[row_c][column_c];
				counter=1;
			}
			}
			else if (state==LOW) key_unpressed++;	
		}
		if (key_unpressed==keypad_rows_num) counter=0;
		}
		}
		
//***********************************************************************************************************************************

	
	
