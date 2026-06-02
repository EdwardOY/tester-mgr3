/**
 ****************************************************************************************************
 * @file        can.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023.3.10
 * @brief       CAN 资源代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台：正点原子 F407电机开发板
 * 在线视频：www.yuanzige.com
 * 技术论坛：http://www.openedv.com/forum.php
 * 公司网址：www.alientek.com
 * 购买地址：zhengdianyuanzi.tmall.com
 *
 * 修改说明
 * V1.0 20211027
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef _RES_CAN_H_
#define _RES_CAN_H_

#include "ThisProj_Conf.h"
#include "convert_path.h"
#include SYS_HEAD
#include UTY_TYP_HEAD
#include UTY_DEBUG_HEAD //Projects/psp/
#include "can.h"


//--Can1------------------------------------------------------------------------------------------
#define CAN_RX_GPIO_PORT                GPIOA
#define CAN_RX_GPIO_PIN                 GPIO_PIN_11
#define CAN_RX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()  

#define CAN_TX_GPIO_PORT                GPIOA
#define CAN_TX_GPIO_PIN                 GPIO_PIN_12
#define CAN_TX_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()   

#define g_can1_hdr              hcan1
/* CAN接收RX0中断使能 */
#define CAN1_RX0_INT_ENABLE      0    //can1-rx-int, 0 is disable; 1 is  enable  
//--End Can1----------------------------------------------------------------------End Can1--------


#endif
/* ---Endline:Full File-----------------------------------------------------------------All-End------*/















