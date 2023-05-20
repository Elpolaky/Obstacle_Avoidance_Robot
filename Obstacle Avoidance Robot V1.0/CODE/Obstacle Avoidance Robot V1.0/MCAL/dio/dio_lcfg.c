
#include "dio.h"

const DIO_PINSTATUS_TYPE PinsStatusArray[TOTAL_PINS]=
{
	OUTPUT,   /* PINA0 - ADC0 */
	OUTPUT,	  /* PINA1 - ADC1 */
	OUTPUT,	  /* PINA2 - ADC2 */
	OUTPUT,	  /* PINA3 - ADC3 */
	OUTPUT,	  /* PINA4 - ADC4 */
	OUTPUT,	  /* PINA5 - ADC5 */
	OUTPUT,	  /* PINA6 - ADC6 */
	OUTPUT,	  /* PINA7 - ADC7 */
	OUTPUT,	  /* PINB0 -	  */
	OUTPUT,	  /* PINB1 -	  */
	INPLUP,	  /* PINB2   INT2 */
	OUTPUT,	  /* PINB3 - OC0  */
	OUTPUT,	  /* PINB4 - SS	  */
	INPLUP,	  /* PINB5 - MOSI */
	INPLUP,	  /* PINB6 - MISO */
	OUTPUT,	  /* PINB7 - SCK  */
	OUTPUT,	  /* PINC0 -	  */
	OUTPUT,	  /* PINC1 -	  */
	OUTPUT,	  /* PINC2 -	  */
	OUTPUT,	  /* PINC3 -	  */
	OUTPUT,	  /* PINC4 -	  */
	OUTPUT,	  /* PINC5 -	  */
	INFREE,	  /* PINC6 -	  */
	OUTPUT,	  /* PINC7 -	  */
	OUTPUT,	  /* PIND0 - RX	  */
	OUTPUT,	  /* PIND1 - TX	  */
	OUTPUT,	  /* PIND2 - INT0 */
	OUTPUT,	  /* PIND3 - INT1 */
	OUTPUT,	  /* PIND4 - OC1B */
	OUTPUT,	  /* PIND5 - OC1A */
	INFREE,	  /* PIND6 - ICP1 */
	OUTPUT	  /* PIND7 - OC2  */
};


dio_config dio_arr[Pins_Total]={
									/*lcd*/
								 {pina1,OUTPUT},
								 {pina2,OUTPUT},
								 {pina3,OUTPUT},
								 {pina4,OUTPUT},
								 {pina5,OUTPUT},
								 {pina6,OUTPUT},
							     {pina7,OUTPUT},
									/*KeyPad*/
							     {pinc5,INFREE},
							     {pinc6,INFREE},
							     {pinc2,OUTPUT},
							     {pinc3,OUTPUT},
								/*PushButtons*/
							     {pinc4,INPLUP},
									 /*Motors*/
							     {pind2,OUTPUT},
							     {pind3,OUTPUT},
								 {pind6,OUTPUT},
								 {pind7,OUTPUT},
								 {pind4,OUTPUT},
								 {pind5,OUTPUT}	
									/*UltraSonic*/
									 								 
							
							 };