#include "system.h"

/*********************************************************************
 * Function:        	unsigned char UartInit(void)
 * Input:           	unsigned char
 * Output:          	void
 * Overview:        	This function initializes the uart. 
 *
 ********************************************************************/
void InterruptInit(void)
{ 
   INTCON = 0;
   PIR1 = 0; PIE1 = 0;
   PIR2 = 0; PIE2 = 0;
   IPR1 = 0; IPR2 = 0;

   //disable priority levels on interrupts
   RCONbits.IPEN = 0;

   //Global interrupt disable
   INTCONbits.GIEH = 1;

   //Enable all unmasked peripheral interrupts
   INTCONbits.PEIE = 1;  
     
   PIE1bits.RCIE = 1; //EUSART RX flag interrupt enable
   IPR1bits.RCIP = 1; //Make recieve interrupt high priority
   
   /*
   //INTCON Register bits
   INTCONbits.TMR0IE  = 0; //timer 0 interrupt enable
   INTCONbits.INT0IE  = 0; //int0 external interrupt enable
   INTCONbits.RABIE   = 0; //RA/RB Port change interrupt enable; At least one pin RA<5:3> or RB<7:4> changed state

   INTCONbits.TMR0IF  = 0; //timer 0 flag
   INTCONbits.INT0IF  = 0; //int0 external interrupt flag
   INTCONbits.RABIF   = 0; //RA/RB Port change interrupt flag; At least one pin RA<5:3> or RB<7:4> changed state
                           //must read PORTA and PORTB then clear flag

   //INTCON2 Register bits
   INTCON2bits.RABPU   = 1; //PORTA & PORTB pull up enable; 1 = pull-ups disabled
   INTCON2bits.INTDG0  = 1; //int0 external interrupt edge select; 0 = int on falling edge
   INTCON2bits.INTDG1  = 1; //int1 external interrupt edge select; 0 = int on falling edge
   INTCON2bits.INTDG2  = 1; //int2 external interrupt edge select; 0 = int on falling edge 
   INTCON2bits.TMR0IP  = 1; //timer 0 priority; 1 = high priority
   INTCON2bits.RABIP   = 1; //RA/RB Port change interrupt priority; 1 = high priority
                          
   //INTCON3 Register bits
   INTCON3bits.INT2IP  = 1; //int2 external interrupt priority; 1 = high priority
   INTCON3bits.INT1IP  = 1;  //int1 external interrupt priority; 1 = high priority
   INTCON3bits.INT2IE  = 0;  //int2 external interrupt enable
   INTCON3bits.INT1IE  = 0;  //int1 external interrupt enable 
   INTCON3bits.INT2IF  = 0;  //int2 external interrupt flag
   INTCON3bits.INT1IF  = 0;  //int1 external interrupt flag
   */

   //PERIPHERAL1 Interrupt Flag Register
   /*   
   PIR1bits.ADIF    = 0; //A/D Converter flag
   PIR1bits.RCIF    = 0; //EUSART RX flag; Read only; Cleared when RCREG is read
   PIR1bits.TXIF    = 0; //EUSART TX flag; Read only; Cleared when TXREG is written
   PIR1bits.SSPIF   = 0; //Master Synchronous Serial Port Flag
   PIR1bits.CCP1IIF = 0; //CCP1 flag;
   PIR1bits.TMR2IF  = 0; //TMR2 to PR2 Match Flag
   PIR1bits.TMR1IF  = 0; //TMR1 register flag
   */  

   //PERIPHERAL2 Interrupt Flag Register
   /*
   PIR2bits.OSCIF   = 0; //Oscillator Fail flag
   PIR2bits.C1IF    = 0; //Comparator C1 flag
   PIR2bits.C2IF    = 0; //Comparator C2 flag
   PIR2bits.EEIF    = 0; //EEPROM Write flag
   PIR2bits.BCLIF   = 0; //Bus collision flag
   PIR2bits.USBIF   = 0; //USB interrupt flag
   PIR2bits.TMR3IF  = 0; //TMR3 overflow flag
   */
 
   //PERIPHERAL1 Interrupt Enable Register
   /* 
   PIE1bits.ADIE    = 0; //A/D Converter interrupt enable
   PIE1bits.RCIE    = 0; //EUSART RX flag interrupt enable
   PIE1bits.TXIE    = 0; //EUSART TX flag interrupt enable
   PIE1bits.SSPIE   = 0; //Master Synchronous Serial Port interrupt enable
   PIE1bits.CCP1IIE = 0; //CCP1 interrupt enable
   PIE1bits.TMR2IE  = 0; //TMR2 to PR2 Match interrupt enable
   PIE1bits.TMR1IE  = 0; //TMR1 register interrupt enable
   */  

   //PERIPHERAL2 Interrupt Enable Register
   /*  
   PIE2bits.OSCIE   = 0; //Oscillator Fail interrupt enable
   PIE2bits.C1IE    = 0; //Comparator C1 interrupt enable
   PIE2bits.C2IE    = 0; //Comparator C2 interrupt enable
   PIE2bits.EEIE    = 0; //EEPROM Write interrupt enable
   PIE2bits.BCLIE   = 0; //Bus collision interrupt enable
   PIE2bits.USBIE   = 0; //USB interrupt interrupt enable
   PIE2bits.TMR3IE  = 0; //TMR3 overflow interrupt enable
   */
 
   //PERIPHERAL1 Interrupt Priority Register
   /* 
   IPR1bits.ADIP    = 0; //A/D Converter interrupt priority
   IPR1bits.RCIP    = 0; //EUSART RX flag interrupt priority
   IPR1bits.TXIP    = 0; //EUSART TX flag interrupt priority
   IPR1bits.SSPIP   = 0; //Master Synchronous Serial Port interrupt priority
   IPR1bits.CCP1IP  = 0; //CCP1 interrupt priority
   IPR1bits.TMR2IP  = 0; //TMR2 to PR2 Match interrupt priority
   IPR1bits.TMR1IP  = 0; //TMR1 register interrupt priority
   */ 

   //PERIPHERAL2 Interrupt Priority Register 
   /*  
   IPR2bits.OSCIP   = 0; //Oscillator Fail interrupt enable
   IPR2bits.C1IP    = 0; //Comparator C1 interrupt enable
   IPR2bits.C2IP    = 0; //Comparator C2 interrupt enable
   IPR2bits.EEIP    = 0; //EEPROM Write interrupt enable
   IPR2bits.BCLIP   = 0; //Bus collision interrupt enable
   IPR2bits.USBIP   = 0; //USB interrupt interrupt enable
   IPR2bits.TMR3IP  = 0; //TMR3 overflow interrupt enable
   */
 
   //Interrupt on change PORTA register
   //IOCA = 0; //disable interrupt on change PORTA<5:3>, PORTA<1:0>
   //IOCB = 0; //disable interrupt on change PORTB<7:4>
}