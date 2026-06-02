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

static char _f_1key_assert_id(const emKeyId_t  pID)  ;
static char _f_allkeys_assert_para(sttKeyCtrl_t* pKey_p);
__WEAK char app_custom_btn0(void* pArg);
__WEAK char app_custom_btn1(void* pArg);
__WEAK char app_custom_btn2(void* pArg);
__WEAK char app_custom_wkup(void* pArg);


///S>==Keys===============================================================================
//s>--------------- 结构体：按键控制 ---------------------
/*******
typedef struct _stt_key_ctrl {

    unsigned int      mDeb_Cnt; //消抖计数
    emKeyRespLvl_t    mVlu;     //当前按键值
    emKeyDone_t       mDone;    //当前按键动作流程
  
//    emKeySta_t        mSta_Cur; //当前按键状态
//    emKeySta_t        mSta_Pre; //上次按键状态

    const emKeyId_t       mID;     //按键ID
    const emKeyActMd_t    mActMd;   //按键动作模式
    const emKeyRespLvl_t  mRespLvl; //按键响应电平

    KeyFunc_t             mFunc;    //按键功能
    void                  *mArg;    //按键功能参数
    sttPrp_Gpio_t         mGpioPrp; //gpio属性
        
} sttKeyCtrl_t;

 ******/
//e<--------------- 结构体：按键控制 ---------------------
//No other keys, only the KEY_BTN0

//keys factory config
static  sttKeyCtrl_t _s_sample_keys_fac[KeyID_Max] = {
    // KEY_BTN0   低有效
    [KeyID_Btn0] = { 
        .mDeb_Cnt = 0,.mVlu = KeyRespLvl_High, .mDone = KeyDone_Idle, .mID = KeyID_Btn0,  
        .mActMd = KeyAct_Edge, .mRespLvl = KeyRespLvl_Low,
        .mFunc = app_custom_btn0, .mArg= NULL,

        .mPin        = GPIO_PIN_3, 
        .mGpioBank_p = GPIOH,   
        .mGpioInit_p = NULL,
      
    },
    // KEY_BTN1  低有效
    [KeyID_Btn1] = {
        
        .mDeb_Cnt = 0,.mVlu = KeyRespLvl_High, .mDone = KeyDone_Idle, .mID = KeyID_Btn1,  
        .mActMd = KeyAct_Edge, .mRespLvl = KeyRespLvl_Low,
        .mFunc = app_custom_btn1, .mArg= NULL,

        .mGpioBank_p = GPIOH,   
        .mPin        = GPIO_PIN_2, 
        .mGpioInit_p = NULL,
    },
    // BTN2  低有效
    [KeyID_Btn2] =  {
        
        .mDeb_Cnt = 0,.mVlu = KeyRespLvl_High, .mDone = KeyDone_Idle, .mID = KeyID_Btn2,  
        .mActMd = KeyAct_Edge, .mRespLvl = KeyRespLvl_Low,
        .mFunc = app_custom_btn2, .mArg= NULL,

        .mGpioBank_p = GPIOC,   
        .mPin        = GPIO_PIN_13, 
        .mGpioInit_p = NULL,
    },

#if  THIS_BOARD == G_ATK_APL429IG_V1 || THIS_BOARD == G_ATK_MINI103_V1_9
    // KEY_WKUP  高有效
    [KeyID_WkUp] =  {
        
        .mDeb_Cnt = 0,.mVlu = KeyRespLvl_Low, .mDone = KeyDone_Idle, .mID = KeyID_WkUp,  
        .mActMd = KeyAct_Edge, .mRespLvl = KeyRespLvl_High,
        .mFunc = app_custom_wkup, .mArg= NULL,

        .mGpioBank_p = GPIOA,   
        .mPin        = GPIO_PIN_0, 
        .mGpioInit_p = NULL,
    },
    // _f_gpio_rccclk_en(STT_GPIO_BK_T* GPIOx)
#endif //

}; //static  sttKeyCtrl_t _s_sample_keys_fac[KeyID_Max]

