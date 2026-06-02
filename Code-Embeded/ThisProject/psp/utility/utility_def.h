/****
* @Filename : utility_def.h
* @Mcu      : all mcus
*	@Platform all development platforms 
* @Purpose : For all development platforms 
             Define public macro
             Declare common variables 
* @Author : EDW.OY
* @version V2.1
* @Copyright(C) 
*****************************************************************************
* @attention : 
    0 Common info
		  0.1 Based on NEC PWM prot
*   1 Devellop platform : Pandora STM32L475VET6(LQFP100)
*     1.1 
*     1.2
*   2 Devellop platform : Apollo STM32G457QEL(LQFP128)         
      2.1
	  3
		4
*****************************************************************************			
	@Update:  
	  V2.1 2021.12.14  Use orgn types£¬don`t use definition of types.h £¬
	  V2.0,2020.12.14  add apis umf_set_glbvar3232bit & umf_setbit_glbvar32_ex
		              glb_Var32(Ex)
								getbit_glbvar32 
	  2020.12.7 , add apis glbf_mkvar() and glbf_mkvar32_ex() 
		2020.11.24, expand array-Glb_Var32 members to  GLBVARn_DFTã€‚ 	
*/	
#ifndef __UTILITY_DFT_H_
#define __UTILITY_DFT_H_


/*+++++++Funtions+++++++++*/
#define BondName(a,b)   a##b  
#define ObjCombin(a,b)  a##b // combines a and b
#define Bond_Name(a,b)  a##_b
#define Bond_Head(a,b)  a##_b.h

/**
  *@brief utility api: Çólog(2)X
  *@param: num-->Ä¿±êÊýÖµ
	*@return ÒÔ2Îªµ×£¬NumµÄ¶ÔÊý
  *@update 2022.10.30,
 */
extern double ulf_log2(unsigned int  num);


/**
 * Definition OS
*/
#define  HEAD_OS_UCOS    <includes.h>
#define  HEAD_OS_FRRT    <FreeRTOS.h> 
#define  HEAD_OS_RTX5    
/**
 * Definition Freq
*/
#define __KHZ         1000U
#define __MHZ         1000000U
#define __GHZ         1000000000U
#define __32p768KHZ   32768U
#define __8MHZ        8000000U
#define __12MHZ       12000000U
#define __16MHZ       16000000U
#define __25MHZ       25000000U
#define __32MHZ       32000000U
#define __64MHZ       64000000U
#define __72MHZ       72000000U
#define __80MHZ       80000000U
#define __100MHZ      100000000U
#define __120MHZ      120000000U
#define __150MHZ      150000000U
#define __164MHZ      164000000U
#define __180MHZ      180000000U
#define __192MHZ      192000000U
#define __200MHZ      200000000U
#define __240MHZ      240000000U
#define __260MHZ      260000000U
#define __280MHZ      280000000U

#define _CLK_xMHZ_72          72         // main-frequency-MHz num of MCU 
#define _CLK_xMHZ_80          80        // main-frequency-MHz num of MCU
#define _CLK_xMHZ_180         180         //main-frequency-MHz num of MCU
#define _CLK_xMHZ_192         192         // main-frequency-MHz num of MCU(using USB module)

//using   __64MHz  = 6400000;

/**
 * Memory storage size
*/
#define __KB          1024
#define __4KB         4096
#define __MB         (__KB * __KB )
#define __GB         (__MB * __MB )

#define ClkPos1   ClkPosA    
#define ClkPos2   ClkPosB    
#define ClkPos3   ClkPosC   
#define ClkPos4   ClkPosD    
#define ClkPos5   ClkPosE    
#define ClkPos6   ClkPosF    
#define ClkPos7   ClkPosG    
#define ClkPos8   ClkPosH  

#define ClkPos9   ClkPosI    
#define ClkPos10  ClkPosJ  
#define ClkPos11  ClkPosK  
#define ClkPos12  ClkPosL   
#define ClkPos13  ClkPosM   
#define ClkPos14  ClkPosN   
#define ClkPos15  ClkPosO   
#define ClkPos16  ClkPosP   

