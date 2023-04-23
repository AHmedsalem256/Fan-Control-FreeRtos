#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#include"STD_TYPES.h"

void DIO_VidSetPinDirection(u8 port , u8 pin , u8 dir);
void DIO_VidSetPortDirection(u8 port , u8 dir);
void DIO_VidSetPinValue(u8 port,u8 pin,u8 val);
void DIO_VidSetPortValue(u8 port, u8 val);
u8 DIO_VidGetPinValue(u8 port,u8 pin);
void DIO_TogglePinValue( u8 port,u8 pin);


#endif
