
/*

ADC DRIVER based on c for AVR ATMEGA32

AUTHOR : AHMED SALEM 

DATE : 22/2/2023


*/


#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"ADC_INTERFACE.h"
#include<avr/io.h>


void ADC_INIT()
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	
   	 ADMUX = 0;	 
	
   	 CLR_BIT(ADMUX,5);

	 /* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADPS2:0 = 110 to choose ADC_Clock=F_CPU/64=8Mhz/64=125Khz --> ADC must operate in range 50-200Khz
	 */
	
	 ADCSRA |= 1 << 1 | 1 << 2 | 1 << 7;
	
}

u16 ADC_READ(u8 channel_num)
{
	 /* channel number must be from 0 --> 7 */
	 /* clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	 /* choose the correct channel by setting the channel number in MUX4:0 bits */
	channel_num &= 0x07; 
	ADMUX &= 0xE0; 
	ADMUX = ADMUX | channel_num; 
	
	 /* start conversion write '1' to ADSC >> START CONVERSION PIN  */
	 /* wait for conversion to complete ADIF becomes '1' */
	 /* clear ADIF by write '1' to it >> wait till conversion is done :) */
	 /* return the data register */
	
	ADCSRA |= 1 << 6; // start conversion
	
	while(GET_BIT(ADCSRA,4) == 1);
	
	SET_BIT(ADCSRA,4);

	return ADC ;
	
}














