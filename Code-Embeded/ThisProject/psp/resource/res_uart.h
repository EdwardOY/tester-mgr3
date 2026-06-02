/**
 * @file 
 * @author 
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2022. All rights reserved.
 */
#ifndef _RES_UART_H_
#define _RES_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ThisProj_Conf.h"
#include "convert_path.h"
#include SYS_HEAD
#include UTY_TYP_HEAD
#include UTY_DEBUG_HEAD //Projects/psp/

///--uart_paras --------------------------------------------------------------------------------------
typedef struct _uart_para{
	__IO Bool           rxtkn;	
	uc16_t              rxbuf_len;	
  u16_t               rxbuf_cnt;    //��ǰ����
  u16_t               rxbuf_precnt; //ǰ�μ���������rxbuf_cnt	
	u8_t                rxbuf[512];
  USART_TypeDef*      uart;
	UART_HandleTypeDef* huart;
}uart_para_t;
extern uart_para_t Uarts[];
///--End uart_paras ------------------------------------------------------------------------------------

///---DBCOM----------------------------------------------------------------------------------DBCOM------
#define DBCOM_REC_LEN   0x400     // uart app rxbuff size ,1KB
#define DBCOM_EN_RX     1         //enable rx-interrupt
#define HdBuf_Size      1         //uart low-level rxbuff size in interrupt 

#define DBCOM_TX_PORT              GPIOA
#define DBCOM_TX_PIN               GPIO_PIN_9
#define DBCOM_TX_AF                GPIO_AF7_USART1
#define DBCOM_TX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define DBCOM_RX_PORT              GPIOA
#define DBCOM_RX_PIN               GPIO_PIN_10
#define DBCOM_RX_AF                GPIO_AF7_USART1
#define DBCOM_RX_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define DBCOM_UX                   USART1
#define DBCOM_UX_IRQn              USART1_IRQn
#define DBCOM_UX_IRQHandler        USART1_IRQHandler
//#define edwDBCOM_UX_IRQHandler     USART1_IRQHandler
#define DBCOM_UX_CLK_ENABLE()      __HAL_RCC_USART1_CLK_ENABLE()

extern uint8_t  g_dbcom_rxbuff[DBCOM_REC_LEN];    // uart app rxbuff
extern __IO uint8_t  g_dbcom_rx_hdbuf[HdBuf_Size]; //uart low-level rxbuff in interrupt 
extern __IO uint16_t g_dbcom_rx_curcnt;   

#define DBCOM              DBCOM_UX   
#define g_dbcom_hdr        huart1
#define sDBCOM             sUart1   // default = 0, ThisProj_Glb.h
#define DBCOM_para         Uarts[sDBCOM]
#define _dbcom_init        MX_USART1_UART_Init
extern __IO Bool g_dbcom_rxtkn ;     //dbcom rx-token: be True if received a data
extern __IO Bool g_dbcom_rxtkn_ovr ; //dbcom rx-token: be True if received a amount of datas over
//#define Hdr_DBCOM          g_dbcom_hdr
//extern __IO Bool  g_dbcom_rxtkn ;
//extern u16_t g_dbcom_rx_curcnt ;
//extern u16_t g_dbcom_rx_precnt ; 
///---End,DBCOM--------------------------------------------------------------------------------End,DBCOM-------

///---rs485d1,rs485 device1------------------------------------------------------------------------------------
#define RS485d1_TX_GPIO_PORT                  GPIOA
#define RS485d1_TX_GPIO_PIN                   GPIO_PIN_2
#define RS485d1_TX_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE() 

#define RS485d1_RX_GPIO_PORT                  GPIOA
#define RS485d1_RX_GPIO_PIN                   GPIO_PIN_3
#define RS485d1_RX_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()

#define RS485d1_UX                            USART2
#define RS485d1_UX_IRQn                       USART2_IRQn
#define RS485d1_UX_CLK_ENABLE()               __HAL_RCC_USART2_CLK_ENABLE()

//select only one between atkRS485d1_UX_IRQHandler & edwRS485d1_UX_IRQHandler(void)
//CMPL_RS485d1_xx are in ThisProj_Glb.h
#if CMPL_RS485d1_RxInt  == CMPL_RS485d1_RxInt_Atk	
#define atkRS485d1_UX_IRQHandler   USART2_IRQHandler  //func is verified
#elif CMPL_RS485d1_RxInt  == CMPL_RS485d1_RxInt_Edw	
#define edwRS485d1_UX_IRQHandler   USART2_IRQHandler  //func is verified
#endif
//---------------------------------------------------------------------------------------------

/* ����RS485d1_RE��, ����RS485����/����״̬
 * RS485d1_RE = 0, �������ģʽ
 * RS485d1_RE = 1, ���뷢��ģʽ
 */
#define RS485d1_REC_LEN   64          /* �����������ֽ��� 64 */
#define RS485d1_EN_RX      1           /* ʹ�ܣ�1��/��ֹ��0��RS485���� */

/* ����RS485d1_RE��, ����RS485d1����/����״̬
 * RS485d1_RE = 0, �������ģʽ
 * RS485d1_RE = 1, ���뷢��ģʽ
 */
#define PRP_RS485d1          RS485d1_UX 
#define _rs485d1_init        MX_USART2_UART_Init
#define sRS485d1             sUart2
#define RS485d1_para         Uarts[sRS485d1]
#define g_rs485d1_hdr        huart2  //g_rs485d1_hdr

extern uint8_t g_rs485d1_rxbuff[RS485d1_REC_LEN] ;   /* ���ջ���,���RS485d1_REC_LEN���ֽ� */
extern __IO uint8_t g_rs485d1_rx_hdbuf[1];

extern u8_t g_rs485d1_rx_curcnt;   //  realtime count rx-datas ,          
extern u8_t g_rs485d1_rx_precnt ;  //
extern __IO Bool g_rs485d1_rxtkn ;     //RS485d1 rx-token: be True if received a data
extern __IO Bool g_rs485d1_rxtkn_ovr ; //RS485d1 rx-token: be True if received a amount of datas over
///---End,rs485d1-----------------------------------------------------------------------------End,rs485d1-------

#ifdef __cplusplus
}
#endif

#endif 
/* ---Endline:Full File-----------------------------------------------------------------------------------All-End------*/

