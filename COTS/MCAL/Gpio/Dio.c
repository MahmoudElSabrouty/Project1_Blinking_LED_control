/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dio.c
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
#include "Dio.h"
#include "Port_Cfg.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
volatile uint32* TempRegVar;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void Dio_ReadChannel(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

Dio_LevelType Dio_ReadChannel(Dio_ChannelType channelId, Dio_PortType portName)
{
    volatile uint32 maskValue =0;
    Dio_LevelType dioValue = DIO_PIN_SNA;
    
    maskValue = PORTX_ِAPB_GPIODATA_MASK(portName, (1<<channelId));

    dioValue = (Dio_LevelType)(maskValue>>channelId);


    return dioValue;
}

/******************************************************************************
* \Syntax          : void Dio_WriteChannel(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

void Dio_WriteChannel(Dio_ChannelType channelId, Dio_PortType portName, Dio_LevelType level)
{
    if (level == DIO_PIN_HIGH)
    {
        PORTX_ِAPB_GPIODATA_MASK(portName, (1<<channelId)) |= ((uint32)((uint32) (1<<channelId)));
    }
    else
    {
        PORTX_ِAPB_GPIODATA_MASK(portName, (1<<channelId)) &= ~((uint32)((uint32) (1<<channelId)));
    }  

}



/******************************************************************************
* \Syntax          : void Dio_WritePort(Dio_PortType PortName, Dio_PortLevelType portMask, Dio_PortLevelType maskValue)
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

void Dio_WritePort(Dio_PortType portName, Dio_PortLevelType portMask, Dio_PortLevelType maskValue)
{
    //TempRegVar = &( PORTX_ِAPB_GPIODATA_MASK(portName, portMask));
    PORTX_ِAPB_GPIODATA_MASK(portName, portMask) = maskValue;
}


/******************************************************************************
* \Syntax          : void Dio_ReadPort(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

Dio_PortLevelType Dio_ReadPort( Dio_PortType portName,Dio_PortLevelType portMask)
{
    volatile uint32 tempPortMaskedValue = 0;
    Dio_PortLevelType portMaskValue = 0xFF;
    TempRegVar = &(PORTX_ِAPB_GPIODATA_MASK(portName, portMask));
    tempPortMaskedValue = PORTX_ِAPB_GPIODATA_MASK(portName, portMask);
    portMaskValue = (Dio_PortLevelType)(tempPortMaskedValue >>2); 
    
    return portMaskValue;

}

void Dio_ISR_Clear(Dio_ChannelType channelId, Dio_PortType portName)
{
    
    PORTX_ِAPB_GPIOICR(portName) |= (uint32)(1<<channelId);
}

/******************************************************************************
* \Syntax          : void Dio_FlipChannel(Dio_ChannelType channelId, Dio_PortType portName)
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

void Dio_FlipChannel(Dio_ChannelType channelId, Dio_PortType portName)
{
     PORTX_ِAPB_GPIODATA_MASK(portName, (1<<channelId)) ^= (1<<channelId);
}



void GPIOF_Handler(void)
{
    GpioIsrHandler();
}


/**********************************************************************************************************************
 *  END OF FILE: Dio.c
 *********************************************************************************************************************/
