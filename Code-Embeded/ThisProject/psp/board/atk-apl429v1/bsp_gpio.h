/**
 * @file n32_gpio.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2022. All rights reserved.
 */
#ifndef _BSP_GPIO_H_
#define _BSP_GPIO_H_
#include "ThisProj_Glb.h"
#include MCU_HEAD
#include RES_GPIO_HEAD

/*---Leds:---------------------------------------------------------------*/
/**\brief init all leds for the  board
          bsp_follow() 升级版，已解决逆向闪烁问题
  *\param void
  *\notion
  *\return void
  *\update
  *    -v1.0-,(verified,2022.10.11) 
  */
void bsp_leds_init(void);
/*---End,Leds-----------------------------------------------------------*/


/*---Buttons: Led1-PA8,Led2-PB4,Led3-PB5 -------------------------------*/


/**\brief init all buttons for the  board
          bsp_follow() 升级版，已解决逆向闪烁问题
  *\param void
  *\notion
  *\return void
  *\update
  *    -v1.0-,(verified,2022.10.11) 
  */
void bsp_btns_init(void);	

uv32_t btns_monitor(u8_t md_press); ////emBtnPrsFlg_t
/*---End,buttons-------------------------------------------------------*/


#endif /* _PROJECT_H_ */
