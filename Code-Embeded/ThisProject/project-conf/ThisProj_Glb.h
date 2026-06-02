/******************************************************************************************************
 * @file        project.h
 * @author      Edwoy
 * @version     V1.0
 * @date        2025-06-21
 * @brief       ESPDev模块TCP透传实验
 * @license     Copyright (c) 
 ****************************************************************************************************
 * @attention
 *     -1-
 ****************************************************************************************************
 * @information
 * 实验平台:ATK-PandoraL496ve

 ****************************************************************************************************
 */

#ifndef _THISPROJ_GLB_H_
#define _THISPROJ_GLB_H_

///==Project-Includes=====================================================================================

#include "ThisProj_Conf.h"
#include "convert_path.h"
//s>--incs by cubeMx----------------------------------------------
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"
//e<--incs by cubeMx----------------------------------------------

#include SYS_HEAD
#include DLY_HEAD
#include UART_HEAD



//s>--3rd pack-atk--------------------------------------------------------------------
//#include LED_HEAD     //   "./Pack-ATK/BSP/LED/led.h"
//#include KEY_HEAD     //   "./Pack-ATK/BSP/KEY/key.h"
//#include ATK_UART_HEAD  //  "./psp/middw/Pack-ATK/SYSTEM/usart/atk_usart.h" //

//#include "usart.h"
#include ATK_BEEP_HEAD   // "./psp/middw/Pack-ATK/BSP/BEEP/beep.h" 

//e<--3rd pack-atk---------------------------------------------------------------------

//s>--3rd pack-armfly-----------------------------------------------------------------
//edwoy260503--
//#include AFL_BSP_HEAD       //    "./psp/Pack-Armfly/blink/bsp.h"
//#include AFL_LED_HEAD         //  "./psp/Pack-Armfly/blink/bsp_led.h"
#include AFL_KEY_HEAD         //   "./psp/Pack-Armfly/blink/bsp_gpio.h"
#include SAMP_AFL_KEY_HEAD   // "./psp/Pack-Armfly/blink/sample_keys_alf.h"
//e<--3rd pack-armfly-----------------------------------------------------------------

#include CMBT_HEAD         //    "./psp/cmBacktrace/cm_backtrace.h"
#include CMBT_DEF_HEAD     // "./psp/middw/cmBacktrace/cmb_def.h"
#include CMBT_SAMPLE_APP_HEAD 

/* 
#include GPIO_HEAD
#include BSP_GPIO_HEAD

//#include MLC_HEAD
//#include CPT_CAT1_HEAD   // "./component/spWiFi/ESP/esp8266.h"


//Don`t include CMBT_LANG_HEAD 



//s>--3rd pack-atk--------------------------------------------------------------------

//#include LCD_HEAD        //"./Pack-ATK/BSP/LCD/lcd.h"
//#include LCD_FONT_HEAD     //   "./Pack-ATK/BSP/LCD/lcdfont.h"

//e<--3rd pack-atk---------------------------------------------------------------------

*/


#include UTY_TYP_HEAD
#include UTY_DEF_HEAD


///s>--sample-----------------------------------------------------------------------------
#include SAMP_KEYS_HEAD    // "./psp/board/atk-apl429v1/sample_gpio.H"
#include SAMP_LEDS_HEAD    // "./psp/board/atk-apl429v1/sample_leds.H"
///e<--sample-----------------------------------------------------------------------------
///==End Project-Includes==========================================================================End====

//s>--system task-----------------------------------------------------------------------------------
void etf_taskHome(void *pArg);
//e<--system task------------------------------------------------------------------------end----

char app_custom_btn0(void* pArg);
char app_custom_btn1(void* pArg);
char app_custom_btn2(void* pArg);
char app_custom_wkup(void* pArg);

#endif // _THISPROJ_GLB_H_
////----Endline : Full file----------------------------------------------------------------------All_End----

//#include "./SYSTEM/sys/sys.h"
//#include "./component/spWiFi/ESP/esp8266.h" //"./BSP/ATK_MW8266D/atk_mw8266d.h"
//#include "./SYSTEM/usart/usart.h"
//#include "./SYSTEM/delay/delay.h"
//#include "./BSP/LED/led.h"
//#include "./BSP/KEY/key.h"
//#include "./BSP/LCD/lcd.h"