/**
 * MCU×ÊÔ´µÄRCCÊ±ÖÓÊ¹ÄÜÎ»£¬ÓÃÓÚmm32_gpio.cÖÐµÄapi
   RccClkPt == RCC Clock Port 
	 Éý¼¶ºó£¬ÔªËØ»òÔËËã£¬¿ÉÒÔÒ»´Î¿ªÆô¶à¸ödevsµÄÊ±ÖÓ
*/		 
typedef enum {
		ClkPosA  =  (1 << 0),
		ClkPosB  =  (1 << 1),
		ClkPosC  =  (1 << 2),
		ClkPosD  =  (1 << 3),
		ClkPosE  =  (1 << 4),
		ClkPosF  =  (1 << 5),
		ClkPosG  =  (1 << 6),
		ClkPosH  =  (1 << 7),
		ClkPosI  =  (1 << 8),
		ClkPosJ  =  (1 << 9),
		ClkPosK  =  (1 << 10),
		ClkPosL  =  (1 << 11),
		ClkPosM  =  (1 << 12),
		ClkPosN  =  (1 << 13),
		ClkPosO  =  (1 << 14),
		ClkPosP  =  (1 << 15),	
}emClkPos_t;




/**
 * cmsis_os ver ; for  mm32_mlc.h
*/
#define CMSS_V1          1
#define CMSS_V2          2


/**\brief Definition manufacturer-ID-addr of mcu
  * ¸ÃµØÖ·ÉÏµÄÖµ£¬ÊÇÓÉ³§ÉÌÐ´ËÀµÄ£¬usrÎÞ·¨¸ü¸Ä
	* ¿É²éÑ¯mcuµÄÓÃ»§ÊÖ²á»ò²Î¿¼ÊÖ²á
  */
#define ID_STM32     (0x1FFF7A10)
#define ID_GD32      (0x1FFF7A10)

/**
 * Definition about MCU series
 * ^^Legacy
*/
#define MACH_STM32_F1XXMINI   0xa10000
#define MACH_STM32_F103X      0xa10300 
#define MACH_STM32_F103RBT6   0xa10301 
#define MACH_STM32_F103VET6   0xa10302 
#define MACH_STM32_F1XXMAX    0xa10800 

#define MACH_STM32_F427X      0xa42700 
#define MACH_STM32_F429X      0xa42900 
#define MACH_STM32_G457QEL   0xa42900 
#define MACH_STM32_F4XXMAX    0xa4ff00 //

#define MACH_STM32_L475X      0x047500
#define MACH_STM32_L475VET6   0x047500

/**
 * Definition about usrpjt series V2
 * ^^Newest is V2
 * @update:2022.3.5
*/
/*MCU MACHä¸»äº§å“çº¿å®šä¹‰ 
 */
#define MACH_C51         1   //51 family
#define MACH_STM8        0x08
#define MACH_STM32       0x20
#define MACH_GD32        0x21 //GigaDevice åŒ—äº¬å…†æ˜“åˆ›æ–°
#define MACH_HC32        0x22 //HuaDa åŽå¤§åŠå¯¼ä½“
#define MACH_N32         0x23 //NC    å›½å®¶åŠå¯¼ä½“
#define MACH_MM32        0x24 //MindMotion  ä¸Šæµ·çµåŠ¨å¾®
#define MACH_HK32        0x25 //æ·±åœ³é¡ºèˆª
#define MACH_Nvt         0x26 //Nuvoton æ–°å”mcu
#define MACH_ESP32       0x27 //ä¹é‘«
#define MACH_AT32        0x28 //Artery é›…ç‰¹åŠ›

#define MACH_FM33        0x33 //FuDanMicro å¤æ—¦å¾®
#define MACH_SH3X        0x34 //Sinowealth ä¸­é¢–
#define MACH_STM32MP1    0x200 //
#define MACH_STM32WB     0x201 //

/**
 * Definition about BSP Board platform
 * ^^Legacy
*/
#define BSP_BD_ATK_MINI_F103RB     0x300  //Atk-F103miniV1.9
#define BSP_BD_ATK_MINI_F103VE     0x301  
#define BSP_BD_BST103              0x302
#define BSP_BD_ATK_F103_WARSHIP    0x330  //Atk-F103warship

#define BRD_ATK_APLO429            0x400
#define BRD_ATK_PDR475             0x401
#define BSP_BD_ATK_APLO_F747       0x700

