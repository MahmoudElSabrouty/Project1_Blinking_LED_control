/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Main.c
 *        \brief  Main File for Main Function Application implmentation 
 *
 *      \details   main is used for Main Function Application implmentation     
 * 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Mcu_Hw.h"
#include "Gpt.h"
#include "Port.h"
#include "Dio.h"
#include "APPL_MAIN.h" 
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	
#define MAX_ALLOWED_STARTUP_TIME_CONFIG     5
#define USE_PRECONFIGURED_LIGHT_TIMING		
#define PRECONFIGURED_LIGHT_ON_TIMING_SEC		15
#define PRECONFIGURED_LIGHT_OFF_TIMING_SEC	10
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
typedef enum{
    CONFIG_MODE,
    RUNNING_MODE,
}SystemStates;
    
typedef enum{
    ON_TIME,
    DIMMING_TIME,
}RunningStates;
        

    static uint8 onTimerControl =0;
    static uint8 offTimerControl =0;
    static uint8 dimmingTimerControl =0;
    static RunningStates RunningSubStates =ON_TIME;


    static sint8 ontimeCalc =0; 
    static sint8 offtimeCalc =0;

    static SystemStates stateMachine =CONFIG_MODE;
    static sint8 onTimeInputCounterSec =0;
    static sint8 offTimeInputCounterSec =0;

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
static  void HandleUserInput( Dio_LevelType sw1Status,  Dio_LevelType sw2Status);
static void    RunningStateHanlder(void);
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void main(void)                                      
* \Description     : main function is application program entry point and has 
                    System super infinite loop                                     
**
**Purpose:** Control **blinking** of an **LED** for a *user-defined* **ON and OFF periods**

- Create a function in the **App layer** that takes as an **input** from the user:
    - a specific **ON time** and **OFF time** in seconds,   --> SW presses 
    - **lights** a LED for the given **ON time**            --> SW presses 
    - and **dim** it for the given **OFF time**.            
    - It’s prohibited to use predefined delay functions, only **timer driver** functions can be used.
    - This function implements implicitly the PWM module using ***Timer Overflow***.
*                                                                            
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

main(void)
{
    static Dio_LevelType sw1State = DIO_PIN_SNA;
    static Dio_LevelType sw2State = DIO_PIN_SNA;
    
		
    Port_Init(PortConfigPtr);
    Gpt_Init(GptConfigPtr);
    IntCrtl_Init();


	while(1){

        switch(stateMachine)
        {
            case CONFIG_MODE:

                sw1State = Dio_ReadChannel(PIN_SW1, PORT_SW1);
                sw2State = Dio_ReadChannel(PIN_SW2, PORT_SW2);
                HandleUserInput(sw1State,sw2State);

            break;

            case RUNNING_MODE:
                RunningStateHanlder();
            break;
                

        }
    }

}

/******************************************************************************
* \Syntax          : void Appl_1SecStartUpConfig(void)                                      
* \Description     : Allow 30 sec from ECU powerup to receive user On/Off Timing configuration 
                    through SW1, SW2                                     
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

void Appl_SecStartUpConfig(void)
{
    static sint8 StartupTimeTolerance = MAX_ALLOWED_STARTUP_TIME_CONFIG;
    Gpt_ISRClear(GPT_TMR6);   
    if(StartupTimeTolerance > 0)
    {
        StartupTimeTolerance--;
    }else
    {   
        stateMachine =RUNNING_MODE;
        Gpt_StartTimer(GPT_TMR8,GPT_PREDEF_TIMER_1000MS_32BIT);
        Gpt_StopTimer(GPT_TMR6);
    }

}



/******************************************************************************
* \Syntax          : void Appl_1SecTimerHanlder(void)                                      
* \Description     : main function is application program entry point and has 
                    System super infinite loop                                     
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/



void Appl_SecTimerHanlder(void)
{


    Gpt_ISRClear(GPT_TMR8); 
    switch(RunningSubStates)
    {
        case ON_TIME:
            if (ontimeCalc>0)
            {
                ontimeCalc--;
            }else
            {
                RunningSubStates = DIMMING_TIME;
                ((offTimeInputCounterSec ==0)? (offtimeCalc = PRECONFIGURED_LIGHT_OFF_TIMING_SEC):(offtimeCalc = offTimeInputCounterSec));
               
              
                onTimerControl =0;
            }
            
        break;

        case DIMMING_TIME:

            if (offtimeCalc>0)
            {
									offtimeCalc--;
            }else
            {
                RunningSubStates = ON_TIME;
                ((onTimeInputCounterSec ==0)? (ontimeCalc = PRECONFIGURED_LIGHT_ON_TIMING_SEC):(ontimeCalc = onTimeInputCounterSec));
               
            
                Gpt_StopTimer(GPT_TMR7);
                offTimerControl =0;
            }

        break;
        
        default:
            /*Do nothing*/
        break;
    }
}


