

/*

LCD driver based on DIO driver


RS -> 1 for data 0-> command (PORTD pin 0)
RW -> zero PORTD PIN 1

VO for POT
VSS -> GND
VDD -> POWER
D0-D7 -> PORT
E - > PORTD pin 2


*/


#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"LCDinterfaceV5.h"
#include"DIO_interface.h"
#include<avr/delay.h>


#define FUNCTION_SET    0b00111000
#define ON_OFF          0b00001111 
#define DISPLAY_CLEAR   0b00000001

#define FUNCTION_SET    0b00111000
#define ON_OFF          0b00001111
#define DISPLAY_CLEAR   0b00000001
#define DATAPORT 2

/* Some important configs */

#define RW  1

#define RS  0

#define E   2

#define DATA_PORT 2

#define CONTROL_PORT 3

void LCD_VidIntialize()
{
	/*Set output PORT */

	DIO_VidSetPortDirection(2,255);

	/* configre RS RW E */

	DIO_VidSetPinDirection(3,RS,1);
	DIO_VidSetPinDirection(3,RW,1);
	DIO_VidSetPinDirection(3,E,1);


	/*Set of LCD data sheet commands*/

	_delay_ms(40);

	LCD_VidSendCommand(FUNCTION_SET);

	_delay_ms(1);

	LCD_VidSendCommand(ON_OFF);

	_delay_ms(1);

	LCD_VidSendCommand(DISPLAY_CLEAR);

	_delay_ms(2);
}

void LCD_VidSendData(u8 value)
{
	/*Set RS */

	DIO_VidSetPinValue(3,RS,1);

	/*RW*/

	DIO_VidSetPinValue(3,RW,0);

	/* Send data in ascii */

	DIO_VidSetPortValue(2,value);

	/* enable sequence */

	DIO_VidSetPinValue(3,E,1);

	_delay_ms(1);

	DIO_VidSetPinValue(3,E,0);

	_delay_ms(1);


}

void LCD_VidSendCommand(u8 value)
{
	/* set RS */
	DIO_VidSetPinValue(3,RS,0);

	/*RW*/

	DIO_VidSetPinValue(3,RW,0);



	DIO_VidSetPortValue(2,value);


	/* enable sequence */
	DIO_VidSetPinValue(3,E,1);

	_delay_ms(1);

	DIO_VidSetPinValue(3,E,0);

	_delay_ms(1);

}

void LCD_VidSendString(u8 *ptr)
{
	u8 i;

	for(i=0 ; ptr[i] != '\0' ;i++)
	{
		LCD_VidSendData(ptr[i]);

	}
}

void LCD_VidSendNum(u32 num)
{
	u8 x = 0;
	u32 rev = 0;

	if(num == 0)
	{
		LCD_VidSendData(48);
		return ;

	}

	while(num)
	{
		rev = (rev *10) + (num %10);

		num/=10;
		x++;

	}
	while(x)
	{
		u8 p = rev%10+48;

		LCD_VidSendData(p);

		rev/=10;

		x--;

	}


}
void LCD_VidGOTOPOS(u8 row,u8 col)
{
	if( 0 == row)
	{
		LCD_VidSendCommand(128 + col);
	}

	if(1 == row)
	{
		LCD_VidSendCommand(128 + 64 + col);
	}
}


void LCD_VidDraw()
{
	LCD_VidSendCommand(64);

	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);

	/* got to DDRAM  */
	LCD_VidGOTOPOS(0,0);

	LCD_VidSendData(0);
}