/**
 * Definition about  version
*/
#define VER_10_3_1                 0x0a0301
#define VER_12_C                   0xCC
#define VER_13_C                   0xDC
#define VER_14                     0xE0
/*
#define HALLIB_VER_1_00_4          0x10004
#define HALLIB_VER_1_06_0          0x10004
#define HALLIB_VER_1_07_0          0x10700
#define HALLIB_VER_1_11_0          0x10b00
#define HALLIB_VER_1_13_0          0x10d00
#define HALLIB_VER_1_14_0          0x10e00
#define HALLIB_VER_1_15_0          0x10f00 
#define HALLIB_VER_1_16_0          0x11000 
#define HALLIB_VER_1_17_0          0x11100 
#define HALLIB_VER_1_18_3          0x11203 
#define HALLIB_VER_1_19_3          0x11203 
#define HALLIB_VER_1_24_0          0x11800
#define HALLIB_VER_1_25_1          0x11901
#define HALLIB_VER_1_25_2          0x11902
#define HALLIB_VER_1_26_1          0x11a01
*/
//STM32Cube_FW version 1
#define HALLIB_VER_1_00_4          0x1004
#define HALLIB_VER_1_06_0          0x1060
#define HALLIB_VER_1_06_1          0x1061
#define HALLIB_VER_1_07_0          0x1070
#define HALLIB_VER_1_08_0          0x1080
#define HALLIB_VER_1_08_3          0x1083
#define HALLIB_VER_1_11_0          0x10b0
#define HALLIB_VER_1_13_0          0x10d0
#define HALLIB_VER_1_14_0          0x10e0
#define HALLIB_VER_1_15_0          0x10f0 
#define HALLIB_VER_1_16_0          0x1100 
#define HALLIB_VER_1_17_0          0x1110 
#define HALLIB_VER_1_18_0          0x1120 
#define HALLIB_VER_1_18_3          0x1123 
#define HALLIB_VER_1_18_4          0x1124
#define HALLIB_VER_1_19_0          0x1130 
#define HALLIB_VER_1_19_3          0x1133 
#define HALLIB_VER_1_21_0          0x1150
#define HALLIB_VER_1_23_0          0x1170
#define HALLIB_VER_1_24_0          0x1180
#define HALLIB_VER_1_24_1          0x1181
#define HALLIB_VER_1_24_2          0x1182
#define HALLIB_VER_1_25_0          0x1190
#define HALLIB_VER_1_25_1          0x1191
#define HALLIB_VER_1_25_2          0x1192
#define HALLIB_VER_1_26_1          0x11a1
#define HALLIB_VER_1_26_2          0x11a2

//STM32Cube_FW version 2(Î´Ê¹ï¿½ï¿½)
//#define CBFWV_1_00_4          0x1004
//#define CBFWV_1_06_0          0x1064
//#define CBFWV_1_07_0          0x1070
//#define CBFWV_1_08_3          0x1083
//#define CBFWV_1_11_0          0x10b0
//#define CBFWV_1_13_0          0x10d0
//#define CBFWV_1_14_0          0x10e0
//#define CBFWV_1_15_0          0x10f0 
//#define CBFWV_1_16_0          0x1100 
//#define CBFWV_1_17_0          0x1110 
//#define CBFWV_1_18_0          0x1120 
//#define CBFWV_1_18_3          0x1123 
//#define CBFWV_1_19_3          0x1133 
//#define CBFWV_1_24_0          0x1180
//#define CBFWV_1_25_0          0x1190
//#define CBFWV_1_25_1          0x1191
//#define CBFWV_1_25_2          0x1192
//#define CBFWV_1_26_1          0x11a1
//#define CBFWV_1_26_2          0x11a2

