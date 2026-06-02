/*************************************************************************************
 *@file:  convert_def.h
 *@brief: This file defines the path macros for this project, and some other macros related to compile selection.
 *@author: EDWOY
 *@date:  2026.5.8
 *@version: V1.0
 *@notice :
     S_CMPL_CVT_EDWOY is invalid,don`t use it
 *************************************************************************************

**************************************************************************************/
#ifndef _CONVERT_DEF_H_
#define _CONVERT_DEF_H_
#include "ThisProj_Conf.h"
#include "convert_path.h"

////S>====Includes============================================================================================
//S>==Path Entry===============================================================================
//All Path Entries are failed to be included,Not recommended
//s>--1,RCC------------------------------------------------------------------------
#ifdef USE_HAL_DRIVER  //MDK->Options->C/C++->Define
#define CONFIG_HEAD      "stm32l4xx_hal_conf.h"
#else
#define _RccClkEn_Gpio    RCC_APB2PeriphClockCmd
#endif
//e<--end1,RCC---------------------------------------------------------------------

#if THIS_PCR == _MCU_STM32_  //MDK->Options->C/C++->Define
#define G_THIS_PCRLINE       "stm32l496ve/"   //processor line
#endif //<THIS_PCR...>

#if THIS_BOARD == G_ATK_PDR496VE  //MDK->Options->C/C++->Define
#define G_THIS_BD      "atk-pdr496ve/"
#endif //<THIS_BOARD...>



#define  S_CMPL_CVT_RAW      0  //valid
#define  S_CMPL_CVT_EDWOY    1  //invalid

#define  S_CMPL_CVT          S_CMPL_CVT_RAW  

//edwpy260427-------
#define G_ENTRY_PROJCONF     "./project-conf/" //./ThisProject/project-conf/
#define G_ENTRY_PD           "./psp/ProcessingDevice/" //./ThisProject/psp/ProcessingDevice/"      
#define G_ENTRY_MIDDW        "./psp/middw/"       //./ThisProject/psp/middw/
#define G_ENTRY_PRP_SHELL    "./psp/prp-shell/"       //./ThisProject/prp-shell/
#define G_ENTRY_RES          "./psp/resource/"       //./ThisProject/psp/resource/
#define G_ENTRY_COMPONENT    "./psp/component/"       //./ThisProject/component/


#define G_ENTRY_PCR          "./psp/ProcessingDevice/"       //./ThisProject/psp/board/
#define G_ENTRY_BORAD        "./psp/board/"       //./ThisProject/psp/board/
#define G_ENTRY_UTY          "./psp/utility/"       //./ThisProject/psp/utility/


#define G_3RD_ATK_BSP    "Pack-ATK/BSP/"
#define G_3RD_ATK_SYS    "Pack-ATK/SYSTEM/"
#define G_3RD_ATK_MLC    "Pack-ATK/MALLOC/"

//E<==Path Entry================================================================================


//s>--sample---------------------------------------------------------------------
//edwoy260501
#define SAMP_KEYS_HEAD   "./psp/board/atk-pdr496ve/sample_key.h"
#define SAMP_LEDS_HEAD   "./psp/board/atk-pdr496ve/sample_led.h"
//e<--sample---------------------------------------------------------------------

//s>--cmBacktrace-------------------------------------------------------------------------
#define CMBT_HEAD         "./psp/middw/cmBacktrace/cm_backtrace.h"
#define CMBT_CFG_HEAD     "./psp/middw/cmBacktrace/cmb_cfg.h"
#define CMBT_DEF_HEAD     "./psp/middw/cmBacktrace/cmb_def.h"
#define CMBT_EN_HEAD      "./psp/middw/cmBacktrace/Languages/en-US/cmb_en_US.h"
#define CMBT_CN_HEAD      "./psp/middw/cmBacktrace/Languages/zh-CN/cmb_zh_CN.h"
#define CMBT_CN_UT8_HEAD      "./psp/middw/cmBacktrace/Languages/zh-CN/cmb_zh_CN_UTF8.h"
#define CMBT_SAMPLE_APP_HEAD      "./psp/middw/cmBacktrace/sample_cmbt_app.h"
//e<--cmBacktrace-------------------------------------------------------------------------

