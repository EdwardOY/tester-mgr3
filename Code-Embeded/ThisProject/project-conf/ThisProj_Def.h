/**
 ****************************************************************************************************
 * @file        ThisProj_Def.h
                The program is copied form  E:\MCU-Exps\prjs-gd32\code1-1-epho407vet-base-ok							                           
 * @platform    ATK Apollo STM32F429IGTB
                https://item.taobao.com/item.htm?spm=a1z09.2.0.0.71ab2e8dBuaOH4&id=678302947208&_u=82v72r364b70 
 * @brief       ÅÜÂíµÆ¡¢dbcom
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
      -2-,verified items
			  2.1 ÅÜÂíµÆ(PB4),toggle
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
        -1- ,SYS_SUPPORT_OS is redefined ,so paced it into ThisProj_Glb.h from sys.h
 */
 
#ifndef _THISPROJ_DEF_H_
#define _THISPROJ_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif
////S>==Processor==========================================================================================
///S>==1,ARM_Cortex================================================================================
#define ARM_CORTEX_M0     0x1000U
#define ARM_CORTEX_M3     0x1003U
#define ARM_CORTEX_M4     0x1004U
#define ARM_CORTEX_M7     0x1007U
#define ARM_CORTEX_M23    0x1015U
#define ARM_CORTEX_M33    0x1021U
#define ARM_CORTEX_M33P   0x1022U
#define ARM_CORTEX_M55    0x1037U
#define ARM_CORTEX_M85    0x1055U

///E<==1,ARM_Cortex================================================================================

///S>==2,RISC_V====================================================================================


///E<==2,RISC_V====================================================================================

///S>==STM=========================================================================================
#define G_PCR_MACH_STM32_F429IG      0x00010000U
#define G_PCR_MACH_STM32_L496VE      0x00020000U
///E<==STM=========================================================================================

////E<==Processor==========================================================================================

//s>--2 Board-------------------------------------------------------------------------------------------
#define  G_ATK_MINI103_V1_9      0x03  //GD32F407V-Photo

#define  G_ATK_APL429IG_V1       0x04
#define  G_ATK_DMF407IG          0x05  //ATK-DMF407IGT6
#define  PhotoGD32F407V          0x06  //GD32F407V-Photo
#define  G_ATK_PDR475VE          0x07  //pandora L475vet6
#define  G_ATK_PDR496VE          0x08  //pandora L475vet6

//#define  THIS_BOARD   G_ATK_APL429IG_V1  //MDK->Options->C/C++->Define
#define G_USE_3RD_PACK_ATK   
//e<--2 Board-----------------------------------------------------------------------------------End-----

//s>--GPIO Sample use-----------------------------------------------------------------------------------
#define  G_USE_SAMP_GPIO_EDW   0U  //invalid
#define  G_USE_SAMP_GPIO_AFL   1U  //valid, use sample_keys_afl
//e<--GPIO Sample use----------------------------------------------------------------------------End----


typedef char (*pFunc_CtmBtn_t)(void* pArg);  //function pointer type definition

#ifdef __cplusplus
}
#endif

#endif // _THISPROJ_DEF_H_
////----EndLine:Full File-----------------------------------------------------------------------------All-End----
