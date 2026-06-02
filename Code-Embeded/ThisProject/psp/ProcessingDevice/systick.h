
/*********************************************************************************

 *	本程序只供学习使用，未经作者许可，不得用于其它任何用途
 *	ALIENTEK Pandora STM32L IOT开发板

 *	******************************************************************************
 *	修改说明
 *	******************************************************************************/
#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include "ThisProj_Conf.h" 
#include "convert_path.h"
#include SYS_HEAD


void stkdly_init(uint8_t SYSCLK);
void stkdly_ms(uint16_t nms);
void stkdly_us(uint32_t nus);
#endif

