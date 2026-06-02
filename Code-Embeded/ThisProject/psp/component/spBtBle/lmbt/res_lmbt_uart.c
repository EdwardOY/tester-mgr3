/******************************************************************************************************
 * @file        spBTBLE.c
 * @author      Edwoy
 * @version     V1.0
 * @date        2021-10-27
 * @brief       Bluetooth&BLE resource src of serialport communication
 * @license     Copyright (c) 2020-2032
 ****************************************************************************************************
 * @attention
 ****************************************************************************************************
 * @note
 *    1 Default hard
          platform: ATK-DMF407
          module : BT-11 of LM(www.lbluetooth.com)			
 ****************************************************************************************************
 * @update
 *   V1.0 
 *
 ****************************************************************************************************
 */

#include "ThisProj_Glb.h"
#include UART_HEAD
#include DLY_HEAD
#include RES_BTBLE_HEAD  //"./component/spBtBle/lmbt/res_lmbt.h"

///==ATK_MODULE->UART===============================================================================

///--atk_module-uart paras-----------------------------------------------------------------------
uint16_t g_atkmodule_rx_curcnt = 0;   //  realtime count rx-datas ,          
uint8_t g_atkmodule_rxbuff[ATK_MODULE_RxBufSize] = {0};  
__IO Bool g_atkmodule_rxtkn_ovr = False; //MODULE rx-token: be True if received a amount of datas over
///---End,atk_module-uart paras------------------------------------------------------------End----

/*******************************************************************
 * @brief       ATK-MODULE发送AT指令
 * @param       cmd    : AT command string
 *              ack    : action string
 *              timeout: 
                     0,     do nothing
										others, The max wait-time,unit is ms 
 * @retval      Err_BTBLE_NONE     : success
 *              Err_BTBLE_TIMEOUT: waiting timeout
 ******************************************************************/
uint8_t app_atkmodule_send_at_cmd(char *cmd, char *ack, uint32_t timeout)
{
    uint8_t *ret = NULL;
    
    app_atkmodule_uartrx_rst();  //atk_module_uart_rx_restart();
    app_atkmodule_uart_printf("%s\r\n", cmd);  //  app_free_printf(&g_atkmodule_hdr, "%s\r\n", cmd);
    
    if ((ack == NULL) || (timeout == 0)){
        return Err_BTBLE_NONE;
			
    }else{
        while (timeout > 0)
        {
            ret = app_atkmodule_get_uartrx_frame();
            if (ret != NULL)
            {
                if (NULL != strstr((const char *)ret, ack)) //ack is right
                {
                    return Err_BTBLE_NONE;
                }
                else //ack is wrong
                {
                    app_atkmodule_uartrx_rst(); //atk_module_uart_rx_restart();
                }
            }
            timeout--;
            stkdly_ms(1); //stkdly_ms(1);
        }
        
        return Err_BTBLE_TIMEOUT;
    }
}

/****************************************
 * @brief   ATK-MODULE UART printf
 * @param   fmt: the target datas being printfed
 * @retval  void
 ****************************************/
void app_atkmodule_uart_printf(char *fmt, ...)
{
    va_list ap;
    uint16_t len;
    uint8_t tx_buf[24] = {0};
		
    va_start(ap, fmt);
    vsprintf((char *)tx_buf, fmt, ap);
    va_end(ap);
    
    len = strlen((const char *)tx_buf);
    HAL_UART_Transmit(&g_atkmodule_hdr, tx_buf, len, HAL_MAX_DELAY);
}

/***************************************************************
 * @brief   reset the rxframe of bluetooth&ble dev`s uartrx
 * @param   void
 * @retval  无
 ***************************************************************/
void app_atkmodule_uartrx_rst(void)
{
    g_atkmodule_rxtkn_ovr = False; 
    g_atkmodule_rx_curcnt = 0;   //  realtime count rx-datas ,          

	  memset(g_atkmodule_rxbuff,0,ATK_MODULE_RxBufSize);	
}

/********************************************************
 * @brief       获取ATK-MODULE UART接收到的一帧数据
 * @param       无
 * @retval      NULL: 未接收到一帧数据
 *              其他: 接收到的一帧数据
 *******************************************************
 *********************************************************/
uint8_t* app_atkmodule_get_uartrx_frame(void)
{
    if(True == g_atkmodule_rxtkn_ovr){
       g_atkmodule_rxbuff[g_atkmodule_rx_curcnt] = '\0';
		   return g_atkmodule_rxbuff ;			
			
		}	else {
			 return NULL;		
		}
}

