    /**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Mcu_Hw.h
 *       Module:  Mcu_Hw
 *
 *  Description:  header file for Registers definition    
 *  
 *********************************************************************************************************************/
#ifndef MCU_HW_H
#define MCU_HW_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
/*Interrupt Control Register definition - Part of SCB Registers*/

typedef struct 
{
    uint32 VECACT   :8;
    uint32          :3;
    uint32 RETBASE  :1;
    uint32 VECPEND  :8;
    uint32          :2;
    uint32 ISRPEND  :1;
    uint32 ISRPRE   :1;
    uint32          :1;
    uint32 PENDSTCLR:1;
    uint32 PENDSTSET:1;
    uint32 UNPENDSV :1;
    uint32 PENDSV   :1;
    uint32          :2;
    uint32 NMISET   :1; 
}INTCTRL_BF;
typedef union 
{
    uint32 R; /*Reference for the register can be used for complete register write*/
    INTCTRL_BF B;
}INTCTRL_Tag;



/*GPIO Register definition*/
/*PORT*/

/* Port Control
    - GPIOPCTL*/

/*Mode Control
    - GPIOAFSEL
    - GPIOADCCTL
    - GPIODMACTL*/


/*Commit Control
    - GPIOLOCK
    - GPIOCR*/

/*Data Control 
    - GPIODIR
    - GPIODATA*/

/* Interrupt Control
    - GPIOIM
    - GPIOICR
    - GPIOIS
    - GPIORIS   - GPIO Interrupt Sense
    ----------
    - GPIOIBE   - GPIO Interrupt Both Edges
    - GPIOIEV   - GPIO Interrupt Event
    - GPIOMIS
    - GPIOSI

*/


/*  PAD Control
    - GPIOPUR
    - GPIOPDR
    - GPIOODR
    - GPIODEN
    ----------
    - GPIODR2R
    - GPIODR4R
    - GPIODR8R
    - GPIOSLR
    - GPIOAMSEL
    */


/*DIO*/
/*To have DIO working the following Register configuration required*/
/*
1. GPIOAFSEL
2. GPIODEN
3. PMCx bit field in the GPIO Port Control (GPIOPCTL) */


/*GPT Register definition*/


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


#define GPIO_UNLOCK_PATTERN                     0x4C4F434B







#define CORTEXM4_PERI_BASE_ADDRESS              0xE000E000
#define SYSTEM_CTRL_BASE_ADDRESS                0x400FE000

#define PORTA_APB_BASE_ADDRESS                  0x40004000
#define PORTB_APB_BASE_ADDRESS                  0x40005000
#define PORTC_APB_BASE_ADDRESS                  0x40006000
#define PORTD_APB_BASE_ADDRESS                  0x40007000
#define PORTE_APB_BASE_ADDRESS                  0x40024000
#define PORTF_APB_BASE_ADDRESS                  0x40025000

/*X Port Register Address start by Zero */
#define PORTX_APB_BASE_ADDRESS(X)           ((X<=3)? (0x40004000 + (X*0x1000)):(0x40024000 + ((X-4)*0x1000)))

#define RCGCGPIO                            *((volatile uint32*)(SYSTEM_CTRL_BASE_ADDRESS+0x608))
#define SRWTIMER                            *((volatile uint32*)(SYSTEM_CTRL_BASE_ADDRESS+0x55C))
#define RCGCTIMER                           *((volatile uint32*)(SYSTEM_CTRL_BASE_ADDRESS+0x604))
#define RCGCWTIMER                          *((volatile uint32*)(SYSTEM_CTRL_BASE_ADDRESS+0x65C))



#define APINT                               *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0xD0C))
#define INTCTRL                             *((volatile INTCTRL_Tag*)(CORTEXM4_PERI_BASE_ADDRESS+0xD04))  /*DONE*/

#define NVIC_EN0                            *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0x100))
#define NVIC_EN1                            *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0x104))

#define NVIC_EN2                            *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0x108))
#define NVIC_EN3                            *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS+0x10C))

/*PORT X APB Registers*/


