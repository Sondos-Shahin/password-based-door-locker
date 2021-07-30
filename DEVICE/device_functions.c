/**********************************************************************************
 * [FILE NAME]: device_functions.c
 *
 * [AUTHOR]: sondos ahmed eladl mohamed
 *
 * [DATE CREATED]: jul 17, 2021
 *
 * [Description]: Functions will be used in  DEVICE.
 *
 ***********************************************************************************/

#include"device_functions.h"



uint8 password_1=5;
uint8 password_2=5;
uint8 pass[password_length];
uint8 misses=0;
uint8 enter=0;


extern tick;
extern timer;
extern danger;
extern door;
extern tick_1;

/***************************************************************************************************
 * [Function Name]: FirstTrial
 *
 * [Description]:  a function enter the first password and confirm it then store it as the default
 *                 password and then continue the system
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

	uint8 count=0;
	for(count=0;count<(password_length);count++){
		UART_sendByte(R_U_READY);
		pass[count]= UART_recieveByte();
		_delay_ms(100);
	}
	UART_sendByte(R_U_READY);

		_delay_ms(500);
		uint8 same=0;
			for(count=0;count<(password_length);count++){

				UART_sendByte(R_U_READY);
				password_2= UART_recieveByte();

				if(pass[count]==password_2){same++;}
			}
			if(same==5)
			{UART_sendByte(match);

				_delay_ms(1000);


                 count=0;
				for(count=0;count<(password_length);count++){
					EEPROM_writeByte( (FIRST_ADDRESS+count)  , pass[count]);
					_delay_ms(100);
				}
				UART_sendByte(R_U_READY);
				options();
			}
			else
			{UART_sendByte(missmatch);
				LCD_clearScreen();
						LCD_displayString("   mismatch");
						_delay_ms(1000);
						LCD_clearScreen();
						FirstTrial();
			}
}


/***************************************************************************************************
 * [Function Name]: options
 *
 * [Description]:  a function that receives orders from the master and controls
 *                 the slaves external peripherals to execute these orders
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
	uint8 key;
	while(UART_recieveByte()!=R_U_READY);
		key=UART_recieveByte();

	if(key==1)

	{
		ch=Check_password();
		if(ch==match)
		{open();}
		else
		{
			           wrong();

		ch=Check_password();
		if(ch==match)
		{open();}
		else
		{
			 wrong();
		ch=Check_password();

		if(ch==match)
		{open();}
		else
		{TimerSetCallBack(Timer_1, timer_buzzer);
		TimerInit(&timer);
		while(danger!=Safe);
		danger=0;
		TimerDeInit(Timer_1);
		UART_sendByte(Safe);
		options();


		}
		}

		}
	}
	else if(key==2)
	{
		ch=Check_password();
				if(ch==match)
				{FirstTrial();}
				else
				{ wrong();

				ch=Check_password();
				if(ch==match)
				{FirstTrial();}
				else
				{
					 //wrong();
					_delay_ms(1000);
				ch=Check_password();

				if(ch==match)
				{FirstTrial();}
				else
				{TimerSetCallBack(Timer_1, timer_buzzer);
				TimerInit(&timer);
				while(danger!=Safe);
				danger=0;
				TimerDeInit(Timer_1);
				UART_sendByte(Safe);
				options();


				}
				}

				}
	}
	else{

									_delay_ms(1000);options();}
}



 /***************************************************************************************************
  * [Function Name]: Check_password
  *
  * [Description]:  a function used by another function (options) that receives the entered password
  *                 and returns value that indicates whether the entered password matches the stored or not
  * [Args]:         none
  *
  * [In]            none
  *
  * [Out]           none
  *
  * [Returns]:     returns value that indicates whether the entered password matches the stored or not
  ***************************************************************************************************/



