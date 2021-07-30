/**********************************************************************************
 * [FILE NAME]: device_functions.c
 *
 * [AUTHOR]: sondos ahmed eladl mohamed
 *
 * [DATE CREATED]: jul 17, 2021
 *
 * [Description]: File contain functions will be used
 *                in the applications for HUMAN_INTERFACE.
 *
 ***********************************************************************************/
#include "device_Functions.h"



/************************************************************************************************
 *                                    device_Functions
 ************************************************************************************************/


/***************************************************************************************************
 * [Function Name]: FirstTrial
 *
 * [Description]:  a function to store the first password and to confirm it the continue the system
 *
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           none
 *
 * [Returns]:     none
 ***************************************************************************************************/



void FirstTrial()
{
	Store_Password();
	LCD_clearScreen();
	while( (UART_recieveByte()!=READY));
	//LCD_displayString("    saved");
	_delay_ms(500);
	LCD_clearScreen();
	FirstTrial_1();
}


/***************************************************************************************************
 * [Function Name]: Store_Password
 *
 * [Description]:  a function that stores the password of the first time and put it in the first address
 *
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           none
 *
 * [Returns]:     none
 ***************************************************************************************************/


void Store_Password(){

	LCD_displayString("enter your first ");
	LCD_goToRowColumn(1,2);
	LCD_displayString(" password");
	_delay_ms(1000);
	LCD_clearScreen();
	uint8 i=0;
	uint8 key=0;
	while(i<=(password_length-1)){
		key = KeyPad_getPressedKey();
		LCD_intgerToString(key);
		_delay_ms(300);
		LCD_goToRowColumn(0,i);
		LCD_displayCharacter('*');
		while(UART_recieveByte()!=READY);
		UART_sendByte(key);

		i++;

	}
}


/***************************************************************************************************
 * [Function Name]: FirstTrial_1
 *
 * [Description]:  a function that is used in other function (FirstTrial)
 *
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           none
 *
 * [Returns]:     none
 ***************************************************************************************************/


void FirstTrial_1(){
	uint8 check=confirm();
	switch(check)
	{
	case match:
		LCD_clearScreen();
		LCD_displayString("   saved");
		_delay_ms(1000);
		LCD_clearScreen();
		while(UART_recieveByte()!=READY);
		options();
		break;
	case missmatch:
		LCD_clearScreen();
		LCD_displayString("   mismatch");
		_delay_ms(1000);
		LCD_clearScreen();
		FirstTrial();

		break;
	}
}




/***************************************************************************************************
 * [Function Name]: confirm
 *
 * [Description]:  a function that confirms the entered password with the first one in the first trial
 *                 to save it if matched or re-write the first password again
 *
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           none
 *
 * [Returns]:      value that decides whether the first password is saved or not
 ***************************************************************************************************/



uint8 confirm()
{

	LCD_displayString("confirm password ");
	_delay_ms(1000);
	LCD_clearScreen();
	uint8 i=0;
	uint8 key=0;
	while(i<=(password_length-1)){
		key = KeyPad_getPressedKey();
		LCD_intgerToString(key);
		_delay_ms(300);
		LCD_goToRowColumn(0,i);
		LCD_displayCharacter('*');
		while(UART_recieveByte()!=READY);
		UART_sendByte(key);

		i++;
	}


	return 	UART_recieveByte();
}



/***************************************************************************************************
 * [Function Name]: Check_password
 *
 * [Description]:  a function that checks the entered password with the stored one
 *                 and returns whether the are matched or not
 *
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           none
 *
 * [Returns]:     value that decides whether the enterd password and the stored one are matched or not
 ***************************************************************************************************/


uint8 Check_password(){

	LCD_displayString("enter password ");
	_delay_ms(1000);
	LCD_clearScreen();
	uint8 i=0;
	uint8 key=0;
	while(i<=(password_length-1)){
		key = KeyPad_getPressedKey();
		LCD_intgerToString(key);
		_delay_ms(300);
		LCD_goToRowColumn(0,i);
		LCD_displayCharacter('*');
		while(UART_recieveByte()!=READY);
		UART_sendByte(key);

		i++;
	}


	return 	UART_recieveByte();
}



