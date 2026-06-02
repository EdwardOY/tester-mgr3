/*
 * This file is part of the CmBacktrace Library.
 *
 * Copyright (c) 2016, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: It is an head file for this library. You can see all be called functions.
 * Created on: 2016-12-15
 */

#ifndef _CORTEXM_BACKTRACE_H_
#define _CORTEXM_BACKTRACE_H_

#include "ThisProj_Conf.h"
#include "convert_def.h"
#if CMPL_THISPROJ == CMPL_RAW
#include <cmb_def.h>
#elif CMPL_THISPROJ == CMPL_EDWOY
#include UTY_DEF_HEAD      //  "./psp/utility/utility_def.h"

//edwoy260429
typedef enum {
    PRINT_MAIN_STACK_CFG_ERROR,
    PRINT_FIRMWARE_INFO,
    PRINT_ASSERT_ON_THREAD,
    PRINT_ASSERT_ON_HANDLER,
    PRINT_THREAD_STACK_INFO,
    PRINT_MAIN_STACK_INFO,
    PRINT_THREAD_STACK_OVERFLOW,
    PRINT_MAIN_STACK_OVERFLOW,
    PRINT_CALL_STACK_INFO,
    PRINT_CALL_STACK_ERR,
    PRINT_FAULT_ON_THREAD,
    PRINT_FAULT_ON_HANDLER,
    PRINT_REGS_TITLE,
    PRINT_HFSR_VECTBL,
    PRINT_MFSR_IACCVIOL,
    PRINT_MFSR_DACCVIOL,
    PRINT_MFSR_MUNSTKERR,
    PRINT_MFSR_MSTKERR,
    PRINT_MFSR_MLSPERR,
    PRINT_BFSR_IBUSERR,
    PRINT_BFSR_PRECISERR,
    PRINT_BFSR_IMPREISERR,
    PRINT_BFSR_UNSTKERR,
    PRINT_BFSR_STKERR,
    PRINT_BFSR_LSPERR,
    PRINT_UFSR_UNDEFINSTR,
    PRINT_UFSR_INVSTATE,
    PRINT_UFSR_INVPC,
    PRINT_UFSR_NOCP,
#if (CMB_CPU_PLATFORM_TYPE == CMB_CPU_ARM_CORTEX_M33)
    PRINT_UFSR_STKOF,
#endif
    PRINT_UFSR_UNALIGNED,
    PRINT_UFSR_DIVBYZERO0,
    PRINT_DFSR_HALTED,
    PRINT_DFSR_BKPT,
    PRINT_DFSR_DWTTRAP,
    PRINT_DFSR_VCATCH,
    PRINT_DFSR_EXTERNAL,
    PRINT_MMAR,
    PRINT_BFAR,
}emCmbtPrintf_t;

#endif //<#if CMPL_THISPROJ == CMPL_RAW --#else--->



#ifdef __cplusplus
extern "C" {
#endif

void cm_backtrace_init(const char *firmware_name, const char *hardware_ver, const char *software_ver);
void cm_backtrace_firmware_info(void);
size_t cm_backtrace_call_stack(uint32_t *buffer, size_t size, uint32_t sp);
void cm_backtrace_assert(uint32_t sp);
void cm_backtrace_fault(uint32_t fault_handler_lr, uint32_t fault_handler_sp);

#ifdef __cplusplus
}
#endif

#endif /* _CORTEXM_BACKTRACE_H_ */
