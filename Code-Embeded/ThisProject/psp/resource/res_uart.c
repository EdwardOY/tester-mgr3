/******************************************************************************************
 * @file   res_uart.c
 * @brief  resource for all uart/usart devices()
 * @author Edwoy
 * @version v1.3 valicated
 * @copyright Copyright (c) 2022. All rights reserved.
 ******************************************************************************************
 * @update
      v1.3 2023.5.13 
			     g_dbcom_rx_sta --> g_dbcom_rx_curcnt
      v1.2 2023.3.29 
 *******************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "ThisProj_Glb.h"


//---DBCOM-----------------------------------------------------------------------------------
/** 接收状态
  *  bit15，      接收完成标志
  *  bit14，      接收到0x0d
  *  bit13~0，    接收到的有效字节数目
  */
__IO uint16_t g_dbcom_rx_curcnt = 0;
__IO uint8_t  g_dbcom_rx_hdbuf[HdBuf_Size]  = {0};   // uart_rx_int 使用的串口接收缓冲 
__IO Bool g_dbcom_rxtkn     = False;     //dbcom rx-token: be True if received a data
__IO Bool g_dbcom_rxtkn_ovr = False; //dbcom rx-token: be True if received a amount of datas over
uint8_t   g_dbcom_rxbuff[DBCOM_REC_LEN] = {0}; // app 接收缓冲, 最大USART_REC_LEN个字节.
//__IO Bool  g_dbcom_rxtkn = False;  // rx finished token;True is finished =, False is not
//u16_t g_dbcom_rx_curcnt  = 0;      // rx current count
//u16_t g_dbcom_rx_precnt  = 0;      // rx pre count
//---End,DBCOM---------------------------------------------------------------------------------

//---rs485d1,rs485-device1---------------------------------------------------------------------
uint8_t g_rs485d1_rxbuff[RS485d1_REC_LEN] = {0}; /* 接收缓冲, 最大 RS485d1_REC_LEN 个字节. */
__IO uint8_t g_rs485d1_rx_hdbuf[1] = {0};

__IO Bool g_rs485d1_rxtkn     = False; //RS485d1 rx-token: if rx a data
__IO Bool g_rs485d1_rxtkn_ovr = False;   //RS485d1 rx-token: if rx over
uint8_t g_rs485d1_rx_curcnt = 0;            /* 接收到的数据长度 */
uint8_t g_rs485d1_rx_precnt = 0;            /* 接收到的数据长度 */

//g_rs485d1_hdr = {.Instance = RS485d1_UX,};
//---End,rs485d1,rs485-device1-----------------------------------------------------------------


//---Uarts[]-----------------------------------------------------------------------------------
//retain

uart_para_t Uarts[] = {
  [sUart1] = {
          .rxtkn        = False ,
          .rxbuf_len    = 512,
          .rxbuf_cnt    = 0,
          .rxbuf_precnt = 0,
          .rxbuf        = {0},
          .uart         = USART1,	
          .huart        = &huart1 ,				
  },
	
  [sUart2] = {
          .rxtkn        = False ,
          .rxbuf_len    = 512,
          .rxbuf_cnt    = 0,
          .rxbuf_precnt = 0,
          .rxbuf        = {0},
          .uart         = USART2,	  
					.huart        = NULL, 
  },  

  [sUart3] = {
          .rxtkn        = False ,
          .rxbuf_len    = 512,
          .rxbuf_cnt    = 0,
          .rxbuf_precnt = 0,
          .rxbuf        = {0},
          .uart         = USART3,	 
          .huart			  = NULL,		
  }, 
	
//	[sUart4] = {
//          .rxtkn        = False ,
//          .rxbuf_len    = 512,
//          .rxbuf_cnt    = 0,
//          .rxbuf_precnt = 0,
//          .rxbuf        = {0},
//          .uart         = UART4,	 	
//	        .huart        = &huart4,
//	},
	
};
 
//---End,Uarts[]------------------------------------------------------------------------------End-----

#ifdef __cplusplus
}
#endif

/* ---Endline:Full File------------------------------------------------------------------------All-End-----*/

