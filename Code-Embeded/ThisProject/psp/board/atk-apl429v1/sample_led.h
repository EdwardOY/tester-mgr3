
/********************************** (C) COPYRIGHT *******************************
* File Name          : sample_gpio.H
                       copied from CH554EVT/EXAM/GPIO/Main.C
* Author             : EDWOY
* Version            : V1.1
* Date               : 2017/11/18
* platform            : WCH CH554/CH552
* Description        : GPIO 设置与使用和GPIO中断使用示例   
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
********************************************************************************/
#ifndef __SAMPLE_LED_H__
#define __SAMPLE_LED_H__
//edwoy260413---
#include "ThisProj_Conf.H"
#include "convert_path.h"
#include GPIO_HEAD

///S>==base GPIO================================================================

///E<==base GPIO================================================================


///S>==LEDs================================================================

//edwoy260430
typedef enum{
		LedID_Red  = 0,
		LedID_Green,
		LedID_Max,
} emLedId_t;

#define IS_VALID_ID_LED(ID) ((ID < LedID_Max) ? 1 : 0)


typedef struct _stt_led_ctrl {
    uint16_t              mPin;     //Gpio pin
    const emLedId_t       mID;     //Led ID
    GPIO_TypeDef         *mGpioBank_p;     //GPIO端口
//    STT_GPIO_INIT_T       mGpioInit;    //GPIO初始化参数
    EM_GPIO_PIN_STA_T     mSwhLvl_On; //LED点亮的电平
    EM_GPIO_PIN_STA_T     mSwhLvl_Off; //LED熄灭的电平

//    sttPrp_Gpio_t          mGpioPrp; //gpio属性
} sttLedCtrl_t;
extern sttLedCtrl_t g_samp_leds[LedID_Max];

/*********************************************
 * @brief app_samp_leds_init
 *       
 * @param:pLedsCtrl, 指向结构体数组
 * * @return: 0:成功，-1:失败
 * 
 *********************************************/
char app_samp_leds_init(sttLedCtrl_t *pLedsCtrl);

///E<==LEDs================================================================



#endif //__SAMPLE_LED_H__

