/**********************************************************************************
 * [FILE NAME]: device_functions.h
 *
 * [AUTHOR]: sondos ahmed eladl mohamed
 *
 * [DATE CREATED]: jul 17, 2021
 *
 * [Description]:File of All types Declaration and Functions prototypes of HUMAN_INTERFACE
 *
 *
 ***********************************************************************************/

#ifndef DEVICE_FUNCTIONS_H_
#define DEVICE_FUNCTIONS_H_



#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#include"keyPad.h"
#include"lcd.h"
#include"uart.h"


                   /*******************************************************************************
                                                    Preprocessor Macros
                    *******************************************************************************/


                             /* uart guided numbers (could have any value)*/

#define password_length    5
#define READY             0x10                     //value defines that the MCU_1 is ready to send or receive
#define first_time         1                       //value defines that the eeprom is empty
#define repeated           2                   //value defines that the eeprom is not empty
#define match              1                   //value defines the password's matching
#define missmatch          0                 //value defines the password's mismatch
#define go_options         99             //MCU_2 sends safe to MCU_1 to go to options after the buzzer is off
#define FIRST_ADDRESS     0X0300        //first address to store the wanted password
#define Safe              100           //MCU_2 sends safe to MCU_1 to continue running the system after the buzzer is off
#define Buzzer_On          9
#define Buzzer_Off        10
#define open_door          0
#define stop_door          1
#define close_door         2



                  /*******************************************************************************
                                                    Functions Prototypes
                   *******************************************************************************/


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

void FirstTrial();


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

void Store_Password();


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

void FirstTrial_1();

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


uint8 confirm();


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

uint8 Check_password();


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

void options();


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

void open();


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

uint8 one();





#endif /* DEVICE_FUNCTIONS_H_ */