sttKeyCtrl_t g_samp_keys[KeyID_Max] = {
    // KEY_BTN0   低有效
    [KeyID_Btn0] = { 
        .mDeb_Cnt = 0,.mVlu = KeyRespLvl_High, .mDone = KeyDone_Idle, .mID = KeyID_Btn0,  
        .mActMd = KeyAct_Edge, .mRespLvl = KeyRespLvl_Low,
        .mFunc = app_custom_btn0, .mArg= NULL,

        .mPin        = GPIO_PIN_3, 
        .mGpioBank_p = GPIOH,   
        .mGpioInit_p = NULL,
      
    },
    // KEY_BTN1  低有效
    [KeyID_Btn1] = {
        
        .mDeb_Cnt = 0,.mVlu = KeyRespLvl_High, .mDone = KeyDone_Idle, .mID = KeyID_Btn1,  
        .mActMd = KeyAct_Edge, .mRespLvl = KeyRespLvl_Low,
        .mFunc = app_custom_btn1, .mArg= NULL,

        .mGpioBank_p = GPIOH,   
        .mPin        = GPIO_PIN_2, 
        .mGpioInit_p = NULL,
    },
    // BTN2  低有效
    [KeyID_Btn2] =  {
        
        .mDeb_Cnt = 0,.mVlu = KeyRespLvl_High, .mDone = KeyDone_Idle, .mID = KeyID_Btn2,  
        .mActMd = KeyAct_Edge, .mRespLvl = KeyRespLvl_Low,
        .mFunc = app_custom_btn2, .mArg= NULL,

        .mGpioBank_p = GPIOC,   
        .mPin        = GPIO_PIN_13, 
        .mGpioInit_p = NULL,
    },

#if  THIS_BOARD == G_ATK_APL429IG_V1 || THIS_BOARD == G_ATK_MINI103_V1_9
    // KEY_WKUP  高有效
    [KeyID_WkUp] =  {
        
        .mDeb_Cnt = 0,.mVlu = KeyRespLvl_Low, .mDone = KeyDone_Idle, .mID = KeyID_WkUp,  
        .mActMd = KeyAct_Edge, .mRespLvl = KeyRespLvl_High,
        .mFunc = app_custom_wkup, .mArg= NULL,

        .mGpioBank_p = GPIOA,   
        .mPin        = GPIO_PIN_0, 
        .mGpioInit_p = NULL,
    },
    // _f_gpio_rccclk_en(STT_GPIO_BK_T* GPIOx)
#endif //
};

static volatile emKeyRespLvl_t s_key_vlus[KeyID_Max] = {
    KeyRespLvl_High,  KeyRespLvl_High,
    // BTN2  低有效
    KeyRespLvl_High, 

#if  THIS_BOARD == G_ATK_APL429IG_V1 || THIS_BOARD == G_ATK_MINI103_V1_9
    KeyRespLvl_Low, // KEY_WKUP  高有效
#endif //    
}; //按键状态缓存，0/1对应Release/Pressed


///s>--keys api2 fifo-------------------------------------------------------------------
//edwoy2600502---
static char _f_1key_assert_para(sttKeyCtrl_t* pKey_p)
{
    if(NULL == pKey_p) {
       return -1; //Valid parameter
    }
    if(!IS_VALID_KEYID(pKey_p->mID)) {
       return -2; //Valid key ID
    }
    if(NULL == pKey_p->mFunc) {
       return -3; //Valid key function
    }
}

/*************************
 * @brief  Only assert key ID
 * @param pKey_p: pointer to key control struct
 * @return:
 *    @arg 0: success;
 *    @arg-1: invalid parameter;
 *    @arg-2: invalid key ID;
 * @date
 *    260417
 *************************/
static char _f_1key_assert_id( const emKeyId_t  pID)  
{
    if(!IS_VALID_KEYID(pID)) {
       return -1; //Valid key ID
    }
    return 0;
}

