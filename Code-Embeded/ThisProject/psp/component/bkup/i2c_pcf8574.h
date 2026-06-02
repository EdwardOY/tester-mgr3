/**
  ******************************************************************************
  * @file   : bsp_pcf8574.h
  * @brief  : The headfile for i2c io extension apis for pcf8574 
  * @Author : EDW.OY
	* @Version: V1.3
  * @State  ：Verified well
  * @Copyright(C) 	
  ******************************************************************************
	* @details:
	    1 pcf
  ******************************************************************************	
	* @attention :
		 1 Devellop platform : 
	*    1.1 Apollo STM32F429IGTB pcf8574 is on bottom board   
	         The i2c io extension on bottom board  is mounted on i2c2 bus 
			 1.2 link MCU io
			      --------------------------------
            pcf8547 | INT  | SCL  | SDA |		
				    --------|------|------|-----|----						
					  Apl429  | PB12 | PH4  | PH5 |
			      --------------------------------			
		   1.2 The devellop platform : Apollo STM32F746
	   2 
**************************************************************************
* @version
    V1.3 use V1.4 bspapp_gpio_i2c drv
			   Ver2.0 Apis use emI2cSort_t emPcf8574Sort_t,in pjt_glb_head.h
    V1.2 加入V2版 Apis  2021.6.24 完成并验证成功	     
    V1.0  2018.4.13
  **************************************************************************				 
*/
#ifndef __PCF8574_H
#define __PCF8574_H
#include "ThisProj_Glb.h"
#include SYS_HEAD
#include I2C_HEAD


/*+++++++++Ver2 Apis ++++++++++*/
extern u8_t pcf8574_init(emPcf8574Sort_t);
extern u8_t pcf8574_1byte_rx(emPcf8574Sort_t);
extern void pcf8574_1byte_tx(emPcf8574Sort_t,u8_t dat_wt);

extern u8_t pcf8574_io_rx(emPcf8574Sort_t,u32_t);
extern void pcf8574_io_tx(emPcf8574Sort_t,u32_t ,u8_t);
extern u8_t bsp_pcf8574_btm_init(void);
extern void bsp_pcf8574_all_init(void);
extern void bsp_pcf8574_btm_iotx(u32_t extio,u8_t vlt);
extern u8_t bsp_pcf8574_btm_iorx(u32_t extio);
/*-------endline V2 Apis---------*/
#endif

