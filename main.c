
/*********************************************************************
 * TITLE - WS2812 Led Controller using PIC18F2520
 * FileName:        main.c
 * Version:         1.0
 * Overview:
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Charles D	  June. 16,2013	     Original Release
 *
 ********************************************************************/

#include "system.h"

#pragma config OSC = HS //For using internal oscillator
//#pragma config HFOFST = ON
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config MCLRE = ON
#pragma config PBADEN = OFF
#pragma config CPD = OFF // eeprom code protection off
#pragma config WRTD = OFF // eeprom write protection off

//Global Variables
//============================
#define BUF_SIZE 64
#define GEN_BUF_SIZE 8
#define MAX_ALARM_SET_TIMES 8

#define MAX_TIME_OFF 43200 //set to 12 hours.
#define MAX_TIME_ON 600  //set to 10 mins.

#define TIME_ON_MODE 1
#define TIME_OFF_MODE 2

char RX_BUFFER[BUF_SIZE];
unsigned char RX_INDEX = 0;
unsigned char RX_CHAR = 0x00;

extern unsigned char CUR_ROW;
extern unsigned char CUR_COL;

unsigned char TimeOnMsg[] = " On Time: 00:00";
unsigned char TimeOffMsg[] = "Off Time: 00:00";

unsigned int TIME_ON = 60;
unsigned int TIME_OFF = 3600;
unsigned int CUR_TIME_ON = 60;
unsigned int CUR_TIME_OFF = 3600;

char PROGRAM_STATE = 2;  //start program in TIME_OFF_MODE on power up

unsigned int LOOP_CNT = 0;

void highPriInt_handler(void);

//setting up interrupt vectors is in C18 user guide
#pragma code high_vector_section = 0x8
void high_vector (void)
{
 _asm goto highPriInt_handler _endasm
}
#pragma code


#pragma interrupt highPriInt_handler
void highPriInt_handler (void)
{
   //if uart rx interrupt
   if(PIR1bits.RCIF)
   {
     //check for buffer errors
     if(RCSTAbits.OERR || RCSTAbits.FERR)
     {
       //Overrun error bit; 1 = Error; Read only; Cleared by clearing CREN bit, 3rd byte into 2-byte buffer
       //Framing error bit; 1 = Error; Read only; Stop bit was not seen.; Cleared by clearing SPEN bit

       //clear framing error by clearing SPEN bit see pg. 239 of manual, will also clear an OERR
       RCSTAbits.SPEN = 0;
       Nop();
       RCSTAbits.SPEN = 1; //enable UART again after clearing overrun error

       //clear overrun error by clearing CREN bit see pg. 239 of manual
       //RCSTAbits.CREN = 0;
       //Nop();
       //RCSTAbits.CREN = 1; //enable receiver again after clearing overrun error
     }

     //read byte from USART
     RX_CHAR = readUart();
     RX_BUFFER[RX_INDEX] = RX_CHAR; //put valid byte into circular buffer
     RX_INDEX = (RX_INDEX+1)% BUF_SIZE;
   }
}
#pragma code

//store serial number into data eeprom memory
#pragma romdata eedata = 0xF00000
const rom char serialNumber[]= {0x00,0x00,0x00,0x00,0x00,0x0,0x4F};
#pragma romdata

