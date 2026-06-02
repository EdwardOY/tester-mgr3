/********************************** (C) COPYRIGHT *******************************
* File Name          : sample_gpio.C
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
///S>==EDWOY================================================================
///<E==EDWOY================================================================

//edwoy260415---
#include "ThisProj_Glb.H"


///S>==Leds==============================================================================
//edwoy260430--
static void _f_delay1ms(void)
{
    unsigned int i;
    for(i=0;i<2880;i++);
}

//s>--LedID setting-------------------------------------------------------------------
sttLedCtrl_t g_samp_leds[LedID_Max] = {
#if  THIS_BOARD  == G_ATK_APL429IG_V1  || THIS_BOARD  == G_ATK_DMF407IG || THIS_BOARD == G_ATK_MINI103_V1_9

    [LedID_Red] = {
        .mID = LedID_Red,.mGpioBank_p =  GPIOB, .mPin = GPIO_PIN_1,
        .mSwhLvl_On = G_GPIO_PIN_RST,//低电平点亮
        .mSwhLvl_Off = G_GPIO_PIN_SET,//高电平熄灭
    },

    [LedID_Green] =  {
        .mID = LedID_Green,.mGpioBank_p =  GPIOB,  .mPin = GPIO_PIN_0,
        .mSwhLvl_On = G_GPIO_PIN_RST,//低电平点亮
        .mSwhLvl_Off = G_GPIO_PIN_SET,//高电平熄灭      
    },

#endif //<#if  THIS_BOARD  == G_ATK_APL429IG_V1>
};


/****************************************************
 * @brief app_samp_leds_init     
 * @param:pLedsCtrl, 指向结构体数组
 * @return: 0:成功，-1:失败
 * @note:
       MX_GPIO_Init() has __HAL_RCC_GPIOB_CLK_ENABLE()    ;
 * @date:
 **************************************************/
char app_samp_leds_init(sttLedCtrl_t *pLedsCtrl)
{
    if(NULL == pLedsCtrl){
        return -1;
    }
    
    STT_GPIO_INIT_T tGpioInit = {
        .Mode  = GPIO_MODE_OUTPUT_OD ,
        .Pull  = GPIO_NOPULL,
        .Speed = GPIO_SPEED_HIGH,        
    };    

    for(emLedId_t  i = 0; i < LedID_Max; i++)
    {
        if(IS_VALID_ID_LED(i)){
            tGpioInit.Pin = pLedsCtrl[i].mPin;
            API_PRP_GPIO_INIT(pLedsCtrl[i].mGpioBank_p, &tGpioInit);
        }
        else{
            return -2;
        }
    }
    return 0;
}
//e<--LedID setting-----------------------------------------------------------End-----
///E<==Leds===============================================================================

