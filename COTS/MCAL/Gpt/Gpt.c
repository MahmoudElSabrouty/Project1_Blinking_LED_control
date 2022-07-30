/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Gpt.c
 *        \brief  General Purpose Timer Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into gorups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals    
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Gpt.h"

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

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/


/*  GPTMCTL.TnEN: Start Count
    GPTMCTL.TnWOT: Wait for trigger
*/
static void Gpt_SetMode(Gpt_ChannelType channelId, Gpt_ChannelModeType chaMode);
static void Gpt_LoadIntervalVal(Gpt_ChannelType channelId, Gpt_PredefTimerType gptPredefinedValue);


//GptLoadSet
static void Gpt_IntCtl(Gpt_ChannelType channelId);


/*Gpt_GetCurrVal()
{
    GPTMTAV
}*/


//interuptConfigure
// 1. Interrupt Status
//GPTM Raw Interrupt - Status (GPTMRIS) 
// - GPTMRIS.TBTORIS (Timeout) ->  cleared by writing 1 to GPTMICR.TBTOCINT
// - GPTMRIS.TATORIS (Timeout) ->  cleared by writing 1 to GPTMICR.TATOCINT
// - GPTMRIS.RTCRIS : RTC event, Cleared by writing 1 to  GPTMICR.RTCCINT



// 3. Interrupt enable 
// GPTMTnMR: INterrupt enable : (used fr match Interrupt)
// XXXX- GPTMIMR.TATOIM-> Timer A time-out interrupt enable(1)
// XXXX- GPTMIMR.TBTOIM-> Timer B time-out interrupt enable(1)
// XXXX- GPTMIMR.RTCIM -> Timer RTC time-out interrupt enable(1)


//----------RTC---------------
// 1. Load Value GPTMTnILR 
// 2. GPTMCTL.TnEN -> Timer A starts counting 
// 3. GPTMTnMATCHR value reached -> GPTMRIS asserted (Timer continues counting till GPTMCTL.TnEN disabled) 

//--------------------PWM Mode------------
//  1. PWM mode is enabled with the GPTMTnMR register by
//      setting the TnAMS bit to 0x1, the TnCMR bit to 0x0, and the TnMR field to 0x2. 
//  2.  timer is configured as (24-bit or 48-bit down-counter
//      - with a start value defined by the GPTMTnILR & GPTMTnPR

/*************************************************/
// 1.Enable the Timer0 peripheral
//SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

// 2. Wait for the Timer0 module to be ready.
//
//while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0))

// Configure TimerA as a half-width one-shot timer
// TimerConfigure(TIMER0_BASE, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_ONE_SHOT |

//TimerLoadSet(TIMER0_BASE, TIMER_A, 3000);

// Enable the timers.

//TimerEnable(TIMER0_BASE, TIMER_BOTH);


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void Gpt_ReadChannel(void)                                      
* \Description     :    GPTMCFG: 
*                  - initalize Timer HW config
*                  - Disable All int notification 
*                  - Set Operation mode -> Normal mode (will skip sleep mode for now)
*                  - Start all GPT Predef Timers at '0' Value                                                         
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/


void Gpt_Init(const Gpt_ConfigType * ConfigPtr)
{
    /*
    - initalize Timer HW config
    - Disable All int notification 
    - Set Operation mode -> Normal mode (will skip sleep mode for now)
    - Start all GPT Predef Timers at '0' Value
    */
    
    uint8 configuredPinIndex;
    
    for (configuredPinIndex=0;configuredPinIndex < GPT_MAX_CH_NO; configuredPinIndex++)
    {
            (GPTMCFG((ConfigPtr[configuredPinIndex].channelId))) ^= GPTMCFG_TIMER_A_ONLY;  /*GPTMCFG - select TIMER A Only - Driver didn't support concatenated mode*/ 
            Gpt_SetMode(ConfigPtr[configuredPinIndex].channelId, ConfigPtr[configuredPinIndex].gptChannelMode);
            Gpt_IntCtl(ConfigPtr[configuredPinIndex].channelId);

            Gpt_LoadIntervalVal(ConfigPtr[configuredPinIndex].channelId, ConfigPtr[configuredPinIndex].gptPredefinedValue);
    
    }

}

static void Gpt_LoadIntervalVal(Gpt_ChannelType channelId, Gpt_PredefTimerType gptPredefinedValue)
{
    GPTMTAILR(channelId) = gptPredefinedValue;
}

