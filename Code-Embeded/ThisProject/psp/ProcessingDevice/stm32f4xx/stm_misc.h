#ifndef  _STM_MISC_H_
#define  _STM_MISC_H_
#include "ThisProj_Glb.h"
#include SYS_HEAD
/* ****
* @Filename : stm_misc.h
* @For Miscellaneous devices module of mcu
* @Mcu : cortex-Mx  stm32xxx
* @Author : EDW.OY
* @version V5.0
* @Date : 2018.5.9
* @Copyright(C)  CLOU (CN) LTD.  2014-2024  All rights released	
*****************************************************************************
* @attention : 
*   1 Default devellop platform : Apollo STM32F429IGTB
*   2 devellop platform : Pandora STM32L475VET(LQFP100)
	
*/	

typedef struct {
	   SWH         it_en   ;  //INT switch 
	   u8_t        prio_prm; //PreemptPriority
   	 u8_t        prio_sub; //SubPriority
	   IRQn_Type   irqn;   
} nvic_para_t;  

extern void clock_enable_gpio( u32_t);
extern void clock_enable_uart( u32_t);
extern void clock_enable_dma( u32_t);
extern void clock_enable_spi( u32_t swh);
extern void clock_enable_can( u32_t swh);
extern void clock_enable_usbotg( u32_t swh);
extern void clock_enable_lcd(u32_t swh);
extern void clock_enable_ltdc(u32_t swh);
extern void clock_enable_timer(u32_t swh);

extern void _nvirq_cfg(nvic_para_t nv);
extern void _nvirq_dis(nvic_para_t nv);

/**
  * @brief  Sets the vector table location and Offset.
            中断向量表重定向
  * @param  NVIC_VectTab: specifies if the vector table is in RAM or FLASH memory.
  *   This parameter can be one of the following values:
  *     @arg NVIC_VectTab_RAM  ,exp 0x2000 0000
  *     @arg NVIC_VectTab_FLASH,exp 0x0800 0000
  * @param  Offset: Vector Table base offset field. This value must be a multiple 
  *         of 0x200.
  * @retval None
  */
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
	
#endif  /*----EndLine:Full file-----*/