/***************************************************************************************************
 * [Function Name]: options
 *
 * [Description]:  a function to display the options and decide by checking the entered password
 *
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           none
 *
 * [Returns]:     none
 ***************************************************************************************************/


void options(){

	uint8 ch;
	LCD_displayString("1)open door");
	LCD_goToRowColumn(1,0);
	LCD_displayString("2)change password");
	uint8 key;
	key = KeyPad_getPressedKey();
	UART_sendByte(READY);
	UART_sendByte(key);

	if(key==1)

	{
ch=one();
if(ch==match)
{open();}
else
{
	            LCD_clearScreen();
				LCD_displayString("wrong password ");
				_delay_ms(1000);
				LCD_clearScreen();

ch=one();
if(ch==match)
{open();}
else
{
	LCD_clearScreen();
			LCD_displayString("wrong password ");
			_delay_ms(1000);
			LCD_clearScreen();
ch=one();

if(ch==match)
{open();}
else
{LCD_clearScreen();
LCD_displayString("    worning");
while(UART_recieveByte()!=Safe);
LCD_clearScreen();
options();}

}
}
}

	else if(key==2)
	{
		ch=one();
		if(ch==match)
		{FirstTrial();}
		else
		{
			            LCD_clearScreen();
						LCD_displayString("wrong password ");
						_delay_ms(1000);
						LCD_clearScreen();

		ch=one();
		if(ch==match)
		{FirstTrial();}
		else
		{
			LCD_clearScreen();
					LCD_displayString("wrong password ");
					_delay_ms(1000);
					LCD_clearScreen();
		ch=one();

		if(ch==match)
		{FirstTrial();}
		else
		{LCD_clearScreen();
		LCD_displayString("    worning");
		while(UART_recieveByte()!=Safe);
		LCD_clearScreen();
		options();}

		}
		}
		}





	else{
		LCD_clearScreen();
							LCD_displayString("invaled option");
							_delay_ms(1000);
							LCD_clearScreen();



		options();}


	}



/***************************************************************************************************
 * [Function Name]: open
 *
 * [Description]:  a function to open the door (motor on/off and stop) by sending order to slave(the other MCU)
 *
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           none
 *
 * [Returns]:     none
 ***************************************************************************************************/


void open()
{
	_delay_ms(500);
	LCD_clearScreen();
	LCD_displayString("  opening door");
	UART_sendByte(READY);
	while(UART_recieveByte()!=READY);
	LCD_clearScreen();
	LCD_displayString("     pass");
	while(UART_recieveByte()!=READY);
	LCD_clearScreen();
	LCD_displayString("  closing door");
	while(UART_recieveByte()!=go_options);
	_delay_ms(1000);
	LCD_clearScreen();
	options();
}


/***************************************************************************************************
 * [Function Name]: one
 *
 * [Description]:  a function that is used in other function (options)
 *
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           unsigned char
 *
 * [Returns]:     result of comparing entered password with the stored one
 ***************************************************************************************************/


uint8 one()
{       uint8 ch;
		LCD_clearScreen();
		LCD_displayString("enter password ");
		_delay_ms(1000);
		LCD_clearScreen();
		uint8 i=0;
		uint8 key=0;
		while(i<=(password_length-1)){
			key = KeyPad_getPressedKey();
			LCD_intgerToString(key);
			_delay_ms(300);
			LCD_goToRowColumn(0,i);
			LCD_displayCharacter('*');
			while(UART_recieveByte()!=READY);
					UART_sendByte(key);

			i++;
		}
		while(UART_recieveByte()!=READY);
		ch=UART_recieveByte();
		LCD_clearScreen();

return ch;
	}
