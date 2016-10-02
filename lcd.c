 #include "system.h"

#define		E			LATAbits.LATA5
#define		RW			LATAbits.LATA3
#define		RS			LATAbits.LATA2

#define		CLR_DISP		0x01
#define		DISP_ON			0x0C
#define		DISP_OFF		0x08
#define		CUR_HOME        0x02
#define		CUR_OFF 		0x0C
#define 	CUR_ON_UNDER    0x0E
#define		CUR_ON_BLINK    0x0F
#define 	CUR_LEFT        0x10
#define		CUR_RIGHT       0x14
#define		CUR_UP  		0x80
#define		CUR_DOWN		0xC0
#define		ENTER           0xC0
#define		DD_RAM_ADDR		0x80
#define		DD_RAM_ADDR2	0xC0

unsigned  int i;
unsigned  char data;

unsigned char CUR_ROW = 0;
unsigned char CUR_COL = 0;

unsigned char OlimexMsg[] = " www.olimex.com ";

void E_Pulse(void) {
	E=1;
	Delay1TCY();
	Delay1TCY();
	Delay1TCY();
        Delay1TCY();
	Delay1TCY();
	Delay1TCY();
	E=0;
}

// Init LCD  after reset
void InitLCD(void) {

	INTCON 	= 0x0;			// Disable inerupt
	CMCON 	= 0x07;		        // Comparators Off
	ADCON1  = 0x06;			// Port as Digital IO
	TRISAbits.RA2 	= 0;			// RS pin as output
	TRISAbits.RA3 	= 0;			// RW pin as output
	TRISAbits.RA5 	= 0;			// E pin as output
	TRISC	= 0xF0;			// D4-D7 as output


	RS=0;
	RW=0;
	mSecDelay(110);
	PORTC=0b00000011;
	E_Pulse();
	mSecDelay(10);
	PORTC=0b00000011;
	E_Pulse();
	mSecDelay(10);
	PORTC=0b00000011;
	E_Pulse();
	mSecDelay(10);
	PORTC=0b00000010;
	E_Pulse();

        LCDSendCmd(DISP_ON);
        LCDSendCmd(CLR_DISP);
}

// Send char to LCD
void LCDSendChar(unsigned char c) {

	mSecDelay(2);
	//get upper nibble
	data = c & 0b11110000;
	//set D4-D7
	data = data >> 4;
	//send data to LCD
	PORTC = data;
	//set LCD to write
	RW=0;
	//set LCD to data mode
	RS=1;
	//toggle E for LCD
	E_Pulse();
	// get lower nibble
	data = c & 0b00001111;
	//send data to LCD
	PORTC = data;
	//set LCD to write
	RW=0;
	//set LCD to data mode
	RS=1;
	//toggle E for LCD
	E_Pulse();
}

// Send command to LCD
void LCDSendCmd(unsigned char c) {

	mSecDelay(2);
	//get upper nibble
	data = c & 0b11110000;
	//set D4-D7
	data = data >> 4;
	//send data to LCD
	PORTC = data;
	//set LCD to write
	RW=0;
	//set LCD to data mode
	RS=0;
	//toggle E for LCD
	E_Pulse();
	// get lower nibble
	data = c & 0b00001111;
	PORTC = data;
	//set LCD to write
	RW=0;
	//set LCD to data mode
	RS=0;
	//toggle E for LCD
	E_Pulse();
}


void LCDSendStr(unsigned char* str) {

	i=0;
	while(str[i]) {
		LCDSendChar(str[i]);
		i++;
	}
}

void LCDcursorPos(unsigned char row, unsigned char col)
{
    unsigned char j = 0;
    if(row > 1) return;
    if(col > 15) return;

    LCDSendCmd(CUR_HOME);

    if(row)
        LCDSendCmd(CUR_DOWN);
    for(j=0;j<col;j++)
        LCDSendCmd(CUR_RIGHT);

    CUR_ROW = row;
    CUR_COL = col;
}

void LCDwriteLine(unsigned char row, unsigned char col, unsigned char* str)
{
    unsigned char j = 0;
    if(row > 1) return;
    if(col > 15) return;

    LCDSendCmd(CUR_HOME);

    if(row)
        LCDSendCmd(CUR_DOWN);

    for(j=0;j<col;j++)
        LCDSendCmd(CUR_RIGHT);

    j=0;
    while(j<(15-col) && (str[j]))
    {
     LCDSendChar(str[j]);
     j++;
    }

    LCDcursorPos(row, 15); //put cursor at end of current row

}