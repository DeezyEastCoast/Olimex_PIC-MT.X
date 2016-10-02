#include "system.h"

#define	COL1		PORTBbits.RB0
#define	COL2		PORTBbits.RB1
#define	COL3		PORTBbits.RB2
#define	LED		LATBbits.LATB4
#define	BUZZ1		LATCbits.LATC4
#define	BUZZ2		LATCbits.LATC5
#define	RELAY		LATAbits.LATA1

#define	OFF		0
#define	ON		1

#define BUTTON_NONE			0
#define BUTTON1_ON			1 //
#define BUTTON1_OFF			2
#define BUTTON2_ON			3
#define BUTTON2_OFF			4
#define BUTTON3_ON			5 //
#define BUTTON3_OFF			6
#define BUTTON4_ON			7 //
#define BUTTON4_OFF			8
#define BUTTON5_ON			9 //
#define BUTTON5_OFF			10
#define BUTTON6_ON			11
#define BUTTON6_OFF			12

unsigned char B1, B2, B3, B4, B5, B6;

void initButtons()
{
    // Clear variable
    B1=B2=B3=B4=B5=B6=0;

    TRISAbits.TRISA1 = 0;    // RELAY pin as output

    TRISBbits.TRISB4 = 0;    // LED pin as output

    TRISCbits.TRISC4 = 0;    //BUZZER pins as outputs
    TRISCbits.TRISC5 = 0;
}

char ButtonScan(void) {

	//set COL1 ---------------------------------------------
	LATB |= 0x07;            // set RB0,RB1,RB2 high
	TRISB |= 0x07;           // set RB0,RB1,RB2 as inputs
	TRISBbits.TRISB0 = 0;    // set pin as output
	mSecDelay(2);

	//button 1 is pressed
	if((COL2==1)&&(B1==OFF)) { B1=ON; return BUTTON1_ON; }
	if((COL2==0)&&(B1==ON))  { B1=OFF; return BUTTON1_OFF; }

	//button 6 is pressed
	if((COL3==1)&&(B6==OFF)) { B6=ON; return BUTTON6_ON; }
	if((COL3==0)&&(B6==ON))  { B6=OFF; return BUTTON6_OFF; }

	//set COL1 ---------------------------------------------
	LATB |= 0x07;
	TRISB |= 0x07;
	TRISBbits.TRISB1 = 0;    // set pin as output
	mSecDelay(2);

	//button 4 is pressed
	if((COL1==1)&&(B4==OFF)) { B4=ON; return BUTTON4_ON; }
	if((COL1==0)&&(B4==ON))  { B4=OFF; return BUTTON4_OFF; }

	//button 2 is pressed
	if((COL3==1)&&(B2==OFF)) { B2=ON; return BUTTON2_ON; }
	if((COL3==0)&&(B2==ON))  { B2=OFF; return BUTTON2_OFF; }

	//set COL1 ---------------------------------------------
	LATB |= 0x07;
	TRISB |= 0x03;
	TRISBbits.TRISB2 = 0;    // set pin as output
	mSecDelay(2);

	//button 3 is pressed
	if((COL1==1)&&(B3==OFF)) { B3=ON; return BUTTON3_ON; }
	if ((COL1==0)&&(B3==ON)) { B3=OFF; return BUTTON3_OFF; }

	//button 5 is pressed
	if((COL2==1)&&(B5==OFF)) { B5=ON; return BUTTON5_ON; }
	if((COL2==0)&&(B5==ON))  { B5=OFF; return BUTTON5_OFF; }

	return BUTTON_NONE;
}

void ledOnOff(unsigned char state)
{
      if(state)
        LED = 1;
    else
        LED = 0;
}

void relayOnOff(unsigned char state)
{
    if(state)
        RELAY = 1;
    else
        RELAY = 0;
}

void Beep1(void) {

	unsigned char t=150;

	while(--t) {
		BUZZ2 = OFF;
		BUZZ1 = ON;
		uSecDelay(125);
		BUZZ1 = OFF;
		BUZZ2 = ON;
	 	uSecDelay(125);
	}
}

void Beep2(void) {

	unsigned char t=75;

	while(--t) {
		BUZZ2 = OFF;
		BUZZ1 = ON;
		uSecDelay(250);
		BUZZ1 = OFF;
		BUZZ2 = ON;
	 	uSecDelay(250);
	}
}