//STM32Cube_FW version3(ï¿½ï¿½Ê¹ï¿½ï¿½)
typedef enum __cbfwv{
		CBFWV_1_00_4 = 0x1004,
		CBFWV_1_06_0 = 0x1060,
		CBFWV_1_06_1 = 0x1061,	
		CBFWV_1_07_0 = 0x1070,
		CBFWV_1_08_3 = 0x1083,
		CBFWV_1_11_0 = 0x10b0,
		CBFWV_1_11_1 = 0x10b1,	
		CBFWV_1_13_0 = 0x10d0,
		CBFWV_1_14_0 = 0x10e0,
		CBFWV_1_15_0 = 0x10f0,
		CBFWV_1_16_0 = 0x1100,
		CBFWV_1_17_0 = 0x1110, 
		CBFWV_1_18_0 = 0x1120, 
		CBFWV_1_18_3 = 0x1123, 
		CBFWV_1_19_3 = 0x1133, 
		CBFWV_1_24_0 = 0x1180,
		CBFWV_1_25_0 = 0x1190,
		CBFWV_1_25_1 = 0x1191,
		CBFWV_1_25_2 = 0x1192,
		CBFWV_1_26_1 = 0x11a1,
		CBFWV_1_26_2 = 0x11a2,	
}tdf_em_cbfwv;

/*############ 0 MCU  datasheet beginning line ###################*/
/*0.1 stm32L4xx****
 **0.1.1 ZI ram :
*/
#define STM32L4XX_SZ_ZIRAM   0x4000  // L4xx ZI datas Ô¤ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½0x4000 bytesï¿½Õ¼ï¿½


/*0.2 stm32F4xx****
 **0.2.1 ZI ram :
*/

/*------------------0 MCU  datasheet  ending line -----------------------*/


/*############ 1 Hard components beginning line ###################*/
/*1.1 uart com ****
 **1.1.1 ATK  token param for XCOM(´®¿Úµ÷ÊÔÖúÊÖ) :
*/
#define XcomPos_Rx1st      14    //The token bit position identifies that the debug usart com  received the 1st word of over
#define XcomPos_RxFsh      15    //The token bit position identifies that the debug usart com  received over
#define XcomTkn_Rx1st      (1 << XcomPos_Rx1st) //The token vlu identifies that the debug usart com  received the 1st word of over
#define XcomTkn_RxFsh      (1 << XcomPos_RxFsh) //The token vlu identifies that the debug usart com  received  over
#define XcomOvrW_1st        0x0d // DBCOM½ÓÊÕÍê³É±êÖ¾×Ö£¬Ê××Ö = 0x0d = '\r' , 
#define XcomOvrW_Fsh        0x0a // DBCOM½ÓÊÕÍê³É±êÖ¾×Ö£¬Ä©×Ö = 0x0a = '\n' ,
                                 // ¼´ÉÏÎ»»úXCOMÏò mcu->DBCOM·¢ËÍascii×Ö·û´®ÐÅÏ¢Ê±£¬ÐÅÏ¢Î²²¿Ä¬ÈÏ×Ô¶¯¼ÓÉÏ"\r\n"(usrÎÞÐèÊÖ¶¯Ìí¼Ó)µÄ
#define XcomCntMsk  			  0x3fff //orgn = 0x3ff  	 
#define XcomVlu_Fg_Rx1st    0x4000 
#define XcomVlu_Fg_RxFsh    0x8000
extern unsigned int  XcomToken ;
//typedef enum{}emXcomAtk_t;
/*
 **1.1.2 MCU and  bsp default dubug com param :
*/

#define BSP_DBCOM_DFT_PRG        (&DBCOM_para)

#define DBCOM_BAUD_DFT       115200   // Default baud rate of debug usart com 
#define DBCOM_RXMAX_DFT      256 	// DBCOM_PRP Ä¬ï¿½Ïµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½256bytesï¿½ï¿½ï¿½ï¿½ï¿½ï¿½