/***************************************************************
 * @brief       获取ATK-MODULE UART接收到的一帧数据的长度
 * @param       无
 * @retval      0   : 未接收到一帧数据
 *              其他: 接收到的一帧数据的长度
 **************************************************************/
uint16_t app_atkmodule_get_uartrx_frame_len(void)
{
    if(True == g_atkmodule_rxtkn_ovr){
       return  g_atkmodule_rx_curcnt;
			
		}	else {
			 return NULL;		
		}		
}

/**
 * @brief       ATK-MODULE UART初始化
 * @param       baudrate: UART通讯波特率
 * @retval      无
 */
void app_atkmodule_uart_init(uint32_t baudrate)
{
    g_atkmodule_hdr.Instance          = ATK_MODULE_UART_PRP;     /* ATK-MODULE UART */
    g_atkmodule_hdr.Init.BaudRate     = baudrate;                     /* 波特率 */
    g_atkmodule_hdr.Init.WordLength   = UART_WORDLENGTH_8B;           /* 数据位 */
    g_atkmodule_hdr.Init.StopBits     = UART_STOPBITS_1;              /* 停止位 */
    g_atkmodule_hdr.Init.Parity       = UART_PARITY_NONE;             /* 校验位 */
    g_atkmodule_hdr.Init.Mode         = UART_MODE_TX_RX;              /* 收发模式 */
    g_atkmodule_hdr.Init.HwFlowCtl    = UART_HWCONTROL_NONE;          /* 无硬件流控 */
    g_atkmodule_hdr.Init.OverSampling = UART_OVERSAMPLING_16;         /* 过采样 */
    HAL_UART_Init(&g_atkmodule_hdr);                                  /* 使能ATK-MODULE UART
                                                                     * HAL_UART_Init()会调用函数HAL_UART_MspInit()
                                                                     * 该函数定义在文件usart.c中
                                                                     */
}


/**********************************************
 * @brief       ATK-MODULE UART中断回调函数
 * @param       无
 * @notice   
         -1-, g_atkmodule_rxbuff[] don`t add '\0' 
 * @retval      无
 *********************************************/
void edwMODULE_UART_IRQHandler(void)
{
    uint8_t tmp;
    
    if(SET == __HAL_UART_GET_FLAG(&g_atkmodule_hdr, UART_FLAG_ORE))        /* UART接收过载错误中断 */
    {
        __HAL_UART_CLEAR_OREFLAG(&g_atkmodule_hdr);                           /* 清除接收过载错误中断标志 */
        (void)g_atkmodule_hdr.Instance->SR;                                   /* 先读SR寄存器，再读DR寄存器 */
        (void)g_atkmodule_hdr.Instance->DR;		  	
    }
    
    if(SET == __HAL_UART_GET_FLAG(&g_atkmodule_hdr, UART_FLAG_RXNE))       /* UART接收中断 */
    {
        HAL_UART_Receive(&g_atkmodule_hdr, &tmp, 1, HAL_MAX_DELAY);           /* UART接收数据 */
			
       //判断UART接收缓冲是否溢出留出一位给结束符'\0'      
        if (g_atkmodule_rx_curcnt < (ATK_MODULE_RxBufSize - 1)) {           
            g_atkmodule_rxbuff[g_atkmodule_rx_curcnt] = tmp;           /* 将接收到的数据写入缓冲 */ 
					  g_atkmodule_rx_curcnt++;
					
        } else {                                                               /* UART接收缓冲溢出 */
            g_atkmodule_rx_curcnt  = 0;                                    /* 覆盖之前收到的数据 */
            g_atkmodule_rxbuff[g_atkmodule_rx_curcnt] = tmp;    /* 将接收到的数据写入缓冲 ;更新接收到的数据长度*/
            g_atkmodule_rx_curcnt++;					
        }
    }
		
		if(SET == __HAL_UART_GET_FLAG(&g_atkmodule_hdr, UART_FLAG_IDLE))       /* UART总线空闲中断 */
    {
        g_atkmodule_rxtkn_ovr = True;                                  /* 标记帧接收完成 */  
        __HAL_UART_CLEAR_IDLEFLAG(&g_atkmodule_hdr);                          /* 清除UART总线空闲中断 */		 	
    }	
}

///==End ATK_MODULE->UART====================================================================End====




/*----Endline : Full file----------------------------------------------------------------------All_End-----*/








