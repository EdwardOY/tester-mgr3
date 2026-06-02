/**
  *
	*/
#ifndef _STM_BLD_IAPUARTBOOT_H_
#define _STM_BLD_IAPUARTBOOT_H_
#include "ThisProj_Glb.h"
#include  SYS_HEAD

typedef  void (*iapfun)(void);				//定义iap函数类型的参数.

#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */

/**\brief: jumpto_self_bld(Jump into mcu`s hard self-bootloader)
	*\for:   跳转到mcu自带的BootLoader(即mcu自带的 system memory)
	*\param: void
	*\return: void
	*\atten
	*   -1-, STM32 Gxx/F429x`s self-bootloader(system memory) address = 0x1FFF0000
	         refer to emSTM32mmap_t in utility_def.h
		  -2-, If using RTOS, __set_CONTROL(0) is need after __set_MSP(*(uint32_t *)BootAddr)		 
			     __set_CONTROL(0) --> Current mode is set to privilege level(特权级)
  *\update:
  *   v1.0(verified) created at 2022.7.24
  */
void jumpto_self_bld(void);

#endif /*----EndLine: Full File-----*/
