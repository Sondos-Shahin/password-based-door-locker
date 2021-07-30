/****************************************************************************************
 * [FILE NAME]: main_master.c
 *
 * [AUTHOR]: sondos ahmed eladl mohamed
 *
 * [DATE CREATED]: jul 17, 2021
 *
 * [Description]: Application based on ATmega16 acts as  human interface with a device
 *                connected to LCD that displays messages to the user from device and a Keypad to enter
 *                password and communicate with another MCU which controls another system
 *                using UART communication protocol.
 *****************************************************************************************/

#include "device_Functions.h"
uint8 start;// variable to check whether the external eeprom is empty or not
int main()
{
	SREG |= (1<<7);

	UART_init();

	LCD_init();

	LCD_displayString("    HELLO ");
	_delay_ms(1000);

	while(1){

		while((UART_recieveByte()!=READY));
		start=UART_recieveByte();
		LCD_clearScreen();


		if(start==first_time){

			FirstTrial();//function to store the password and to confirm it
		}

		else if(start==repeated){


					options();//function to display the options and check the password

		}





	}}
