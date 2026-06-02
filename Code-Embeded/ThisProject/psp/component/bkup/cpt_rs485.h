/**
 ****************************************************************************************************
 * @file        rs485.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-27
 * @brief       RS485 驱动代码
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

#ifndef _CPT_RS485_H_
#define _CPT_RS485_H_

#include "ThisProj_Glb.h"
#include SYS_HEAD
#include UART_HEAD

#include "usart.h"

#define app_rs485_init  app_uart_init //defined in shell_uart.c
void app_rs485d1_rst(void);
void bsp_rs485s_init(void);


#endif
/*----Endline : Full file---------------------------------------------------------------------------*/