void main(void)
{
   char but = 0;
   unsigned char OlimexMsg[] = "Hi Kimmie!";

   configuration();

    //write default settings to memory if not already there
    if(eeprom_read(0x00) != 0x40)
    {
      mSecDelay(100);
      eepromWriteInt(0x01, TIME_ON);
      mSecDelay(100);
      eepromWriteInt(0x03, TIME_OFF);
      mSecDelay(100);
 
      eeprom_write(0x00, 0x40);  //show that initial settings have been written to memory
    }

    //get settings from memory
    TIME_ON = eepromReadInt(0x01);
    mSecDelay(100);
    TIME_OFF  = eepromReadInt(0x03);
    mSecDelay(100);

    if((TIME_ON >0) && (TIME_OFF>0))
    {
      CUR_TIME_ON = TIME_ON;
      CUR_TIME_OFF = TIME_OFF;
    }
    
   LCDSendCmd(1);
   LCDwriteLine(0, 0, OlimexMsg);
   mSecDelay(1000);

   LCDSendCmd(1);
   LCDwriteLine(0, 0, TimeOnMsg);
   LCDwriteLine(1, 0, TimeOffMsg);
   LCDSendCmd(0x0F); //show cursor

   outputTimeOff(TIME_OFF);
   outputTimeOn(TIME_ON);
   relayOnOff(0); // turn relay off
   LCDSendCmd(0x0C); //turn off cursor

  while(1)
  {
   but = ButtonScan();

   switch (but)
        {
            case 1: //button 1 -- UP

                if(PROGRAM_STATE == 0)
                {
                  if(CUR_ROW == 1)
                  {
                      TIME_OFF = (TIME_OFF + 1800) % 45000; //increment in 30 minute intervals, max of 12 hrs
                      CUR_TIME_OFF = TIME_OFF;
                      outputTimeOff(TIME_OFF);
                  }
                  else
                  {
                      TIME_ON = (TIME_ON + 30) % 630; //increment in 30 second intervals, max of 10 minutes
                      CUR_TIME_ON = TIME_ON;
                      outputTimeOn(TIME_ON);
                  }
                  Beep2();
                }
                break;
                
            case 3: //button 2 -- CENTER
                /* does not work */
                break;

            case 5: //button 3 -- LEFT

                if( PROGRAM_STATE == 0 )
                {
                  if((TIME_OFF>0) && (TIME_ON>0))
                  {
                    PROGRAM_STATE = TIME_ON_MODE; //start current program
                    relayOnOff(1); // turn relay on
                    LCDSendCmd(0x0C); //turn off cursor

                    //write settings to memory
                    mSecDelay(300);
                    eepromWriteInt(0x01, TIME_ON);
                    eepromWriteInt(0x03, TIME_OFF);
                    mSecDelay(300);
                  }
                }
                else if( PROGRAM_STATE !=0 )  // stop current program, reset timers
                {
                    PROGRAM_STATE = 0;
                    CUR_TIME_ON = TIME_ON;
                    CUR_TIME_OFF = TIME_OFF;
                    outputTimeOff(TIME_OFF);
                    outputTimeOn(TIME_ON);
                    relayOnOff(0); // turn relay off
                    LCDSendCmd(0x0F); //show cursor
                    LCDcursorPos(1, 15);
                }

                break;

            case 7: //button 4 -- RIGHT -- toggle between rows
              
                if(CUR_ROW == 1)
                {
                    LCDcursorPos(0, 15);
                    Beep1();
                }
                else
                {
                    LCDcursorPos(1, 15);
                    Beep1();
                }
               
                break;

            case 9:
                if (PROGRAM_STATE == 0)
                {
                    if (CUR_ROW == 1)
                    {
                        TIME_OFF = TIME_OFF - 1800; //increment in 30 minute intervals
                        if (TIME_OFF > 45000) TIME_OFF = 43200; //set to 12 hrs
                        CUR_TIME_OFF = TIME_OFF;
                        outputTimeOff(TIME_OFF);
                    }
                    else
                    {
                        TIME_ON = TIME_ON - 30; //increment in 30 second intervals
                        if (TIME_ON > 630) TIME_ON = 600; //set to 10 mins.
                        CUR_TIME_ON = TIME_ON;
                        outputTimeOn(TIME_ON);
                    }

                    Beep2();
                }
                break;

            case 11: /* Does not work */
                Beep1(); 
                break;
        }

   //handle current PROGRAM STATE
   if((LOOP_CNT % 10 == 0) && (PROGRAM_STATE)) //every second
   {
       if(PROGRAM_STATE == TIME_ON_MODE)
       {
           CUR_TIME_ON--;
           if((CUR_TIME_ON == 0) || (CUR_TIME_ON > 630))
           {
               PROGRAM_STATE = TIME_OFF_MODE;
               CUR_TIME_ON = TIME_ON;
               relayOnOff(0); // turn relay off
           }
           outputTimeOn(CUR_TIME_ON);
       }
       else if(PROGRAM_STATE == TIME_OFF_MODE)
       {
           CUR_TIME_OFF--;
           if((CUR_TIME_OFF <= 0)  || (CUR_TIME_OFF > 45000))
           {
               PROGRAM_STATE = TIME_ON_MODE;
               CUR_TIME_OFF = TIME_OFF;
               relayOnOff(1); //turn relay on
           }
           outputTimeOff(CUR_TIME_OFF);
       }
       else
       {
           PROGRAM_STATE = 0;
           relayOnOff(0); // turn relay off
       }
   }

   // Toggle led
   if(PROGRAM_STATE == 0)ledOnOff(0);//turn off led}
   if(PROGRAM_STATE) PORTB ^= 0x10;

   LOOP_CNT++;
   mSecDelay(100);
    
  }
}// end main()

