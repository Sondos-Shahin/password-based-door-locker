/**********************************************************************************
 * [FILE NAME]: Timer.h
 *
 * [AUTHOR]: sondos ahmed eladl mohamed
 *
 * [DATE CREATED]: jul 17, 2021
 *
 * [Description]: File of All types Declaration and Functions prototypes of timer
 *                configuration.
 ***********************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

#define CLEAR_CLOCK_VALUE        0XF8
#define NULL   (void*)0

typedef enum
{
	Timer_0,Timer_1,Timer_2
}Timer_Type;


typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}Timer_Clock;


typedef enum
{
	Overflow,Compare
}Timer_Mode;


typedef enum
{
	Channel_A, Channel_B
}Channel_Type;

typedef struct
{
	uint16 timer_Initial_Value;
	uint16 timer_Match_Value;
	Timer_Type  timer_type;
	Timer_Clock timer_clk;
	Timer_Mode  timer_mode;
	Channel_Type compare_register;

}Timer_Configuration;




/***************************************************************************************************
 * [Function Name]: TimerSetCallBack
 *
 * [Description]:  Function to set the Call Back function address.
 *
 * [Args]:        timer_type ,Function_ptr
 *
 * [In]           Function_ptr: -Pointer to function
 *                        -To use it to save receive the function call back name
 *                        -To store it in the global pointer to function to use it in
 *
 *                 timer_type: -Variable from type enum Timer_Type
 *                             -To use it to choose the type of the timer
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/

void TimerSetCallBack( Timer_Type  timer_type,void(*Function_ptr)(void) );






/***************************************************************************************************
 * [Function Name]: TimerInit
 *
 * [Description]:  Function to Initialize Timer Driver
 *                 - Working in Interrupt Mode
 *                  - Choose Timer initial value
 *                 - Choose Timer match value  if using CTC mode (compare mode)
 *                 - Choose Timer_Type (Timer_0, Timer_1, Timer_2)
 *                  - Choose Timer_Clock
 *                 - Choose Timer_Mode (OverFlow, Compare)
 *                 - Choose channel_Type in case of Timer_1
 *
 *
 *
 * [Args]:         Configuration_Ptr
 *
 * [In]            Configuration_Ptr which is a Pointer to Structure of Timer Configurations
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/

void TimerInit(const Timer_Configuration * Configuration_Ptr);



/***************************************************************************************************
 * [Function Name]: TimerStop
 *
 * [Description]:  Function to stop the clock of the timer to stop incrementing
 *
 * [Args]:         timer_type
 *
 *
 * [In]            timer_type: -Variable from type enum Timer_Type
 *                             -To use it to choose the type of the timer
 *                             -stop the required timer
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/


void TimerStop(Timer_Type timer_type);

/***************************************************************************************************
 * [Function Name]: TimerDeInit
 *
 * [Description]:  Function to DeInit the timer to start again from beginning
 *
 * [Args]:         timer_type
 *
 *
 * [In]            timer_type: -Variable from type enum Timer_Type
 *                             -To use it to choose the type of the timer
 *                             -DeInit the required timer
 *
 * [Out]           NONE
 *
 * [Returns]:      NONE
 ***************************************************************************************************/

void TimerDeInit(Timer_Type timer_type);

#endif /* TIMER_H_ */
