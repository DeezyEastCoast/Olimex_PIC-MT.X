#ifndef BUTTONS_H
#define	BUTTONS_H


void initButtons(void);
char ButtonScan(void);

void ledOnOff(unsigned char state);
void relayOnOff(unsigned char state);

void Beep1(void);
void Beep2(void);

#endif	/* BUTTONS_H */

