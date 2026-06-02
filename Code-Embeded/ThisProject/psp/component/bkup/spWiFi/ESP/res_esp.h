/******************************************************************************************************
 * @file        res_esp.h
 * @author      Edwoy
 * @version     V1.0
 * @date        2021-10-27
 * @brief       Bluetooth&BLE resource header
 * @license     Copyright (c) 2020-2032
 ****************************************************************************************************
 * @attention
 ****************************************************************************************************
 * @note
 *    1 Default hard
          platform: ATK-DMF407
          module : Esp8266 of LM(www.lbluetooth.com)			
 ****************************************************************************************************
 * @update
 *   V1.0 
 *
 ****************************************************************************************************
 */

#ifndef _RES_WIFI_H_
#define _RES_WIFI_H_
#include "ThisProj_Glb.h"
#include RES_UART_HEAD
#include RES_WIFI_UART_HEAD
#include UTY_WIFI_HEAD  // "./component/spWiFi/UTY/utyWiFi.h"

///==ESP Setting==================================================================================
#define __DlyMs_Esp   (uint8_t)5

//---ESP-dev-rst-----------------------------------------------------------------------------
#define WIFI_RST_GPIO_PORT           GPIOI
#define WIFI_RST_GPIO_PIN            GPIO_PIN_10
#define WIFI_RST_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOI_CLK_ENABLE(); }while(0) /* PI口时钟使能 */


#define WIFI_RST_GPIO(x)             do{ x ?                                                                              \
                                         HAL_GPIO_WritePin(WIFI_RST_GPIO_PORT, WIFI_RST_GPIO_PIN, GPIO_PIN_SET) :  \
                                         HAL_GPIO_WritePin(WIFI_RST_GPIO_PORT, WIFI_RST_GPIO_PIN, GPIO_PIN_RESET); \
                                       }while(0)
//---end ESP-dev-rst-------------------------------------------------------------------end---

//---ESP-dev-paras---------------------------------------------------------------------------
																			 //CWMODE
typedef enum{
	EspCWM_Sta   = 1,
	EspCWM_Ap    = 2,
	EspCWM_StaAp = 3,
}emEsp8266CWMODE_t;

typedef struct {
	uint8_t             deeptim; //
	uint8_t             lowtim ; //
	emEsp8266CWMODE_t   sta_cwm ;
	emWIFI_DevState_t   sta_dev;
	
}sttWIFI_DevParas_t;
extern sttWIFI_DevParas_t g_atkmoudle_esp_dev0;
//---end ESP-dev-paras-----------------------------------------------------------------end---

//---RF power grade----------------------------------------------------------------------
typedef enum
{
    WIFI_PwrGrd_N15DBM = 0x00,            /* -15.7dBm */
    WIFI_PwrGrd_N12DBM,                   /* -12.5dBm */
    WIFI_PwrGrd_N10DBM,                   /* -10dBm */
    WIFI_PwrGrd_N6DBM,                    /* -6.6dBm */
	  WIFI_PwrGrd_N4DBM,
	  WIFI_PwrGrd_N2DBM,           
    WIFI_PwrGrd_N0DBM,                    /* -0.1dBm */
    WIFI_PwrGrd_P2DBM,                    /* +2.1dBm */
    WIFI_PwrGrd_P4DBM,                    /* +4.6dBm */	
    WIFI_PwrGrd_P6DBM,                    /* +6.4dBm */
	  WIFI_PwrGrd_CHK   = 0xcf,             // check cmd
} emWIFI_PwrGrd_t;
#define IS_VALID_PWRGRD_ESP(x)   ((WIFI_PwrGrd_N15DBM == x) || (WIFI_PwrGrd_N12DBM == x) || (WIFI_PwrGrd_N10DBM == x) || \
                                   (WIFI_PwrGrd_N6DBM  == x) || (WIFI_PwrGrd_N4DBM  == x) || (WIFI_PwrGrd_N2DBM  == x) || \
                                   (WIFI_PwrGrd_N0DBM  == x) || (WIFI_PwrGrd_P2DBM  == x) || (WIFI_PwrGrd_P6DBM  == x)) 
//---end RF power grade-----------------------------------------------------------end---

///--power mode-----------------------------------------------------------------------------
typedef enum
{
    WIFI_PwrMd_AutoLow = 0x00,  // enable lowpower mode
    WIFI_PwrMd_Normal  = 0x01,  // enable normal power mode
	  WIFI_PwrMd_CHK     = 0xcf,  // check cmd
} emWIFI_PwrMd_t;
#define IS_VALID_PWRMD_ESP(x)   ((WIFI_PwrMd_Normal == x) || (WIFI_PwrMd_AutoLow == x)) 

typedef enum
{
    WIFI_DeepSleep_Dis = 0x00,     // exit deepsleep
    WIFI_DeepSleep_Min = 5,       // Min s to enter deepsleep
	  WIFI_DeepSleep_Max = 200,      // Max s to enter deepsleep
	  WIFI_DeepSleep_CHK = 0xcf,     // check cmd
} emWIFI_DeepSleep_t;
#define IS_VALID_DEEPSLP_ESP(x)   ((x >= WIFI_DeepSleep_Min ) && (x <= WIFI_DeepSleep_Max)) 
///--end power mode-------------------------------------------------------------------end---
///==End ESP Setting=======================================================================End====

