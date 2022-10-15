/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCtrl_Lcfg.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Port_Cfg.h"
#include "Port_Types.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

const Port_ConfigType PortConfigPtr[PORT_MAX_PIN_NO] = 
{

    {
        PORT_SW1,       /* PortName of type PORT_PortName                   */
        PIN_SW1,        /* ChannelName of Type PORT_ChannelName             */
        PIN_LOW,        /* PortPinLevelValue of Type Port_PinType           */
        PIN_IN,         /* pinDir of Type Port_PinDirectionType             */
        PIN_GPIO,       /* PortPinMode of Type Port_PinModeType             */
        PULL_DOWN,      /* pinIntAttach of Type Port_PinInternalAttachType  */
        ENABLED,        /* pinInterruptEnable of type Port_PinInterruptEnable*/    
       
    },
    {
        PORT_SW2,       /* PortName of type PORT_PortName                   */
        PIN_SW2,        /* ChannelName of Type PORT_ChannelName             */
        PIN_LOW,        /* PortPinLevelValue of Type Port_PinType           */
        PIN_IN,         /* pinDir of Type Port_PinDirectionType             */
        PIN_GPIO,       /* PortPinMode of Type Port_PinModeType             */
        PULL_DOWN,      /* pinIntAttach of Type Port_PinInternalAttachType  */
        ENABLED,        /* pinInterruptEnable of type Port_PinInterruptEnable*/            
    },
		{
        PORT_LED1,       /* PortName of type PORT_PortName                   */
        PIN_LED1,        /* ChannelName of Type PORT_ChannelName             */
        PIN_LOW,        /* PortPinLevelValue of Type Port_PinType           */
        PIN_OUT,        /* pinDir of Type Port_PinDirectionType             */
        PIN_GPIO,       /* PortPinMode of Type Port_PinModeType             */
        PULL_DOWN,     /* pinIntAttach of Type Port_PinInternalAttachType  */
        DISABLED,        /* pinInterruptEnable of type Port_PinInterruptEnable*/    
    }
};

 
/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Lcfg.c
 *********************************************************************************************************************/
