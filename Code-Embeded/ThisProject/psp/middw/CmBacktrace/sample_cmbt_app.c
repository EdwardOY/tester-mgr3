/***************************************************************************
 * @brief: sample_cnbt_app.c
 *         copied from CmBacktrace\demos\non_os\mcu\fault_test.c
 *
 *  Created on: 2026/4/29
 *      Author: Armink
 ***************************************************************************/

#include <stdio.h>
#include "ThisProj_Glb.h"

#if CMPL_THISPROJ == CAMPL_RAW

#elif CMPL_THISPROJ == CMPL_EDWOY

#endif //<#elif CMPL_THISPROJ == CMPL_EDWOY-->

/*****************************************
 * @brief  fault handler test :  unalign
 *         非对齐报错
 *         verified
 * @param  void
 * @retval void
 * @note:
 *    SCB->CCR`bit3 = 1,enable unalign;  = 0,disable  unalign
 * @date:2026.4.29
 *****************************************/
void fault_test_by_unalign(void) {
    volatile int * SCB_CCR = (volatile int *) 0xE000ED14; // SCB->CCR

    volatile int * p;
    volatile int value;

    *SCB_CCR |= (1 << 3); /* bit3: UNALIGN_TRP. */

    p = (int *) 0x00;
    value = *p;
    printf("addr:0x%02X value:0x%08X\r\n", (int) p, value);

    p = (int *) 0x04;
    value = *p;
    printf("addr:0x%02X value:0x%08X\r\n", (int) p, value);

    p = (int *) 0x03;
    value = *p;
    printf("addr:0x%02X value:0x%08X\r\n", (int) p, value);
}

/***********************************************************
 * @brief  fault handler test : 
 *         除零异常，报错
 *         verified
 * @param  void
 * @retval void
 * @note:
 *    SCB->CCR`bit4 = 1,enable DIV_0_TRP.; = 0,disable DIV_0_TRP.
 * @date:2026.4.29
 ***********************************************************/
void fault_test_by_div0(void) {
    volatile int * SCB_CCR = (volatile int *) 0xE000ED14; // SCB->CCR
    int x, y, z;

    *SCB_CCR |= (1 << 4); /* bit4: DIV_0_TRP. */

    x = 10;
    y = 0;
    z = x / y;
    printf("z:%d\n", z);
}


/*************************************
 * @brief  fault handler test : 
 *          1. unalign
 * @param  void
 * @retval void
 * @note:
 *    SCB->CCR`bit3 = 1,enable unalign;  = 0,disable  unalign
 * @date:
 * ****************************
void fault_test_by_unalign(void) {
    volatile int * p;
    volatile int value;

    SCB->CCR |= (1 << 3); // bit3: enable UNALIGN_TRP.

    p = (int *) 0x00;
    value = *p;
    printf("addr:0x%02X value:0x%08X\r\n", (int) p, value);

    p = (int *) 0x04;
    value = *p;
    printf("addr:0x%02X value:0x%08X\r\n", (int) p, value);

    p = (int *) 0x03;
    value = *p;
    printf("addr:0x%02X value:0x%08X\r\n", (int) p, value);
}

 *****************************************/

/***********************************************************
 * @brief  fault handler test : 
 *         除零异常，报错
 * @param  void
 * @retval void
 * @note:
 *    SCB->CCR`bit4 = 1,enable DIV_0_TRP.; = 0,disable DIV_0_TRP.
 * @date:
 * ********************
void fault_test_by_div0(void) {

    int x, y, z;

    SCB->CCR |= (1 << 4); // bit4: DIV_0_TRP. 

    x = 10;
    y = 0;
    z = x / y;
    printf("z:%d\n", z);
}
 ***********************************************************/

