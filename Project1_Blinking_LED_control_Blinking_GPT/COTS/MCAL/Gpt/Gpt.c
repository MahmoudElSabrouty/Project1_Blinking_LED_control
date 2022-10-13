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
static void enableGptClkGating(const Gpt_ConfigType * ConfigPtr);


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
* \Syntax          : void Gpt_Init(const Gpt_ConfigType * ConfigPtr)
* \Description     :     
*                  - initalize Timer HW config
*                  - Disable All int notification 
*                  - Set Operation mode -> Normal mode (will skip sleep mode for now)
*                  - Start all GPT Predef Timers at '0' Value                                                         
*       Detailed Steps:
*       - Step 0 as precondition is to enable Clock Gating for the driver.
*       - The GPTM is configured for One-Shot and Periodic modes by the following sequence:
*       - 1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making
*       - any changes.
*       - 2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.
*       - 3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
*       - a. Write a value of 0x1 for One-Shot mode.
*       - b. Write a value of 0x2 for Periodic mode.
*       - 4. Optionally configure the TnSNAPS, TnWOT, TnMTE, and TnCDIR bits in the GPTMTnMR register
*       - to select whether to capture the value of the free-running timer at time-out, use an external
*       - trigger to start counting, configure an additional trigger or interrupt, and count up or down.
*       - 5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).   
*       - 6. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register
*           (GPTMIMR).
*       - 7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
*       - 8. Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). In both cases,
*           the status flags are cleared by writing a 1 to the appropriate bit of the GPTM Interrupt Clear
*            Register (GPTMICR).
*
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

volatile uint32  tempRegVal  = 0xFFFFFFFF;
volatile uint32* tempRegAddr1 = 0xFFFFFFFF;
volatile uint32* tempRegAddr2 = 0xFFFFFFFF;
void Gpt_Init(const Gpt_ConfigType * ConfigPtr)
{
    /*  Disable TMR:
        1- Set CTRL_E to Zero (Turn off Systic Device)
        2- RELOAD: set with Value
        3- CURR set to Zero 

        Configure TMR
        1- set CTRL: 101 -> disable INT, enable counter and chose clk source 16 MHZ
        2- RELOAD: ex: 5000 -->     


    
    
    */




    
    uint8 configuredPinIndex = 0;
    /* As a precondition is to enable Clock Gating for the driver.*/
    enableGptClkGating(ConfigPtr);


    for (configuredPinIndex=0;configuredPinIndex < GPT_MAX_CH_NO; configuredPinIndex++)
    {

            /*1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared)*/

            (GPTMCTL((ConfigPtr[configuredPinIndex].channelId))) &= ~(GPTMCTL_TAEN | GPTMCTL_TBEN);
            
            /*2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000*/
            //GPTMCFG(ConfigPtr[configuredPinIndex].channelId) =0x00000000;

            (GPTMCFG((ConfigPtr[configuredPinIndex].channelId))) |= GPTMCFG_TIMER_A_ONLY;  /*GPTMCFG - select TIMER A Only - Driver didn't support concatenated mode*/ 
            Gpt_SetMode(ConfigPtr[configuredPinIndex].channelId, ConfigPtr[configuredPinIndex].gptChannelMode);
            Gpt_IntCtl(ConfigPtr[configuredPinIndex].channelId);

            Gpt_LoadIntervalVal(ConfigPtr[configuredPinIndex].channelId, ConfigPtr[configuredPinIndex].gptPredefinedValue);
					(GPTMCTL((ConfigPtr[configuredPinIndex].channelId))) |= (GPTMCTL_TAEN | GPTMCTL_TBEN);
    
    }

}


#define XTAL_HZ     16000000U   /*0.0625 usec*/
#define BSP_TICKS0_PER_SEC   2U     //
#define BSP_TICKS1_PER_SEC   20U    // 100 msec or 50 ms if clk is 16 MHZ 

