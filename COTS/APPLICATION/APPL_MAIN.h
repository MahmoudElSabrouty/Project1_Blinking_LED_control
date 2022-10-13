/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  APPL_MAIN.h
 *       Module:  APPL_MAIN
 *
 *  Description:  /* Board Support Package for the EK-TM4C123GXL board */    
/*********************************************************************************************************************/
#ifndef APPL_MAIN_H
#define APPL_MAIN_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Mcu_Hw.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define USE_PRECONFIGURED_LIGHT_TIMING	

#define TIVAC_HAL_LED_RED       PORTF_PIN_1
#define TIVAC_HAL_LED_BLUE      PORTF_PIN_2
#define TIVAC_HAL_LED_GREEN     PORTF_PIN_3
#define TIVAC_HAL_SW_1          PORTF_PIN_4
#define TIVAC_HAL_SW_2          PORTF_PIN_0 


/* system clock setting [Hz] */
#define SYS_CLOCK_HZ 16000000U

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


void Appl_DimmingHanlder(void);
void Appl_SecTimerHanlder(void);
void Appl_SecStartUpConfig(void);
void GpioIsrHandler(void);
void RunningStateHanlder(void);
#endif  /* APPL_MAIN_H */

/**********************************************************************************************************************
 *  END OF FILE: APPL_MAIN.h
 *********************************************************************************************************************/
