/******************************************************************************************************
 * @file        res_lmbt.h
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
          module : BT-11 of LM(www.lbluetooth.com)			
 ****************************************************************************************************
 * @update
 *   V1.0 
 *
 ****************************************************************************************************
 */

#ifndef _RES_LMBT_H_
#define _RES_LMBT_H_
#include "ThisProj_Glb.h"
#include RES_UART_HEAD
#include RES_BTBLE_UART_HEAD
#include UTY_BTBLE_HEAD  // "./component/spBtBle/UTY/utyBTBLE.h"

///==LMBT Setting==================================================================================
#define __DlyMs_Lmbt   (uint8_t)4

//---lmbt-dev-paras---------------------------------------------------------------------------
typedef struct {
	uint8_t             deeptim; //
	uint8_t             lowtim ; //
	emBTBLE_DevState_t  state;
	
}sttLMBT_DevParas_t;
extern sttLMBT_DevParas_t g_atkmoudle_lmbt_dev0;
//---end lmbt-dev-paras-----------------------------------------------------------------end---

//---RF power grade----------------------------------------------------------------------
typedef enum
{
    LMBT_PwrGrd_N15DBM = 0x00,            /* -15.7dBm */
    LMBT_PwrGrd_N12DBM,                   /* -12.5dBm */
    LMBT_PwrGrd_N10DBM,                   /* -10dBm */
    LMBT_PwrGrd_N6DBM,                    /* -6.6dBm */
	  LMBT_PwrGrd_N4DBM,
	  LMBT_PwrGrd_N2DBM,           
    LMBT_PwrGrd_N0DBM,                    /* -0.1dBm */
    LMBT_PwrGrd_P2DBM,                    /* +2.1dBm */
    LMBT_PwrGrd_P4DBM,                    /* +4.6dBm */	
    LMBT_PwrGrd_P6DBM,                    /* +6.4dBm */
	  LMBT_PwrGrd_CHK   = 0xcf,             // check cmd
} emLMBT_PwrGrd_t;
#define IS_VALID_PWRGRD_LMBT(x)   ((LMBT_PwrGrd_N15DBM == x) || (LMBT_PwrGrd_N12DBM == x) || (LMBT_PwrGrd_N10DBM == x) || \
                                   (LMBT_PwrGrd_N6DBM  == x) || (LMBT_PwrGrd_N4DBM  == x) || (LMBT_PwrGrd_N2DBM  == x) || \
                                   (LMBT_PwrGrd_N0DBM  == x) || (LMBT_PwrGrd_P2DBM  == x) || (LMBT_PwrGrd_P6DBM  == x)) 
//---end RF power grade-----------------------------------------------------------end---

///--power mode-----------------------------------------------------------------------------
typedef enum
{
    LMBT_PwrMd_AutoLow = 0x00,  // enable lowpower mode
    LMBT_PwrMd_Normal  = 0x01,  // enable normal power mode
	  LMBT_PwrMd_CHK     = 0xcf,  // check cmd
} emLMBT_PwrMd_t;
#define IS_VALID_PWRMD_LMBT(x)   ((LMBT_PwrMd_Normal == x) || (LMBT_PwrMd_AutoLow == x)) 

typedef enum
{
    LMBT_DeepSleep_Dis = 0x00,     // exit deepsleep
    LMBT_DeepSleep_Min = 5,       // Min s to enter deepsleep
	  LMBT_DeepSleep_Max = 200,      // Max s to enter deepsleep
	  LMBT_DeepSleep_CHK = 0xcf,     // check cmd
} emLMBT_DeepSleep_t;
#define IS_VALID_DEEPSLP_LMBT(x)   ((x >= LMBT_DeepSleep_Min ) && (x <= LMBT_DeepSleep_Max)) 
///--end power mode-------------------------------------------------------------------end---
///==End LMBT Setting=======================================================================End====

///==LMBT->UART(ATK_MODULE)_Paras=====================================================================================
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
	  UART_BAUDRATE_460800 = 460800,

} em_lmbt_uart_baud_t;
#define IS_VALID_UART_BAUDRATE_LMBT(x)   ((9600   == x) || (19200  == x) || (38400  == x) || \
                                          (57600  == x) || (115200 == x) || (230400 == x) || \
                                          (256000 == x) || (460800 == x))
//---end uart baudrate-------------------------------------------------------------end---

//---uart parity-------------------------------------------------------------------------
typedef enum
{
    LMBT_UART_PARI_NONE = 0x00,        /* 无校验 */
    LMBT_UART_PARI_EVEN = 0x01,        /* 偶校验 */	
    LMBT_UART_PARI_ODD  = 0x02,        /* 奇校验 */
	  LMBT_UART_PARI_CHK  = 0xcf,       // check cmd
} em_lmbt_uart_pari_t;
#define IS_VALID_UART_PARI_LMBT(x)   ((LMBT_UART_PARI_NONE  == x) || (LMBT_UART_PARI_EVEN == x) || ( LMBT_UART_PARI_ODD == x))
//---end uart parity---------------------------------------------------------------end---

//---uart stopbit------------------------------------------------------------------------
typedef enum
{
    LMBT_UART_STOP_1   = 0x00,     // 1位停止位 
    LMBT_UART_STOP_1P5 = 0x01,     // 1.5位停止位 
	  LMBT_UART_STOP_2   = 0x02,     // 2位停止位
    LMBT_UART_STOP_CHK = 0xcf,	    // check cmd
} em_lmbt_uart_stop_t;   
#define IS_VALID_UART_STOP_LMBT(x) ((LMBT_UART_STOP_1  == x) || (LMBT_UART_STOP_1P5 == x) || (LMBT_UART_STOP_2 == x))
//---end uart stopbit--------------------------------------------------------------end---

//---uart hardflow-----------------------------------------------------------------------
typedef enum
{
    LMBT_UART_FLOW_CLOSE = 0x00,      
    LMBT_UART_FLOW_OPEN  = 0x01,  
    LMBT_UART_FLOW_CHK   = 0xcf,	 // check cmd
} em_lmbt_uart_hardflow_t;
#define IS_VALID_UART_FLOW_LMBT(x) ((LMBT_UART_FLOW_CLOSE == x) || (LMBT_UART_FLOW_OPEN  == x))
//---end uart hardflow--------------------------------------------------------------end---
///--end atk_module-uart-2 base parameters--------------------------------------------------------end---



///==End LMBT->UART(ATK_MODULE)_Paras==========================================================================End====



#endif
/*----Endline : Full file----------------------------------------------------------------------All_End-----*/