static void Gpt_LoadIntervalVal(Gpt_ChannelType channelId, Gpt_PredefTimerType gptPredefinedValue)
{
#if 0
  //  GPTMTAILR(channelId) = gptPredefinedValue;
#else
    GPTMTAILR(channelId) = gptPredefinedValue;//(XTAL_HZ/BSP_TICKS0_PER_SEC)*10 //0x7FFFFFFF ;

 #endif   
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
            GPTMTAMR(channelId) |= (GPTMCFG_TAMR_PERIODIC | GPTMCFG_TACDIR_COUNTUP);
        break;

        case GPT_CH_MODE_ONESHOT_COUNTUP: 
            GPTMTAMR(channelId) |= (GPTMCFG_TAMR_ONESHOT | GPTMCFG_TACDIR_COUNTUP);
        break;
#ifdef GPT_PWM_ENABLE
        case GPT_CH_MODE_PWM_PERIODIC: 
            GPTMTAMR(channelId) |= (GPTMCFG_TAAMS_PWM_ENABLE | GPTMCFG_TAMR_PERIODIC | GPTMCFG_TAPWMIE_ENABLE);
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
    
    GPTMCTL(channelId) |= (GPTMCTL_TAEN); /*Enable Timer A interrupts */
    
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

        GPTMIMR(channelId) |= (GPTMIMR_TATOIM); /*Enable Timer A interrupts */
    
}



static void enableGptClkGating(const Gpt_ConfigType * ConfigPtr)
{   
    /*Question: why Setting the same bit again will clear it
        ANS: 	- TIMERn bit must be set in the RCGCTIMER or RCGCWTIMER 
		        - the peripheral-specific registers must be accessed by read-modify-write operations */
    uint8 configuredChIndex     = 0;
    uint8 usedDriBitmap         = 0x00;
    uint8 usedWDriBitmap        = 0x00;
    
    for (configuredChIndex=0;configuredChIndex < GPT_MAX_CH_NO; configuredChIndex++)
    {
        if((ConfigPtr[configuredChIndex].channelId) <= GPT_TMR5)
        {
            usedDriBitmap |= (1<< ConfigPtr[configuredChIndex].channelId);  
        } 
            else
        {
            usedWDriBitmap |= (1<< ((ConfigPtr[configuredChIndex].channelId)-(GPT_TMR6)));  
        } 

    }
    
    RCGCTIMER |= (uint32)usedDriBitmap;  
    
    RCGCWTIMER|= (uint32)usedWDriBitmap;   

    /*Timer Reset 
    SRWTIMER  |= (uint32)usedWDriBitmap;  

    SRWTIMER  &= ~((uint32)usedWDriBitmap); Reset is completed by setting then resetting the corresponding Bits*/   
}


/* Interrupt Handlers Implmentation*/

void TIMER0A_Handler(void)		  {if (gptCallbackNotifications[0 ] != NULL_PTR)	gptCallbackNotifications[0 ]();}
void TIMER1A_Handler(void)		  {if (gptCallbackNotifications[1 ] != NULL_PTR)	gptCallbackNotifications[1 ]();}
void TIMER2A_Handler(void)		  {if (gptCallbackNotifications[2 ] != NULL_PTR)	gptCallbackNotifications[2 ]();}
void TIMER3A_Handler(void)		  {if (gptCallbackNotifications[3 ] != NULL_PTR)	gptCallbackNotifications[3 ]();}
void TIMER4A_Handler(void)		  {if (gptCallbackNotifications[4 ] != NULL_PTR)	gptCallbackNotifications[4 ]();}
void TIMER5A_Handler(void)		  {if (gptCallbackNotifications[5 ] != NULL_PTR)	gptCallbackNotifications[5 ]();} 
void WTIMER0A_Handler(void)	    {if (gptCallbackNotifications[6 ] != NULL_PTR)	gptCallbackNotifications[6 ]();} 
void WTIMER1A_Handler(void)	    {if (gptCallbackNotifications[7 ] != NULL_PTR)	gptCallbackNotifications[7 ]();} 
void WTIMER2A_Handler(void)	    {if (gptCallbackNotifications[8 ] != NULL_PTR)	gptCallbackNotifications[8 ]();} 
void WTIMER3A_Handler(void)	    {if (gptCallbackNotifications[9 ] != NULL_PTR)	gptCallbackNotifications[9 ]();} 
void WTIMER4A_Handler(void)	    {if (gptCallbackNotifications[10] != NULL_PTR)	gptCallbackNotifications[10]();} 
void WTIMER5A_Handler(void)	    {if (gptCallbackNotifications[11] != NULL_PTR)	gptCallbackNotifications[11]();} 





/**********************************************************************************************************************
 *  END OF FILE: Gpt.c
 *********************************************************************************************************************/
