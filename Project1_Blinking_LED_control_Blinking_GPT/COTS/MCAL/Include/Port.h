/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Port.h
 *       Module:  Port
 *
 *  Description:  header file for Port Module    
 *  
 *********************************************************************************************************************/
#ifndef Port_H
#define Port_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Port_Types.h"
#include "Port_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

extern const Port_ConfigType PortConfigPtr[PORT_MAX_PIN_NO];
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
/******************************************************************************
* \Syntax          : void Port_Init(void)                                      
* \Description     : initialize Port Module by parsing the Configuration 
*                    Structure Pointer                                     
*       
*                   1. Enable the clock         -> RCGCGPIO register ( SCGCGPIO and DCGCGPIO For Sleep mode Clk)
*                   2. Set the direction        -> GPIODIR register. "A write of a 1 indicates output and a write of a 0 indicates input."
*                   3. Alternate pin Function   -> GPIOAFSEL register
*                   4. Drive strength           -> GPIODR2R, GPIODR4R, and GPIODR8R registers
*                   5. Program Pad              -> GPIOPUR, GPIOPDR, GPIOODR register (GPIOSLR if req)   
*                   6. Enable GPIO digital I/Os -> GPIODEN register.
*                      For Analog Function      -> Set GPIOAMSEL bit in the GPIOAMSEL register. 
*                   7. interrupt Config         -> GPIOIS, GPIOIBE, GPIOEV, and GPIOIM registers 
*                       Interrupt Handler:
*                           - clearing the IME field in the GPIOIM register
*                           -  IS field in the GPIOIS register and the IBE field in the GPIOIBE register.
*                           - Clear the GPIORIS register
*                           - Unmask the port by setting the IME field in the GPIOIM register
*                   
*                   8. Software Lock(OPTIONAL)  -> GPIOLOCK registe
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr of type  Port_ConfigType                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/


void Port_Init(const Port_ConfigType * ConfigPtr);
 
#endif  /* Port_H */

/**********************************************************************************************************************
 *  END OF FILE: Port.h
 *********************************************************************************************************************/
