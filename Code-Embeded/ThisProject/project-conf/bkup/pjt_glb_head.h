/**
 ****************************************************************************************************
 * @file        pjt_glb_head.h
                The program is copied form  E:\MCU-Exps\prjs-gd32\code1-1-epho407vet-base-ok							                           
 * @platform    ATK Apollo STM32F429IGTB
                https://item.taobao.com/item.htm?spm=a1z09.2.0.0.71ab2e8dBuaOH4&id=678302947208&_u=82v72r364b70 
 * @brief       跑马灯、dbcom
 * @date        2023.1.14
 * @state       validating
 * @author      Edwoy
 * @version     V1.1
 * @license     Copyright
 ****************************************************************************************************
 * @attention
      -1-,dbcom
			   1.1 Use usart2,tx is PA2,rx is PA3
				 1.2 Don`t use microLIB
				 1.3 Disable semihosting mode
			-2-,Use s8_t~s32_t to replace s8~s32 ,if run freeRTOS v10.4.6

 ****************************************************************************************************
 * @Details 
 *    -1-,Burn the same-type stm32 program into the corresponding gd32 , and then execute it.
      -2-,validated items
			  2.1 跑马灯(PB4),toggle
				2.2 dbcom(USART2), printf and rx datas
			-3-,RTOS
			  3.1 bare
			-4,
 * 
 ****************************************************************************************************
 * @Update
     V1.1  verfied and valid ,at 2023.1.14
		      use app_dbcom_init() in shell_uart.h
     V1.0 verfied and valid ,at2022,12,13
        -1- ,SYS_SUPPORT_OS is redefined ,so paced it into pjt_glb_head.h from sys.h
 */
 
#ifndef _PJT_GLB_HEAD_H_
#define _PJT_GLB_HEAD_H_

/*---SYS_SUPPORT_OS用于定义系统文件夹是否支持OS--------------------------------------------
 * 0,不支持OS
 * 1,支持OS
 */
#ifndef OS_EN_FRRT  
#define OS_EN_FRRT      0   
#endif
#define SYS_SUPPORT_OS  OS_EN_FRRT 
/*---End,SYS_SUPPORT_OS------------------------------------------------------------------*/

#include "./psp/utility/types.h"
#include UTY_DEF_HEAD
#include "convert_path.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <stdarg.h> 	
//#include <cstdlib.h>
#include "math.h"
//#include "debug.h"

#ifdef __cplusplus
extern "C" {
#endif

///--1 MCU --------------------------------------------------------------------------------------------
#ifdef _MCU_STM32_
#define MCU         stm32
#define MCU_HEAD   "stm32f4xx_hal.h"

#define  G_ATK_APL429IG_V1       0x04
#define  G_ATK_DMF407IG      0x05  //ATK-DMF407IGT6

#define  THIS_BOARD   G_ATK_APL429IG_V1 

#endif //<_MCU_STM32_>
///--End:1 MCU --------------------------------------------------------------------------------End-----


///--2 SortNumber of peripherals的排序号+--------------------------------------------------------------
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
 *   3.1.1 atkRS485d1_UX_IRQHandler(validated ),use ATK-MtrCtrl orgn-codes
             Fill rx-datas in atkRS485d1_UX_IRQHandler
 *   3.1.2 (default use)edwRS485d1_UX_IRQHandler(validated )
           Fill rx-datas in HAL_UART_RxCpltCallback
 *----------------------------------------------------------------------------*/
#define CMPL_RS485d1_RxInt_Atk  1
#define CMPL_RS485d1_RxInt_Edw  2
#define CMPL_RS485d1_RxInt      0  //close rx485

/**3.2 CMPL_DBCOM_RxInt to select only one between atk and edw 
 *   3.2.1 CMPL_DBCOM_RxInt == CMPL_DBCOM_RxInt_Atk (validated ),use ATK-MtrCtrl orgn-codes
           Fill rx-datas in HAL_UART_RxCpltCallback
 *   3.2.2 (default use)CMPL_DBCOM_RxInt == CMPL_DBCOM_RxInt_Edw(validated )
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



#ifdef __cplusplus
}
#endif

#endif 
/*----EndLine:Full File-----------------------------------------------------------------------------All-End----*/