uint8 Check_password()
{
	_delay_ms(1000);

	    uint8 count=0;
		uint8 same=0;
		for(count=0;count<(password_length);count++){

			_delay_ms(300);
			UART_sendByte(R_U_READY);
			password_2= UART_recieveByte();

			EEPROM_readByte( (FIRST_ADDRESS+count)  ,& pass[count]);
			if(pass[count]==password_2){same++;}LCD_intgerToString(same);
		}

		UART_sendByte(R_U_READY);
	if(same==5){	UART_sendByte(match);return match;}else{UART_sendByte(missmatch);return missmatch;}

}


 /***************************************************************************************************
  * [Function Name]: open
  *
  * [Description]:  a function that receives orders from the master and calls
  *                 the door(motor) and its timer functions to be open or close or stop the motor
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
	while(UART_recieveByte()!=R_U_READY);
				door=0;
				Motor_C_Wise();
				TimerSetCallBack(Timer_1, timer_door_on);
				TimerInit(&timer);
				while(door!=opened);
				Motor_Stop();
				UART_sendByte(R_U_READY);
				TimerSetCallBack(Timer_1, timer_door_stop);
				TimerInit(&timer);
				while(door!=stopped);
				Motor_C_C_Wise();
				UART_sendByte(R_U_READY);
				TimerSetCallBack(Timer_1, timer_door_off);
				TimerInit(&timer);
				while(door!=closed);
				Motor_Stop();
				TimerDeInit(Timer_1);
				UART_sendByte(go_options);
				options();
}






 /***************************************************************************************************
  * [Function Name]: wrong
  *
  * [Description]:  a function that is used by another function (options)
  *                 its only used to take the same delay as the master so that they can communicate at the same time
  * [Args]:         none
  *
  * [In]            none
  *
  * [Out]           none
  *
  * [Returns]:     none
  ***************************************************************************************************/


void wrong()
{
/*its only used to take the same delay as the master so that they can communicate at the same time */

	_delay_ms(1000);


}



                 /*******************************************************************************
                                             motor Functions Prototypes
                  *******************************************************************************/

 /***************************************************************************************************
  * [Function Name]: Motor_Init
  *
  * [Description]:  a function that initialize (clear)the motor pins and define them as output
  * [Args]:         none
  *
  * [In]            none
  *
  * [Out]           none
  *
  * [Returns]:     none
  ***************************************************************************************************/


void Motor_Init()
{
	MOTOR_DIRECTION_PORT = SET_BIT(MOTOR_DIRECTION_PORT,MOTOR_IN1 );
	MOTOR_DIRECTION_PORT = SET_BIT(MOTOR_DIRECTION_PORT,MOTOR_IN2 );

	MOTOR_DATA_PORT = CLEAR_BIT( MOTOR_DATA_PORT, MOTOR_IN2);
	MOTOR_DATA_PORT = CLEAR_BIT( MOTOR_DATA_PORT, MOTOR_IN1);

}
 /***************************************************************************************************
  * [Function Name]: Motor_C_Wise
  *
  * [Description]:  a function that sets the motor pin INT2 and clears the motor pin INT1
  *                 to spin the motor clk-wise
  * [Args]:         none
  *
  * [In]            none
  *
  * [Out]           none
  *
  * [Returns]:     none
  ***************************************************************************************************/

void Motor_C_Wise()
{
	MOTOR_DATA_PORT = CLEAR_BIT(MOTOR_DATA_PORT , MOTOR_IN1);
	MOTOR_DATA_PORT = SET_BIT(MOTOR_DATA_PORT , MOTOR_IN2);

}

 /***************************************************************************************************
   * [Function Name]: Motor_C_C_Wise
   *
   * [Description]:  a function that sets the motor pin INT1 and clears the motor pin INT2
   *                 to spin the motor counter clk-wise
   * [Args]:         none
   *
   * [In]            none
   *
   * [Out]           none
   *
   * [Returns]:     none
   ***************************************************************************************************/

void Motor_C_C_Wise()
{
	MOTOR_DATA_PORT = CLEAR_BIT( MOTOR_DATA_PORT, MOTOR_IN2);
	MOTOR_DATA_PORT = SET_BIT (MOTOR_DATA_PORT, MOTOR_IN1);

}

 /***************************************************************************************************
   * [Function Name]: Motor_Stop
   *
   * [Description]:  a function that clear the motor pins to stop the motor
   * [Args]:         none
   *
   * [In]            none
   *
   * [Out]           none
   *
   * [Returns]:     none
   ***************************************************************************************************/
