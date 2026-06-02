/*****
	* @brief: stmf4x_sys.h
	* @FOR  : RCC clock,FMC base address
	* @Mcu  : cortex-Mx  stmxxx
	* @Author : EDW.OY
	* @version V5.1( verified) 
  * @Date :   2018.5.9
	* @Copyright(C)  SAE Magnetics (H.K) LTD.  2014-2024  All rights released	
*****************************************************************************
* @attention : 
*   1 Default devellop platform : Apollo STM32F429IGTB
	
*****************************************************************************
   @update
*/

/* SYSTEM_SUPPORT_OS determines whether the file-system  supports  rtos
 * Follow usr_bsp_config.h
 * 0,not support
 * 1,support
 * OS_ENABLE comes from usr_bsp_config.h
 * !!Notice : sEnable "EXPORT  PendSV_Handler" of os_cpu_a.asm line45 if use uC/OS x
      sDisable it  if don`t use uC/OS x
 */ 
#ifndef _STM32F4_SYS_H_
#define _STM32F4_SYS_H_

#include "ThisProj_Conf.h"
#include "convert_path.h"
#include MCU_HEAD //#include "stm32f4xx.h"
#include UTY_TYP_HEAD

#include "core_cm4.h"

#ifdef USE_HAL_DRIVER
#include "stm32f4xx_hal.h"
#endif

#define MCU_SYSCLK_X_MHZ  (SystemCoreClock / 1000000)     //=180, Default main-frequency-MHz num of MCU


#endif //<#ifndef _PJT_GLB_HEAD_H_ >
#define MCU_SYSCLK_DFT    __180MHZ

#define MCU_APB1_MHZn      (MCU_SYSCLK_X_MHZ / 4)
#define MCU_APB1TIM_MHZn   (MCU_SYSCLK_X_MHZ / 2)
#define MCU_APB2_MHZn      (MCU_SYSCLK_X_MHZ / 2)
#define MCU_APB2TIM_MHZn    MCU_SYSCLK_X_MHZ 


#define MCU_BASEADDR_INFLS FLASH_BASE     // = 0x08000000ul  base addr of flash inside mcu, in stm32f4xx.h
#define MCU_BASEADDR_SRAM  0x20000000ul   // base addr of sram inside mcu
#define MCU_SZ_SRAM        (__KB * 192)   // 0x30000 ,192KB of sram inside mcu

#define MCU_BASEADDR_CCM   0x10000000ul  // base addr of CCM sram inside mcu
#define MCU_SZ_CCM         (__KB * 64)  // 0x10000 ,64KB of CCM sram inside mcu

#define ADDR_FMC_BK1   0x60000000ul // base addr of FMC bank1
#define SZ_FMC_BK1         (__MB * 256) // size of FMC bank1

#define ADDR_FMC_BK2   0x70000000ul  // base addr of FMC bank2
#define SZ_FMC_BK2         SZ_FMC_BK1  // size of FMC bank2

#define ADDR_FMC_BK3   0x80000000ul  // base addr of FMC bank3
#define SZ_FMC_BK3         SZ_FMC_BK1  // size of FMC bank3

#define ADDR_FMC_BK4   0x90000000ul  // base addr of FMC bank4
#define SZ_FMC_BK4         SZ_FMC_BK1  // size of FMC bank4

#define ADDR_FMC_BK5   0xC0000000ul  // base addr of FMC bank5,for SDRAM1 port
#define SZ_FMC_BK5         SZ_FMC_BK1  // size of FMC bank5

#define ADDR_FMC_BK6   0xD0000000ul    // base addr of FMC bank6,for SDRAM2 port
#define SZ_FMC_BK6         SZ_FMC_BK1    // size of FMC bank6


//-----------------MCU FMC NAND Flash--------------------
//PD6 nand闲/忙判定引脚IO
#define MCU_IO_FMCNAND_RB     PDin(6)
#define MCU_FMCBK_NAND        ADDR_FMC_BK3  // fmc bank for nand

#define MCU_FMCBK_LCD         ADDR_FMC_BK1   // fmc bank  for LCD
#define MCU_FMCBK_SDM         ADDR_FMC_BK5   // fmc bank  for sdram

#define MaxNum_ChnPerTim    9   //  Maximum channels of timer
/*
* Inside devices number of mcu
*/
#define McuDevNum_Tim      8

typedef struct{
  u32_t plln;
	u32_t pllm;
	u32_t pllp;
	u32_t pllq;	
	
}sttClkTree_t;	

extern sttClkTree_t stm32f4_168Mhz ,stm32f4_180Mhz , stm32f4_192Mhz;
	 
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).M4同M3类似,只是寄存器地址变了.
//IO口操作宏定义
#define BITBAND(addr, bitnum)   ((addr & 0xF0000000) + 0x2000000 +     \
                                ((addr & 0xFFFFF) << 5) + (bitnum << 2)) 
#define MEM_ADDR(addr)          *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)  MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014 
#define GPIOJ_ODR_ADDr    (GPIOJ_BASE+20) //0x40022414
#define GPIOK_ODR_ADDr    (GPIOK_BASE+20) //0x40022814

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010 
#define GPIOJ_IDR_Addr    (GPIOJ_BASE+16) //0x40022410 
#define GPIOK_IDR_Addr    (GPIOK_BASE+16) //0x40022810 

//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //输出 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //输入

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //输出 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //输入

#define PJout(n)   BIT_ADDR(GPIOJ_ODR_Addr,n)  //输出 
#define PJin(n)    BIT_ADDR(GPIOJ_IDR_Addr,n)  //输入

#define PKout(n)   BIT_ADDR(GPIOK_ODR_Addr,n)  //输出 
#define PKin(n)    BIT_ADDR(GPIOK_IDR_Addr,n)  //输入

extern void stm_clock_init(sttClkTree_t clk);
extern void init_clock_stm32f4x(u32_t plln,u32_t pllm,u32_t pllp,u32_t pllq);//时钟系统配置

////以下为汇编函数
//void WFI_SET(void);		//执行WFI指令
//void INTX_DISABLE(void);//关闭所有中断
//void INTX_ENABLE(void);	//开启所有中断
//void MSR_MSP(u32_t addr);	//设置堆栈地址 

/*******************^^^^^^^^^^^^^^^^^^^^^^^^^^^^**/


/*函数声明*******************************************************************************************/

void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset);                         /* 设置中断偏移量 */
void sys_standby(void);                                                                     /* 进入待机模式 */
void sys_soft_reset(void);                                                                  /* 系统软复位 */
uint8_t sys_stm32_clock_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq);   /* 配置系统时钟 */


/* 以下为汇编函数 */
void sys_wfi_set(void);             /* 执行WFI指令 */
void sys_intx_disable(void);        /* 关闭所有中断 */
void sys_intx_enable(void);         /* 开启所有中断 */
void sys_msr_msp(uint32_t addr);    /* 设置栈顶地址 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void);
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void);

#endif 
/*----EndLine:Full File-------------------------------------------------------------------------------*/

