/**********************************************************************************
 * [FILE NAME]: device_functions.h
 *
 * [AUTHOR]: sondos ahmed eladl mohamed
 *
 * [DATE CREATED]: jul 17, 2021
 *
 * [Description]:File of All types Declaration and Functions prototypes of DEVICE
 *
 *
 ***********************************************************************************/

#ifndef DEVICE_FUNCTIONS_H_
#define DEVICE_FUNCTIONS_H_


#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include"lcd.h"
#include"uart.h"
#include"i2c.h"
#include"external_eeprom.h"
#include "Timer.h"

                    /*******************************************************************************
                                                    Preprocessor Macros
                    *******************************************************************************/

                  /* uart guided numbers (could have any value) but must be the same for both MCU's*/

#define password_length    5                       //length of the password(can be changed)
#define R_U_READY          0x10                   //value defines that the MCU_1 is ready to send or receive
#define first_time         1                      //value defines that the eeprom is empty
#define repeated           2                    //value defines that the eeprom is not empty
#define go_options         99                 //MCU_2 sends safe to MCU_1 to go to options after the buzzer is off
#define match              1                //value defines the password's matching
#define missmatch          0               //value defines the password's mismatch
#define FIRST_ADDRESS     0X0300        //first address to store the wanted password
#define Safe              100          //MCU_2 sends safe to MCU_1 to continue running the system after the buzzer is off
#define second              1000

                                                        /*buzzer*/
#define BUZZER_DIRECTION_PORT                 DDRA
#define BUZZER_DATA_PORT                      PORTA
#define BUZZER_PIN                            PA0
#define Buzzer_On     9
#define Buzzer_Off     10

                                                       /*motor(door)*/


#define MOTOR_DIRECTION_PORT               DDRA
#define MOTOR_IN1                          PA1
#define MOTOR_IN2                          PA3
#define MOTOR_DATA_PORT                    PORTA


#define opened        1
#define stopped       2
#define closed        3


                  /*******************************************************************************
                                                    Functions Prototypes
                   *******************************************************************************/


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
void FirstTrial();



/***************************************************************************************************
 * [Function Name]: Check_password
 *
 * [Description]:  a function that checks the entered password with the stored one
 *                 and returns value that indicates whether the entered password matches the stored or not
 *
 * [Args]:         none
 *
 * [In]            none
 *
 * [Out]           unsigned char
 *
 * [Returns]:     returns value that indicates whether the entered password matches the stored or not
 ***************************************************************************************************/

uint8 Check_password();



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

 void options();



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

 void open();

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

 void wrong();





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


 void Motor_Init();

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

 void Motor_C_Wise();// the door is opening
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

 void Motor_C_C_Wise();// the door is closing
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

 void Motor_Stop();




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


 void timer_door_on();

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


 void timer_door_stop();

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


 void timer_door_off();


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
void Buzzer_Init();


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

void Buzzer_ON();

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

void Buzzer_OFF();

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

void timer_buzzer();

#endif /* DEVICE_FUNCTIONS_H_ */
