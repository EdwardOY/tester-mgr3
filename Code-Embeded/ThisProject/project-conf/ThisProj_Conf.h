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

#ifndef _THISPROJ_CONF_H_
#define _THISPROJ_CONF_H_

#include <string.h>
#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <stdarg.h> 	
#include <stdbool.h> 	
#include "math.h"

#include "ThisProj_Def.h"

///S>==This Project==========================================================================================
///s>--1 Processing Device ------------------------------------------------------------------------------
#define G_THIS_PCR_FRAME         ARM_CORTEX_M4

#if THIS_PCR == _MCU_STM32_  //MDK->Options->C/C++->Define

#define G_THIS_PCR_MACH        G_PCR_MACH_STM32_L496VE 
#define MCU_HEAD               "stm32l4xx.h" //"stm32f4xx_hal.h"

#endif //<THIS_PCR == _MCU_STM32_>
///e<--1 Processing Device ---------------------------------------------------------------------End-----

//s>--2 Board-------------------------------------------------------------------------------------------
#define THIS_BOARD        G_ATK_PDR496VE
#define G_SYS_TOCK        15000U
//e<--2 Board-----------------------------------------------------------------------------------End-----

//s>--3 CMPL compile sellector--------------------------------------------------------------------------
#define CMPL_RAW          0
#define CMPL_EDWOY        1
#define CMPL_THISPROJ     CMPL_EDWOY
//e<--3 CMPL compile sellector--------------------------------------------------------------------End----

//s>--4 cmBacktrace--------------------------------------------------------------------------------------
//edwoy260429---
// https://github.com/armink/CmBacktrace
#define G_USE_CMBT       1
//e<--4 cmBacktrace------------------------------------------------------------------------------End----

//s>--GPIO Sample use-----------------------------------------------------------------------------------
#define G_USE_SAMP_GPIO  G_USE_SAMP_GPIO_AFL 
//e<--GPIO Sample use----------------------------------------------------------------------------End----



///--2 SortNumber of peripherals的排序号+----------------------------------------------------------------
//retain,unused
//buttons 排序号
typedef enum {sBtn0 = 0U,sBtn1 = 1U,sBtn2 = 2U,sWkUp = 3U,} emBtnSort_t; 

//leds 排序号
typedef enum {sRED_LED = 0, sBlueLed = 1, sGREEN_LED = 2,} emLedSort_t; 

//emExtiSort_t:各Exti的排序号，作EXTIs数组成员 BSP_EXTIn序号
//Btn0 = PHin(3), Btn1 = PHin(2), 所以Btn0&Btn1一起配置
typedef enum {sExtiB0 = 0,sExtiB1 = 1, sExtiB2 = 2,sExtiWkUp = 3,} emExtiSort_t;  
//各UART排序号，作Uarts各数组成员(BSP_UARTqty)序号
typedef enum {sUart1 = 0,sUart2 = 1,sUart3 = 2,sUart4 = 3} emUartSort_t;  
//各timer的排序号，作Timers数组成员BSP_TIMn序号
typedef enum {sTim1 = 0,sTim4 = 1,sTim5 = 2} emTimSort_t; 

//i2c port Sort
typedef enum{sI2c1 = 0, sI2c2 = 1,}emI2cSort_t; 
#define sI2cChA    sI2c2
#define sI2cChB    sI2c1

typedef enum{sRamIn = 0, sFmcSdm = 1, sRamCcm = 2}emRamSort_t; //Ram sort

///--End:2 SortNumber of peripherals-------------------------------------------------------------End-----

///-3 Project Config/Setting/CMPL....--------------------------------------------------------------------

/**3.1 CMPL_RS485d1_RxInt to select only one between atk and wdw 
 *   3.1.1 atkRS485d1_UX_IRQHandler(verified ),use ATK-MtrCtrl orgn-codes
             Fill rx-datas in atkRS485d1_UX_IRQHandler
 *   3.1.2 (default use)edwRS485d1_UX_IRQHandler(verified )
           Fill rx-datas in HAL_UART_RxCpltCallback
 *----------------------------------------------------------------------------*/
#define CMPL_RS485d1_RxInt_Atk  1
#define CMPL_RS485d1_RxInt_Edw  2
#define CMPL_RS485d1_RxInt      0  //close rx485

/**3.2 CMPL_DBCOM_RxInt to select only one between atk and edw 
 *   3.2.1 CMPL_DBCOM_RxInt == CMPL_DBCOM_RxInt_Atk (verified ),use ATK-MtrCtrl orgn-codes
           Fill rx-datas in HAL_UART_RxCpltCallback
 *   3.2.2 (default use)CMPL_DBCOM_RxInt == CMPL_DBCOM_RxInt_Edw(verified )
           Fill rx-datas in DBCOM_UX_IRQHandler
 *----------------------------------------------------------------------------*/
#define CMPL_DBCOM_RxInt_Atk  0
#define CMPL_DBCOM_RxInt_Edw  1
#define CMPL_DBCOM_RxInt      CMPL_DBCOM_RxInt_Edw

/**3.3 CMPL_MODULE_RxInt to select only one between atk and edw 
 *   3.3.1 CMPL_MODULE_RxInt == CMPL_MODULE_RxInt_Atk (),use ATK-MtrCtrl orgn-codes
           Fill rx-datas in HAL_UART_RxCpltCallback
 *   3.3.2 (default use)CMPL_MODULE_RxInt == CMPL_MODULE_RxInt_Edw( )
           Fill rx-datas in MODULE_UX_IRQHandler
 *----------------------------------------------------------------------------*/
//#define CMPL_MODULE_RxInt_Atk  0
//#define CMPL_MODULE_RxInt_Edw  1
//#define CMPL_MODULE_RxInt      CMPL_MODULE_RxInt_Edw

///--End:3 Project Config/Setting/CMPL....----------------------------------------------------------End----


///E<==This Project===================================================================================End====

/*---SYS_SUPPORT_OS用于定义系统文件夹是否支持OS--------------------------------------------
 * 0,不支持OS
 * 1,支持OS
 */
#ifndef OS_EN_FRRT  
#define OS_EN_FRRT      0   
#endif
#define SYS_SUPPORT_OS  OS_EN_FRRT 
/*---End,SYS_SUPPORT_OS------------------------------------------------------------------*/

#endif // _THISPROJ_CONF_H_
////----Endline : Full file-----------------------------------------------------------------------------------All_End-----

//#include "./SYSTEM/sys/sys.h"
//#include "./component/spWiFi/ESP/esp8266.h" //"./BSP/ATK_MW8266D/atk_mw8266d.h"
//#include "./SYSTEM/usart/usart.h"
//#include "./SYSTEM/delay/delay.h"
//#include "./BSP/LED/led.h"
//#include "./BSP/KEY/key.h"
//#include "./BSP/LCD/lcd.h"

