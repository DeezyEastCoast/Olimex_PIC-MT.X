#include "system.h"

/*********************************************************************
 * Function:        	void Timer0Init(void)
 * Input:           	void
 * Output:          	void
 * Overview:        	This function initializes Timer1.
 ********************************************************************/
void Timer0Init(void)
{
   //Fosc = 16Mhz
   //Fcy  = Fosc/4
   //Below prescaler set to 1/64 so Ftimer1 = Fosc/256 
   //Timer period is 16uS--->62500 ticks is 1 sec
   //16-bit timer = 65536 ticks to overflow (Max number 65535)
   //Pre-set timer to 65535-62500 = 3036 (0x0BDC) so it overflows every 1 sec

   //set up Timer0
   T0CONbits.T08BIT = 0;    //configure timer as 16 bit timer
   T0CONbits.T0CS = 0;      //clock source is internal instruction cycle Fosc/4
   T0CONbits.PSA = 0;       //use prescaler on clock source 
   T0CONbits.T0PS2 = 1;     //choose prescale of 1/64
   T0CONbits.T0PS1 = 0; 
   T0CONbits.T0PS0 = 1;
   T0CONbits.TMR0ON = 1;    //turn timer on
   INTCONbits.TMR0IF = 0;   //clear timer overflow flag
   TMR0H = 0x0B;   //set timer high byte, must write to high byte first. 
   TMR0L = 0xDC;   //set timer low byte 
    
   //Disable Timer0 overflow interrupt
   INTCONbits.TMR0IE = 0;

   //Timer 0 as high priority interrupt
   INTCON2bits.TMR0IP = 1;   
}

/*********************************************************************
 * Function:        	unsigned char Timer0Overflow(void)
 * Input:           	void
 * Output:          	unsigned char
 * Overview:        	This function checks if timer 1 flag is set.
 ********************************************************************/
unsigned char Timer0Overflow(void)
{
    if(INTCONbits.TMR0IF)
    {
      INTCONbits.TMR0IF = 0;   //clear timer overflow flag
      //preset timer for 1 sec overflow
      TMR0H = 0x0B;   //set timer high byte, must write to high byte first. 
      TMR0L = 0xDC;   //set timer low byte 
      return 0xFF;
    } 
   
   return 0x00;
}


/*********************************************************************
 * Function:        	void Timer1Init(void)
 * Input:           	void
 * Output:          	void
 * Overview:        	This function initializes Timer1.
 ********************************************************************/
void Timer1Init(void)
{
   //Fosc = 16Mhz
   //Fcy  = Fosc/4
   //Below prescaler set to 1/8 so Ftimer1 = Fosc/32
   //Timer period is 2uS
   //16-bit timer = 65536 ticks to overflow (Max number 65535)
   //Pre-set timer to 65535-62500 = 3036 (0x0BDC) so it overflows every 1 sec

   //set up Timer1
   T1CONbits.RD16 = 1;     //read/write timer1 in one 16-bit operation (like timer0)
   T1CONbits.TMR1CS = 0;   //clock source is internal instruction cycle Fosc/4
   T1CONbits.T1CKPS1 = 1;  //choose prescale of 1/8
   T1CONbits.T1CKPS0 = 1;
   T1CONbits.TMR1ON = 1;   //turn timer on
   PIR1bits.TMR1IF = 0;    //clear timer overflow flag
   //TMR1H = 0x0B;           //set timer high byte, must write to high byte first. 
   //TMR1L = 0xDC;           //set timer low byte 
    
   //Disable Timer1 overflow interrupt
   PIE1bits.TMR1IE = 0;

   //Timer 1 as high priority interrupt
   IPR1bits.TMR1IP = 1;   
}