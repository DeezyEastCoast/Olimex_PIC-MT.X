#ifndef _uart14k50_H
#define	_uart14k50_H

void initUart(unsigned char baud);
void writeUart(unsigned char character);
unsigned char readUart(void);
void writeUartString(char*);
void writeUartConstString(const far rom char*);
char parseRxBuffer(char*);
void flushRxBuffer(void);

#endif