/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gpt_Types.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef GPT_TYPES_H
#define GPT_TYPES_H

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


typedef enum{
        GPT_TMR0 =0 ,		/*16/32-bit Timer 0 base: 0x4003.0000			*/
        GPT_TMR1    ,       /*16/32-bit Timer 1 base: 0x4003.1000         	*/
        GPT_TMR2    ,       /*16/32-bit Timer 2 base: 0x4003.2000         	*/
        GPT_TMR3    ,       /*16/32-bit Timer 3 base: 0x4003.3000         	*/
        GPT_TMR4    ,       /*16/32-bit Timer 4 base: 0x4003.4000         	*/
        GPT_TMR5    ,       /*16/32-bit Timer 5 base: 0x4003.5000         	*/
        GPT_TMR6    ,       /*32/64-bit Wide Timer 0 base: 0x4003.6000    	*/
        GPT_TMR7    ,       /*32/64-bit Wide Timer 1 base: 0x4003.7000    	*/
        GPT_TMR8    ,       /*32/64-bit Wide Timer 2 base: 0x4004.C000    	*/
        GPT_TMR9    ,       /*32/64-bit Wide Timer 3 base: 0x4004.D000    	*/
        GPT_TMR10   ,      /*32/64-bit Wide Timer 4 base: 0x4004.E000    	*/
        GPT_TMR11   ,      /*32/64-bit Wide Timer 5 base: 0x4004.F000    	*/   
}Gpt_ChannelType;

typedef uint32 Gpt_ValueType;

typedef enum{
    GPT_PREDEF_TIMER_10MS_32BIT     = 160000U,
    GPT_PREDEF_TIMER_100MS_32BIT    = 1600000U,
    GPT_PREDEF_TIMER_500MS_32BIT    = 8000000U,
    GPT_PREDEF_TIMER_1000MS_32BIT   = 16000000U,
    GPT_PREDEF_TIMER_2000MS_32BIT   = 32000000U
}Gpt_PredefTimerType;


typedef enum{
    GPT_CH_MODE_CONTINUOUS_COUNTUP =0,
    GPT_CH_MODE_ONESHOT_COUNTUP,
#ifdef GPT_PWM_ENABLE    
    GPT_CH_MODE_PWM_PERIODIC,
#endif
}Gpt_ChannelModeType;

typedef void (*GptCallbackNotificationPtr)(void);

typedef struct
{
    /*All GPT configuration elements */
    Gpt_ChannelType     channelId;
    Gpt_ChannelModeType gptChannelMode;
    Gpt_PredefTimerType gptPredefinedValue;
}Gpt_ConfigType;

 
#endif  /* GPT_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: Gpt_Types.h
 *********************************************************************************************************************/
