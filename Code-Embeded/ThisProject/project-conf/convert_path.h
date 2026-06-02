/*************************************************************************************
 *@file:  convert_path.h
 *@brief:  路径转换
 *@author: EDWOY
 *@date:  2026.4.27
 *@version: V1.0
 *************************************************************************************

**************************************************************************************/
#ifndef _CONVERT_PATH_H_
#define _CONVERT_PATH_H_
#include "ThisProj_Conf.h"
#include "convert_def.h"

//S>==Path Entry===============================================================================


//E<==Path Entry===============================================================================

//s>--Items selection--------------------------------------------------------------
#define RS485_HEAD        ATK_RS485_HEAD
#define CAN_HEAD          EDW_CAN_HEAD
#define UART_HEAD         EDW_UART_HEAD 
#define SYS_HEAD          EDW_SYS_HEAD    //   "./psp/ProcessingDevice/stm32l496ve/sys_stm32l496ve.h" //./ThisProject/psp/ProcessingDevice/"  
#define DLY_HEAD          EDW_DLY_HEAD
//e<--End Items selection----------------------------------------------------------

//s>--cmBacktrace-------------------------------------------------------------------------
/* 
//valid: 2026.4.29
#define CMBT_EN_HEAD      "./psp/middw/cmBacktrace/Languages/en-US/cmb_en_US.h"

//valid: 2026.4.29
#define CMBT_CN_HEAD      "./psp/middw/cmBacktrace/Languages/zh-CN/cmb_zh_CN.h" 

//invalid: 2026.4.29
#define CMBT_CN_UT8_HEAD      "./psp/middw/CmBacktrace/Languages/zh-CN/cmb_zh_CN_UTF8.h"
 */

#define CMBT_LANG_HEAD     CMBT_CN_HEAD //CMBT_EN_HEAD
#define G_CMBT_VER_HW               "V1.0.0"
#define G_CMBT_VER_SW               "V0.1.0"

//e<--cmBacktrace-------------------------------------------------------------------------

#endif // _CONVERT_PATH_H_
////----EndLine:Full File--------------------------------------------------------------------

//#define DBCOM_HEAD      "./Pack-ATK/SYSTEM/usart/usart.h"
//#define BSP_HEAD_BTMGPIO "./psp/board/atk-apl429v1/bsp_gpio.h"
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
