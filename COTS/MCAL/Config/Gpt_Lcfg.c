/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Gpt_Lcfg.c
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
#include "Gpt_Types.h"
#include "Gpt.h"
#include "APPL_MAIN.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/


const GptCallbackNotificationPtr gptCallbackNotifications[12]=
{
    NULL_PTR, /* Notification Callback for TIMER0A	*/
    NULL_PTR, /* Notification Callback for TIMER1A  */
    NULL_PTR, /* Notification Callback for TIMER2A  */
    NULL_PTR, /* Notification Callback for TIMER3A  */
    NULL_PTR, /* Notification Callback for TIMER4A  */
    NULL_PTR, /* Notification Callback for TIMER5A  */
    &Appl_SecStartUpConfig, /* Notification Callback for WTIMER0A	*/
    &Appl_DimmingHanlder, /* Notification Callback for WTIMER1A	*/
    &Appl_SecTimerHanlder, /* Notification Callback for WTIMER2A	*/
    NULL_PTR, /* Notification Callback for WTIMER3A	*/
    NULL_PTR, /* Notification Callback for WTIMER4A	*/
    NULL_PTR, /* Notification Callback for WTIMER5A	*/
};

const Gpt_ConfigType GptConfigPtr[GPT_MAX_CH_NO] = 
{
    {
        GPT_TMR6,
        GPT_CH_MODE_CONTINUOUS_COUNTUP,
        GPT_PREDEF_TIMER_1000MS_32BIT,
    },
    {
        GPT_TMR7,
        GPT_CH_MODE_CONTINUOUS_COUNTUP,
        GPT_PREDEF_TIMER_100MS_32BIT,
    },
    {
        GPT_TMR8,
        GPT_CH_MODE_CONTINUOUS_COUNTUP,
        GPT_PREDEF_TIMER_1000MS_32BIT,
        
    }
};

 
/**********************************************************************************************************************
 *  END OF FILE: Gpt_Lcfg.c
 *********************************************************************************************************************/