/*********************************************************************
 * Function:        	void Configuration(void)
 * PreCondition:    	None
 * Input:           	None
 * Output:          	None
 * Side Effects:    	None
 * Stack Requirements:	1 level deep
 * Overview:        	This function initialises configuration bits
 *                      in the 14k50.
 ********************************************************************/
void configuration(void)
{
    //clear PIC ports
    //portReset();

    //set up oscillator

    //select device enters sleep on "sleep" instruction
    //OSCCONbits.IDLEN = 0;
    //select 16Mhz oscillator speed
    //OSCCONbits.IRCF0 = 1;
    //OSCCONbits.IRCF1 = 1;
    //OSCCONbits.IRCF2 = 1;
    //select primary oscillator
    //OSCCONbits.SCS0  = 0;
    //OSCCONbits.SCS1  = 0;
   //enable PLL for 4X internal oscillator,
   //must enable PLL AFTER selecting oscillator
   //speed and primary source
    //OSCTUNEbits.PLLEN = 1;


    //set all A/D ports as digital to start
    ADCON1bits.PCFG3 = 1;
    ADCON1bits.PCFG2 = 1;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG0 = 1;

    TRISA = 0xFF;  //0 = output, 1 = input
    TRISB = 0xFF;
    TRISC = 0xFF;

    //setup interrupts
    InterruptInit();

    //setup 9.6k baud uart
    //initUart(0);

    //setup LCD
    InitLCD();

    initButtons();

    //setup ADC
    //AnalogInit();

    //initialize/start timer1
    //Timer0Init();

}


void outputTimeOff(unsigned int inputSecs)
{
    char tensHrsCol = 0;
    char onesHrsCol = 0;
    char tensMinCol = 0;
    char onesMinCol = 0;

    if(inputSecs > 43200) return; //max of 12 hrs

    tensHrsCol = (inputSecs/36000) + 48;
    onesHrsCol = ((inputSecs % 36000)/3600) + 48;
    tensMinCol = ((inputSecs % 3600)/600) + 48;
    onesMinCol = ((inputSecs % 600)/60) + 48;

    TimeOffMsg[10] = tensHrsCol;
    TimeOffMsg[11] = onesHrsCol;
    TimeOffMsg[12] = ':';
    TimeOffMsg[13] = tensMinCol;
    TimeOffMsg[14] = onesMinCol;

    LCDwriteLine(1, 0, TimeOffMsg);
    
    //unsigned char TimeOffMsg[] = "Off Time: 00:00";
}

void outputTimeOn(unsigned int inputSecs)
{
    char tensMinCol = 0;
    char onesMinCol = 0;
    char tensSecCol = 0;
    char onesSecCol = 0;

    if(inputSecs > 600) return; //max of 10 mins.

    tensMinCol = (inputSecs/600) + 48;
    onesMinCol = ((inputSecs % 600)/60) + 48;
    tensSecCol = ((inputSecs % 60)/10) + 48;
    onesSecCol = (inputSecs % 10) + 48;

    TimeOnMsg[10] = tensMinCol;
    TimeOnMsg[11] = onesMinCol;
    TimeOnMsg[12] = ':';
    TimeOnMsg[13] = tensSecCol;
    TimeOnMsg[14] = onesSecCol;

    LCDwriteLine(0, 0, TimeOnMsg); 
}


/*********************************************************************
 * Function:        	void mSecDelay(unsigned int)
 * Input:           	unsigned int
 * Overview:        	This function delays program execution for given
 *                      number of thousanths of a second.
 ********************************************************************/
