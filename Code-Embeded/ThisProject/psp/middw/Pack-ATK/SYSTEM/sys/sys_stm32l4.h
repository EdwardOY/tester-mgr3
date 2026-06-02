
/*********************************************************************************

 *	ALIENTEK Pandora STM32L IOT开发板
 *	系统时钟初始化
 *	包括时钟设置/中断管理/GPIO设置等
 *	创建日期:2016/1/5
 *	版本：V1.0
 *	版权所有，盗版必究。

 *	******************************************************************************
 *	版本修改说明
 *	无
 *	******************************************************************************/
#ifndef _SYS_STM32L4_H_
#define _SYS_STM32L4_H_
#include "ThisProj_Conf.h" 
#include "convert_path.h"
#include MCU_HEAD
#include "stm32l4xx.h"
//0,不支持os
//1,支持os
#define SYSTEM_SUPPORT_OS		0		//定义系统文件夹是否支持OS

//定义一些常用的数据类型短关键字
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;
typedef const int16_t sc16;
typedef const int8_t sc8;

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;
typedef __I int16_t vsc16;
typedef __I int8_t vsc8;

typedef uint32_t  uint32_t;
typedef uint16_t uint16_t;
typedef uint8_t  uint8_t;

typedef const uint32_t uc32;
typedef const uint16_t uc16;
typedef const uint8_t uc8;

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;
typedef __I uint16_t vuc16;
typedef __I uint8_t vuc8;


void SystemClock_Config(void);//时钟系统配置
//以下为汇编函数
void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(uint32_t addr);	//设置堆栈地址 

#endif



