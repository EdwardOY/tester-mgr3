
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


///S>==Keys================================================================
//edwoy260430---doubao-----
#define KEY_DEBOUNCE_MS  26         // 防抖基数时基 1ms

//s>----------- 枚举：按键激活方式 -----------------------------
typedef enum{
    KeyAct_Edge  = 0,      // 边沿触发（按下一次）
    KeyAct_Level  = 1,      // 电位触发（按住一直有效）
    KeyAct_ShortPress = 2,       // 短按(30ms <= t <= 200ms)触发（按下一定时间才有效，暂未实现）
    KeyAct_LongPress = 3,        // 长按(200ms <= t <= 1500ms)触发（按住超过一定时间才有效，暂未实现）
    KeyAct_DoubleClick = 4,       // 双击触发（两次按下间隔短于一定时间才有效，暂未实现）
    KeyAct_Max,
} emKeyActMd_t;
//e<----------- 枚举：按键激活方式 -----------------------------

//s>----------- 枚举：按键动作 -----------------------------
//edwoy260417
typedef enum{
    KeyDone_Idle      = 0,            //无任何动作
    KeyDone_Click1st  = 1,           // 按键转变为KeyDone_Idle后，首次检测到按下状态
    KeyDone_FuncStart = 2,       // 按键转变为KeyDone_Click1st后,经历防抖延迟，再次检测到按下状态

    KeyDone_FuncOver,        //return 保留不用 按键转变为KeyDone_Click1st后,经历(200ms <= t <= 1500ms)延迟过程中，一直都能检测到按下状态
    KeyDone_DoubleClick,     //return 保留不用
    KeyDone_Max,
} emKeyDone_t;
//e<----------- 枚举：按键动作 -----------------------------

//s>------------ 枚举：按键响应电位 ---------------------------
typedef enum{
    KeyRespLvl_Low   = 0,      // 低电位响应
    KeyRespLvl_High  = 1,       // 高电位响应
} emKeyRespLvl_t;
//e<------------ 枚举：按键响应电位 ---------------------------
//s>------------ 枚举：按键状态 ---------------------------
typedef enum{
    KeySta_Release  = 0,
    KeySta_Pressed  = 1
} emKeySta_t;
//e<------------ 枚举：按键状态 ---------------------------


//s>-----------------------------------------------------
//edwoy260430---
#if THIS_BOARD == G_ATK_APL429IG_V1

#elif  THIS_BOARD ==  G_ATK_DMF407IG

#endif // <#elif  THIS_BOARD ==  G_ATK_DMF407IG>
//e<-----------------------------------------------------

//s>--other keys---------------------------------------------------
//edwoy260430---doubao-----


//s>---------- 枚举：按键编号 -----------------------------
typedef enum{
    KeyID_Btn0 = 0,
    KeyID_Btn1 ,
    KeyID_Btn2 ,	       
#if THIS_BOARD  == G_ATK_APL429IG_V1 || THIS_BOARD  == G_ATK_MINI103_V1_9 
    KeyID_WkUp,
#endif //    
    KeyID_Max,
} emKeyId_t;
//e<---------- 枚举：按键编号 -----------------------------

//edwoy260417---
#define IS_VALID_KEYID(id)  ((id) < KeyID_Max) 
#define IS_VALID_KEYFUN(fun)  ((fun) != NULL )
//e<--other keys---------------------------------------------------

typedef char (*KeyFunc_t)(void* pArg);
//s>--------------- 结构体：按键控制 ---------------------
    /*   
    emKeySta_t        mSta_Cur; //当前按键状态
    emKeySta_t        mSta_Pre; //上次按键状态
    */ 
   
typedef struct _stt_key_ctrl {

    unsigned int      mDeb_Cnt; //消抖计数
    volatile emKeyRespLvl_t    mVlu;     //当前按键值 edwoy260502
    
    emKeyDone_t       mDone;    //当前按键动作

    const emKeyId_t       mID;     //按键ID
    const emKeyActMd_t    mActMd;   //按键动作模式
    const emKeyRespLvl_t  mRespLvl; //按键响应电平

    KeyFunc_t             mFunc;    //按键功能
    void                 *mArg;    //按键功能参数
    //    sttPrp_Gpio_t         mGpioPrp; //gpio属性
    //     uv32_t*               mGpio ;       //仅适用于支持gpio位段的mcu

    uint16_t              mPin;    //gpio`s detail pin
        
    STT_GPIO_BK_T*         mGpioBank_p;     // gpio bank，_GpioPrp is GPIO_TypeDef 
    STT_GPIO_INIT_T*        mGpioInit_p;   // STT_GPIO_INIT_T is GPIO_InitTypeDef        
} sttKeyCtrl_t;

extern sttKeyCtrl_t g_samp_keys[KeyID_Max] ;
//e<--------------- 结构体：按键控制 ---------------------

//s>=====================函数声明=========================
void GPIO_KeyInit(void);

emKeySta_t Key_GetStatus(emKeyId_t id);
unsigned char Key_GetPressFlag(emKeyId_t id);
void Key_ClearPressFlag(emKeyId_t id);

char app_samp_hdr_keys(sttKeyCtrl_t* pKey_p);
char app_samp_keys_monitor(sttKeyCtrl_t* pKey_p);
char app_samp_keys_get_stavlu_poll(sttKeyCtrl_t* pKey_p);

EM_GPIO_PIN_STA_T  app_key_pin_rd(emKeyId_t pID);
/* 
__WEAK char app_custom_btn0(const emKeyId_t pID, void* pArg);
__WEAK char app_custom_btn1(const emKeyId_t pID, void* pArg);
__WEAK char app_custom_btn2(const emKeyId_t pID, void* pArg);
__WEAK char app_custom_wkup(const emKeyId_t pID, void* pArg);
 */

char app_samp_keys_init(sttKeyCtrl_t* pKey_p);
char app_samp_keys_reset(sttKeyCtrl_t* pKey_p,emKeyId_t pID);
/********************************************
 * @brief Read pins of a GPIO bank
 * @param pGpioBank_p: pointer to GPIO bank
 * @return:
 *    @arg: G_GPIO_PIN_RST, Low level;
 *    @arg: G_GPIO_PIN_SET, High level;
 * @date:
 *    260501,V1,
 *******************************************/
int app_samp_gpio_bank_rd(STT_GPIO_BK_T *pGpioBank_p);

/********************************************
 * @brief write all pins of a GPIO bank
 * @param pGpioBank_p: pointer to GPIO bank
 *    @arg: GPIOA~GPIOG
 * @param pPinVlu: value of pins
 * @return:
 *    @arg 0: success;
 *    @arg-1: invalid parameter;
 * @date:
 *    260501,V1,
 *******************************************/
char app_samp_gpio_bank_wt(STT_GPIO_BK_T *pGpioBank_p, const uint16_t pPinVlu);

//e<========================函数声明========================

///s>--keys api2 fifo-------------------------------------------------------------------
/************************************************************
 * @brief Poll a key
 * @param pKey_p: pointer to key control struct
 * @return:
 *    @arg 0: success;
 *    @arg-1: invalid parameter;

 ************************************************************/
char app_samp_1key_pollhdr(sttKeyCtrl_t* pKey_p);

char app_samp_allkeys_pollhdr(sttKeyCtrl_t* pKey_p);
///e<--keys api2 fifo-------------------------------------------------------------------
///E<==Keys===================================================================================

void app_samp_led_poll(void) ;
void app_samp_gpios_init(void) ;

#endif //__SAMPLE_LED_H__