#define PORTX_ِAPB_GPIODATA(X)          *((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x000))   
#define PORTX_ِAPB_GPIODATA_MASK(X,MASK)*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+((uint16)(MASK<<2))))   
#define PORTX_ِAPB_GPIODIR(X)          	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x400))   
#define PORTX_ِAPB_GPIOIS(X)           	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x404))   
#define PORTX_ِAPB_GPIOIBE(X)       	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x408))   
#define PORTX_ِAPB_GPIOIEV(X)          	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x40C))   
#define PORTX_ِAPB_GPIOIM(X)        	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x410))   
#define PORTX_ِAPB_GPIORIS(X) 			*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x414))	
#define PORTX_ِAPB_GPIOMIS(X) 			*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x418))	
#define PORTX_ِAPB_GPIOICR(X) 			*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x41C))	
#define PORTX_ِAPB_GPIOAFSEL(X)        	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x420))   
#define PORTX_ِAPB_GPIODR2R(X)         	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x500))   
#define PORTX_ِAPB_GPIODR4R(X)         	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x504))   
#define PORTX_ِAPB_GPIODR8R(X)         	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x508))   
#define PORTX_ِAPB_GPIOODR(X)          	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x50C))   
#define PORTX_ِAPB_GPIOPUR(X)          	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x510))   
#define PORTX_ِAPB_GPIOPDR(X)          	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x514))   
#define PORTX_ِAPB_GPIOSLR(X)          	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x518))   
#define PORTX_ِAPB_GPIODEN(X)          	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x51C))   
#define PORTX_ِAPB_GPIOLOCK(X)         	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x520))   
#define PORTX_ِAPB_GPIOCR(X)           	*((volatile uint32*)(PORTX_APB_BASE_ADDRESS(X)+0x524))  

/*PORT A APB Registers*/
#define PORTA_ِAPB_GPIODATA         	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x000))   
#define PORTA_ِAPB_GPIODATA_MASK(MASK)  *((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x000+((uint16)(MASK<<2))))   
#define PORTA_ِAPB_GPIODIR          	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x400))   
#define PORTA_ِAPB_GPIOIS           	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x404))   
#define PORTA_ِAPB_GPIOIBE          	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x408))   
#define PORTA_ِAPB_GPIOIEV              *((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x40C))   
#define PORTA_ِAPB_GPIOIM        	    *((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x410))   
#define PORTA_ِAPB_GPIORIS 			    *((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x414))	
#define PORTA_ِAPB_GPIOMIS 			    *((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x418))	
#define PORTA_ِAPB_GPIOICR 			    *((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x41C))	
#define PORTA_ِAPB_GPIOAFSEL        	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x420))   
#define PORTA_ِAPB_GPIODR2R         	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x500))   
#define PORTA_ِAPB_GPIODR4R         	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x504))   
#define PORTA_ِAPB_GPIODR8R         	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x508))   
#define PORTA_ِAPB_GPIOODR          	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x50C))   
#define PORTA_ِAPB_GPIOPUR          	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x510))   
#define PORTA_ِAPB_GPIOPDR          	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x514))   
#define PORTA_ِAPB_GPIOSLR          	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x518))   
#define PORTA_ِAPB_GPIODEN          	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x51C))   
#define PORTA_ِAPB_GPIOLOCK         	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x520))   
#define PORTA_ِAPB_GPIOCR           	*((volatile uint32*)(PORTA_APB_BASE_ADDRESS+0x524))  

	 /*PORT B APB Registers*/
#define PORTB_ِAPB_GPIODATA         	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x000))
#define PORTB_ِAPB_GPIODATA_MASK(MASK)  *((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x000+((uint16)(MASK<<2))))      
#define PORTB_ِAPB_GPIODIR          	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x400))   
#define PORTB_ِAPB_GPIOIS           	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x404))   
#define PORTB_ِAPB_GPIOIBE          	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x408))   
#define PORTB_ِAPB_GPIOIEV          	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x40C))   
#define PORTB_ِAPB_GPIOIM        	    *((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x410))   
#define PORTB_ِAPB_GPIORIS 			    *((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x414))	
#define PORTB_ِAPB_GPIOMIS 			    *((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x418))	
#define PORTB_ِAPB_GPIOICR 			    *((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x41C))	
#define PORTB_ِAPB_GPIOAFSEL        	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x420))   
#define PORTB_ِAPB_GPIODR2R         	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x500))   
#define PORTB_ِAPB_GPIODR4R         	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x504))   
#define PORTB_ِAPB_GPIODR8R         	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x508))   
#define PORTB_ِAPB_GPIOODR          	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x50C))   
#define PORTB_ِAPB_GPIOPUR          	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x510))   
#define PORTB_ِAPB_GPIOPDR          	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x514))   
#define PORTB_ِAPB_GPIOSLR          	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x518))   
#define PORTB_ِAPB_GPIODEN          	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x51C))   
#define PORTB_ِAPB_GPIOLOCK         	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x520))   
#define PORTB_ِAPB_GPIOCR           	*((volatile uint32*)(PORTB_APB_BASE_ADDRESS+0x524))


	 /*PORT C APB Registers*/
