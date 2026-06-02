/******************************************************************************************************
 * @file        utyBTBLE.h
 * @author      Edwoy
 * @version     V1.0
 * @date        2021-10-27
 * @brief       Bluetooth&BLE  utility-drv header 
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

#ifndef _UTY_BTBLE_H_
#define _UTY_BTBLE_H_
#include "ThisProj_Glb.h"

///==Utility-BtBle-Devs=====================================================================================
//---glb cmd-----------------------------------------------------------------------------
#define CHECK_CMD_BTBLE   0xcf
//---end glb cmd-------------------------------------------------------------------end---

//---err codes---------------------------------------------------------------------------
#define Err_BTBLE_NONE      0    // No error
#define Err_BTBLE_ERROR     1    // general error
#define Err_BTBLE_TIMEOUT   2    // err of timeout
#define Err_BTBLE_INVAL     3    // err of invalid para
//---end err codes-----------------------------------------------------------------end---

//---lmbt-dev-paras---------------------------------------------------------------------------
typedef enum _BtBleDev{	
	  BTBLE_Ready      = 0, //"IM_READY" of LMBTstring 	
	  BTBLE_Disconnect = 1, //"IM_DISC" of LMBTstring 	
   	BTBLE_Connect    = 2, //"IM_CONN" of LMBTstring 
	 	BTBLE_DeepSleep ,
	  BTBLE_LowPower,      //LowPower mode
	  BTBLE_Normal,        //NormalPower mode
}emBTBLE_DevState_t;
//---end lmbt-dev-paras-----------------------------------------------------------------end---
//---connection state--------------------------------------------------------------------
typedef enum
{
    ATK_MODULE_CONNECTED = 0x00,             /* 已连接 */
    ATK_MODULE_DISCONNECTED,                 /* 未连接 */
} atk_module_conn_sta_t;
//---end connection state----------------------------------------------------------end---
///==End Utility-BtBle-Devs==========================================================================End====


#endif
/*----Endline : Full file----------------------------------------------------------------------All_End-----*/










