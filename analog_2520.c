#include "system.h"

/*********************************************************************
 * Function:        	void AnalogInit(void)
 * Input:           	void
 * Output:          	void
 * Overview:        	This function initializes ADC.
 ********************************************************************/
void AnalogInit(void)
{
  //set up Vdd as positive voltage reference
  //set up Vss as negative voltage reference
  ADCON1bits.VCFG1 = 0;
  ADCON1bits.VCFG0 = 0;

  //place conversion results in least significant bits (Right Justified)
  ADCON2bits.ADFM = 1; 

  //A/D Acquistion Time Selected as 20TAD
  ADCON2bits.ACQT2 = 1; 
  ADCON2bits.ACQT1 = 1;
  ADCON2bits.ACQT0 = 1; 

  //A/D Conversion Time Clock Select bits as Fosc/64
  //From table 17-1 pg 161
  ADCON2bits.ADCS2 = 1; 
  ADCON2bits.ADCS1 = 1;
  ADCON2bits.ADCS0 = 0;
}

/*********************************************************************
 * Function:        	char getVoltage(void)
 * PreCondition:    	None
 * Input:           	None
 * Output:          	None
 * Side Effects:    	None
 * Stack Requirements:	1 level deep
 * Overview:        	This function gets the 10-bit result of A to D 
                        converter which is measuring the voltage at an
                        A2D output.
 ********************************************************************/
unsigned int getVoltage(char port)
{
  int temp1 = 0;
  int temp2 = 0;
  int result = 0;
  unsigned int output = 0;

  //select an analog channel (AN0 thru AN4)
  if( ((port >= 0) && (port <= 4)) && ((port >= 8) && (port <= 12)) )
  {
     ADCON0bits.CHS3 = (0x08 & port)/8;
     ADCON0bits.CHS2 = (0x04 & port)/4;
     ADCON0bits.CHS1 = (0x02 & port)/2;
     ADCON0bits.CHS0 = 0x01 & port;

     //set bit high to connect pin to ADC 
     switch(port)
     {
       case 0:  ADCON1  = 0b00001110;  break;
       case 1:  ADCON1  = 0b00001101;  break;
       case 2:  ADCON1  = 0b00001100;  break;
       case 3:  ADCON1  = 0b00001011;  break;
       case 4:  ADCON1  = 0b00001010;  break;
       case 8:  ADCON1  = 0b00000110;  break;
       case 9:  ADCON1  = 0b00000101;  break;
       case 10: ADCON1 =  0b00000100;  break;
       case 11: ADCON1 =  0b00000011;  break;
       case 12: ADCON1 =  0b00000010;  break;
     }
  }
  else
  {
    return 0;
  }
  
  //turn on A/D module pg 159
  ADCON0bits.ADON = 1;

  //start conversion by setting Go/Done bit pg 159
  //conversion will start after programmed acquisition (sampling) time
  //(as choosen in openA2D) is finished
  ADCON0bits.GO = 1;

  while(ADCON0bits.GO)
          ;//wait for for conversion to complete
  
  result = ADRESL; 
  temp1 = ADRESH;

  ADCON0bits.ADON = 0; //turn off A/D module

  temp2 = temp1 << 8; 
  result |= temp2;
  output = result;
  
  return output;
 }
