/*************************************************************************
 * @brief  res_gpio.h, gpio resouce header for board
 * @author  Edwoy
 * @version v1.1
 * @state   verified，2023.5.10
 * @copyright Copyright (c) 2034. All rights reserved.
 ************************************************************************
 * @update
     v1.1 verified，2023.5.10
		     Rectifying the definitions of red LED and green LED
     v1.0 orgn version
 *************************************************************************/
#ifndef _RES_GPIO_H_
#define _RES_GPIO_H_

#include "ThisProj_Conf.h"
#include "convert_path.h"
#include SYS_HEAD
#include UTY_TYP_HEAD
#include UTY_DEBUG_HEAD //Projects/psp/
#include SAMP_LEDS_HEAD

#ifdef __cplusplus
extern "C" {
#endif
///S>==peripherals======================================================================================
//edwoy260502---
//gpioinit:input,polldown
extern STT_GPIO_INIT_T g_gpioinit_in_dn ;

//gpioinit:input,polldown
extern STT_GPIO_INIT_T g_gpioinit_in_up ;

//gpioinit:output,opendrain,nopull
extern STT_GPIO_INIT_T g_gpioinit_out_od_np ;
//gpioinit:output,pp,pullup
extern STT_GPIO_INIT_T g_gpioinit_out_pp_up ;
//gpioinit:output,pp,pulldown
extern STT_GPIO_INIT_T g_gpioinit_out_pp_dn ;

///E<==peripherals======================================================================================

///S>==Leds=============================================================================================
#if  G_ATK_PDR496VE == THIS_BOARD 
typedef enum{  LightOn = GPIO_PIN_RESET,  LightOff = GPIO_PIN_SET } emLedState_t;


//--RED_LED paras----------------------------------------------------------------------
#define GPIO_CLK_ENABLE_LED_RED()       __HAL_RCC_GPIOE_CLK_ENABLE()          
#define GPIO_PORT_LED_RED            GPIOE
#define GPIO_PIN_LED_RED      GPIO_PIN_7 

#define RED_LED(x)           HAL_GPIO_WritePin(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED,x)  //SYS_RUN_LED(x) 
#define RED_LED_ON()         HAL_GPIO_WritePin(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED,GPIO_PIN_RESET)
#define RED_LED_OFF()        HAL_GPIO_WritePin(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED,GPIO_PIN_SET)
#define RED_LED_TGG()        HAL_GPIO_TogglePin(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED)
//--End RED_LED paras----------------------------------------------------------End-----


//--GREEN_LED paras--------------------------------------------------------------------

#define GPIO_CLK_ENABLE_LED_GREEN()       __HAL_RCC_GPIOE_CLK_ENABLE()      

#define GPIO_PORT_LED_GREEN     GPIOE
#define GPIO_PIN_LED_GREEN      GPIO_PIN_8

#define GREEN_LED(x)         HAL_GPIO_WritePin(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN,x)  //LED1(x) 
#define GREEN_LED_ON()       HAL_GPIO_WritePin(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN,GPIO_PIN_RESET)
#define GREEN_LED_OFF()      HAL_GPIO_WritePin(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN,GPIO_PIN_SET)
#define GREEN_LED_TGG()      HAL_GPIO_TogglePin(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN)
//--End GREEN_LED paras--------------------------------------------------------End-----

//--BLUE_LED paras--------------------------------------------------------------------

#define GPIO_CLK_ENABLE_LED_BLUE()       __HAL_RCC_GPIOE_CLK_ENABLE()      

#define GPIO_PORT_LED_BLUE     GPIOE
#define GPIO_PIN_LED_BLUE      GPIO_PIN_9


#define BLUE_LED(x)         HAL_GPIO_WritePin(GPIO_PORT_LED_BLUE,GPIO_PIN_LED_BLUE,x)  //LED2(x) 
#define BLUE_LED_ON()       HAL_GPIO_WritePin(GPIO_PORT_LED_BLUE,GPIO_PIN_LED_BLUE,GPIO_PIN_RESET)
#define BLUE_LED_OFF()      HAL_GPIO_WritePin(GPIO_PORT_LED_BLUE,GPIO_PIN_LED_BLUE,GPIO_PIN_SET)
#define BLUE_LED_TGG()      HAL_GPIO_TogglePin(GPIO_PORT_LED_BLUE,GPIO_PIN_LED_BLUE)
//--End BLUE_LED paras--------------------------------------------------------End-----

#endif //<#if  G_ATK_PDR496VE == THIS_BOARD  >


#if  G_ATK_DMF407IG == THIS_BOARD 
typedef enum{  LightOn = GPIO_PIN_RESET,  LightOff = GPIO_PIN_SET } emLedState_t;

//--GREEN_LED paras--------------------------------------------------------------------
#define GPIO_PORT_LED_RED     GPIOE
#define GPIO_PIN_LED_RED      GPIO_PIN_0 
#define Tgg_Led0()    HAL_GPIO_TogglePin(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED)
#define Open_Led0()   HAL_GPIO_WritePin(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED,GPIO_PIN_RESET)
#define Close_Led0()  HAL_GPIO_WritePin(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED,GPIO_PIN_SET)

#define RED_LED(x)           HAL_GPIO_WritePin(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED,x)  //SYS_RUN_LED(x) 
#define RED_LED_ON()         Open_Led0()
#define RED_LED_OFF()        Close_Led0()
#define RED_LED_TGG()        Tgg_Led0()
//--End GREEN_LED paras--------------------------------------------------------End-----

//--RED_LED paras----------------------------------------------------------------------
#define GPIO_CLK_ENABLE_LED_RED()       __HAL_RCC_GPIOE_CLK_ENABLE()          
#define GPIO_CLK_ENABLE_LED_GREEN()       __HAL_RCC_GPIOE_CLK_ENABLE()      

#define GPIO_PORT_LED_GREEN     GPIOE
#define GPIO_PIN_LED_GREEN      GPIO_PIN_1 
#define Tgg_Led1()    HAL_GPIO_TogglePin(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN)
#define Open_Led1()   HAL_GPIO_WritePin(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN,GPIO_PIN_RESET)
#define Close_Led1()  HAL_GPIO_WritePin(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN,GPIO_PIN_SET)

#define GREEN_LED(x)         HAL_GPIO_WritePin(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN,x)  //LED1(x) 
#define GREEN_LED_ON()       Open_Led1()
#define GREEN_LED_OFF()      Close_Led1()
#define GREEN_LED_TGG()      Tgg_Led1() 
//--End RED_LED paras----------------------------------------------------------End-----
#endif //<#if  G_ATK_DMF407IG == THIS_BOARD  >

#if THIS_BOARD  == G_ATK_APL429IG_V1 
//s>--RED_LED paras----------------------------------------------------------------------
#define GPIO_CLK_ENABLE_LED_GREEN()       __HAL_RCC_GPIOB_CLK_ENABLE()   
#define GPIO_PORT_LED_GREEN     GPIOB
#define GPIO_PIN_LED_GREEN      GPIO_PIN_1 
#define Tgg_Led1()    app_gpio_tgg(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN)
#define Open_Led1()   app_gpio_low(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN)
#define Close_Led1()  app_gpio_high(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN)

#define   RED_LED(x)           app_gpio_out(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN,x)  //LED1(x) 
#define   RED_LED_ON()         Open_Led1()
#define   RED_LED_OFF()        Close_Led1()
#define   RED_LED_TGG()        Tgg_Led1()
//e<--RED_LED paras----------------------------------------------------------End-----
//s>--GREEN_LED paras--------------------------------------------------------------------
#define GPIO_CLK_ENABLE_LED_RED()       __HAL_RCC_GPIOB_CLK_ENABLE()          
#define GPIO_PORT_LED_RED             GPIOB
#define GPIO_PIN_LED_RED              GPIO_PIN_0 
#define Tgg_Led0()            API_PRP_GPIO_PIN_TOGG(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED)
#define Open_Led0()           API_PRP_GPIO_PIN_WT(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED,GPIO_PIN_RESET)
#define Close_Led0()          API_PRP_GPIO_PIN_WT(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED,GPIO_PIN_SET)

#define   GREEN_LED(x)         API_PRP_GPIO_PIN_WT(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED,x)  //SYS_RUN_LED(x) 
#define   GREEN_LED_ON()       Open_Led0()
#define   GREEN_LED_OFF()      Close_Led0()
#define   GREEN_LED_TGG()      Tgg_Led0() 
//e<-- GREEN_LED paras--------------------------------------------------------End-----

//s>--New LedID setting-------------------------------------------------------------------
extern sttLedCtrl_t g_samp_leds[LedID_Max] ;

//e<--New LedID setting-----------------------------------------------------------End-----

#endif //<#if THIS_BOARD  == G_ATK_APL429IG_V1 >


//--SYSRUN_LED setting------------------------------------------------------------------
#define SYSRUN_LED(x)        GREEN_LED(x)
#define SYSRUN_LED_ON()      GREEN_LED_ON()  
#define SYSRUN_LED_OFF()     GREEN_LED_OFF()  
#define SYSRUN_LED_TGG()     GREEN_LED_TGG()  

//--End SYSRUN_LED setting------------------------------------------------------End-----

///E<==Leds======================================================================================End====

///s>==Buttons==========================================================================================

#if  PhotoGD32F407V  == THIS_BOARD 

#define PORT_WKUP    GPIOA
#define PIN_WKUP     GPIO_PIN_0
#define KEY_WKUP     API_PRP_GPIO_PIN_RD(PORT_WKUP ,PIN_WKUP) 

#define KEY_STA_PRESSED   G_GPIO_PIN_SET
#define KEY_STA_RELEASE   G_GPIO_PIN_RST

#elif G_ATK_APL429IG_V1 == THIS_BOARD 

//buttons按下标志值
typedef enum {
  PrsFlg_None = 0U,
	PrsFlg_Btn0 = 1 << 0,
	PrsFlg_Btn1 = 1 << 1 ,
	PrsFlg_Btn2 = 1 << 2, 
	PrsFlg_WkUp = 1 << 3 ,
}emBtnPrsFlg_t;  

#define PORT_BTN0                  GPIOH
#define PIN_BTN0                   GPIO_PIN_3
#define Btn0_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOH_CLK_ENABLE()

#define PORT_BTN1                  GPIOH
#define PIN_BTN1                   GPIO_PIN_2
#define Btn1_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOH_CLK_ENABLE()

#define PORT_BTN2                  GPIOC
#define PIN_BTN2                   GPIO_PIN_13
#define Btn2_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()

#define PORT_WKUP                  GPIOA
#define PIN_WKUP                   GPIO_PIN_0
#define WKUP_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE() 

/* 
#if defined(USE_HAL_DRIVER)
#define KEY_BTN0        HAL_GPIO_ReadPin(PORT_BTN0, PIN_BTN0)     
#define KEY_BTN1        HAL_GPIO_ReadPin(PORT_BTN1, PIN_BTN1)   
#define KEY_BTN2        HAL_GPIO_ReadPin(PORT_BTN2, PIN_BTN2)     
#define KEY_WKUP        HAL_GPIO_ReadPin(PORT_WKUP, PIN_WKUP)     
#endif
 */
#define KEY_BTN0        API_PRP_GPIO_PIN_RD(PORT_BTN0, PIN_BTN0)     
#define KEY_BTN1        API_PRP_GPIO_PIN_RD(PORT_BTN1, PIN_BTN1)   
#define KEY_BTN2        API_PRP_GPIO_PIN_RD(PORT_BTN2, PIN_BTN2)     
#define KEY_WKUP        API_PRP_GPIO_PIN_RD(PORT_WKUP, PIN_WKUP)     

#elif  G_ATK_PDR496VE == THIS_BOARD 

//buttons按下标志值
typedef enum {
    PrsFlg_None = 0U,
	PrsFlg_Btn0   = 1 << 0,
	PrsFlg_Btn1   = 1 << 1 ,
	PrsFlg_Btn2   = 1 << 2, 
	PrsFlg_WkUp   = 1 << 3 ,
} emBtnPrsFlg_t;  

#define PORT_BTN0                  GPIOD
#define PIN_BTN0                   GPIO_PIN_10
#define Btn0_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOD_CLK_ENABLE()

#define PORT_BTN1                  GPIOD
#define PIN_BTN1                   GPIO_PIN_9
#define Btn1_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOD_CLK_ENABLE()

#define PORT_BTN2                  GPIOD
#define PIN_BTN2                   GPIO_PIN_8
#define Btn2_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOD_CLK_ENABLE()


#define PORT_WKUP                  GPIOC
#define PIN_WKUP                   GPIO_PIN_13
#define WKUP_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()

#define KEY_BTN0        API_PRP_GPIO_PIN_RD(PORT_BTN0, PIN_BTN0)     /* 读取Btn0引脚 */
#define KEY_BTN1        API_PRP_GPIO_PIN_RD(PORT_BTN1, PIN_BTN1)     /* 读取Btn1引脚 */
#define KEY_BTN2        API_PRP_GPIO_PIN_RD(PORT_BTN2, PIN_BTN2)     /* 读取Btn2引脚 */
#define KEY_WKUP        API_PRP_GPIO_PIN_RD(PORT_WKUP, PIN_WKUP)     /* 读取WkUp引脚 */

#endif //<#if  PhotoGD32F407V  == THIS_BOARD >
///e<==Buttons===================================================================================End====


#ifdef __cplusplus
}
#endif

#endif 
/* ---Endline:Full File---------------------------------------------------------All-End------*/

