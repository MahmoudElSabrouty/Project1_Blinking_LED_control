/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Gpt.h
 *       Module:  Gpt
 *
 *  Description:  header file for Gpt Module    
 *  
 *********************************************************************************************************************/
#ifndef GPT_H
#define GPT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Mcu_Hw.h"
#include "Gpt_Types.h"
#include "Gpt_Cfg.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define GPTMCFG_TIMER_A_ONLY                   (0x04U) /*Driver didn't support concatenated mode*/


#define GPTMCFG_TAAMS_PWM_ENABLE               (1U<<3)
#define GPTMCFG_TAMR_ONESHOT                    0x01U
#define GPTMCFG_TAMR_PERIODIC                   0x02U
#define GPTMCFG_TAPWMIE_ENABLE                  (1U<<9)
#define GPTMCFG_TACDIR_COUNTUP                  (1U<<4) /*1: Count Up*/
#define GPTMCTL_TAEN                            (1U)
#define GPTMCTL_TBEN                         (0x100U)
#define GPTMIMR_TATOIM                          (1U)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
extern const Gpt_ConfigType GptConfigPtr[GPT_MAX_CH_NO];
extern const GptCallbackNotificationPtr gptCallbackNotifications[12];
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
 
/******************************************************************************
* \Syntax          : void Gpt_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

void Gpt_Init(const Gpt_ConfigType * ConfigPtr);
/******************************************************************************
* \Syntax          : void Gpt_StartStop(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

void Gpt_StopTimer(Gpt_ChannelType channelId);
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

void Gpt_StartTimer(Gpt_ChannelType channelId, Gpt_ValueType TimerVale);

void Gpt_ISRClear(Gpt_ChannelType channelId);
#endif  /* GPT_H */

/**********************************************************************************************************************
 *  END OF FILE: Gpt.h
 *********************************************************************************************************************/
