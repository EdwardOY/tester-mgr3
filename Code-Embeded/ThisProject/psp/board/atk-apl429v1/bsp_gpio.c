/**
 * @file main.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright 
 */
#include "ThisProj_Glb.h"
#include "bsp_misc.h"
#include DLY_HEAD
#include GPIO_HEAD
#include BSP_GPIO_HEAD

/*****************************************************
  *\brief init all leds for the  board
          bsp_follow() 升级版，已解决逆向闪烁问题
  *\param void
  *\notion 
  *\return void
  *\date
  *    -v1.0-,(verified,2022.10.11) 
  ***************************************************/
void bsp_leds_init()
{
	app_gpio_out_od_np_init(PORT_LED0, PIN_LED0);	
	app_gpio_out_od_np_init(PORT_LED1, PIN_LED1);	
	
  SYSRUN_LED_OFF();
  RED_LED_OFF() ;
}


/**********************************************
  *\brief init all buttons for the  board
  *\param void
  *\notion
  *\return void
  *\date
  *    -v1.0-,(verified,2022.10.11) 
  *********************************************/
void bsp_btns_init()
{
	app_gpio_ipu_init(PORT_BTN0, PIN_BTN0);	//pull-up input init
	app_gpio_ipu_init(PORT_BTN1, PIN_BTN1);
	app_gpio_ipu_init(PORT_BTN2, PIN_BTN2);	

#if THIS_BOARD == G_ATK_APL429IG_V1 || THIS_BOARD == G_ATK_MINI103_V1_9
	app_gpio_ipd_init(PORT_WKUP ,PIN_WKUP);
// 	app_gpio_ipd_init(PORT_WKUP, PIN_WKUP); //pull-down input init
#else

#endif //<#if THIS_BOARD == G_ATK_APL429IG_V1 --#else--->	
}//<void bsp_btns_init()>

/********************************************************************
  *\brief monitor buttons
  *\param :md_press, press active-mode,check it in utility_def.h
      -BtnTrg_JpE-,(=0) Jamp edge tragger
      -BtnTrg_VtL-,(=1) Voltage Level tragger

  *\return emBtnPrsFlg_t,check it in bsp_misc.h
  *\date,
      -v1.3-,2023.4.28 G_ATK_DMF407IG == THIS_BOARD
  *   -v1.2-,2022.7.27 verified ,
             uv8_t mark_btn_press
  *   -v1.1-,2022.7.3 verified 
             return-vlu u8_t-->u32_t
  *   -v1.0-,
  *********************************************************************/
uv32_t btns_monitor(u8_t md_press) ////emBtnPrsFlg_t
{
	static uv8_t mark_btn_press  = 1;     //按键松开标志

	if(md_press != BtnTrg_JpE)
		 mark_btn_press = 1;    //支持连按
	
#if THIS_BOARD == G_ATK_APL429IG_V1 
	if(mark_btn_press &&    \
		( 0 == KEY_BTN0 || 0 == KEY_BTN1 || 0 == KEY_BTN2 || 1 == KEY_WKUP ))
	{
			stkdly_ms(15);
			mark_btn_press = 0;
			if(!KEY_BTN0)    return PrsFlg_Btn0;
			if(!KEY_BTN1)    return PrsFlg_Btn1;
			if(!KEY_BTN2)    return PrsFlg_Btn2;
			if(KEY_WKUP)     return PrsFlg_WkUp;  
		
	}else if(1 == KEY_BTN0 && 1 == KEY_BTN1 && 1 == KEY_BTN2 && 0 == KEY_WKUP)
			mark_btn_press = 1;
	
#elif G_ATK_DMF407IG == THIS_BOARD
	if(mark_btn_press && (0 == KEY_BTN0 || 0 == KEY_BTN1 || 0 == KEY_BTN2))
	{
			stkdly_ms(15);
			mark_btn_press = 0;
			if(!KEY_BTN0)    return PrsFlg_Btn0;
			if(!KEY_BTN1)    return PrsFlg_Btn1;
			if(!KEY_BTN2)    return PrsFlg_Btn2;
		
	}else if(1 == KEY_BTN0 && 1 == KEY_BTN1 && 1 == KEY_BTN2 )
			mark_btn_press = 1;	
#endif //<#if G_ATK_APL429IG_V1 == THIS_BOARD  >	

	return PrsFlg_None;   //无按键按下	
	
}