/******************************************************************************
* \Syntax          : void Appl_DimmingHanlder(void)                                      
* \Description     : main function is application program entry point and has 
                    System super infinite loop                                     
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

void Appl_DimmingHanlder(void)
{
    Gpt_ISRClear(GPT_TMR7); 
    Dio_FlipChannel(PIN_LED1, PORT_LED1);    
}

/******************************************************************************
* \Syntax          : void RunningStateHanlder(void)                                      
* \Description     : handle main login during Running State
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

static void    RunningStateHanlder(void)
{
        
    switch(RunningSubStates)
    {
        case ON_TIME:

            if (onTimerControl ==0)
            {
                Dio_WriteChannel(PIN_LED1, PORT_LED1, DIO_PIN_HIGH);
              
                
                ((onTimeInputCounterSec ==0)? (ontimeCalc = PRECONFIGURED_LIGHT_ON_TIMING_SEC):(ontimeCalc = onTimeInputCounterSec));
                
                
                onTimerControl =0xFF;
            }

        break;

        case DIMMING_TIME:
            if (offTimerControl ==0)
            {
                Dio_WriteChannel(PIN_LED1, PORT_LED1, DIO_PIN_HIGH);
           
                
                ((offTimeInputCounterSec ==0)? (offtimeCalc = PRECONFIGURED_LIGHT_OFF_TIMING_SEC):(offtimeCalc = offTimeInputCounterSec));
           
                offTimerControl =0xFF;

                Gpt_StartTimer(GPT_TMR7,GPT_PREDEF_TIMER_500MS_32BIT);
                dimmingTimerControl =0xFF;
            }

        break;

    }
}
/******************************************************************************
* \Syntax          : void HandleUserInput( Dio_LevelType sw1Status,  Dio_LevelType sw2Status)
* \Description     : Allow 30 sec from ECU powerup to receive user On/Off Timing configuration through SW1, SW2                                     
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/

static void HandleUserInput( Dio_LevelType sw1Status,  Dio_LevelType sw2Status)
{
    static uint8 startTimerOnce =0;
    uint8 iter = 100;

    Dio_ISR_Clear(PIN_LED1, PORT_LED1);
    if (startTimerOnce ==0)
    {
           Gpt_StartTimer(GPT_TMR6,GPT_PREDEF_TIMER_1000MS_32BIT);
           startTimerOnce =0xFF;
    }

		

}


void GpioIsrHandler(void)
{

 


        if (PORTF_ِAPB_GPIOMIS & (1<<PIN_SW1)) /* check if interrupt causes by PF4/SW1*/
        {  
            onTimeInputCounterSec++;
            Dio_ISR_Clear(PIN_SW1, PORT_SW1);
	
        }
        else if(PORTF_ِAPB_GPIOMIS & (1<<PIN_SW2)) /* check if interrupt causes by PF0/SW2 */
        { 
            offTimeInputCounterSec++;
            Dio_ISR_Clear(PIN_SW2, PORT_SW2);
  
        }
    

}
/**********************************************************************************************************************
 *  END OF FILE: Main.c
 *********************************************************************************************************************/