/*
 **1.1.3 ï¿½ï¿½ï¿½ï¿½Ä¬ï¿½ï¿½RS485ï¿½Ó¿Úºï¿½ModBus-rtu ï¿½ï¿½ï¿½ï¿½Ö¡Ä¬ï¿½Ï²ï¿½ï¿½ï¿½:
*/
//1.1.3.1 rs485Ë«ï¿½ï¿½ï¿½Õ·ï¿½ï¿½ï¿½ï¿½ï¿½Í¨ï¿½Å£ï¿½
#define CMPL_RS485d1_DFT          CMPL_UART2_RS485  // ï¿½ï¿½ï¿½ï¿½RS485--->defaut usart2
#define DEFPRM_RS485d1_BAUD       256000            // ï¿½ï¿½ï¿½ï¿½RS485ï¿½Ó¿ï¿½Ä¬ï¿½Ï²ï¿½ï¿½ï¿½->ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ = 256000bpsï¿½ï¿½ï¿½ï¿½ï¿½ï¿½9600 19200 115200 460800  
typedef enum _ptl_rs485{
		ovrw485_1st = XcomOvrW_1st,  //Ô¤ï¿½ï¿½Î´ï¿½Ã£ï¿½rs485ï¿½ï¿½ï¿½Õ½ï¿½ï¿½ï¿½ï¿½ï¿½Ö¾ï¿½ï¿½:ï¿½ï¿½Î»
		ovrw485_fsh = XcomOvrW_Fsh,  //Ô¤ï¿½ï¿½Î´ï¿½Ã£ï¿½rs485ï¿½ï¿½ï¿½Õ½ï¿½ï¿½ï¿½ï¿½ï¿½Ö¾ï¿½ï¿½:Ä©Î»
	  rs485ptl_rxlength   = 16,     //Ä¬ï¿½ï¿½Ê¹ï¿½ï¿½, rs485Ä¬ï¿½Ïµï¿½ï¿½Î½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ýµï¿½ï¿½ï¿½ï¿½ï¿½Ö½ï¿½ï¿½ï¿½ï¿½ï¿½Ô­code = 8
	  rs485def_dly        = 600,   //rs485Ä¬ï¿½Ï²ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ç¾ï¿½È·ï¿½ï¿½Ê±Ïµï¿½ï¿½
	  rs485def_tmo        = 0x100, //rs485Ä¬ï¿½Ï²ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê±ï¿½È´ï¿½Ïµï¿½ï¿½
} tdf_em_ptl_rs485;

//1.1.3.2 ï¿½ï¿½ï¿½ï¿½rs485ï¿½ï¿½modbus-rtu Í¨ï¿½Å£ï¿½Ä¬ï¿½ï¿½Ð­ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
#define DEFPRG_MDBRTU           BSP_BD_PPG_RS485  //ï¿½ê¶¨ï¿½ï¿½bspÄ¬ï¿½ï¿½modbus-rtuï¿½ï¿½ï¿½ï¿½ï¿½é£¬Ò»ï¿½ï¿½ï¿½ï¿½ï¿½rs485ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½MCU usart2 ï¿½Ë¿ï¿½

//1.1.3.3 modbusÍ¨ï¿½ï¿½(rs232/rs485/tcp Í¨ï¿½ï¿½)ï¿½ï¿½Ä¬ï¿½ï¿½Ã¶ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
typedef enum _glbv_mdb{
  	mdbdef_devid_reqr     = 0,      /* default device id of requesterï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½(Ò»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Õ¾ï¿½è±¸)ï¿½ï¿½Ê¼Ä¬ï¿½ï¿½idï¿½ï¿½ */ 
    mdbdef_devid_rspdr    = 1,      /* default device id of responderï¿½ï¿½Ó¦ï¿½ï¿½ï¿½ï¿½(Ò»ï¿½ï¿½ï¿½Ç±ï¿½ï¿½ï¿½ï¿½ï¿½Ä¿ï¿½ï¿½Ó½Úµï¿½ï¿½è±¸)ï¿½Ä³ï¿½Ê¼Ä¬ï¿½ï¿½idï¿½ï¿½  */ 
	  mdbdef_minlen_frm     = 3,      /* min length of frameï¿½ï¿½modbusï¿½ï¿½ï¿½ï¿½Ö¡Ä¬ï¿½ï¿½ï¿½ï¿½Ð¡ï¿½ï¿½ï¿½ï¿½(ï¿½ï¿½Î»ï¿½ï¿½bytes)
	                                     min Frame: Addr(id)| cmd | data-1byte  */
	  mdbdef_len_frm        = 16,     /* default length of frame, modbusï¿½ï¿½ï¿½ï¿½Ö¡Ä¬ï¿½Ï³ï¿½ï¿½ï¿½(ï¿½ï¿½Î»ï¿½ï¿½bytes)ï¿½ï¿½Ä¬ï¿½Ï³ï¿½Ê¼Öµï¿½ï¿½16ï¿½Ö½ï¿½ */ 
    mdbdef_maxlen_frm     = 68,     /* max length of frame, modbusï¿½ï¿½ï¿½ï¿½Ö¡Ä¬ï¿½ï¿½ï¿½ï¿½ó³¤¶ï¿½(ï¿½ï¿½Î»ï¿½ï¿½bytes)ï¿½ï¿½Ä¬ï¿½Ï³ï¿½Ê¼Öµï¿½ï¿½64ï¿½Ö½ï¿½ */ 
	  mdbdef_bcaddr         = 0xbc,	  /* Ä¬ï¿½Ï¹ã²¥ï¿½ï¿½Ö·  */  
	  mdb_idle_chr          = 17,      /* 10 * Idle interval between chars,ï¿½Ö·ï¿½Ö®ï¿½ï¿½Ä¿ï¿½ï¿½Ð¼ï¿½ï¿½(1.5ï¿½ï¿½ï¿½Ö·ï¿½)10ï¿½ï¿½Ïµï¿½ï¿½ï¿½ï¿½Êµï¿½Ê¼ï¿½ï¿½ï¿½ï¿½ï¿½Òªï¿½ï¿½10
	                                    ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ð¡ï¿½ï¿½ï¿½ï¿½ï¿½Ö£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½17 ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½15 */
	  mdb_idle_frm          = 37,     /* 10 * Idle interval between frames,Ö¡Ö®ï¿½ï¿½Ä¿ï¿½ï¿½Ð¼ï¿½ï¿½(3.5ï¿½ï¿½ï¿½Ö·ï¿½)10ï¿½ï¿½Ïµï¿½ï¿½ï¿½ï¿½Êµï¿½Ê¼ï¿½ï¿½ï¿½ï¿½ï¿½Òªï¿½ï¿½10 
	                                    ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ð¡ï¿½ï¿½ï¿½ï¿½ï¿½Ö£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½37 ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½35 */
} emMdbGlbDef_t;


