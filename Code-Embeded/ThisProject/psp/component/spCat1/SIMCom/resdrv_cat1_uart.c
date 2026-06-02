/**
 ****************************************************************************************************
 * @file        app_cat1_uart.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ESPDev模块UART接口驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 ****************************************************************************************************
 * 实验平台:正点原子 F407电机开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 ****************************************************************************************************
 
  static uint8_t g_atkmodule_txbuff[ATK_MODULE_TxBufSize]; 
 ****************************************************************************************************
 */
#include "ThisProj_Glb.h"
#include RES_CAT1_UART_HEAD //"./component/spWiFi/ESP/resdrv_iot_uart.h"
#include UART_HEAD          //"./prp-shell/shell_uart.h" 
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

//--edwoy-codes-------------------------------------------------------------------------------

//UART_HandleTypeDef  g_atkmodule_hdr;          /* ESPDev UART */
uint8_t  g_atkmodule_rxbuff[ATK_MODULE_RxBufSize] = {0} ;  
uint16_t  g_atkmodule_rx_curcnt = 0;   //  realtime count rx-datas , 
__IO Bool g_atkmodule_rxtkn_ovr = False; //MODULE rx-token: be True if received a amount of datas over

//--end edwoy-codes--------------------------------------------------------------------end----

/******************************************************
 * @brief       ESPDev UART printf
 * @param       fmt: 待打印的数据
 * @retval      无
 * @attention
      -1-, The mqtt cmd is long,
           so the size of txbuf needs to be increased
 ******************************************************/
void app_atkmodule_printf(char *fmt, ...)
{
    va_list ap;
    uint16_t len;
    uint8_t txbuff[320] = {0};
    va_start(ap, fmt);
    vsprintf((char *)txbuff, fmt, ap);
    va_end(ap);
    
    len = strlen((const char *)txbuff);
    HAL_UART_Transmit(&g_atkmodule_hdr, txbuff, len, HAL_MAX_DELAY);
}

/**
 * @brief       ESPDev UART重新开始接收数据
 * @param       无
 * @retval      无
 */
void app_atkmodule_uartrx_rst(void)
{
//    g_atkmodule_rx_curcnt     = 0;
//    g_atkmodule_rxtkn_ovr   = 0;
	memset(g_atkmodule_rxbuff,0,ATK_MODULE_RxBufSize);
	g_atkmodule_rxtkn_ovr =  False;
	g_atkmodule_rx_curcnt = 0;	
}

/**
 * @brief       获取ESPDev UART接收到的一帧数据
 * @param       无
 * @retval      NULL: 未接收到一帧数据
 *              其他: 接收到的一帧数据
 */
uint8_t *app_atkmodule_rxmsg(void)
{
    if(g_atkmodule_rxtkn_ovr){
        g_atkmodule_rxbuff[g_atkmodule_rx_curcnt] = '\0';
        return g_atkmodule_rxbuff;
			
    }else{
        return NULL;
    }
}

/**
 * @brief       获取ESPDev UART接收到的一帧数据的长度
 * @param       无
 * @retval      0   : 未接收到一帧数据
 *              其他: 接收到的一帧数据的长度
 */
uint16_t app_atkmodule_rxmsg_length(void)
{
    if (g_atkmodule_rxtkn_ovr)
    {
        return g_atkmodule_rx_curcnt;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief       ESPDev UART初始化
                不使用这个函数去初始化 atk-module
                MX_UART4_Init() 取代了这个函数
 * @param       baudrate: UART通讯波特率
 * @retval      无
 */
void app_atkmodule_init(uint32_t baudrate)
{
    g_atkmodule_hdr.Instance          = ATK_MODULE_UART_INTERFACE ;   /* ESPDev UART */
    g_atkmodule_hdr.Init.BaudRate     = baudrate;                     /* 波特率 */
    g_atkmodule_hdr.Init.WordLength   = UART_WORDLENGTH_8B;           /* 数据位 */
    g_atkmodule_hdr.Init.StopBits     = UART_STOPBITS_1;              /* 停止位 */
    g_atkmodule_hdr.Init.Parity       = UART_PARITY_NONE;             /* 校验位 */
    g_atkmodule_hdr.Init.Mode         = UART_MODE_TX_RX;              /* 收发模式 */
    g_atkmodule_hdr.Init.HwFlowCtl    = UART_HWCONTROL_NONE;          /* 无硬件流控 */
    g_atkmodule_hdr.Init.OverSampling = UART_OVERSAMPLING_16;         /* 过采样 */
    HAL_UART_Init(&g_atkmodule_hdr);                                  /* 使能ESPDev UART
                                                                     * HAL_UART_Init()会调用函数HAL_UART_MspInit()
                                                                     * 该函数定义在文件usart.c中
                                                                     */
}

/**
 * @brief       ESPDev UART中断回调函数
 * @param       无
 * @retval      无
 */
void edwMODULE_UART_IRQHandler(void)
{
    uint8_t tmp;
    
    if(RESET != __HAL_UART_GET_FLAG(&g_atkmodule_hdr, UART_FLAG_ORE))        /* UART接收过载错误中断 */
    {
        __HAL_UART_CLEAR_OREFLAG(&g_atkmodule_hdr);                           /* 清除接收过载错误中断标志 */
        (void)g_atkmodule_hdr.Instance->SR;                                   /* 先读SR寄存器，再读DR寄存器 */
        (void)g_atkmodule_hdr.Instance->DR;
    }
    
    if(RESET != __HAL_UART_GET_FLAG(&g_atkmodule_hdr, UART_FLAG_RXNE))       /* UART接收中断 */
    {
        HAL_UART_Receive(&g_atkmodule_hdr, &tmp, 1, HAL_MAX_DELAY);           /* UART接收数据 */
        
        if (g_atkmodule_rx_curcnt < (ATK_MODULE_RxBufSize - 1))             /* 判断UART接收缓冲是否溢出
                                                                             * 留出一位给结束符'\0'
                                                                             */
        {
            g_atkmodule_rxbuff[g_atkmodule_rx_curcnt] = tmp;             /* 将接收到的数据写入缓冲 */
            g_atkmodule_rx_curcnt++;                                      /* 更新接收到的数据长度 */
        }
        else  //UART接收缓冲已溢出 
        {
					  printf("(%d)g_atkmodule_rx_curcnt ovrride!!\r\n",g_atkmodule_rx_curcnt);
            g_atkmodule_rx_curcnt = 0;                                    /* 覆盖之前收到的数据 */
//            g_atkmodule_rxbuff[g_atkmodule_rx_curcnt] = tmp;             /* 将接收到的数据写入缓冲 */
//            g_atkmodule_rx_curcnt++;                                      /* 更新接收到的数据长度 */
					  memset(g_atkmodule_rxbuff,0,ATK_MODULE_RxBufSize);
        }
    }
    
    if (__HAL_UART_GET_FLAG(&g_atkmodule_hdr, UART_FLAG_IDLE) != RESET)       /* UART总线空闲中断 */
    {
        g_atkmodule_rxtkn_ovr = 1;                                      /* 标记帧接收完成 */
//        printf("AdmIrqHdr{%s}%dbytes\r\n",g_atkmodule_rxbuff,g_atkmodule_rx_curcnt);
        __HAL_UART_CLEAR_IDLEFLAG(&g_atkmodule_hdr);                          /* 清除UART总线空闲中断 */
    }
}
