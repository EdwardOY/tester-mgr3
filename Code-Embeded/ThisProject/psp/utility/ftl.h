#ifndef __FTL_H
#define __FTL_H
#include "string.h"
#include "mcu_sys_head.h"
#include MCU_SYS
#include MCU_URT
#include MCU_NAD
#include PJT_HEAD_MLC	 

//********************************************************************************
//升级说明
//V1.1 20160124
//修改ftl_blk_cpywt和ftl_sec_wt函数,提高非0XFF时的写入速度.  
//V1.2 20160520
//1,修改ftl_sec_rd,增加ECC出错判断,检测坏块处理,并增加多块连读,提高速度
//2,新增ftl_blk_cpr和ftl_badblk_srch函数,用于搜寻坏块
//3,修改ftl_format坏块检测方式,增加FTL_USE_BAD_BLOCK_SEARCH宏
//V1.3 20160530
//修改当1bit ECC错误出现时，读取2次，来确认1bit 错误，以防错误的修改数据
////////////////////////////////////////////////////////////////////////////////// 	

//坏块搜索控制
//如果设置为1,将在ftl_format的时候,搜寻坏块,耗时久(512M,3分钟以上),且会导致RGB屏乱闪
#define FTL_USE_BAD_BLOCK_SEARCH		0		//定义是否使用坏块搜索



uint8_t init_ftl(void); 
void ftl_badblk_mark(uint32_t blocknum);
uint8_t ftl_badblk_chk(uint32_t blocknum); 
uint8_t ftl_unused_badblk_mark(uint32_t blocknum);
uint32_t ftl_unusedblk_fd(uint32_t sblock,uint8_t flag);
uint32_t ftl_unused_sameplane_fd(uint32_t sblock);
uint8_t ftl_blk_cpywt(uint32_t Source_PageNum,uint16_t ColNum,uint8_t *pBuffer,uint32_t NumByteToWrite);
uint16_t ftl_lbnt2pbn(uint32_t LBNNum); 
uint8_t ftl_sec_wt(uint8_t *pBuffer,uint32_t SectorNo,uint16_t SectorSize,uint32_t SectorCount);
uint8_t ftl_sec_rd(uint8_t *pBuffer,uint32_t SectorNo,uint16_t SectorSize,uint32_t SectorCount);
uint8_t ftl_lut_create(uint8_t mode);
uint8_t ftl_blk_cpr(uint32_t blockx,uint32_t cmpval);
uint32_t ftl_badblk_srch(void);
uint8_t ftl_format(void); 
#endif

