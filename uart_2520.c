#include "system.h"

#define BUF_SIZE 64
extern unsigned char RX_BUFFER[];  //is defined in main.c
extern unsigned char RX_INDEX;
extern unsigned char RX_CHAR;


/*********************************************************************
 * Function:        	unsigned char UartInit(void)
 * Input:           	unsigned char
 * Output:          	void
 * Overview:        	This function initializes the uart. 
 *
 ********************************************************************/
void initUart(unsigned char baud)
{ 
  //Set up baud rate; See page 189 of 14K50 data sheet

 /* 
  //set up USART for Async, 8 bits, 1 stop bit, 9600, No Parity
    OpenUSART( USART_TX_INT_OFF  &
               USART_RX_INT_OFF  & 
               USART_ASYNCH_MODE & 
               USART_EIGHT_BIT   & 
               USART_CONT_RX     & 
               USART_BRGH_HIGH, 
               51 );
   */

  TRISCbits.TRISC6 = 0;  //TX pin as output
  TRISCbits.TRISC7 = 0;  //RX pin as input

  switch (baud)
  {
    case 0:
            SPBRG = 51;  //9600 baud --->Fosc = 32Mhz
            SPBRGH = 0;   
            TXSTAbits.BRGH = 0;
            BAUDCONbits.BRG16 = 0;  //16-bit baudrate Generator; 0 = 8-bit rate generator; 1 = 16-bit
    break;


    default:
             SPBRG = 51;  //9600 baud --->Fosc = 32Mhz, BRG16 = 0, BRGH = 0
             SPBRGH = 0; 
             TXSTAbits.BRGH = 0;
             BAUDCONbits.BRG16 = 0;  
    break;
  }

  TXSTAbits.SYNC    = 0;  //EUSART Mode Select; 0 = async; 1 = sync
  RCSTAbits.SPEN    = 1;  //Serial Port Enable bit;  0 = disable; Configures RX/TX pins as uart
  TXSTAbits. TX9D   = 0;  //Bit transmission enable bit; 0 = 8-bit; 1 = 9-bit
  //BAUDCONbits.SCKP = 0;   //Asynchronous Clock/Transmit Polarity Select; 0 = TX Idle state is high
  TXSTAbits.TXEN    = 1;  //Transmission enable bit; 0= disabled
  RCSTAbits.CREN    = 1;  //Reciever enable bit; 0 = disable;


  //BAUDCONbits.ABDEN = 0;  //Auto-baud Detect Enable Bit; 0 = disable; async mode only
  //BAUDCONbits.WUE   = 0;  //Wake up Enable Bit; 0 = normal operation; 1 = wake up on rx; async mode only
  
  //BAUDCONbits.DTRXP = 0;  //Data/RX Polarity Select; 0 = RX data not inverted (active high)
  //BAUDCONbits.RCIDL;      //RX idle flag bit; 1 =  Reciever is idle; Read only
  //BAUDCONbits.ABDOVF;     //Auto-baud Detect Overflow Bit; 1 = Auto-baud timer overflow; Read only; async mode only
  
  //TXSTAbits.CSRC   = 0;  //Clock source for synchronous mode   
  //TXSTAbits.SENDB  = 0;  //Send Break Char Bit; async mode only; 0 = no break char
  //TXSTAbits.TRMT;        //transmit shift register status bit; 0 = empty, 1 =  full; Is read only.
  //TXSTAbits.TX9    = 0;  //Ninth Transmit Bit; This is bit sent if using 9-bit mode
  
  //set up RX pin
  //RCSTAbits.RX9D;       //Ninth recieve bit; Is the ninth bit recieved if using 9-bit mode
  //RCSTAbits.OERR;       //Overrun error bit; 1 = Error; Read only; Cleared by clearing CREN bit
  //RCSTAbits.FERR;       //Framing error bit; 1 = Error; Read only; Refreshed by reading RCREG register
  //RCSTAbits.ADDEN  = 0;  //Address detect enable bit; Only used in 9-bit mode (RX9=1)  
  //RCSTAbits.SREN   = 1;  //Single recieve enable bit;  0 = disable; Only used in sync mode
  //RCSTAbits.RX9    = 0;  //8/9-bit recieve enable; 0 = 8-bit, 1 = 9-bit;  

}