//s>--utility-------------------------------------------------------------------------
#if S_CMPL_CVT == S_CMPL_CVT_RAW
#define UTY_DEF_HEAD          "./psp/utility/utility_def.h"
#define UTY_TYP_HEAD          "./psp/utility/types.h"
#define UTY_DEBUG_HEAD        "./psp/utility/debug.h"
#elif S_CMPL_CVT == S_CMPL_CVT_EDWOY
#define UTY_DEF_HEAD        G_ENTRY_UTY"utility_def.h"
#define UTY_TYP_HEAD       G_ENTRY_UTY"types.h"

#endif //<#elif S_CMPL_CVT == S_CMPL_CVT_EDWOY>

//e<--utility-------------------------------------------------------------------------

//s>--3rd pack-armfly-----------------------------------------------------------------
//edwoy260503--
#define AFL_BSP_HEAD        "./psp/middw/Pack-Armfly/blink/bsp.h"
#define AFL_LED_HEAD        "./psp/middw/Pack-Armfly/blink/bsp_led.h"
#define AFL_KEY_HEAD        "./psp/middw/Pack-Armfly/blink/bsp_key.h"
#define SAMP_AFL_KEY_HEAD        "./psp/middw/Pack-Armfly/blink/sample_keys_afl.h"
//e<--3rd pack-armfly-----------------------------------------------------------------

//s>--3rd pack-atk--------------------------------------------------------------------
#if S_CMPL_CVT == S_CMPL_CVT_RAW
        
#define ATK_SYS_HEAD        "./psp/middw/Pack-ATK/SYSTEM/sys/sys_stm32l4.h"

#define ATK_UART_HEAD   "./psp/middw/Pack-ATK/SYSTEM/usart/atk_usart.h" //
#define ATK_DLY_HEAD        "./psp/middw/Pack-ATK/SYSTEM/delay/atk_stkdly.h"
#define ATK_BEEP_HEAD   "./psp/middw/Pack-ATK/BSP/BEEP/beep.h" 
#define LED_HEAD        "./psp/middw/Pack-ATK/BSP/LED/led.h"
#define KEY_HEAD        "./psp/middw/Pack-ATK/BSP/KEY/key.h"
#define LCD_HEAD        "./psp/middw/Pack-ATK/BSP/LCD/lcd.h"
#define LCD_FONT_HEAD   "./psp/middw/Pack-ATK/BSP/LCD/lcdfont.h"
#define I2C_HEAD        "./psp/middw/Pack-ATK/BSP/IIC/myiic.h"
#define PCF8574_HEAD    "./psp/middw/Pack-ATK/BSP/PCF8574/pcf8574.h"
#define ATK_RS485_HEAD   "./psp/middw/Pack-ATK/BSP/RS485/rs485.h"
#define ATK_CAN_HEAD    "./psp/middw/Pack-ATK/BSP/CAN/atk_can.h"

#define MLC_HEAD        "./psp/middw/Pack-ATK/MALLOC/malloc.h"


#elif S_CMPL_CVT == S_CMPL_CVT_EDWOY
#define SYS_HEAD        G_ENTRY_MIDDW G_3RD_ATK_SYS"sys_stm32l4.h"
#define ATK_UART_HEAD   G_ENTRY_MIDDW G_3RD_ATK_SYS"atk_usart.h" //
#define DLY_HEAD        G_ENTRY_MIDDW G_3RD_ATK_BSP"delay.h"
#define LED_HEAD        G_ENTRY_MIDDW G_3RD_ATK_BSP"led.h"
#define KEY_HEAD        G_ENTRY_MIDDW G_3RD_ATK_BSP"key.h"
#define LCD_HEAD        G_ENTRY_MIDDW G_3RD_ATK_BSP"lcd.h"
#define I2C_HEAD        G_ENTRY_MIDDW G_3RD_ATK_BSP"myiic.h"
#define ATK_RS485_HEAD   G_ENTRY_MIDDW G_3RD_ATK_BSP"rs485.h"
#define ATK_CAN_HEAD    G_ENTRY_MIDDW G_3RD_ATK_BSP"atk_can.h"
#define PCF8574_HEAD    G_ENTRY_MIDDW G_3RD_ATK_BSP"pcf8574.h"

