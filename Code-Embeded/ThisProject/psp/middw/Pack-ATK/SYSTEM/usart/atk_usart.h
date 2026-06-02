/*********************************************************************************
 *	本程序只供学习使用，未经作者许可，不得用于其它任何用途
 *	ALIENTEK Pandora STM32L IOT开发板
 *	串口1初始化

 *	修改日期:2026/5/5
 *	版本：V1.0

 *	******************************************************************************
 *	V1.0修改说明
 *	******************************************************************************/
#ifndef _ATK_USART_H_
#define _ATK_USART_H_
#include "ThisProj_Conf.h" 
#include "convert_path.h"
#include SYS_HEAD

#include "stdio.h"




#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

extern uint8_t  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern uint16_t USART_RX_STA;         		//接收状态标记
extern UART_HandleTypeDef UART1_Handler; //UART句柄

#define RXBUFFERSIZE   1 //缓存大小
extern uint8_t aRxBuffer[RXBUFFERSIZE];//HAL库USART接收Buffer

//如果想串口中断接收，请不要注释以下宏定义
void uart_init(uint32_t bound);



#endif


