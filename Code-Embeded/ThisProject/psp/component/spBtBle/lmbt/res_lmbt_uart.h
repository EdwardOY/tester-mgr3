/******************************************************************************************************
 * @file        spBTBLE.h
 * @author      Edwoy
 * @version     V1.0
 * @date        2021-10-27
 * @brief       Bluetooth&BLE resource header of serialport communication
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

#ifndef _RES_LMBT_UART_H_
#define _RES_LMBT_UART_H_
#include "ThisProj_Glb.h"

///==ATK_MODULE->UART=====================================================================================

///--atk_module-uart defintion----------------------------------------------------------------------
#define ATK_MODULE_RxBufSize               2048
#define ATK_MODULE_UART_TX_BUF_SIZE        64

///--end atk_module-uart defintion------------------------------------------------------------end---

///--atk_module-uart-1 gpio-------------------------------------------------------------------------
#define ATK_MODULE_UART_TX_GPIO_PORT         GPIOC
#define ATK_MODULE_UART_TX_GPIO_PIN          GPIO_PIN_10
#define ATK_MODULE_UART_TX_GPIO_AF           GPIO_AF8_UART4
#define ATK_MODULE_UART_TX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

#define ATK_MODULE_UART_RX_GPIO_PORT         GPIOC
#define ATK_MODULE_UART_RX_GPIO_PIN          GPIO_PIN_11
#define ATK_MODULE_UART_RX_GPIO_AF           GPIO_AF8_UART4
#define ATK_MODULE_UART_RX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()

#define ATK_MODULE_UART_PRP                  UART4
#define ATK_MODULE_UART_IRQn                 UART4_IRQn
#define ATK_MODULE_UART_CLK_ENABLE()         __HAL_RCC_UART4_CLK_ENABLE()

#define edwMODULE_UART_IRQHandler            UART4_IRQHandler  //func is validated

///--end atk_module-uart-1 gpio-----------------------------------------------------------------end---

///--atk_module-uart- paras---------------------------------------------------------------------------
#define PRP_MODULE          ATK_MODULE_UART_PRP
#define _atkmodule_init     MX_UART4_UART_Init
#define sMODULE             sUart4
#define MODULE_para         Uarts[sMODULE]
#define g_atkmodule_hdr     huart4  

extern uint8_t g_atkmodule_rxbuff[ATK_MODULE_RxBufSize] ;  
extern u16_t g_atkmodule_rx_curcnt;   //  realtime count rx-datas , 
extern __IO Bool g_atkmodule_rxtkn_ovr ; //MODULE rx-token: be True if received a amount of datas over

///---End,atk_module-uart- paras----------------------------------------------------------------End----

///====Codes-ATK-MODULE===================================================================================
/*******************************************************************
 * @brief       ATK-MODULE发送AT指令
 * @param       cmd    : AT command string
 *              ack    : action string
 *              timeout: 
                     0,No need action
										others, The max wait-time,unit is ms 
 * @retval      Err_BTBLE_NONE     : success
 *              Err_BTBLE_TIMEOUT: waiting timeout
 ******************************************************************/
uint8_t app_atkmodule_send_at_cmd(char *cmd, char *ack, uint32_t timeout);

/**
 * @brief       通过UART唤醒ATK-MODULE
 * @param       无
 * @retval      无
 */
void atk_module_wakeup_by_uart(void);

/****************************************
 * @brief   ATK-MODULE UART printf
 * @param   fmt: the target datas being printfed
 * @retval  void
 ****************************************/
void app_atkmodule_uart_printf(char *fmt, ...);


/***************************************************************
 * @brief   reset the rxframe of bluetooth&ble dev`s uartrx
 * @param   void
 * @retval  无
 ***************************************************************/
void app_atkmodule_uartrx_rst(void);

/**
 * @brief       ATK-MODULE UART重新开始接收数据
 * @param       无
 * @retval      无
 */
void atk_module_uart_rx_restart(void);

/********************************************************
 * @brief       获取ATK-MODULE UART接收到的一帧数据
 * @param       无
 * @retval      NULL: 未接收到一帧数据
 *              其他: 接收到的一帧数据

 *********************************************************/
uint8_t* app_atkmodule_get_uartrx_frame(void);

/***************************************************************
 * @brief       获取ATK-MODULE UART接收到的一帧数据的长度
 * @param       无
 * @retval      0   : 未接收到一帧数据
 *              其他: 接收到的一帧数据的长度
 **************************************************************/
uint16_t app_atkmodule_get_uartrx_frame_len(void);

/**
 * @brief       ATK-MODULE UART初始化
 * @param       baudrate: UART通讯波特率
 * @retval      无
 */
void app_atkmodule_uart_init(uint32_t baudrate);





///==End ATK_MODULE->UART==========================================================================End====


#endif
/*----Endline : Full file----------------------------------------------------------------------All_End-----*/










