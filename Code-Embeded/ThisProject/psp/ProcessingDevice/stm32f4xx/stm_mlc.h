/* ****
* @Filename : bsp_malloc_atk_pdra.h
* @brief : Mem-map malloc for altk pandora board 
* @Mcu : cortex-M4  stm32l475vet6
* @Author : EDW.OY
* @version V2.0
* @Date : 2019.5.17
* @Copyright(C)  CLOU (CN) LTD.  2014-2024  All rights vlu_reverved	
*****************************************************************************
* @attention : 
*   1 Develop platform : ALTK Pandora STM32L475VET6(LQFP100)
     1.0 Don`t allocated all storage space of the sramx
				Usually less than 70% of the total capacity.
		 
     1.1 The inside-embed sram
       1.1.1 total cap :128KB(sram1+sram2)
			 1.1.2 sram1 96KB,area: 0x2000 0000 ~ 0x2001 8000
			 1.1.3 sram2 32KB,area: 0x1000 0000 ~ 0x1000 8000		
		 1.2 .  
		 1.3
	  2 Platform2:ALTK Apollo STM32F429IGTB(LQFP176)
     2.1 The inside-embed sram
       2.1.1 total cap :256KB+32MB+64KB (sRamIn/RAM1 + sFmcSdm/RAM2 + CCM/RAM3)
			 2.1.2 sRamIn 256KB,取地址范围: 0x2000 0000 ~ 0x2001 8000
			 2.1.3 sFmcSdm 32MB, 取址范围:  0XC01F 4000 ~ 0xC1FF FFFF;前2MB给LTDC用了(1280*800*2)
       2.1.4 sRamCcm 64KB,取址范围:	0x1000 0000 ~	0x1000efff 
		 2.2  
* 
*/ 

#ifndef _STM_MALLOC_H_
#define _STM_MALLOC_H_
#include "ThisProj_Glb.h"
#include SYS_HEAD
#include BSP_RES_HEAD 

#ifndef NULL
#define NULL   0
#endif

		 
typedef enum {
    err_mlc_none     = 0,
	  err_mlc_uninit   = 4,
	  err_mlc_nospace  = 5,
	  err_mlc_overrang = 6,
	  err_mlc_dupli    = 7,
}	em_mlc_t;



//内存管理控制器
struct _dev_mem_manager
{
	emRamSort_t   mem_st; 
	void (*init)(u8_t);					//初始化
	u16_t (*perused)(u8_t);		  	    	//内存使用率
	u8_t 	*membase[RamBks_Num];				//内存池 管理RamBks_Num个区域的内存
	u32_t *memmap[RamBks_Num]; 				//内存管理状态表
	u8_t  memrdy[RamBks_Num]; 				//内存管理是否就绪
};

extern struct _dev_mem_manager dev_malloc;	 //在mallco.c里面定义


void _mlc_init(u8_t memx);				//内存管理初始化函数(外/内部调用)
//u32_t _mmdev_malloc(u8_t memx,u32_t size);	//内存分配(内部调用)
//u8_t _mmdev_free(u8_t memx,u32_t offset);		//内存释放(内部调用)

////////////////////////////////////////////////////////////////////////////////
//用户调用函数
em_mlc_t api_sfree(void *ptr)  ;   // ptr 无法指向 0
em_mlc_t api_mem_free(void* psrc)  ;
void *api_malloc(u8_t memx,u32_t size);			//内存分配(外部调用)
void *api_realloc(u8_t memx,void *ptr,u32_t size);//重新分配内存(外部调用)
void api_free(u8_t memx,void *ptr);  			//内存释放(外部调用)
void api_memset(void *s,u8_t c,u32_t count);	//设置内存
void api_memcpy(void *des,void *src,u32_t n);//复制内存     

u16_t  api_mem_perused(u8_t memx) ;			//获得内存使用率(外/内部调用) 
em_mlc_t dupli_mlc_check(void * psrc)  ; //检查同一个指针是否重复分配

/*+++++++++V2: MLC drv++++++++++++++*/

//内存管理控制器
typedef struct {
	emRamSort_t   mem_st; 
	void (*init)(u8_t);					//初始化
	u16_t (*perused)(u8_t);		  	    	//内存使用率
	u8_t 	*membase;				//内存池 管理RamBks_Num个区域的内存
	u32_t *memmap; 				//内存管理状态表
	u8_t  memrdy; 				//内存管理是否就绪
}mlc_para_t;

/*---------End:V2-MLC drv-----------*/

#endif /*----EndLine:Full File-----*/