static char _f_allkeys_assert_para(sttKeyCtrl_t* pKey_p)
{
    unsigned char i = 0;	
    if(NULL == pKey_p) {return -1;} //Invalid parameter

    for(i=0;i<KeyID_Max;i++) {
        if(IS_VALID_KEYID(pKey_p[i].mID)) {
            continue; //Valid key ID
        }
        else{
            return -2;  //Invalid key ID
        }
        if(IS_VALID_KEYFUN(pKey_p[i].mFunc)) {
            continue; //Valid key ID
        }
        else{
            return -3;  //Invalid key function
        }
    }//<for(i=0;i<KeyID_Max;i++)>

    return 0;
}


/******************************************************
 * @brief Keys`s assert
 * @param pKey_p: pointer to key control struct
 * @return:
 *    @arg 0: success;
 *    @arg-1: invalid parameter;
 *    @arg-2: invalid key ID;
 *    @arg-3: invalid key function;
 * @date
 *    260502
 * ****************
    s_key_vlus[KeyID_Btn0]  = (emKeyRespLvl_t)KEY_BTN0;
    s_key_vlus[KeyID_Btn1]  = (emKeyRespLvl_t)KEY_BTN1;    
    s_key_vlus[KeyID_Btn2]  = (emKeyRespLvl_t)KEY_BTN2;    
#if  THIS_BOARD == G_ATK_APL429IG_V1 || THIS_BOARD == G_ATK_MINI103_V1_9
    s_key_vlus[KeyID_WkUp]  = (emKeyRespLvl_t)KEY_WKUP;
#endif   
 *******************************************************/
static char _f_keys_callback_vlu(sttKeyCtrl_t* pKey_p)
{
    char tRes = _f_1key_assert_para(pKey_p);
    if(0 > tRes ) {
        return tRes;
    }
    pKey_p->mVlu = (emKeyRespLvl_t)API_PRP_GPIO_PIN_RD(pKey_p->mGpioBank_p, pKey_p->mPin);
    return 0;

} //<static char _f_keys_poll_vlu(emLedId_t pID)>

static char _f_key_chk_click1st(sttKeyCtrl_t* pKey_p)
{
/*     
    char tRes = _f_1key_assert_para(pKey_p);
    if(0 > tRes ) {
        return tRes;
    }
 */
    s_key_vlus[KeyID_WkUp]  = (emKeyRespLvl_t)KEY_WKUP;
    //按键是空闲时，判断是否按下
    if(pKey_p->mDone == KeyDone_Idle){    
        _f_keys_callback_vlu(pKey_p); //扫描按键值    
        if( pKey_p->mVlu == pKey_p->mRespLvl){
            pKey_p->mDone    = KeyDone_Click1st; //记录该按键idle后的第一次按下       
        }        
    } //<if(pKey_p->mDone == KeyDone_Idle)>

    _f_keys_callback_vlu(pKey_p); //扫描按键值

    return 0;
} 

static char _f_key_chk_funcstart(sttKeyCtrl_t* pKey_p)
{
    char tRes = _f_1key_assert_para(pKey_p);
    if(0 > tRes ) {
        return tRes;
    }

    if(pKey_p->mDone == KeyDone_Click1st){ //按键第一次按下
        switch(pKey_p->mActMd){
            case KeyAct_Edge:
            case KeyAct_Level:            
                //消抖中
                if(pKey_p->mDeb_Cnt++ >= KEY_DEBOUNCE_MS){
                    _f_keys_callback_vlu(pKey_p); //扫描按键值
                    //按键仍然按下
                    if(pKey_p->mVlu == pKey_p->mRespLvl) {
                        pKey_p->mDone = KeyDone_FuncStart;  //消抖后确定按键是按下的
                        pKey_p->mDeb_Cnt = 0;     //消抖计数清零           
                    }//<if(pKey_p->mDeb_Cnt++ >= KEY_DEBOUNCE_MS)>

                    //按键已经释放,则复位此按钮
                    else{
                        app_samp_keys_reset(pKey_p,pKey_p->mID) ; //reset key status
                    }               
                }

                break;

            case KeyAct_ShortPress:
            case KeyAct_LongPress:
            case KeyAct_DoubleClick:
                break;
            default:
                break;

        }//<switch(pKey_p->mActMd){..}>      
    } //<if(pKey_p->mDone == KeyDone_Click1st)>

    return 0;
} 

