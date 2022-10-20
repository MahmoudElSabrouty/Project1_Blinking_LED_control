/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Port.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into gorups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals    
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Port.h"
#include "Mcu_Hw.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
    static void enablePortClkGating(const Port_ConfigType * ConfigPtr);
    static void enablePortXPinInterrupt(Port_PinInterruptEnable intStatus, PORT_ChannelName chNum,PORT_PortName portName);
    static void setPortXPinDir(Port_PinDirectionType pinDir, PORT_ChannelName chNum,PORT_PortName portName);
    static void setPortXPinMode(Port_PinModeType pinMode, PORT_ChannelName chNum,PORT_PortName portName);
    static void setPortXpinIntAttach(Port_PinInternalAttachType pinAttach, PORT_ChannelName chNum,PORT_PortName portName);
    static void setPortXPinLevelValue(Port_PinType pinType, PORT_ChannelName chNum,PORT_PortName portName);


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

static void enablePortXPinInterrupt(Port_PinInterruptEnable intStatus, PORT_ChannelName chNum,PORT_PortName portName)
{		
	if (intStatus == ENABLED)
    {			
          (PORTX_ِAPB_GPIOIM(portName)) |= (1<< chNum);     /*Enable corresponding interrupt*/
          (PORTX_ِAPB_GPIORIS(portName))|= (1<< chNum);     /*Configure corresponding interrupt Level Sensitive*/
          (PORTX_ِAPB_GPIOIEV(portName))|= (1<< chNum);     /*Configure corresponding interrupt Level High*/
    }
}




static void enablePortClkGating(const Port_ConfigType * ConfigPtr)
{   
    /*Question: why Setting the same bit again will clear it*/
    uint8 configuredPinIndex =0;
    uint8 usedPortsBitmap = 0x00;
    for (configuredPinIndex=0;configuredPinIndex < PORT_MAX_PIN_NO; configuredPinIndex++)
    {
        usedPortsBitmap |= (1<< ConfigPtr[configuredPinIndex].PortName);  
    }
    
    RCGCGPIO  = usedPortsBitmap;  
}
static void unlockPort(PORT_PortName portName)
{
    PORTX_ِAPB_GPIOLOCK(portName) = GPIO_UNLOCK_PATTERN;

}

static void setPortXPinDir(Port_PinDirectionType pinDir, PORT_ChannelName chNum,PORT_PortName portName)
{
	
	PORTX_ِAPB_GPIOLOCK(portName) = GPIO_UNLOCK_PATTERN;
    PORTX_ِAPB_GPIOCR(portName) |= (1<< chNum);         
		
	if (pinDir == PIN_IN)
    {			
        (PORTX_ِAPB_GPIODIR(portName)) &= (~(1<< chNum)); 
    }else if (pinDir == PIN_OUT)
    {
          (PORTX_ِAPB_GPIODIR(portName)) |= (1<< chNum);  
    }
}

static void setPortXPinMode(Port_PinModeType pinMode, PORT_ChannelName chNum,PORT_PortName portName)
{
    if (pinMode == PIN_GPIO)
    {
        /*Do Nothing for Alternate Function - default Mode is GPIO*/;
        /* Diagital Enable for corresponding PIN & PORT*/
        PORTX_ِAPB_GPIOLOCK(portName) = GPIO_UNLOCK_PATTERN;

        PORTX_ِAPB_GPIOCR(portName) |= (1<< chNum);         
        PORTX_ِAPB_GPIODEN(portName) |= (1<< chNum);         
    }
}

static void setPortXpinIntAttach(Port_PinInternalAttachType pinAttach, PORT_ChannelName chNum,PORT_PortName portName)
{
    PORTX_ِAPB_GPIOLOCK(portName) = GPIO_UNLOCK_PATTERN;
    PORTX_ِAPB_GPIOCR(portName) |= (1<< chNum);    

    if (pinAttach == PULL_UP)
    {
        PORTX_ِAPB_GPIOPUR(portName) |= (1<< chNum); 
    }else if (pinAttach == PULL_DOWN)
    {
        PORTX_ِAPB_GPIOPDR(portName) |= (1<< chNum);  
    }else if (pinAttach == OPEN_DRAIN)
    {
        PORTX_ِAPB_GPIOODR(portName) |= (1<< chNum);  
    }

}

static void setPortXPinLevelValue(Port_PinType pinType, PORT_ChannelName chNum,PORT_PortName portName)
{
    if (pinType == PIN_LOW)
    {
        PORTX_ِAPB_GPIODATA_MASK(portName,chNum) = PIN_LOW; 
    }else if (pinType == PIN_HIGH)
    {
        PORTX_ِAPB_GPIODATA_MASK(portName,chNum) = PIN_HIGH;  
    }
    else if (pinType == PIN_SNA)
    {
      /*Do nothing*/
    }

}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void Port_Init(const Port_ConfigType * ConfigPtr)                                      
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
void Port_Init(const Port_ConfigType * ConfigPtr)
{
    uint8 configuredPinIndex=0; 

        enablePortClkGating(ConfigPtr);                                                           /* 1. Enable the clock */
    for (configuredPinIndex=0;configuredPinIndex < PORT_MAX_PIN_NO; configuredPinIndex++)
    {
    	setPortXPinDir(ConfigPtr[configuredPinIndex].pinDir, ConfigPtr[configuredPinIndex].ChannelName,ConfigPtr[configuredPinIndex].PortName);                      /* 2. Set the direction*/
        setPortXPinMode(ConfigPtr[configuredPinIndex].PortPinMode, ConfigPtr[configuredPinIndex].ChannelName,ConfigPtr[configuredPinIndex].PortName);                /* 3. Alternate pin Function &  6. Enable GPIO digital I/Os*/
        enablePortXPinInterrupt(ConfigPtr[configuredPinIndex].pinInterruptEnable, ConfigPtr[configuredPinIndex].ChannelName,ConfigPtr[configuredPinIndex].PortName);
                                                                                                            /* 4. Drive strength - Skipped - keep Default        */    
        setPortXpinIntAttach(ConfigPtr[configuredPinIndex].pinIntAttach, ConfigPtr[configuredPinIndex].ChannelName,ConfigPtr[configuredPinIndex].PortName);          /* 5. Program Pad */   
        /* 7. interrupt Config*/                                                                                                    /* 7. interrupt Config*/
        setPortXPinLevelValue(ConfigPtr[configuredPinIndex].PortPinLevelValue, ConfigPtr[configuredPinIndex].ChannelName,ConfigPtr[configuredPinIndex].PortName);    /* (OPT) Pin Init Value */
    }
}






/**********************************************************************************************************************
 *  END OF FILE: Port.c
 *********************************************************************************************************************/
