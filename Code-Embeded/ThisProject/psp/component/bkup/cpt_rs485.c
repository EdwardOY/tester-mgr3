/**
 ****************************************************************************************************
 * @file        rs485.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 7* @date        2021-10-27
 * @brief       RS485d1_ 驱动代码
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
 
#include "ThisProj_Glb.h"
#include CPT_RS485_HEAD  // "./component/cpt_rs485.h"
#include DLY_HEAD
#include RES_UART_HEAD

UART_HandleTypeDef Hdr_RS485d1 ;   



uint8_t g_485d1_rx_buf[RS485d1_REC_LEN]; /* 接收缓冲, 最大 RS485d1_REC_LEN 个字节. */
uint8_t g_rs485d1_rx_cnt = 0;            /* 接收到的数据长度 */

void RS485d1_UX_IRQHandler(void)
{
    uint8_t res;

    if ((__HAL_UART_GET_FLAG(&Hdr_RS485d1, UART_FLAG_RXNE) != RESET)) /* 接收到数据 */
    {
         HAL_UART_Receive_IT(&Hdr_RS485d1, &res, 1); //HAL_UART_Receive(&Hdr_RS485d1, &res, 1, 1000);

        if (g_rs485d1_rx_cnt < RS485d1_REC_LEN)         /* 缓冲区未满 */
        {
            g_rs485d1_rx_buf[g_rs485d1_rx_cnt] = res;   /* 记录接收到的值 */
            g_rs485d1_rx_cnt++;                       /* 接收数据增加1 */
        }
    }
}


/**
 * @brief       RS485d1_初始化函数
 *   @note      该函数主要是初始化串口
 * @param       baudrate: 波特率, 根据自己需要设置波特率值
 * @retval      无
 */
void app_rs485d1_init(uint32_t baudrate)
{
//    /* USART 初始化设置 */
//    Uarts[sort].huart->Instance        = Uarts[sort].uart;  /* 选择485对应的串口 */
//    Uarts[sort].huart->Init.BaudRate   = baudrate;               /* 波特率 */
//    Uarts[sort].huart->Init.WordLength = UART_WORDLENGTH_8B;   /* 字长为8位数据格式 */
//    Uarts[sort].huart->Init.StopBits   = UART_STOPBITS_1;        /* 一个停止位 */
//    Uarts[sort].huart->Init.Parity     = UART_PARITY_NONE;         /* 无奇偶校验位 */
//    Uarts[sort].huart->Init.HwFlowCtl  = UART_HWCONTROL_NONE;   /* 无硬件流控 */
//    Uarts[sort].huart->Init.Mode       = UART_MODE_TX_RX;            /* 收发模式 */
//    HAL_UART_Init(Uarts[sort].huart);                        /* 使能对应的串口, 调用Msp */
	
    __HAL_UART_DISABLE_IT(Uarts[sort].huart, UART_IT_TC);
               
    __HAL_UART_ENABLE_IT(Uarts[sort].huart, UART_IT_RXNE);   /* 开启接收中断 */
    HAL_NVIC_EnableIRQ(RS485d1_IRQn);                      /* 使能USART1中断 */
    HAL_NVIC_SetPriority(RS485d1_IRQn, 1, 3);              /* 抢占优先级3，子优先级3 */


}

/**
 * @brief       RS485d1_发送len个字节
 * @param       buf     : 发送区首地址
 * @param       len     : 发送的字节数(为了和本代码的接收匹配,这里建议不要超过 RS485d1_REC_LEN 个字节)
 * @retval      无
 */
void rs485_tx_data(emUartSort_t sort,uint8_t *buf, uint8_t len)
{
    HAL_UART_Transmit(Uarts[sort].huart, buf, len, 1000); /* 串口2发送数据 */
    g_rs485d1_rx_cnt = 0;
}

/**
 * @brief       RS485d1_查询接收到的数据
 * @param       buf     : 接收缓冲区首地址
 * @param       len     : 接收到的数据长度
 *   @arg               0   , 表示没有接收到任何数据
 *   @arg               其他, 表示接收到的数据长度
 * @retval      无
 */
void rs485_rx_data(emUartSort_t sort,uint8_t *buf, uint8_t *len)
{
    uint8_t rxlen = g_rs485d1_rx_cnt;
    uint8_t i = 0;
    *len = 0;     /* 默认为0 */
    stkdly_ms(10); /* 等待10ms,连续超过10ms没有接收到一个数据,则认为接收结束 */

    if (rxlen == g_rs485d1_rx_cnt && rxlen) /* 接收到了数据,且接收完成了 */
    {
        for (i = 0; i < rxlen; i++)
        {
            buf[i] = g_rs485d1_rx_buf[i];
        }

        *len = g_rs485d1_rx_cnt; /* 记录本次数据长度 */
        g_rs485d1_rx_cnt = 0;    /* 清零 */
    }
}

///====CodesAdding edwoy======================================================================
/**
 * @brief       RS485d1_初始化函数
 * @note      该函数主要是初始化串口
 * @param       baudrate: 波特率, 根据自己需要设置波特率值
 * @retval      无
 */
void bsp_rs485s_init(emUartSort_t sort)
{
    __HAL_UART_DISABLE_IT(Uarts[sort].huart, UART_IT_TC);

#if RS485d1_EN_RX /* 如果使能了接收 */
    __HAL_UART_ENABLE_IT(Uarts[sort].huart, UART_IT_RXNE);   /* 开启接收中断 */
#endif

}

void app_rs485d1_rst(void)
{
  memset(g_rs485d1_rx_buf,0,RS485d1_REC_LEN);   /* 接收缓冲,最大RS485d1_REC_LEN个字节 */
  g_rs485d1_rx_cnt = 0;        	
}

///====End CodesAdding edwoy==================================================================

/*----Endline : Full file---------------------------------------------------------------------------*/