void Motor_Stop()
{
	MOTOR_DATA_PORT = CLEAR_BIT(MOTOR_DATA_PORT , MOTOR_IN2);
	MOTOR_DATA_PORT = CLEAR_BIT( MOTOR_DATA_PORT, MOTOR_IN1);

}


            /*******************************************************************************
                                            timer_ motor Functions Prototypes
             *******************************************************************************/

 /***************************************************************************************************
 * [Function Name]: timer_door_on
 *
 * [Description]:  a function that counts 10 seconds while motor is clk-wise
 *                  and then change a variable to indicate that it finished counting
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           none
 *
 * [Returns]:     none
 ***************************************************************************************************/


void timer_door_on(void)
{
	tick_1++;
	_delay_ms(500);
	//LCD_clearScreen();
//	LCD_intgerToString(tick_1);
	if(tick_1 == 10 )
	{
		tick_1=0;
		door=opened;
	}

}

 /***************************************************************************************************
 * [Function Name]: timer_door_stop
 *
 * [Description]:  a function that counts 5 seconds while motor is stopped
 *                 and then change a variable to indicate that it finished counting
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           none
 *
 * [Returns]:     none
 ***************************************************************************************************/



void timer_door_stop (void)
{
	tick_1++;
	if(tick_1 == 5 )
	{
		tick_1=0;
		door=stopped;
	}
}




 /***************************************************************************************************
 * [Function Name]: timer_door_off
 *
 * [Description]:  a function that counts 10 seconds while motor is counter clk-wise
 *                 and then change a variable to indicate that it finished counting
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           none
 *
 * [Returns]:     none
 ***************************************************************************************************/




void timer_door_off(void)
{
	tick_1++;
	_delay_ms(500);
	if(tick_1 == 10 )
	{
		tick_1=0;
		door=closed;
	}

}

                /*******************************************************************************
                                            buzzer Functions Prototypes
                 *******************************************************************************/


 /***************************************************************************************************
  * [Function Name]: Buzzer_Init
  *
  * [Description]:  a function that initialize (clear)the buzzer pin and define it as output
  *
  * [Args]:         none
  *
  * [In]            none
  *
  * [Out]           none
  *
  * [Returns]:     none
  ***************************************************************************************************/

void Buzzer_Init()
{
	BUZZER_DIRECTION_PORT = SET_BIT(BUZZER_DIRECTION_PORT, BUZZER_PIN);
	BUZZER_DATA_PORT = CLEAR_BIT(BUZZER_DATA_PORT, BUZZER_PIN);


}



/***************************************************************************************************
 * [Function Name]: Buzzer_ON
 *
 * [Description]:  a function that sets the buzzer pin to 1
 *
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           none
 *
 * [Returns]:     none
 ***************************************************************************************************/


void Buzzer_ON()
{
	SET_BIT(BUZZER_DATA_PORT , BUZZER_PIN );

}

/***************************************************************************************************
 * [Function Name]: Buzzer_OFF
 *
 * [Description]:  a function that stops the buzzer by clearing pin
 *
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           none
 *
 * [Returns]:     none
 ***************************************************************************************************/

void Buzzer_OFF()
{
	CLEAR_BIT(BUZZER_DATA_PORT , BUZZER_PIN);

}
              /*******************************************************************************
                                            timer_ buzzer Functions Prototypes
               *******************************************************************************/

/***************************************************************************************************
 * [Function Name]: timer_buzzer
 *
 * [Description]:  a function that switches on the buzzer and counts fifteen seconds an the switches off the buzzer
 *
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           none
 *
 * [Returns]:     none
 ***************************************************************************************************/


void timer_buzzer(void)
{
	tick++;

	if( tick < 15)
	{
		Buzzer_ON();


	}

	else if(tick == 15 )
	{
		Buzzer_OFF();

		TimerDeInit(Timer_1);

		tick=0;

		danger= Safe;

	}

}