#define MLC_HEAD        G_ENTRY_MIDDW G_3RD_ATK_MLC"malloc.h"

#endif //<#elif S_CMPL_CVT == S_CMPL_CVT_EDWOY>

//e<--3rd pack-atk---------------------------------------------------------------------

//s>--prp-shell--------------------------------------------------------------------
#if S_CMPL_CVT == S_CMPL_CVT_RAW
#define EDW_UART_HEAD    "./psp/prp-shell/shell_uart.h" 
#define SPI_HEAD        "./psp/prp-shell/shell_spi.h"
#define GPIO_HEAD       "./psp/prp-shell/shell_gpio.h"
#define EDW_CAN_HEAD     "./psp/prp-shell/shell_can.h"

#elif S_CMPL_CVT == S_CMPL_CVT_EDWOY

#define EDW_UART_HEAD    G_ENTRY_PRP_SHELL"shell_uart.h" 
#define SPI_HEAD        G_ENTRY_PRP_SHELL"shell_spi.h"
#define GPIO_HEAD       G_ENTRY_PRP_SHELL"shell_gpio.h"
#define EDW_CAN_HEAD     G_ENTRY_PRP_SHELL"shell_can.h"
#endif //<#elif S_CMPL_CVT == S_CMPL_CVT_EDWOY>
//e<--prp-shell--------------------------------------------------------------------

//s>--bsp board--------------------------------------------------------------------

#if S_CMPL_CVT == S_CMPL_CVT_EDWOY 
#define G_PATH_BSP       G_ENTRY_BORAD G_THIS_BD 
#define BSP_GPIO_HEAD    G_PATH_BSP"bsp_gpio.h"
#define BSP_RES_HEAD     G_PATH_BSP"bsp_resource.h"
#define BSP_MISC_HEAD    G_PATH_BSP"bsp_misc.h"

#elif S_CMPL_CVT == S_CMPL_CVT_RAW
#define BSP_GPIO_HEAD    "./psp/board/atk-pdr496ve/bsp_gpio.h"
#define BSP_RES_HEAD     "./psp/board/atk-pdr496ve/bsp_resource.h"
#define BSP_MISC_HEAD    "./psp/board/atk-pdr496ve/bsp_misc.h"
#endif //<#elif S_CMPL_CVT == S_CMPL_CVT_EDWOY>
//e<-- bsp board-------------------------------------------------------------------

//s>--resource---------------------------------------------------------------------

#if S_CMPL_CVT == S_CMPL_CVT_EDWOY 
#define RES_MISC_HEAD    G_ENTRY_RES"res_misc.h"
#define RES_TIM_HEAD     G_ENTRY_RES"res_tim.h"
#define RES_GPIO_HEAD    G_ENTRY_RES"res_gpio.h"
#define RES_UART_HEAD    G_ENTRY_RES"res_uart.h"
#define RES_CAN_HEAD     G_ENTRY_RES"res_can.h"