/*********************************************************
 * @brief Handler a key`s ovrer
 * @param pKey_p: pointer to key control struct
 * @param pArg: pointer to argument
 * @return: 
 *   @arg 0: success; 
 *   @arg-1: invalid parameter; 
 *   @arg-2: invalid key ID; 
 *   @arg-3: invalid function pointer;
 * **********
 *  if(pKey_p->mDone == KeyDone_FuncOver){

    }//<if(pKey_p->mDone == KeyDone_FuncOver)>   
 ********************************************************/
static char _f_key_hdr_func_ovr(sttKeyCtrl_t* pKey_p,unsigned int tMs)
{
    char tRes = 0;
    if(NULL == pKey_p)           { return -1; }
    if(KeyID_Max <= pKey_p->mID) { return -2; }
//   if(NULL == pKey_p->mFunc)    { return -3; }
    
    _f_keys_callback_vlu(pKey_p);
    if(pKey_p->mVlu != pKey_p->mRespLvl) { //按键释放
        if(pKey_p->mDeb_Cnt++ > tMs * KEY_DEBOUNCE_MS){
            _f_keys_callback_vlu(pKey_p);
            if(pKey_p->mVlu != pKey_p->mRespLvl){ //消抖后,按键释放
                app_samp_keys_reset(pKey_p,pKey_p->mID) ; //reset key status
            //    app_kbk_send_rst(); //usbd-hid reset-report in sample_usbd_hid.c
            }                
        }
    } //<if(pKey_p->mVlu != pKey_p->mRespLvl) >   
	return 0;
} //<static char _f_key_hdr_func_ovr(sttKeyCtrl_t* pKey_p,unsigned int tMs)>


/****************************************************
 * @brief Poll a key
 * @param pKey_p: pointer to key control struct
 * @return:
 *    @arg 0: success;
 *    @arg-1: invalid parameter;
 **************************************************
    char tRes = _f_1key_assert_para(pKey_p);
    if(0 > tRes ) {
        return tRes;
    }
 ****************************************************/
static char _f_key_polldone_frame(sttKeyCtrl_t* pKey_p)
{


    switch(pKey_p->mDone){
        case KeyDone_Idle:
            _f_key_chk_click1st(pKey_p);
            break;

        case KeyDone_Click1st:
            _f_key_chk_funcstart(pKey_p);
            break;

        case KeyDone_FuncStart:
            pKey_p->mFunc(pKey_p->mArg);
            pKey_p->mDeb_Cnt = 0;     //消抖计数清零
            pKey_p->mDone    = KeyDone_FuncOver;  
            break;

        case KeyDone_FuncOver:
            _f_key_hdr_func_ovr(pKey_p,1); //20ms
            break;

        default:
            break;
    }
    
    return 0;
} //<static char _f_key_polldone_frame(sttKeyCtrl_t* pKey_p)>

/************************************************************
 * @brief Poll all keys
 * @param pKey_p: pointer to key control struct
 * @return:
 *    @arg 0: success;
 *    @arg-1: invalid parameter;
 * **********************************************

 ************************************************************/
char app_samp_allkeys_pollhdr(sttKeyCtrl_t* pKey_p)
{

    for(emKeyId_t tID = KeyID_Btn0; tID < KeyID_Max; tID++){
        _f_key_polldone_frame(&pKey_p[tID]);
    }

    return 0;
}

/************************************************************
 * @brief Poll a key
 * @param pKey_p: pointer to key control struct
 * @return:
 *    @arg 0: success;
 *    @arg-1: invalid parameter;
 * **********************************************

 ************************************************************/
char app_samp_1key_pollhdr(sttKeyCtrl_t* pKey_p)
{

   _f_key_polldone_frame(pKey_p);

    return 0;
}

///e<--keys api2 fifo-------------------------------------------------------------------


