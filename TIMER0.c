

/**

code to run timer zero 

*/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"TIMERPRIV.h"


void VidTimer0_PWM_INIT()
{

	TCCR0 |= 1 << 6 | 1 << 3 | 1 << 5 | 1 << 4 | 1 << 1 ;

}

void VidTimer0SetPWMDutyCycle(u8 Dyty)
{
	OCR0 = Dyty;
}