#elif S_CMPL_CVT == S_CMPL_CVT_RAW
#define RES_MISC_HEAD    "./psp/resource/res_misc.h"
#define RES_TIM_HEAD     "./psp/resource/res_tim.h"
#define RES_GPIO_HEAD    "./psp/resource/res_gpio.h"
#define RES_UART_HEAD    "./psp/resource/res_uart.h"
#define RES_CAN_HEAD     "./psp/resource/res_can.h"
#define RES_BTBLE_HEAD   "./psp/component/spBtBle/lmbt/res_lmbt.h"
#define RES_BTBLE_UART_HEAD   "./psp/component/spBtBle/lmbt/res_lmbt_uart.h"
#define RES_WIFI_HEAD         "./psp/component/spWiFi/ESP/res_esp.h"
#define RES_WIFI_UART_HEAD    "./psp/component/spWiFi/ESP/resdrv_iot_uart.h"
#define RES_CAT1_HEAD         "./psp/component/spCat1/SIMCom/res_cat1.h"
#define RES_CAT1_UART_HEAD    "./psp/component/spCat1/SIMCom/resdrv_cat1_uart.h"

#endif //<#elif S_CMPL_CVT == S_CMPL_CVT_EDWOY>

//e<--resource--------------------------------------------------------------------

//s>--component-------------------------------------------------------------------
#define CPT_RS485_HEAD   "./psp/component/cpt_rs485.h"
#define CPT_RS232_HEAD   "./psp/component/serialport.h"
#define CPT_BTBLE_HEAD   "./psp/component/spBtBle/lmbt/lmbt.h"
#define CPT_WIFI_HEAD    "./psp/component/spWiFi/ESP/esp8266.h"
#define CPT_CAT1_HEAD    "./psp/component/spCat1/SIMCom/a7670c.h"
//e<--component-------------------------------------------------------------------

/*-------------------------------------------------------------------------------*/
#define UTY_BTBLE_HEAD   "./psp/component/spBtBle/UTY/utyBtBle.h"
#define UTY_WIFI_HEAD    "./psp/component/spWiFi/UTY/utyWiFi.h"
#define UTY_CAT1_HEAD    "./psp/component/spCat1/UTY/utyCat1.h"
/*-------------------------------------------------------------------------------*/

//s>--EDWOY own header----------------------------------------------------------------
#define EDW_SYS_HEAD        "./psp/ProcessingDevice/stm32l4xx/sys_stm32l496ve.h" //./ThisProject/psp/ProcessingDevice/"  
#define EDW_DLY_HEAD        "./psp/ProcessingDevice/systick.h"
//e<--EDWOY own header----------------------------------------------------------------

////E<====Includes=====================================================================================END====

////S>==2,Peripherals=========================================================================================

///s>==2.1,GPIO======================================================================================
//s>--2.1apis------------------------------------------------------------------------------------
#if defined(USE_HAL_DRIVER)
#define API_PRP_GPIO_INIT          HAL_GPIO_Init   //api: Init the GPIO
#define API_PRP_GPIO_DEINIT        HAL_GPIO_DeInit
#define API_PRP_GPIO_PIN_RD        HAL_GPIO_ReadPin
#define API_PRP_GPIO_PIN_WT        HAL_GPIO_WritePin
#define API_PRP_GPIO_PIN_TOGG      HAL_GPIO_TogglePin
#define API_PRP_GPIO_PIN_LOCK      HAL_GPIO_LockPin
#elif defined(USE_FULL_LL_DRIVER)
#define API_PRP_GPIO_INIT          LL_GPIO_Init 
#define API_PRP_GPIO_INIT_STT      LL_GPIO_StructInits
#define API_PRP_GPIO_DEINIT        LL_GPIO_DeInit
#define API_PRP_GPIO_PIN_RD        LL_GPIO_ReadPin
#define API_PRP_GPIO_PIN_WT        LL_GPIO_WritePin
#define API_PRP_GPIO_PIN_TOGG      LL_GPIO_TogglePin
#define API_PRP_GPIO_PIN_LOCK      LL_GPIO_LockPin
#elif defined(USE_STDERIPH_DRIVER)

#endif



//e<--2.1apis------------------------------------------------------------------------------------

#define STT_PRP_GPIO_T                sttPrp_Gpio_t    //retain

#if defined(USE_HAL_DRIVER)

