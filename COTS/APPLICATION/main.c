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
#define MAX_ALLOWED_STARTUP_TIME_CONFIG     30
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

 static  SystemStates stateMachine =CONFIG_MODE;
 static  sint8 onTimeInputCounterSec =0;
 static  sint8 offTimeInputCounterSec =0;

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
#if 1
	  RCGCGPIO |= (1<<5);   /* Set bit5 of RCGCGPIO to enable clock to PORTF*/
    
	 /* PORTF0 has special function, need to unlock to modify */
    PORTF_ِAPB_GPIOLOCK = 0x4C4F434B;   /* unlock commit register */
    PORTF_ِAPB_GPIOCR = 0x01;           /* make PORTF0 configurable */
    PORTF_ِAPB_GPIOLOCK = 0;            /* lock commit register */


    /*Initialize PF3 as a digital output, PF0 and PF4 as digital input pins */
	
    PORTF_ِAPB_GPIODIR &= ~(1<<4)|~(1<<0);  /* Set PF4 and PF0 as a digital input pins */
    PORTF_ِAPB_GPIODIR |= (1<<3);           /* Set PF3 as digital output to control green LED */
    PORTF_ِAPB_GPIODEN |= (1<<4)|(1<<3)|(1<<0);             /* make PORTF4-0 digital pins */
    PORTF_ِAPB_GPIOPUR |= (1<<4)|(1<<0);             /* enable pull up for PORTF4, 0 */
    
    /* configure PORTF4, 0 for falling edge trigger interrupt */
    PORTF_ِAPB_GPIOIS  &= ~(1<<4)|~(1<<0);        /* make bit 4, 0 edge sensitive */
    PORTF_ِAPB_GPIOIBE &=~(1<<4)|~(1<<0);         /* trigger is controlled by IEV */
    PORTF_ِAPB_GPIOIEV &= ~(1<<4)|~(1<<0);        /* falling edge trigger */
    PORTF_ِAPB_GPIOICR |= (1<<4)|(1<<0);          /* clear any prior interrupt */
    PORTF_ِAPB_GPIOIM  |= (1<<4)|(1<<0);          /* unmask interrupt */
    
    /* enable interrupt in NVIC and set priority to 3 */
   // NVIC->IP[30] = 3 << 5;     /* set interrupt priority to 3 */
    NVIC_EN0 |= (1<<30);      /*IQR 30 - Enable PORTF Interrupt */


#else
    Port_Init(PortConfigPtr);
    Gpt_Init(GptConfigPtr);
    IntCrtl_Init();
#endif

	while(1){

        switch(stateMachine)
        {
            case CONFIG_MODE:


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
    
    if(StartupTimeTolerance > 0)
    {
        StartupTimeTolerance--;
    }else
    {   
        stateMachine =RUNNING_MODE;
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



    switch(RunningSubStates)
    {
        case ON_TIME:
            if (ontimeCalc>0)
            {
                ontimeCalc--;
            }else
            {
                RunningSubStates = DIMMING_TIME;
                Dio_WriteChannel(PIN_LED1, PORT_LED1, DIO_PIN_LOW);
                Gpt_StopTimer(GPT_TMR8);
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
                Dio_WriteChannel(PIN_LED1, PORT_LED1, DIO_PIN_LOW);
                Gpt_StopTimer(GPT_TMR8);
                Gpt_StopTimer(GPT_TMR7);
                offTimerControl =0;
            }

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
                Gpt_StartTimer(GPT_TMR8,GPT_PREDEF_TIMER_1000MS_32BIT);
                ontimeCalc = onTimeInputCounterSec;
                onTimerControl =0xFF;
            }

        break;

        case DIMMING_TIME:
            if (offTimerControl ==0)
            {
                Dio_WriteChannel(PIN_LED1, PORT_LED1, DIO_PIN_HIGH);
                Gpt_StartTimer(GPT_TMR8,GPT_PREDEF_TIMER_1000MS_32BIT);
                offtimeCalc = offTimeInputCounterSec;
                offTimerControl =0xFF;

                Gpt_StartTimer(GPT_TMR7,GPT_PREDEF_TIMER_100MS_32BIT);
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
    
    if (startTimerOnce ==0)
    {
           Gpt_StartTimer(GPT_TMR6,GPT_PREDEF_TIMER_1000MS_32BIT);
           startTimerOnce =0xFF;
    }




}




void GpioIsrHandler(void)
{

    if(stateMachine ==CONFIG_MODE)
    {
        if (PORTF_ِAPB_GPIOMIS & (1<<PIN_SW1)) /* check if interrupt causes by PF4/SW1*/
        {  
            onTimeInputCounterSec++;
            PORTF_ِAPB_GPIOICR |= (1<<PIN_SW1); 
        }
        else if (PORTF_ِAPB_GPIOMIS & (1<<PIN_SW2)) /* check if interrupt causes by PF0/SW2 */
        { 
            offTimeInputCounterSec++;
            PORTF_ِAPB_GPIOICR |= (1<<PIN_SW2); 
        }
    }
}
/**********************************************************************************************************************
 *  END OF FILE: Main.c
 *********************************************************************************************************************/
