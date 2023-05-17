
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
	OUTPUT,	  /* PINB2   INT2 */
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


dio_config dio_arr[Pins_Total]={ {pina0,INPLUP},
								 {pinc7,OUTPUT},
								 {pind7,INPLUP},
								 {pinb2,OUTPUT},
								 {pind1,INPLUP},
								 {pinc5,OUTPUT},
								 {pinc4,OUTPUT},
								 {pina7,INPLUP},
								 {pina5,INFREE},
								 {pind6,OUTPUT},
								 {pind6,OUTPUT},
};