#define PORTC_ِAPB_GPIODATA         	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x000))
#define PORTC_ِAPB_GPIODATA_MASK(MASK)  *((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x000+((uint16)(MASK<<2))))   
#define PORTC_ِAPB_GPIODIR          	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x400))
#define PORTC_ِAPB_GPIOIS           	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x404))
#define PORTC_ِAPB_GPIOIBE          	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x408))
#define PORTC_ِAPB_GPIOIEV          	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x40C))
#define PORTC_ِAPB_GPIOIM        	    *((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x410))
#define PORTC_ِAPB_GPIORIS 			    *((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x414))
#define PORTC_ِAPB_GPIOMIS 			    *((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x418))
#define PORTC_ِAPB_GPIOICR 			    *((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x41C))
#define PORTC_ِAPB_GPIOAFSEL        	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x420))
#define PORTC_ِAPB_GPIODR2R         	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x500))
#define PORTC_ِAPB_GPIODR4R         	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x504))
#define PORTC_ِAPB_GPIODR8R         	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x508))
#define PORTC_ِAPB_GPIOODR          	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x50C))
#define PORTC_ِAPB_GPIOPUR          	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x510))
#define PORTC_ِAPB_GPIOPDR          	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x514))
#define PORTC_ِAPB_GPIOSLR          	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x518))
#define PORTC_ِAPB_GPIODEN          	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x51C))
#define PORTC_ِAPB_GPIOLOCK         	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x520))
#define PORTC_ِAPB_GPIOCR           	*((volatile uint32*)(PORTC_APB_BASE_ADDRESS+0x524))

	 /*PORT D APB Registers*/
#define PORTD_ِAPB_GPIODATA         	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x000))
#define PORTD_ِAPB_GPIODATA_MASK(MASK)  *((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x000+((uint16)(MASK<<2))))   
#define PORTD_ِAPB_GPIODIR          	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x400))
#define PORTD_ِAPB_GPIOIS           	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x404))
#define PORTD_ِAPB_GPIOIBE          	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x408))
#define PORTD_ِAPB_GPIOIEV          	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x40C))
#define PORTD_ِAPB_GPIOIM        	    *((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x410))
#define PORTD_ِAPB_GPIORIS 			    *((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x414))
#define PORTD_ِAPB_GPIOMIS 			    *((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x418))
#define PORTD_ِAPB_GPIOICR 			    *((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x41C))
#define PORTD_ِAPB_GPIOAFSEL        	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x420))
#define PORTD_ِAPB_GPIODR2R         	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x500))
#define PORTD_ِAPB_GPIODR4R         	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x504))
#define PORTD_ِAPB_GPIODR8R         	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x508))
#define PORTD_ِAPB_GPIOODR          	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x50C))
#define PORTD_ِAPB_GPIOPUR          	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x510))
#define PORTD_ِAPB_GPIOPDR          	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x514))
#define PORTD_ِAPB_GPIOSLR          	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x518))
#define PORTD_ِAPB_GPIODEN          	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x51C))
#define PORTD_ِAPB_GPIOLOCK         	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x520))
#define PORTD_ِAPB_GPIOCR           	*((volatile uint32*)(PORTD_APB_BASE_ADDRESS+0x524))


	 /*PORT E APB Registers*/
#define PORTE_ِAPB_GPIODATA         	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x000))
#define PORTE_ِAPB_GPIODATA_MASK(MASK)  *((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x000+((uint16)(MASK<<2))))   
#define PORTE_ِAPB_GPIODIR          	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x400))
#define PORTE_ِAPB_GPIOIS           	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x404))
#define PORTE_ِAPB_GPIOIBE          	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x408))
#define PORTE_ِAPB_GPIOIEV          	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x40C))
#define PORTE_ِAPB_GPIOIM        	    *((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x410))
#define PORTE_ِAPB_GPIORIS 			    *((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x414))
#define PORTE_ِAPB_GPIOMIS 			    *((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x418))
#define PORTE_ِAPB_GPIOICR 			    *((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x41C))
#define PORTE_ِAPB_GPIOAFSEL        	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x420))
#define PORTE_ِAPB_GPIODR2R         	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x500))
#define PORTE_ِAPB_GPIODR4R         	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x504))
#define PORTE_ِAPB_GPIODR8R         	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x508))
#define PORTE_ِAPB_GPIOODR          	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x50C))
#define PORTE_ِAPB_GPIOPUR          	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x510))
#define PORTE_ِAPB_GPIOPDR          	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x514))
#define PORTE_ِAPB_GPIOSLR          	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x518))
#define PORTE_ِAPB_GPIODEN          	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x51C))
#define PORTE_ِAPB_GPIOLOCK         	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x520))
#define PORTE_ِAPB_GPIOCR           	*((volatile uint32*)(PORTE_APB_BASE_ADDRESS+0x524))


	 /*PORT F APB Registers*/