/*1.2 GPIO  ****
 **1.2.1 Button pressing GPIO_Mode :
*/
#define BtnTrg_JpE   (unsigned char)0x00  //Jump Edge tragger
#define BtnTrg_VtL   (unsigned char)0x01  //Voltage Level tragger

/*1.3 Infra-red  ****
 **1.3.1 The params about ATK ifrd remote control board :
*/

#define AtkIfrd_Btn_Num    (unsigned char)21             // ï¿½ï¿½ï¿½ï¿½Ò£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
extern  unsigned char AtkIfrd_Tab_Vlu[AtkIfrd_Btn_Num] ;  // ï¿½ï¿½ï¿½ï¿½Ò£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Öµ
extern  unsigned char AtkIfrd_Tab_Str[AtkIfrd_Btn_Num][16] ;	//ï¿½ï¿½ï¿½ï¿½Ò£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ó¦ï¿½ï¿½ï¿½Ö·ï¿½

/*1.4 Memory def****
 *
*/
#define SZ_SEC_SDC            512    // the size of a sdcard section
#define BASE_ADDR_FMCND_F42X  0x80000000 // the base addr of mcu fmc bus for nand

/*1.5 LCD****
 * * 1.5.1 font param
 */
#define DEF_FT_CW     8    // default font char width
#define DEF_FT_CH     16   // default font char highth
/*
   1.5.2 LCDÔÚÀ©Õ¹sdramÉÏËùÕ¼µÄ×î´ó»º´æÇø´óÐ¡
     update:2021.5.26
*/
#define MaxCacheSz_LCD32b  0x3b0000 // >= 1200*800*4 = 0x3a9800 = 3840000
#define MaxCacheSz_LCD16b  0x1f4000 // >= 1200*800*2 = 0x1d4c00 = 1920000

#define LcdColorsNum_Atk      21 //ÑÕÉ«ÊýÁ¿
extern unsigned short  Color_Pre  ;       //ÉÏÒ»´ÎµÄÑÕÉ«
extern unsigned short  POINT_COLOR;		   //Ä¬ÈÏ»­±ÊÑÕÉ«
extern unsigned short  BACK_COLOR;		     //Ä¬ÈÏ±³¾°ÑÕÉ«
extern const int LcdColorTabAtk[LcdColorsNum_Atk ] ; //É«±í

