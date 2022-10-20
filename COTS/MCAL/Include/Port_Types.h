/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Port_Types.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef PORT_TYPES_H
#define PORT_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum {
    PORTA =0,
    PORTB,
    PORTC,
    PORTD,
    PORTE,
    PORTF
} PORT_PortName;

typedef enum {
    CH0 =0,
    CH1,
    CH2,
    CH3,
    CH4,
    CH5,
    CH6,
    CH7,
    CH8,
} PORT_ChannelName;


typedef enum {
    PIN_LOW = 0,
    PIN_HIGH,
    PIN_SNA 
}Port_PinType;

typedef enum {
    PIN_IN =0,
    PIN_OUT
}Port_PinDirectionType;

typedef enum {
    PIN_GPIO =0,  /*By Default GPIO*/
}Port_PinModeType;

typedef enum {
    PULL_UP,
    PULL_DOWN,
    OPEN_DRAIN
}Port_PinInternalAttachType;


typedef enum {
    DISABLED =0,
    ENABLED,
}Port_PinInterruptEnable;

/*
typedef enum {
    MA_2,
    MA_4,
    MA_8
}Port_PinOutputCurrentType;
*/
typedef struct port_Types
{
    /* data */
    PORT_PortName               PortName;
    PORT_ChannelName            ChannelName;
    Port_PinType                PortPinLevelValue;
    Port_PinDirectionType       pinDir;
    Port_PinModeType            PortPinMode;
    Port_PinInternalAttachType  pinIntAttach;
    Port_PinInterruptEnable     pinInterruptEnable; 
    /*Port_PinOutputCurrentType   pinOutCurr;*/
}Port_ConfigType;

 
#endif  /* PORT_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Port_Types.h
 *********************************************************************************************************************/