void mSecDelay(unsigned int secs)
{
   unsigned int counter = 0;

   for (counter = 0; counter < secs; counter ++)
   {
      //Delay10KTCYx(2);  // 1 TCY cycle is 0.5uS ---Fosc = 8Mhz, Fcy = 2Mhz
                          // 1 Delay1KTCYx ---> 1000 * TCY ---> .0005 sec delay
                          // (2) corresponds to about .001 sec delay

      //Delay1KTCYx(8);    //for Fosc = 32Mhz

      Delay1KTCYx(5);    // 1 TCY cycle is 0.2uS --- Fosc = 20Mhz, Fcy = 5Mhz
                          // 1 Delay1KTCYx ---> 1000 * TCY ---> .0002 sec delay
                          // (5) corresponds to .001 sec delay
   }
}


/*********************************************************************
 * Function:        	void uSecDelay(unsigned int)
 * Input:           	unsigned int
 * Overview:        	This function delays program execution for given
 *                      number of millionths of a second.
 ********************************************************************/
void uSecDelay(unsigned int secs)
{
   unsigned int counter = 0;

   for (counter = 0; counter < secs; counter ++)
   {
      Delay1TCY();       // 1 TCY cycle is 0.2uS --- Fosc = 20Mhz, Fcy = 5Mhz
      Delay1TCY();       // (5) corresponds to 1 uSec delay
      Delay1TCY();
      Delay1TCY();
      Delay1TCY();
   }
}

/*********************************************************************
 * Function:        	get_edata(unsigned char)
 * Input:           	void
 * Output:          	void
 * Overview:        	Returns an integer(2-byte) from
 *                      the onboard eeprom starting at e_address
 *                      (hi - lo byte order)
 ********************************************************************/
unsigned int get_edata (unsigned char e_address)
{
	unsigned char LSByte,MSByte;
	unsigned int value;

    LSByte = eeprom_read(e_address+1);	//get lo byte first
	MSByte = eeprom_read(e_address);		//get hi byte
    value = MSByte *16; //shifts MSByte 4 times
    value |= LSByte;    //converts lo/hi bytes into a 2-byte integer

	return value;
}
/*********************************************************************
 * Function:        	void put_edata(void)
 * Input:           	void
 * Output:          	void
 * Overview:        	Writes an integer(2-byte) to
 *                      the onboard eeprom starting at e_address
 *                      (hi - lo byte order)
 ********************************************************************/
void put_edata (unsigned char e_address, unsigned int value)
{
	unsigned char e_data=0;
	e_data = (unsigned char)value; //put low byte into e_data
    eeprom_write(e_address+1, e_data );
	e_data = (unsigned char)(value >> 8);  //put high byte into e_data
    eeprom_write(e_address, e_data);
}

/*********************************************************************
 * Function:        	void onboard_eeread(void)
 * Input:           	void
 * Output:          	void
 * Overview:            Reads one byte from the onboard eeprom
 *                      at e_address up to 256
 ********************************************************************/
 unsigned char eeprom_read(unsigned char e_address)
{
      //Disable all high priority interrutpts
	  INTCONbits.GIEH = 0;

      //EEADRH = 0; //unused high address byte
      EEADR = e_address;  //place address to be read from in pointer
      EECON1bits.EEPGD = 0; //point to data memory, not program memory pg 68
      EECON1bits.CFGS  = 0; //read from Program or Data memory, not configuration memory
      EECON1bits.RD = 1;   //initiate a data EEPROM read cycle, and wait till done

      while(EECON1bits.RD)
	         ;//wait for read to complete

      //Enable all high priority interrutpts
	  INTCONbits.GIEH = 1;

  return EEDATA;
}

/*********************************************************************
 * Function:        	void onboard_eewrite(void)
 * Input:           	void
 * Output:          	void
 * Overview:            Write e_data byte to the onboard eeprom at
 *                      e_address up to 256. Can write EEPROM in
 *                      single bytes. No pre-erasure required.
 ********************************************************************/