/************************************************************************
 * @brief Reset all keys' status
 * @param pKey_p: pointer to key control struct
 * @param pID: number of keys
 * @note:
 *     1,pID = KeyID_Max is valid that All keys are reseted
       2,MX_GPIO_Init() has __HAL_RCC_GPIOx_CLK_ENABLE()    ;
 * @return:
 *    @arg 0: success;
 *    @arg-1: invalid parameter;
 * @date:
 *    260417,V1,
****************************************************************************/
char app_samp_keys_reset(sttKeyCtrl_t* pKey_p,emKeyId_t pID)
{
    // 轮询读取按键状态，更新状态机
    unsigned char i = 0;
    if(NULL == pKey_p) {return -1;} //Invalid parameter
    if(pID > KeyID_Max) {return -2;} //Invalid parameter
    
    if(pID == KeyID_Max) {
        memcpy(pKey_p, _s_sample_keys_fac, sizeof(sttKeyCtrl_t) * KeyID_Max); //
    }
    else {
        if(IS_VALID_KEYID(pID)) {
        //   pKey_p[pID] = _s_sample_keys_fac[pID];
          memcpy(&pKey_p[pID] , &_s_sample_keys_fac[pID], sizeof(sttKeyCtrl_t)); //
        }
        else{
            return -2; //Invalid key ID
        }
    }
    
    return 0;
}

/*********************************************************************
 * @brief Init all keys
 * @param pKey_p: pointer to key control struct
 * @return:
 *    @arg 0: success;
 *    @arg-1: invalid parameter;
 *********************************************************************/
char app_samp_keys_init(sttKeyCtrl_t* pKey_p)
{
    emKeyId_t i= 0;
    char tRes = _f_allkeys_assert_para(pKey_p);
    if(0 != tRes){
        return tRes;
    }

    for( i = 0; i < KeyID_Max; i++){

       //s>--补齐_s_KeysCtrl_fac[i].mGpioInit_p-----
        if(pKey_p[i].mID == KeyID_WkUp){
            g_gpioinit_in_dn.Pin = pKey_p[i].mPin;
            _s_sample_keys_fac[i].mGpioInit_p = &g_gpioinit_in_dn ; //wkup is pulldown 
        }
        else{
            g_gpioinit_in_up.Pin = pKey_p[i].mPin;
            _s_sample_keys_fac[i].mGpioInit_p = &g_gpioinit_in_up  ; //others are pullup
        }
        //_s_sample_keys_fac[i].mGpioInit_p->Pin = _s_sample_keys_fac[i].mPin;
        //e<--补齐_s_KeysCtrl_fac[i].mGpioInit_p-----

  //      pKey_p[i] = _s_sample_keys_fac[i]; //复制
        memcpy(&pKey_p[i] , &_s_sample_keys_fac[i], sizeof(sttKeyCtrl_t)); //

    //    API_PRP_GPIO_INIT(pKey_p[i].mGpioBank_p, pKey_p[i].mGpioInit_p); // MX_GPIO_Init() has inited this process
        
    }

    //2. Copy keys' status
   // app_samp_keys_reset(pKey_p, KeyID_Max);

    return 0;
}

/********************************************
 * @brief Read key pin
 * @param pID: key ID
 * @return:
 *    @arg: G_GPIO_PIN_RST, Low level;
 *    @arg: G_GPIO_PIN_SET, High level;
 * @date:
 *    260501,V1,
 *******************************************/
EM_GPIO_PIN_STA_T  app_key_pin_rd(emKeyId_t pID)
{
    if(!IS_VALID_KEYID(pID)) {
        return -1; //Valid key ID
    }
    return API_PRP_GPIO_PIN_RD(_s_sample_keys_fac[pID].mGpioBank_p, _s_sample_keys_fac[pID].mPin);
}

/********************************************
 * @brief Read pins of a GPIO bank
 * @param pGpioBank_p: pointer to GPIO bank
 *    @arg: GPIOA~GPIOG
 * @return:
 *    @arg: G_GPIO_PIN_RST, Low level;
 *    @arg: G_GPIO_PIN_SET, High level;
 * @date:
 *    260501,V1,
 *******************************************/
