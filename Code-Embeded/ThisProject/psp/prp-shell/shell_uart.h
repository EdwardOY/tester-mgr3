/**
 ****************************************************************************************************
 * @file        shell_uart.h
 * @author      EDWOY
 * @version     V1.0
 * @date        2022-12-08
 * @brief       串口初始化代码(一般是串口1)，支持printf
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台：ATK Apollo STM32F429IGTB
 * 在线视频：www.yuanzige.com
 * 技术论坛：http://www.openedv.com/forum.php
 * 公司网址：www.alientek.com
 * 购买地址：zhengdianyuanzi.tmall.com
 *
 * 修改说明
 * V1.0 20211014
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef _SHELL_UART_H_
#define _SHELL_UART_H_

#include "ThisProj_Conf.h"
#include "convert_path.h"
#include MCU_HEAD
#include SYS_HEAD
#include UTY_TYP_HEAD
#include RES_UART_HEAD   //"./resource/res_uart.h" in convert_path.h

///====CodesAdding edwoy============================================================================
void app_dbcom_init(void) ;
void app_dbcom_rxpoll_it(void);
void app_dbcom_rst(void);
void app_dbcom_rxpoll(void);
void app_dbcom_cmd_hdr(u8_t*);
void app_dbcom_cmd_hdr2(u8_t* tmpvlu);

/**************************************************************
 * @brief  Reset uart`s rx(clear rxbuff and reset token)
 * @state  verified 
 * @note  
 * @param  void
 * @retval void
 *******bkcode*********
 **************************************************************/
void app_uart_rstrx(emUartSort_t sort);

void app_free_printf(UART_HandleTypeDef* huart,char* fmt,...) ;

void bsp_dbcom_rst(void);	
void bsp_dbcom_rxpoll_it(void);

///====End CodesAdding edwoy=========================================================================

#endif 
/*----Endline : Full file-------------------------------------------------------------------All-End------*/
//void dbcom_init(uint32_t baudrate);             /* 串口初始化函数 ，orgn, usart_init*/






