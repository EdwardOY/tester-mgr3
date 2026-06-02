/**
  ******************************************************************************
  * @Filename  stm_stkdelay.h
	* @Mcu :     cortex-Mx  stmxxx
  * @brief     headfile of precise delay module based on Systick Clock
  * @author    Edward·OY
  * @CurVer    V5.3(Verified well)
  * @Date :    2022.7.24
  * @date  

*****************************************************************************
  * @note&attention: 
  *   1 devellop platform :
        1.1 default Apollo STM32F429IGTB
				1.2 ATKF103rbt6 mini v1.9
        1.3 PandoraL475VET6 				
  *   2	RTOS api: CMSIS_RTOS2
  ******************************************************************************
	* @tech
       			
  ******************************************************************************
	* @update 
	    V5.3 2022.7.24
			     [+] stkdly_rst(),reset,clear and close systick 	
	    V5.2 2022.4.13 
			     [+] RTX5，注意要用osDelay，而不是用osDelayUntil
	    V5.1：2021.8.31
			      注释更新
			      void stkdly_s(u8_t);
	    V5.0：2018.9.25
	    V1.0：2015.1.23 初步测试成功
  */ 
	
#ifndef _STM_STKDELAY_H_
#define _STM_STKDELAY_H_

#include "ThisProj_Conf.h"
#include "convert_path.h"
#include MCU_HEAD
#include UTY_TYP_HEAD


#define FreqDiv_Stk        8
 
 // The valude of SysTick->CTRL
#define StkRegCtl           SysTick->CTRL //*((volatile unsigned long *)0xE000E0010)  
#define StkRegCtl_b_En       0x01
#define StkRegCtl_b_Int     (1 << 1)
#define StkRegCtl_b_Clk     (1 << 2)
#define StkRegCtl_b_Flag    (1 << 16)

#define MaxLoadVlu   SysTick_LOAD_RELOAD_Msk  // SysTick->Load max value :SysTick_LOAD_RELOAD_Msk = 2^24 = 0xffffffUL


void stkdly_init(uint16_t SYSCLK);
void stkdly_ms(uint16_t nms);
void stkdly_us(uint32_t nus);
void stkdly_rst(void);
void stkdly_enable(bool pEn);



#endif //<end,#ifndef _STM_STKDELAY_H_>

/*---------------endline:the overall file ----------------*/

