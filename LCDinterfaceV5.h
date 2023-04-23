#ifndef LCDINTERFACEV5_H
#define LCDINTERFACEV5_H

#include"STD_TYPES.h"
void LCD_VidIntialize();
void LCD_VidSendCommand(u8 value);
void LCD_VidSendData(u8 value);
void LCD_VidSendString(u8 *ptr);
void LCD_VidSendNum(u32 num);
void LCD_VidGOTOPOS(u8 row,u8 col);


#endif