#define PORTF_ِAPB_GPIODATA         	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x000))
#define PORTF_ِAPB_GPIODATA_MASK(MASK)  *((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x000+((uint16)(MASK<<2))))   
#define PORTF_ِAPB_GPIODIR          	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x400))
#define PORTF_ِAPB_GPIOIS           	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x404))
#define PORTF_ِAPB_GPIOIBE          	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x408))
#define PORTF_ِAPB_GPIOIEV          	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x40C))
#define PORTF_ِAPB_GPIOIM        	    *((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x410))
#define PORTF_ِAPB_GPIORIS 			    *((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x414))
#define PORTF_ِAPB_GPIOMIS 			    *((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x418))
#define PORTF_ِAPB_GPIOICR 			    *((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x41C))
#define PORTF_ِAPB_GPIOAFSEL        	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x420))
#define PORTF_ِAPB_GPIODR2R         	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x500))
#define PORTF_ِAPB_GPIODR4R         	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x504))
#define PORTF_ِAPB_GPIODR8R         	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x508))
#define PORTF_ِAPB_GPIOODR          	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x50C))
#define PORTF_ِAPB_GPIOPUR          	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x510))
#define PORTF_ِAPB_GPIOPDR          	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x514))
#define PORTF_ِAPB_GPIOSLR          	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x518))
#define PORTF_ِAPB_GPIODEN          	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x51C))
#define PORTF_ِAPB_GPIOLOCK         	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x520))
#define PORTF_ِAPB_GPIOCR           	*((volatile uint32*)(PORTF_APB_BASE_ADDRESS+0x524))

#define PORTF_PIN_0                         PORTF_ِAPB_GPIODATA_MASK(0U)
#define PORTF_PIN_1                         PORTF_ِAPB_GPIODATA_MASK(1U)
#define PORTF_PIN_2                         PORTF_ِAPB_GPIODATA_MASK(2U)    
#define PORTF_PIN_3                         PORTF_ِAPB_GPIODATA_MASK(3U)
#define PORTF_PIN_4                         PORTF_ِAPB_GPIODATA_MASK(4U)
#define PORTF_PIN_5                         PORTF_ِAPB_GPIODATA_MASK(5U)



/******************************* GPTM Registers ******************************/
#if 0
/*GPT Registers definations */
typedef struct 
{
    uint32 GPTMCFG  :3; /*0x4: select Timer without concatenation*/
    uint32          :29;
}GPTMCFG_BF;

typedef union 
{
    uint32 R; /*Reference for the register can be used for complete register write*/
    GPTMCFG_BF B;
}GPTMCFG_Tag;

#endif


/*X Port Register Address start by Zero */
#define GPTX_BASE_ADDRESS(X)            ((X<=7)? (0x40030000 + (X*0x1000)):(0x4004C000 + ((X-8)*0x1000)))

/*  Common GPT Registers */
#define GPTMCFG(X)                      *((volatile uint32*)(GPTX_BASE_ADDRESS(X)+0x000))        
#define GPTMCTL(X)                      *((volatile uint32*)(GPTX_BASE_ADDRESS(X)+0x00C))  
#define GPTMIMR(X)                      *((volatile uint32*)(GPTX_BASE_ADDRESS(X)+0x018))  

#define GPTMICR(X)                      *((volatile uint32*)(GPTX_BASE_ADDRESS(X)+0x024))  

/*  Common TIMER A GPT Registers */
#define GPTMTAMR(X)                     *((volatile uint32*)(GPTX_BASE_ADDRESS(X)+0x004))  
#define GPTMTAILR(X)                    *((volatile uint32*)(GPTX_BASE_ADDRESS(X)+0x028))  


#define GPTMTAV(X)                      *((volatile uint32*)(GPTX_BASE_ADDRESS(X)+0x050))  
#define GPTMTAR(X)                      *((volatile uint32*)(GPTX_BASE_ADDRESS(X)+0x048))  
#define GPTMTAPR(X)                     *((volatile uint32*)(GPTX_BASE_ADDRESS(X)+0x038))  
/*  Common TIMER B GPT Registers */



/*
    Timer A Control
---------------------
    - GPTMTAPS
    - GPTMTAPMR
    - GPTMTAILR
    - GPTMTAMATCHR
    - GPTMTAPR
    - GPTMTAMR    */

/*  Timer B Control
---------------------
    - GPTMTBPMR
    - GPTMTBILR
    - GPTMTBMATCHR
    - GPTMTBPR
    - GPTMTBMR
    - GPTMTBPS */


/* Interrupt - Config
----------------------
    - GPTMCFG
    - GPTMRIS
    - GPTMICR
    - GPTMMIS
    - GPTMIMR
    - GPTMCTL
    - GPTMSYNC
    - GPTMPP */
/******************************* GPTM Registers ******************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 

 
#endif  /* MCU_HW_H */

/**********************************************************************************************************************
 *  END OF FILE: Mcu_Hw.h
 *********************************************************************************************************************/