///==ESP->UART(ATK_MODULE)_Paras=====================================================================================
///--atk_module-uart-2 base parameters-----------------------------------------------------------------
//---uart baudrate-----------------------------------------------------------------------
typedef enum
{
	 	UART_BAUDRATE_CHK    = 0xcf,           // check
    UART_BAUDRATE_9600   = 9600 ,          /* 9600bps */
    UART_BAUDRATE_19200  = 19200,          /* 19200bps */
    UART_BAUDRATE_38400  = 38400,          /* 38400bps */
    UART_BAUDRATE_57600  = 57600,          /* 57600bps */
    UART_BAUDRATE_115200 = 115200,         /* 115200bps */
    UART_BAUDRATE_230400 = 230400,         /* 230400bps */
	  UART_BAUDRATE_256000 = 256000,
	  UART_BAUDRATE_307200 = 307200 ,
	  UART_BAUDRATE_460800 = 460800,
	  UART_BAUDRATE_512000 = 512000,
	  UART_BAUDRATE_600000 = 600000,
	  UART_BAUDRATE_750000 = 750000,
} emEspUart_baud_t;
#define IS_VALID_UART_BAUDRATE_ESP(x)   ((9600   == x) || (19200  == x) || (38400  == x) || \
                                         (57600  == x) || (115200 == x) || (230400 == x) || \
                                         (256000 == x) || (307200 == x) || (460800 == x) || \
                                         (512000 == x) || (600000 == x) || (750000 == x))
//---end uart baudrate-------------------------------------------------------------end---

//---uart parity-------------------------------------------------------------------------
typedef enum
{
    ESP_UART_PARI_NONE = 0x00,        /* 无校验 */
	  ESP_UART_PARI_ODD  = 0x01,        /* 奇校验 */
    ESP_UART_PARI_EVEN = 0x02,        /* 偶校验 */	
	  ESP_UART_PARI_CHK  = 0xcf,       // check cmd
} emEspUart_pari_t;
#define IS_VALID_UART_PARI_ESP(x)   ((ESP_UART_PARI_NONE == x) ||  \
                                     (ESP_UART_PARI_EVEN == x) || ( ESP_UART_PARI_ODD == x))
//---end uart parity---------------------------------------------------------------end---

//---uart stopbit------------------------------------------------------------------------
typedef enum
{
    ESP_UART_STOP_1   = 0x01,     // 1位停止位 
    ESP_UART_STOP_1P5 = 0x02,     // 1.5位停止位 
	  ESP_UART_STOP_2   = 0x03,     // 2位停止位
    ESP_UART_STOP_CHK = 0xcf,	    // check cmd
} emEspUart_stop_t;   
#define IS_VALID_UART_STOP_ESP(x) ((ESP_UART_STOP_1   == x) ||   \
                                   (ESP_UART_STOP_1P5 == x) || (ESP_UART_STOP_2 == x))
//---end uart stopbit--------------------------------------------------------------end---

//---uart hardflow-----------------------------------------------------------------------
typedef enum
{
    ESP_UART_FLOW_CLOSE   = 0x00,      
    ESP_UART_FLOW_RTS     = 0x01,  
    ESP_UART_FLOW_CTS     = 0x02,  	
	  ESP_UART_FLOW_RTSCTS  = 0x03,  	
    ESP_UART_FLOW_CHK     = 0xcf,	 // check cmd
} emEspUart_hardflow_t;
#define IS_VALID_UART_FLOW_ESP(x)  ((ESP_UART_FLOW_CLOSE  == x) || (ESP_UART_FLOW_RTS  == x) || \
                                    (ESP_UART_FLOW_RTSCTS == x) || (ESP_UART_FLOW_CTS  == x))     
//---end uart hardflow--------------------------------------------------------------end---

//---uart hardflow-----------------------------------------------------------------------
typedef enum
{
    ESP_UART_BITS_5   = 0x05,      
    ESP_UART_BITS_6   = 0x06,  
    ESP_UART_BITS_7   = 0x07,  	
	  ESP_UART_BITS_8   = 0x08,  	
    ESP_UART_BITS_CHK = 0xcf,	 // check cmd
} emEspUart_databits_t;
#define IS_VALID_UART_BITS_ESP(x)  ((ESP_UART_BITS_5 == x) || (ESP_UART_BITS_6  == x) || \
                                    (ESP_UART_BITS_7 == x) || (ESP_UART_BITS_8  == x))                              
//---end uart hardflow--------------------------------------------------------------end---

///--end atk_module-uart-2 base parameters--------------------------------------------------------end---



///==End ESP->UART(ATK_MODULE)_Paras==========================================================================End====



#endif
/*----Endline : Full file-------------------------------------------------------------------------------------All_End---*/

