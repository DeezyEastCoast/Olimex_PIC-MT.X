#ifndef _LCD_H
#define	_LCD_H

void InitLCD(void);
void E_Pulse(void);
void LCDSendChar(unsigned char);
void LCDSendCmd(unsigned char);
void LCDSendStr(unsigned char*);
void LCDwriteLine(unsigned char row, unsigned char col, unsigned char* str);
void LCDcursorPos(unsigned char row, unsigned char col);

#endif