typedef enum { 
	
	  BLACK = 0x0000,     BLUE = 0x001F,     GREEN = 0x07E0,       GBLUE = 0X07FF,    CYAN = 0x7FFF,      GRAY  = 0X8430,  BROWN = 0XBC40, 
	
	  BRED  = 0XF81F,     RED = 0xF800,      GRED = 0XFFE0,        MAGENTA = 0xF81F,  YELLOW = 0xFFE0,    BRRED = 0XFC07,  DARKBLUE = 0X01CF,
	                                                              
	  LIGHTBLUE = 0X7D7C, GRAYBLUE = 0X5458, LIGHTGREEN = 0X841F,  LGRAY = 0XC618,    LGRAYBLUE = 0XA651, LBBLUE = 0X2B12, WHITE = 0xFFFF, 

} emLcdColorAtk_t;  


/*1.6 Globale Variables****
 */
#define GLBVARn_DFT       16    //Ä¬ÈÏÈ«¾Ö±äÁ¿ÊýÁ¿(´æ´¢ÓÚMCU ÄÚ²¿sram)
extern unsigned int  Glb_Var32[GLBVARn_DFT] ; // in MCU internal SRAM,
extern void* glbf_mkvar(unsigned char num);     //¸øglbvar·ÖÅäMCUÄÚ²¿sramÇøÓò£¬update:2020.12.6
extern unsigned int umf_set_glbvar32(unsigned char , unsigned int );
extern unsigned int umf_setbit_glbvar32(unsigned char , unsigned char ,unsigned char );
extern unsigned char getbit_glbvar32(unsigned char no,unsigned char bit);

#define GLBVARn_EX_DFT    16    //Ä¬ÈÏÈ«¾Ö±äÁ¿ÊýÁ¿(´æ´¢ÓÚFmc-sdram1½Ó¿ÚµÄsdramÉÏ)
extern unsigned int* Glb_Var32Ex ;       // external extend RAM
extern unsigned int* glbf_mkvar32_ex(unsigned char num);//¸øglbver·ÖÅäÍâ²¿À©Õ¹sdramÇøÓò£¬update:2020.12.6 
extern unsigned int umf_set_glbvar32_ex( unsigned char no, unsigned int );
extern unsigned int umf_setbit_glbvar32_ex(unsigned char no,unsigned char  , unsigned char ); //Î»²Ù×÷
extern unsigned char getbit_glbvar32_ex(unsigned char no,unsigned char bit);

/*1.7 ADC
*@brief ADC1 
*@update 2021.8.30
***/
#define DEFPRM_ADC_VrefVlt  (float)3.3  //default parameter: The reference voltage value of ADC
#define PRM_STM32_ADC_DIGMSRNG    4096      //Digital measuring range  of MCU->STM`s ADC,stm MCUs ADCµÄÊý×ÖÁ¿³Ì(12bit-->2^12)
extern float Data_McuTemp;  //MCUÄÚ²¿ADCÍ¨µÀ²âÊÔ: tempsensor MCU-PN½áÎÂ¶È
extern float Data_Vbat ;    //MCUÄÚ²¿ADCÍ¨µÀ²âÊÔ: Vbat £¬BATµç³ØµçÑ¹
extern float Data_Vrefint ; //MCUÄÚ²¿ADCÍ¨µÀ²âÊÔ: Vrefint £¬²Î¿¼µçÑ¹ 
extern unsigned int   PrmV_ChOccu_Adc1 ;
extern unsigned short PrmV_ChOccu_Adc2 ;
extern unsigned short PrmV_ChOccu_Adc3 ;

/*1.8 Memory 
*@update 2021.9.20
***/
//1.8.1 global variables of the descriptor for memory-storage
typedef enum _glbv_memstg_dptr{
   	memstg_dptr_dsknum         = 3,        //default usbd msc disk number
	  memstg_dptr_nd_fmc         = 1 << 1,   //usbd msc disk of nand flash	on fmc
    memstg_dptr_sdc_sdio       = 1 << 2,   //usbd msc disk of SDcard on sdio
	  memstg_dptr_sdc_spi        = 1 << 3,   //usbd msc disk of SDcard on spi
	  memstg_dptr_norfls_spi     = 1 << 4,   //usbd msc disk of norflash(w25qx) on spi
	  memstg_dptr_norfls_qspi    = 1 << 5,   //usbd msc disk of norflash(w25qx) on qspi	
} tdf_em_glbv_memstg_dptr;