#define STT_GPIO_BK_T            GPIO_TypeDef    //be similar to stm32`s GPIO_TypeDef_d
#define STT_GPIO_INIT_T       GPIO_InitTypeDef  //be similar to stm32`s GPIO_InitTypeDef_d 
#define EM_GPIO_PIN_STA_T     GPIO_PinState       //be similar to stm32`s uint16_t_d
#define G_GPIO_PIN_RST          GPIO_PIN_RESET //Bit_RESET      //be similar to stm32`s GPIO_PIN_RESET_d    
#define G_GPIO_PIN_SET           GPIO_PIN_SET   //Bit_SET        //be similar to stm32`s GPIO_PIN_SET_d  

#elif defined(USE_FULL_LL_DRIVER)
#define LL_GPIO_InitTypeDef            LL_GPIO_InitTypeDef
#elif defined(USE_STDERIPH_DRIVER)

#elif defined(USE_REG_DRIVER)

#endif
///e<==2.1,GPIO=======================================================================================

///s>==2.2,USART======================================================================================
#if defined(USE_HAL_DRIVER)
#define STT_UART_BK_T            UART_TypeDef    //be similar to stm32`s UART_TypeDef_d
#define STT_UART_INIT_T          UART_InitTypeDef  //be similar to stm32`s UART_InitTypeDef_d 


#elif defined(USE_FULL_LL_DRIVER)

#elif defined(USE_STDERIPH_DRIVER)

#else // use register level driver

#endif
///e<==2.2,USART======================================================================================

///s>==2.3,I2C========================================================================================

///e<==2.3,I2C========================================================================================

///s>==2.4,SPI========================================================================================

///e<==2.4,SPI========================================================================================

///s>==2.5,Can========================================================================================

///e<==2.5,Can========================================================================================

///s>==2.6,Timer======================================================================================

///e<==2.6,Timer======================================================================================

///s>==2.7,USB========================================================================================

///e<==2.7,USB========================================================================================

///s>==2.8,Ethernet===================================================================================

///e<==2.8,Ethernet===================================================================================

///s>==2.9,ADC========================================================================================

///e<==2.9,ADC========================================================================================

////E<==2,Peripherals==================================================================================END====

#endif // _CONVERT_DEF_H_
////----EndLine:Full File--------------------------------------------------------------------

//#define DBCOM_HEAD      "./psp/middw/Pack-ATK/SYSTEM/usart/usart.h"
//#define BSP_HEAD_BTMGPIO "./psp/board/atk-pdr496ve/bsp_gpio.h"
//#define MISC_HEAD     "./psp/ProcessingDevice/stm_misc.h"
//#define MLC_HEAD      "./psp/ProcessingDevice/stm_mlc.h" 
//#define SDM_HEAD      "./psp/prp-shell/stm_fmc_sdram.h" 
//#define TIM_HEAD      "./psp/prp-shell/stm_timer.h"
//#define USMT_HEAD     "./psp/prp-shell/stm_usmt.h"
//#define IWDG_HEAD     "./psp/prp-shell/stm_iwdg.h"
//#define WWDG_HEAD     "./psp/prp-shell/stm_wwdg.h"
//#define DMA_HEAD      "./psp/prp-shell/stm_dma.h"

//#define BSP_GPIO_HEAD  "bsp_gpio.h" 
//#define BSP_TIM_HEAD   "bsp_timcls.h"

//#define CPT__chA_et6144_HEAD  "./psp/component/i2c_et6144.h"
//#define CPT_SP_HEAD       "./psp/component/serialport.h"

//#define RL_ETHINCS_HEAD   "./RL-ARM/RL-TCPnet/rl_tcpnet_incs.h"
//#define RL_ETHMAC_HAED    "./RL-ARM/RL-TCPnet/EMAC_STM32F4xx.h"
//#define RL_ETHPHY_HEAD    "./RL-ARM/RL-TCPnet/PHY_LAN8720.h"
