#ifndef _MAIN_H
#define	_MAIN_H

void configuration (void);

void portReset(void);

void outputTimeOn(unsigned int inputSecs);
void outputTimeOff(unsigned int inputSecs);
void openA2D(unsigned char);

void mSecDelay(unsigned int);
void uSecDelay(unsigned int secs);

unsigned int get_edata (unsigned char);
void put_edata (unsigned char, unsigned int);
unsigned char eeprom_read(unsigned char);
void eeprom_write(unsigned char, unsigned char);
unsigned int eepromReadInt(unsigned char);
void eepromWriteInt(unsigned char, unsigned int);

void int2Hex(unsigned int, char*);
unsigned int hex2Int(char*);
char getChecksum(unsigned char*);

void send_serial_byte(unsigned char);

void ioInit(void);

#endif