/*********************************************************************
 * Function:        	void writeUart(unsigned char character)
 * PreCondition:    	init(), initUart()
 * Input:           	unsigned char
 * Output:          	None
 * Overview:        	This function prints a character to the uart.
 ********************************************************************/
void writeUart(unsigned char character)
{
   while(!PIR1bits.TXIF);//wait for TXREG register to be empty
   TXREG = character;
}


/*********************************************************************
 * Function:        	unsigned char readUart(void)
 * PreCondition:    	init(), initUart()
 * Input:           	None
 * Output:          	unsigned char
 * Overview:        	This function gets a charcter from
 *                      the rx register.
 ********************************************************************/
unsigned char readUart(void)
{
  return RCREG;
}

/*********************************************************************
 * Function:        	void flushRxBuffer(void)
 * Input:           	void
 * Output:          	void
 * Overview:        	This function clears the RX_BUFFER by setting
                        all elements equal to NULL.
 ********************************************************************/
void flushRxBuffer(void)
{
  int i = 0;

  for(i = 0; i< BUF_SIZE; i++)
  {
     RX_BUFFER[i] = 0x00;
  }

  RX_CHAR  = 0;
  RX_INDEX = 0;
}

/*****************************************************************************
 * Function: writeUartString
 * Precondition: uartInit() must be called before.
 * Overview: This function outputs a string to the UART.
 * Input: Binary data.
 * Output: None.
 *
 *****************************************************************************/
void writeUartString(char* strToSend)
{
  int i = 1;
  
  while( i < BUF_SIZE && i <= strToSend[0] )
  {
     writeUart( strToSend[i] );
     //hundrethSecDelay(10);
     i++;
  }

}

/*****************************************************************************
 * Function:         writeUartConstString
 * Precondition:     uartInit() must be called before.
 * Overview:         This function outputs a constant string to the UART.
 * Input:            Const string. ex/ "Get Money"
 * Output:           None.
 *
 *****************************************************************************/
void writeUartConstString(const far rom char* strToSend)
{
  int i = 0;
  
 //putrsUSART (strToSend); //works but putrsUSART adds null to end of string, and need to include <usart.h>

  while( strToSend[i] != 0x00 )
  {   
     while(!PIR1bits.TXIF);//wait for TXREG register to be empty
     TXREG = strToSend[i++];
  }
}

/*********************************************************************
 * Function:        	char parseRxBuffer(char *)
 * Input:           	char *
 * Output:          	char
 * Overview:        	This function checks for a given character array
 *                      in the rx buffer.  If the array is found this 
 *                      function returns true, otherwise it returns
 *                      false.
 ********************************************************************/
char parseRxBuffer(char* strToRx)
{
  int i = 1;

  for(i=1; i <= strToRx[0]; i++)
  {
    if( RX_BUFFER[i-1] == strToRx[i])
     ;//do nothing
    else 
    { 
        return 0x00; //returns false i.e. no match
    }
  }

  return 0xFF;
}

/*********************************************************************
 * Function:        	char getRxResponse(char* delim)
 * Input:           	char * -- a null terminated string of delimiters
 * Output:          	char
 * Overview:        	This function gets a delimited response. If
 *                      none is found then null is returned.
 ********************************************************************/
/*
char* getRxResponse(char* delim)
{
  char* word;
  word = strtok(RX_BUFFER, delim);

  return word;
}
*/
/*********************************************************************
 * Function:        	void debugRxBuffer(void)
 * Input:           	None
 * Output:          	None
 * Overview:        	This function prints out the receive buffer.
 ********************************************************************/
/*
void debugRxBuffer(void)
{
  unsigned char i=0;
 
  writeUart('?');

  for(i=0; i<BUF_SIZE; i++)
   writeUart(RX_BUFFER[i]);

  writeUart('*');
}
*/