static void Gpt_SetMode(Gpt_ChannelType channelId, Gpt_ChannelModeType chaMode){
    
  /* Set Timer Mode 
    GPTMTnMR.TnMR :  one-shot or periodic mode 
    GPTMTnMR.TnCDIR: Count direction
    */
    
    /*TAILD - skipped*/
    switch(chaMode)
    {
        case GPT_CH_MODE_CONTINUOUS_COUNTUP: 
            GPTMTAMR(channelId) ^= (GPTMCFG_TAMR_PERIODIC | GPTMCFG_TACDIR_COUNTUP);
        break;

        case GPT_CH_MODE_ONESHOT_COUNTUP: 
            GPTMTAMR(channelId) ^= (GPTMCFG_TAMR_ONESHOT | GPTMCFG_TACDIR_COUNTUP);
        break;
#ifdef GPT_PWM_ENABLE
        case GPT_CH_MODE_PWM_PERIODIC: 
            GPTMTAMR(channelId) ^= (GPTMCFG_TAAMS_PWM_ENABLE | GPTMCFG_TAMR_PERIODIC | GPTMCFG_TAPWMIE_ENABLE);
        break;
#endif

    }

}
/******************************************************************************
* \Syntax          : void Gpt_StartTimer(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/


void Gpt_StartTimer(Gpt_ChannelType channelId, Gpt_ValueType TimerVale)
{
    
    GPTMCTL(channelId) ^= (GPTMCTL_TAEN); /*Enable Timer A interrupts */
    
} 
/******************************************************************************
* \Syntax          : void Gpt_StopTimer(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

void Gpt_StopTimer(Gpt_ChannelType channelId)
{
 
   GPTMCTL(channelId) &= ~(GPTMCTL_TAEN); /*Disable Timer A interrupts */
 
}; 



static void Gpt_IntCtl(Gpt_ChannelType channelId)
{
    /* 2. Interrupt Enable: 
         GPTMIMR: INterrupt Mask:
         - GPTMIMR.TATOIM-> Timer A time-out interrupt enable(1)
         - GPTMIMR.TBTOIM-> Timer B time-out interrupt enable(1)
         - GPTMIMR.RTCIM -> Timer RTC time-out interrupt enable(1) */

        GPTMIMR(channelId) ^= (GPTMIMR_TATOIM); /*Enable Timer A interrupts */
    
}



/* Interrupt Handlers Implmentation*/

void TIMER0A_Handler(void)		{if (gptCallbackNotifications[0 ] != NULL_PTR)	gptCallbackNotifications[0 ];}
void TIMER1A_Handler(void)		{if (gptCallbackNotifications[1 ] != NULL_PTR)	gptCallbackNotifications[1 ];}
void TIMER2A_Handler(void)		{if (gptCallbackNotifications[2 ] != NULL_PTR)	gptCallbackNotifications[2 ];}
void TIMER3A_Handler(void)		{if (gptCallbackNotifications[3 ] != NULL_PTR)	gptCallbackNotifications[3 ];}
void TIMER4A_Handler(void)		{if (gptCallbackNotifications[4 ] != NULL_PTR)	gptCallbackNotifications[4 ];}
void TIMER5A_Handler(void)		{if (gptCallbackNotifications[5 ] != NULL_PTR)	gptCallbackNotifications[5 ];} 
void WTIMER0A_Handler(void)	    {if (gptCallbackNotifications[6 ] != NULL_PTR)	gptCallbackNotifications[6 ];} 
void WTIMER1A_Handler(void)	    {if (gptCallbackNotifications[7 ] != NULL_PTR)	gptCallbackNotifications[7 ];} 
void WTIMER2A_Handler(void)	    {if (gptCallbackNotifications[8 ] != NULL_PTR)	gptCallbackNotifications[8 ];} 
void WTIMER3A_Handler(void)	    {if (gptCallbackNotifications[9 ] != NULL_PTR)	gptCallbackNotifications[9 ];} 
void WTIMER4A_Handler(void)	    {if (gptCallbackNotifications[10] != NULL_PTR)	gptCallbackNotifications[10];} 
void WTIMER5A_Handler(void)	    {if (gptCallbackNotifications[11] != NULL_PTR)	gptCallbackNotifications[11];} 





/**********************************************************************************************************************
 *  END OF FILE: Gpt.c
 *********************************************************************************************************************/
