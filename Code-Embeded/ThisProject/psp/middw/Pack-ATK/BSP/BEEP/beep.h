/*********************************************************************************

 *	******************************************************************************
 *	本程序只供学习使用，未经作者许可，不得用于其它任何用途
 *	ALIENTEK Pandora STM32L IOT开发板
 *	蜂鸣器驱动代码

 *	创建日期:2018/10/27
 *	版本：V1.0
 *	版权所有，盗版必究。

 *	******************************************************************************
 *	初始版本
 *	******************************************************************************/
#ifndef __BEEP_H
#define __BEEP_H

#define BEEP(n)	(n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET))
#define BEEP_TogglePin	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_2)


void BEEP_Init(void);




#endif


