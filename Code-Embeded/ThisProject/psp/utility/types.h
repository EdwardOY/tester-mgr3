/****
* @Filename : types.h
* @Purpose : For data types
* @Author : EDW.OY
* @version v2.5
*****************************************************************************			
	@Update:
	  v2.5,verfied and valid,2022.12.14 
		    Delate the definitions of s8/s16/s32, because of conflict with rtos
				Use s8_t~s32_t to replace s8~s32
	  v2.4,verfied and valid ,2022.11.27
		   [+] ch32 `s family mcus
	  v2.3,verfied,2022.11.10
		   [+] mm32 `s family mcus
    v2.2,verfied,2022.8.5  
       [+] __IO,__I, __O  		
	  v2.1,verfied and valid,2022.7.25,verfied,[+] volatile const
	  v2.0,verfied and valid ,2020.12.14 
*/	
#ifndef _TYPES_H_
#define _TYPES_H_

/* 1 signed types
 * 有符号数据类型
 */
//国民N32系列 mcu.h(exp n32g031.h)里已经定义了 sx数据类型
#if !defined _MCU_N32_ && !defined _MCU_CH32_
//Delate the definitions of s8/s16/s32, because of conflict with rtos
//#ifndef s8
//#define s8    char 
//#endif

//#ifndef s16
//#define s16   short 
//#endif

//#ifndef s32
//#define s32   int 
//#endif
#endif //<#if  !defined _MCU_N32_ && !defined _MCU_CH32_>


#ifdef _MCU_MM32_
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
#define     __I     volatile                        ///< Defines 'read only' permissions
#else
#define     __I     volatile const                  ///< Defines 'read only' permissions
#endif
#define     __O     volatile                        ///< Defines 'write only' permissions
#define     __IO    volatile                        ///< Defines 'read / write' permissions

//typedef long long    s64;                           ///< used for signed 64bit
//typedef signed int   s32;
//typedef signed short s16;
//typedef signed char  s8;

typedef signed int  const  sc32;                    ///< Read Only
typedef signed short const sc16;                    ///< Read Only
typedef signed char  const sc8;                     ///< Read Only

typedef volatile signed int   vs32;
typedef volatile signed short vs16;
typedef volatile signed char  vs8;

typedef volatile signed int  const  vsc32;          ///< Read Only
typedef volatile signed short const vsc16;          ///< Read Only
typedef volatile signed char  const vsc8;           ///< Read Only

typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;

typedef unsigned int  const  uc32;                  ///< Read Only
typedef unsigned short const uc16;                  ///< Read Only
typedef unsigned char  const uc8;                   ///< Read Only

typedef volatile unsigned int   vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned int  const  vuc32;        ///< Read Only
typedef volatile unsigned short const vuc16;        ///< Read Only
typedef volatile unsigned char  const vuc8;         ///< Read Only
typedef bool    BOOL;
#ifndef NULL
#define NULL ((void *)0)
#endif
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;


#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

#define U8_MAX     ((uint8_t)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((uint16_t)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((uint32_t)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483648uL)

#define MAX(a,b)((a)>(b)?(a):(b))
#define MIN(a,b)((a)<(b)?(a):(b))

#define SET_BIT(reg, bit)     ((reg) |= (bit))
#define CLEAR_BIT(reg, bit)   ((reg) &= ~(bit))
#define READ_BIT(reg, bit)    ((reg) & (bit))
#define CLEAR_REG(reg)        ((reg) = (0x0))
#define WRITE_REG(reg, value)   ((reg) = (value))
#define READ_REG(reg)         ((reg))
#define MODIFY_REG(reg, CLEARMASK, SETMASK)  WRITE_REG((reg), (((READ_REG(reg)) & (~(CLEARMASK))) | (SETMASK)))
#define POSITION_VAL(value)     (__CLZ(__RBIT(value)))

#define LEFT_SHIFT_BIT(x)   (1 << x)

#endif //<end,#ifdef _MCU_MM32_>

typedef char           s8_t;  
typedef short          s16_t;  
typedef int            s32_t;  
typedef long long      s64_t; 
#define  s64            s64_t
	
#define sv8   volatile char
#define sv16  volatile short
#define sv32  volatile int
#define sv64  volatile long long

typedef const char        sc8_t;  
typedef const short       sc16_t;  
typedef const int         sc32_t;  
typedef const long long   sc64_t; 

typedef volatile const char       svc8_t;  
typedef volatile const short      svc16_t;  
typedef volatile const int        svc32_t;  
typedef volatile const long long  svc64_t; 

/**\2 unsigned types
 * 无符号数据类型
 * ux 已经在 core_cmx.h的ITM_Type里面定义了，所以此处定义为ux_t
 */
typedef unsigned char              u8_t;  
typedef unsigned short             u16_t;  
typedef unsigned int               u32_t;  
typedef unsigned long long         u64_t; 

typedef volatile unsigned char      uv8_t   ;
typedef volatile unsigned short     uv16_t ;
typedef volatile unsigned long      uv32_t;  
typedef volatile unsigned long long uv64_t  ;

typedef const unsigned char        uc8_t;  
typedef const unsigned short       uc16_t;  
typedef const unsigned int         uc32_t;  
typedef const unsigned long long   uc64_t; 

typedef volatile const unsigned char      uvc8_t  ;
typedef volatile const unsigned short     uvc16_t ;
typedef volatile const unsigned long      uvc32_t ;  
typedef volatile const unsigned long long uvc64_t ;

/* 3 float types
 * 浮点数数据类型
 */
typedef float                 f32_t;
typedef double                f64_t;
typedef long double           f128_t;
typedef const float           fc32_t;  
typedef const double          fc64_t;  
typedef const long double     fc128_t;  
typedef volatile float        fv32_t;
typedef volatile double       fv64_t;
typedef volatile long double  fv128_t;

typedef volatile const float        fvc32_t;
typedef volatile const double       fvc64_t;
typedef volatile const long double  fvc128_t;


/* 4 Bool
 * 布尔数据类型
 * 或者 #inlude "stdbool.h" ---> bool {false,true}
 */
#define   eDisable  0
#define   eEnable   1
typedef enum{Low = 0,High = !Low} Level;
typedef enum{False = 0,True = !False} Bool;
typedef enum{sDisable  = 0,  sEnable = !sDisable} SWH; 

#ifndef __I
#define __I  volatile const
#endif

#ifndef __O
#define __O  volatile
#endif


#ifndef __IO
#define __IO  volatile
#endif

#endif 
/*--EndLine:Full File---------------------------------------------------------------------------------------------End All---*/

/*
typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vuc32;  
typedef __I int16_t vuc16; 
typedef __I int8_t vuc8;   



typedef __IO uint32_t  vu32;
typedef __IO uint16_t uv16_t;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  
typedef __I uint16_t vuc16; 
typedef __I uint8_t vuc8;  
*/



