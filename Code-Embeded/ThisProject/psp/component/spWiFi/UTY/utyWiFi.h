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
          module : Esp8266 of LM(www.lbluetooth.com)			
 ****************************************************************************************************
 * @update
 *   V1.0 
 *
 ****************************************************************************************************
 */

#ifndef _UTY_WIFI_H_
#define _UTY_WIFI_H_
//#include "ThisProj_Glb.h"

///==Utility-BtBle-Devs=====================================================================================
//---glb cmd-----------------------------------------------------------------------------
#define CHECK_CMD_WIFI   0xcf
//---end glb cmd-------------------------------------------------------------------end---

//---err codes---------------------------------------------------------------------------
#define Err_WIFI_NONE      0    // No error
#define Err_WIFI_ERROR     1    // general error
#define Err_WIFI_TIMEOUT   2    // err of timeout
#define Err_WIFI_INVAL     3    // err of invalid para
//---end err codes-----------------------------------------------------------------end---

//---ESP-dev-paras---------------------------------------------------------------------------
typedef enum _WiFiDev{	
	  WIFI_Disconnect = 100, //"IM_DISC" of LMBTstring 	
	  WIFI_Ready      = 101, //"IM_READY" of LMBTstring 		
	 	WIFI_GotIP      = 102,
   	WIFI_Connect    = 103, //"IM_CONN" of LMBTstring 	
//	  WIFI_LowPower,      //LowPower mode
//	  WIFI_Normal,        //NormalPower mode
}emWIFI_DevState_t;

//---end ESP-dev-paras-----------------------------------------------------------------end---
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










