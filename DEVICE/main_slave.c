/****************************************************************************************
 * [FILE NAME]: main_master.c
 *
 * [AUTHOR]: sondos ahmed eladl mohamed
 *
 * [DATE CREATED]: jul 17, 2021
 *
 * [Description]: Application based on ATmega16 MCU(DEVICE) control a system of
 *                a Motor act as door, Buzzer and LED (and buzzer)to make loud sound if any
 *                one try to hack the system and an external EEPROM used to store password
 *                received from HUMAN_INTERFACE using UART communication protocol
 *****************************************************************************************/

#include"device_functions.h"
                                  /*global variables*/
uint8 start=0;//used to check whether the first address in eeprom is empty or not

uint8 tick=0;//used with the timer
uint8 tick_1=0;//used with the timer

/*indicates that the password has been entered wrong for three times if it equals to 1
  and switch on the buzzer
  */
uint8 danger=0;
uint8 door=0;
Timer_Configuration timer={0, second, Timer_1, F_CPU_1024, Compare};
int main()
{  Buzzer_Init();
   Motor_Init();
SREG |= (1<<7);
UART_init();
LCD_init();
EEPROM_init();
start=0;




while(1) {
	EEPROM_readByte(FIRST_ADDRESS, &start);
	UART_sendByte(R_U_READY);// massage send to master to start the system

	/*check whether the first address in the eeprom is empty or no and send the result to the master */
	if(start==0xFF){UART_sendByte(first_time);}else{UART_sendByte(repeated);}


	if(start==0XFF){

		FirstTrial();// a function that receive the first address and store it then go to options


	}
	else{
        _delay_ms(1000);
        /*a function that receive orders from the master (the option choice)then receive
           password to check with the stored one
          */
		options();



	}

}}
