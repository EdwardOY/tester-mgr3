/******************************************************************************************************
 * @file        project.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ESPDev模块TCP透传实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *     -1-
 ****************************************************************************************************
 * @information
 * 实验平台:正点原子 F407电机开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#ifndef _PROJECT_H_
#define _PROJECT_H_

///==Project-Includes=====================================================================================

#include "ThisProj_Glb.h"
#include DLY_HEAD
#include SYS_HEAD
#include GPIO_HEAD
#include UART_HEAD
#include BSP_GPIO_HEAD
#include PCF8574_HEAD
//#include MLC_HEAD
#include CPT_CAT1_HEAD   // "./component/spWiFi/ESP/esp8266.h"
///==End Project-Includes==========================================================================End====

//--system task-----------------------------------------------------------------------------------
void etf_taskHome(void);
//--end system task------------------------------------------------------------------------end----

#endif
/*----Endline : Full file----------------------------------------------------------------------All_End-----*/

//#include "./SYSTEM/sys/sys.h"
//#include "./component/spWiFi/ESP/esp8266.h" //"./BSP/ATK_MW8266D/atk_mw8266d.h"
//#include "./SYSTEM/usart/usart.h"
//#include "./SYSTEM/delay/delay.h"
//#include "./BSP/LED/led.h"
//#include "./BSP/KEY/key.h"
//#include "./BSP/LCD/lcd.h"