int app_samp_gpio_bank_rd(STT_GPIO_BK_T *pGpioBank_p)
{
    unsigned char i = 0;
    uint8_t tPinVlu = 0;
    int tRes = 0;

    if(NULL == pGpioBank_p) {
        return -1; //invalid parameter
    }

    for(i = 0; i <= 15; i++){
        
        tPinVlu = API_PRP_GPIO_PIN_RD(pGpioBank_p, (uint16_t)(1 << i)) ? 1:0 ;
        if(tPinVlu){
          tRes |= (1 << i);
        }
    }
    return tRes;
} //<int app_samp_gpio_bank_rd(STT_GPIO_BK_T *pGpioBank_p)>

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
char app_samp_gpio_bank_wt(STT_GPIO_BK_T *pGpioBank_p, const uint16_t pPinVlu)
{
    unsigned char i = 0;
    uint8_t tVar = 0;

    if(NULL == pGpioBank_p) {
        return -1; //invalid parameter
    }
    
    if(pPinVlu > 1 << 15){
        return -2; //invalid parameter
    }

    for(i = 0; i <= 15; i++){
        
        tVar = (pPinVlu >> i) & 0x01;
        API_PRP_GPIO_PIN_WT(pGpioBank_p, (uint16_t)(1 << i), tVar);

    }
    return 0;
}

///s>--Keys custom-------------------------------------------------------------------------
/**************************************************
 * @brief BTN0按键,客制处理函数
 * @param pID: 按键ID
 * @param pArg: 参数
 * @return: 
 *   @arg 0: success; 
 *   @arg-1: invalid parameter; 
 *   @arg-2: invalid key ID; 
 *   @arg-3: invalid function pointer;
 * @date
 *    2026.4.18,v1.0,创建
 *************************************************/
__WEAK char app_custom_btn0(void* pArg)
{

    pArg = pArg;
		
/*    
   if(g_usbd_rdy){
   //     app_kbk_send_space(); //发送键盘空格键
        SYSRUN_LED_TGG();
    }
    else{
        return 0;
    }
 */
    SYSRUN_LED_TGG();

    return 0;
}

/**************************************************
 * @brief BTN1按键,客制处理函数
 * @param pID: 按键ID
 * @param pArg: 参数
 * @return: 
 *   @arg 0: success; 
 *   @arg-1: invalid parameter; 
 *   @arg-2: invalid key ID; 
 *   @arg-3: invalid function pointer;
 * @date
 *    2026.4.18,v1.0,创建
 *************************************************/
__WEAK char app_custom_btn1(void* pArg)
{

	pArg = pArg;
		
    return 0;
}

/**************************************************
 * @brief BTN1按键,客制处理函数
 * @param pID: 按键ID
 * @param pArg: 参数
 * @return: 
 *   @arg 0: success; 
 *   @arg-1: invalid parameter; 
 *   @arg-2: invalid key ID; 
 *   @arg-3: invalid function pointer;
 * @date
 *    2026.4.18,v1.0,创建
 *************************************************/
__WEAK char app_custom_btn2(void* pArg)
{

	pArg = pArg;
		
    return 0;
}


/**************************************************
 * @brief WKUP按键,客制处理函数
 * @param pID: 按键ID
 * @param pArg: 参数
 * @return: 
 *   @arg 0: success; 
 *   @arg-1: invalid parameter; 
 *   @arg-2: invalid key ID; 
 *   @arg-3: invalid function pointer;
 * @date
 *    2026.4.18,v1.0,创建
 *************************************************/
__WEAK char app_custom_wkup(void* pArg)
{

	pArg = pArg;
		
    return 0;
}
///e<--Keys custom-------------------------------------------------------------------------
///E<==Keys=====================================================================================



