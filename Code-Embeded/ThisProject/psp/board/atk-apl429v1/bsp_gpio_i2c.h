/**
  ******************************************************************************
  * @file   : bspapp_gpio_i2c.h
	            代称：BSP_HEAD_I2C in bsp_glbtree_xxx,h 
  * @brief  : The head file for gpio i2c module 
  * @Author : EDW.OY
	* @CurVer ：V1.4(2022.4.15)	
  * @State  ：Verified well
  * @Copyright(C) 	
  ******************************************************************************
	* @update
    V1.4 2022.4.15
		    [+]  Api-V2 
    V1.3,2021.9.1(√)
		   2 handle_i2c加入项目： 
           gpio_scl --> GpioPin-SclOut
           gpio_sda --> GpioPin-Sda	
		   1 tdf_ppgapp_gpio_dev 加入项目： 
		       dev_slvaddrtl; 
	         dev_addr = dev_slvaddrhd << 4 | dev_slvaddrtl
    V1.2 加入tdapp_gpio_gpio_dev 2021.6.24 完成并验证成功	     
    V1.0  2018.4.13
  **************************************************************************		
* @attention :
    1 devellop platform : 
		  1.1 Apollo STM32F429IGTB
			1.2 AtkF103mini v1.9			
*   2 因意法和NXP关于I2c协议上有专利纠纷问题 STMxx MCUs的硬件i2c port存在诸多问题，比如必须低速运行(<=70kbps)，中断致使i2c bus出故障等, 
      推荐使用GPIO模拟i2c协议的方式去使用
*   3 Pay attention to the multiplexing of pins,  
          such as the common pins of SPI1.1 and iic1.2: PA4 and PA5.
		4 IOMAP		
						 	 |MCUHdport |    SCL    |     SDA     |    SMBA   |  
      ---------|----------|-----------|-------------|-----------|----------												 
							 |   I2C1	  | PB6/P2-14 |  PB7/P2-15  | PB5/P2-13 | MCU-HardPort,P2-xx: P2 connector`s No.xx pin 
			Apl429	 |   I2C2	  | PH4/P2-4  |	 PH5/P2-5   | PH6/P3-18 | MCU-HardPort,P11-x: P11 connector PINx 
			lqfp176	 | gpioI2C2 | PH4/P2-4	|  PH5/P2-5 	| PH6/P3-18 | GPIO模拟i2c PCF8745Btm & At24cxx Btm :  PCF8745/At24c02 On board without SMBA
			  			 |   I2C3   | PH7/P3-14 |  PH8/P2-29  | PH9/P3-19 | MCU-HardPort,connector P2&P3
      ---------|----------|-----------|-------------|-----------|—————————————
							 |   I2C1	  | PB6/P1-11 |  PB7/P1-12  | PB5/P2-10 | MCU-HardPort,   
			F103Mini |	 I2C2	  |           |             |       
			V1.9		 | gpioI2C	| PC12/		  |  PC11/	    |     NC    | At24c02 On board without SMBA
			lqfp64	 |   
      ---------|———————————————————————————————————————
**************************************************************************
*/

#ifndef _BSP_GPIO_I2C_H_
#define _BSP_GPIO_I2C_H_

#include "ThisProj_Glb.h"
#include SYS_HEAD
#include GPIO_HEAD

#define  CMPL_ORGN_I2C  0  // 1-->compile by alientek ; 0-->compile by edwoy
#define  UET_I2C       (u8_t)250  //UC Error Time
#define  SdaDir_In     (u8_t)0
#define  SdaDir_Out    (u8_t)1
	

void sda_mode_set(GPIO_TypeDef*,u16_t,u8_t );


//## Api-V2 ##+++++
typedef struct _handle_i2c{
		u16_t            SdaPin;
		u16_t            tmo ;   //超时等待时间	
	  sttPrp_Gpio_t       io_scl;
	  sttPrp_Gpio_t       io_sda;	
}i2c_para_t;

typedef struct _i2c_ppg{
	       u32_t       dev_typ ;
	  const u8_t       dev_slvaddrhd;  //device`s slave address head
	  const u8_t       dev_slvaddrtl;  //device`s slave address tail(A3/A2/A1 << 1)
	        u8_t       dev_addr;       //i2c设备的最终地址
	  i2c_para_t *     i2c_para_p;
}i2cdev_ppg_t;

void _i2c_init(i2c_para_t*);                //初始化IIC的IO口				
void _i2c_start(i2c_para_t*);			        	//发送IIC开始信号
void _i2c_stop(i2c_para_t*);	  			      //发送IIC停止信号
void _i2c_1byte_tx(i2c_para_t*,u8_t txd);			        //IIC发送一个字节
u8_t _i2c_1byte_rx(i2c_para_t*,u8_t ack);    //IIC读取一个字节
u8_t _i2c_ack_wait(i2c_para_t*); 				      //IIC等待ACK信号
void _i2c_ack(i2c_para_t*);					        //IIC发送ACK信号
void _i2c_nonack(i2c_para_t*);			      	//IIC不发送ACK信号
void _i2c_devaddr_gen(i2cdev_ppg_t* dev_i2c);
//## End: Api-V2 ##-----



#endif //<end:#ifndef _BSP_GPIO_I2C_H_>

/*-------endline:the overall file-----*/