void eeprom_write(unsigned char e_address, unsigned char e_data)
{
      EECON1bits.WRERR = 0; //clear write error bit

      //EEADRH = 0; //unused high address byte
      EEADR = e_address;  //place address to be written to in pointer
      EEDATA = e_data;    //place byte to be written in writer

      EECON1bits.EEPGD = 0; //point to data memory, not program memory pg 68
      EECON1bits.CFGS  = 0; //writes to Program or Data memory, not configuration memory
      //EECON1bits.FREE  = 0; //perform write only not row erase, default is 0
      EECON1bits.WREN = 1; //enable EEPROM writing

      //Disable all high priority interrutpts
	  INTCONbits.GIEH = 0;

      //required sequence pg 75
	  EECON2 = 0x55;
	  EECON2 = 0xAA;
	  EECON1bits.WR = 1;   //initiate a data EEPROM write cycle, and wait till done

       while(EECON1bits.WR)
	         ;//wait for write to complete

      //PIR2bits.EEIF = 0; //clear write complete interrupt bit ?? pg 69

      //Enable all high priority interrutpts
	  INTCONbits.GIEH = 1;

	  EECON1bits.WREN = 0; //disable EEPROM writing
}

/*********************************************************************
 * Function:        	void eepromReadInt(void)
 * Input:           	void
 * Output:          	void
 * Overview:        	This function reads two consecutive bytes
 *                      from eeprom memory. It reads addr and addr+1.
 ********************************************************************/
unsigned int eepromReadInt(unsigned char address)
{
  unsigned char LSByte = 0;
  unsigned char MSByte = 0;
  unsigned int cInt = 0;

  MSByte = eeprom_read(address);
  LSByte = eeprom_read(address+1);

  cInt = MSByte;
  cInt = cInt << 8;
  cInt = cInt | LSByte;

  return cInt;
}

/*********************************************************************
 * Function:        	void eepromWriteInt(int, unsigned char)
 * Input:           	int, unsigned char
 * Output:          	void
 * Overview:        	This function writes two consecutive bytes
 *                      to eeprom memory. It writes addr and addr+1.
 ********************************************************************/
void eepromWriteInt(unsigned char address, unsigned int data)
{
  unsigned char LSByte = 0;
  unsigned char MSByte = 0;

  LSByte = (unsigned char)data;
  MSByte = (unsigned char)(data >> 8);

  eeprom_write(address, MSByte);
  eeprom_write(address+1, LSByte);
}

/*********************************************************************
 * Function:            void int2Hex(void)
 * Input:               void
 * Output:              void
 * Overview:            This function converts an unsigned int to a
 *                      four byte ascii hex.
 ********************************************************************/
void int2Hex(unsigned int data, char * nib)
{
   char i = 0;
   //char HEX_DATA = {'0','0','0','0'};

   nib[3] = data & 0x000F;     //LSB
   nib[2] = (data & 0x00F0)/16;
   nib[1] = (data & 0x0F00)/256;
   nib[0] = (data & 0xF000)/4096; //MSB

   for(i=0;i<4;i++)
   {
      if(nib[i]<=9)
      {
         nib[i] = nib[i]+ '0';
      }
      else
      {
         nib[i] = nib[i] + 55;
      }
   }

}

/*********************************************************************
 * Function:            void hex2Int(void)
 * Input:               void
 * Output:              void
 * Overview:            This function converts a 4 ascii byte
 *                      representation of a 4 char hex number to
 *                      an integer.
 ********************************************************************/
unsigned int hex2Int(char * nib)
{
   char i = 0;
   unsigned int data[] = {0,0,0,0};
   unsigned int totalInt = 0;

   for(i=0;i<4;i++)
   {
      if( ((nib[i]-55) >= -7) && ((nib[i]-55) <=2) ) //this is a 0-9 char
      {
         data[i] = nib[i]- '0';
      }
      else if ( ((nib[i]-55) >= 10) && ((nib[i]-55) <=15))  //this is an A-F char
      {
         data[i] = nib[i] - 55;
      }
   }

   totalInt = (data[0]*4096) + (data[1]*256) + (data[2]*16) + data[3];

   return totalInt;
}

/*********************************************************************
 * Function:            unsigned getChecksum(void)
 * PreCondition:        None
 * Input:               None
 * Output:              None
 * Side Effects:        None
 * Stack Requirements:  1 level deep
 * Overview:            This function returns XOR checksum of data
 *                      XOR is the odd function, high when odd inputs
 ********************************************************************/
char getChecksum(unsigned char* data)
{
  int i = 2;
  unsigned char buf[10];
  unsigned char result = 0;

  result = data[1];

  while( (data[i] != '*')  && (i<BUF_SIZE) )
  {
     result = result ^ data[i];
     i++;
  }

  return result;
}