/***************validated items********************
void main( ) 
{
    CfgFsys( );                 //CH554时钟选择配置   
    mDelaymS(20);

    Port1Cfg(1,PIN_LED0);       //P10设置推挽模式
	  LED0 = 0;
	
    //Port3Cfg(3,PIN_BTN);        //P30设置类51模式，开漏输入输出，有上拉
	  app_samp_keys_init(&g_samp_keys);

	  mInitSTDIO( );              //必须加入，否则程序不允许串口0初始化
	  

    while(1){
      app_samp_hdr_keys(&g_samp_keys);

    }
}

//s>--item2--260418------------
      app_samp_hdr_keys(&g_samp_keys);
//e<--item1--260418------------   

//s>--item1--260415------------
		SYSRUN_LED_TGG();
		mDelaymS(300);		
//e<--item1--260415------------     

 ***************validated items********************/

 
/********************************************************************************
 * @brief       按键扫描函数
 * @note        该函数有响应优先级(同时按下多个按键): WK_UP > KEY2 > KEY1 > KEY0!!
 * @param       mode:0 / 1, 具体含义如下:
 *   @arg       0,  不支持连续按(当按键按下不放时, 只有第一次调用会返回键值,
 *                  必须松开以后, 再次按下才会返回其他键值)
 *   @arg       1,  支持连续按(当按键按下不放时, 每次调用该函数都会返回键值)
 * @retval      键值, 定义如下:
 *              KEY0_PRES, 1, KEY0按下
 *              KEY1_PRES, 2, KEY1按下
 *              KEY2_PRES, 3, KEY2按下
 *              WKUP_PRES, 4, WKUP按下
 ********************************************************************************/
uint8_t app_samp_getkeyvlu(uint8_t mode)
{
    static uint8_t key_up = 1;  /* 按键按松开标志 */
    uint8_t keyval = 0;

    if (mode) key_up = 1;       /* 支持连按 */

#if G_ATK_APL429IG_V1 == THIS_BOARD   
    if (key_up && (WKUP || KEY0 == 0 || KEY1 == 0 || KEY2 == 0))  /* 按键松开标志为1, 且有任意一个按键按下了 */
    {
        stkdly_ms(15);           /* 去抖动 */
        key_up = 0;

        if (KEY0 == 0) {
					 keyval = KEY0_PRES;

        }else if (KEY1 == 0){
					 keyval = KEY1_PRES;

        }else if (KEY2 == 0){
					 keyval = KEY2_PRES;
			
			  }else if(WKUP == 1){
					 keyval = WKUP_PRES;
					
				}else {
           keyval = NONE_PRES;
					
        }					
    }
    else if (WKUP == 0 && KEY0 == 1 && KEY1 == 1 && KEY2 == 1)         /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }
		
#elif G_ATK_DMF407IG == THIS_BOARD
    if (key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0))  /* 按键松开标志为1, 且有任意一个按键按下了 */
    {
        stkdly_ms(15);           /* 去抖动 */
        key_up = 0;

        if (KEY0 == 0) {
					 keyval = KEY0_PRES;

        }else if (KEY1 == 0){
					 keyval = KEY1_PRES;

        }else if (KEY2 == 0){
					 keyval = KEY2_PRES;
					
				}else {
           keyval = NONE_PRES;
					
        }					
    }
    else if (KEY0 == 1 && KEY1 == 1 && KEY2 == 1)         /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }	
#endif //<#if G_ATK_APL429IG_V1 == THIS_BOARD  >	
	
    return keyval;              /* 返回键值 */
}//<u8_t key_scan(uint8_t mode)>

/*************************************************
 * 
 * 
 * 
 ***************************************************/
char app_samp_allkeys_scan(uint8_t mode)
{
    uint8_t tKeyVlu = 0;
    tKeyVlu = app_samp_getkeyvlu(mode);
    switch(tKeyVlu){
        case KEY0_PRES:
            RED_LED_ON();
            break;

        case KEY1_PRES:
            RED_LED_OFF();
            break;
        case KEY2_PRES:
            printf("KEY2_PRES\r\n");
            break;

        case WKUP_PRES:
            printf("WKUP_PRES\r\n");
            break;

        default:
            break;
    }

    return 0;
}