/*1.9 i2c
 *
 */
typedef enum{
	 i2c_hd_et6144  = 0x4,
	 i2c_hd_et6144a = 0x7,
	 i2c_hd_at24cx   = 0xa,
}emI2cDevHead_t;

typedef  enum {
	  apl_extio_beep = 0 , //·äÃùÆ÷¿ØÖÆÒý½Å  	P0
	  apl_extio_apit     , //AP3216CÖÐ¶ÏÒý½Å	P1
	  apl_extio_dcmipwr  , //DCMIµÄµçÔ´¿ØÖÆÒý½Å	P2
		apl_extio_usbpwr  ,  //USBµçÔ´¿ØÖÆÒý½Å	P3
		apl_extio_ext ,      //À©Õ¹IO,×Ô¶¨ÒåÊ¹ÓÃ 	P4
		apl_extio_mpuit ,    //MPU9250ÖÐ¶ÏÒý½Å	P5
		apl_extio_rs485re ,  //RS485_REÒý½Å		P6
		apl_extio_ethrst ,   //ÒÔÌ«Íø¸´Î»Òý½Å		P7
}emAtkPfc8574Extio_t ;

/*^^^^^^^^^^^^^^^1 Hard components ending line ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*##################2 Middev tools params ################*/
/*2.1 FatFs
*/
#define SZ_FFS_DIK             512     // the size of fatfs disks
#define BSP_DFTPRM_FFS_FONT    936     // Default font is Chinese of fatfs
#define DEFPRM_FFS_SecPerBlk   8     	 //Ã¿ï¿½ï¿½BLOCKï¿½ï¿½8ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½	
/*^^^^^^^^^^^^^^^2 Meddev tools params ending line ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*################## Global api functions and general vars################*/

extern void umf_setled(unsigned char clr,unsigned char sta);
extern void umf_vluled(void(*ledset)(unsigned char),unsigned char sta);
//extern unsigned int umf_set_glbvar32_ex(  unsigned  char no,  unsigned int val); //update:2020.12.6 

extern void glbf_mcupace(void); //update:2020.12.6 
extern void glbf_mcupaceV2(unsigned short tm); //update:2021.6.24 

extern unsigned char  ErrCode_8bit ;

/**\brief ·Ç¾«×¼ÑÓÊ±ÏµÁÐ imprecise delay*******
 ÑéÖ¤ºÏ¸ñ,same in RTOS and bare
 ÓÃLEDÊµ²â·­×ªËÙ¶È(stm32f429-180Mhz/FreeRTOS v10.31.0)Ô¼Îª 18.75Mbps
 ¾ÙÀýËµÃ÷(stm32f429-180Mhz bare or FreeRTOS v10.31.0)£º 
   1 Èç¹ûÒªÊµÏÖÒ»¸ö1msµÄ·Ç¾«È·ÑÓÊ±£¬ÄÇÃ´ nCount µÄÊýÖµÔ¼Îª 18750
	 2 Èç¹ûÒªÊµÏÖÒ»¸ö1usµÄ·Ç¾«È·ÑÓÊ±£¬ÄÇÃ´ nCount µÄÊýÖµÔ¼Îª 18~20
***************/
extern void ulf_impdly_us(volatile unsigned int  nCount);
extern void ulf_impdly_ms(volatile unsigned int 	nCount);
extern void ulf_impdly_s(volatile unsigned short nCount);
extern void ulf_impdly_free(double nCount);

/**********************************************************************************
 * @name: num_to_str
 * @brief: ½«´«ÈëµÄÊý×Ö×ª»¯Îª×Ö·û´®
 * @param : srcnum £ºÐèÒª×ª»¯Êý×Ö cnt:×ª»¯Êý×ÖµÄÎ»Êý
            deststr,
 * @rev: ×ª»¯ºÃµÄ×Ö·û´®
 * @note :   
       -1-,from paidaxintaotao
***********************************************************************************/
void num_to_str(unsigned char srcnum, unsigned char *deststr);


#endif 
 /*--EndLine:Full File---------------------------------------------------------------------------------------------End All---*/
