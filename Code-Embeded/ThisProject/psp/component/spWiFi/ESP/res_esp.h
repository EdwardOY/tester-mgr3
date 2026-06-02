/******************************************************************************************************
 * @file        res_esp.h
 * @author      Edwoy
 * @version     V1.0
 * @date        2021-10-27
 * @brief       Bluetooth&BLE resource header
 * @license     Copyright (c) 2020-2032
 ****************************************************************************************************
 * @attention
 ****************************************************************************************************
 * @note
 *    1 Default hard
          platform: ATK-DMF407
          module : Esp8266 of 
 ****************************************************************************************************
 * @update
     V2.0 add mqtt
 *   V1.0 
 *
 ****************************************************************************************************
 */

#ifndef _RES_ESP_H_
#define _RES_ESP_H_
#include "ThisProj_Glb.h"
#include RES_UART_HEAD
#include RES_WIFI_UART_HEAD
#include UTY_WIFI_HEAD  // "./component/spWiFi/UTY/utyWiFi.h"

///==ESP->paras==============================================================================================
#define __DlyMs_Esp    (uint8_t)70

//---WiFidev_RstGpio------------------------------------------------------------------------------
#define WIFI_RST_GPIO_PORT           GPIOI
#define WIFI_RST_GPIO_PIN            GPIO_PIN_10
#define WIFI_RST_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOI_CLK_ENABLE()
#define WIFI_RST_GPIO(x)    do{ x ?                                                                      \
																HAL_GPIO_WritePin(WIFI_RST_GPIO_PORT, WIFI_RST_GPIO_PIN, GPIO_PIN_SET) :  \
																HAL_GPIO_WritePin(WIFI_RST_GPIO_PORT, WIFI_RST_GPIO_PIN, GPIO_PIN_RESET); \
                            }while(0)

#define WIFI_RST_EN()       WIFI_RST_GPIO(0)  
#define WIFI_RST_DIS()      WIFI_RST_GPIO(1)  
//--End WiFidev_RstGpio-------------------------------------------------------------------End-----	
														
//--DownloadGpio----------------------------------------------------------------------------------										
#define WIFI_MODE_GPIO_PORT           GPIOI
#define WIFI_MODE_GPIO_PIN            GPIO_PIN_11
#define WIFI_MODE_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOI_CLK_ENABLE()
#define WIFI_MODE_GPIO(x)    do{ x ?                                                                      \
																HAL_GPIO_WritePin(WIFI_MODE_GPIO_PORT, WIFI_MODE_GPIO_PIN, GPIO_PIN_SET) :  \
																HAL_GPIO_WritePin(WIFI_MODE_GPIO_PORT, WIFI_MODE_GPIO_PIN, GPIO_PIN_RESET); \
                            }while(0)

#define WIFI_MODE_DOWNLOAD()   WIFI_MODE_GPIO(0) //when download espdev firmware
#define WIFI_MODE_WORK()       WIFI_MODE_GPIO(1) // when espdev runs(serialnet or mqtt ...)		
//--End DownloadGpio-----------------------------------------------------------------------End-----													
///---End ESP-dev-gpio--------------------------------------------------------------------------------End---

//---ESP-dev-paras---------------------------------------------------------------------------------
//CWMODE para,called by app_esp_set_cwmode in esp8266.c
typedef enum{
	EspCWM_Sta   = 1, //TCP-Client,station
	EspCWM_Ap    = 2, //TCP-Server,soft AP
	EspCWM_StaAp = 3, // UDP,station & soft AP
}emEsp8266CWMODE_t;
#define IS_VALID_CWMODE_ESP(x)   ((EspCWM_Sta == x) || (EspCWM_Ap == x) || (EspCWM_StaAp == x))

//Espdev links RouterAP AutoConnection-Mode Parameters
typedef enum{
	SmtCfg_Disable          = 0, //unuse smartconfig,usr link route-ap manually
	SmtCfg_EspTouch         = 1, //only use EspTouch app
	SmtCfg_AirKiss          = 2, //only use wechat->Ai-Thinker
	SmtCfg_EspTouchAirKiss  = 3, //EspTouch app and wechat->Ai-Thinker
	SmtCfg_EspTouchV2       = 4, 
}emEspSmartConfig_t;
#define IS_VALID_SMTCFG_ESP(x)  ((SmtCfg_EspTouch == x) || (SmtCfg_AirKiss == x) ||  \
                                 (SmtCfg_EspTouchAirKiss == x) || (SmtCfg_EspTouchV2 == x))
//---end ESP-dev-paras-------------------------------------------------------------------------end---
///==End ESP->paras=====================================================================================End====

///==MQTT->paras================================================================================================
//--mqtt->thing-communi cation titlestring------------------------------------------------------------
#define MQTT_STR_SYS    "/sys/"
#define MQTT_STR_LINK1   "/"
#define MQTT_STR_TOP     "/thing/event/property/"
#define MQTT_STR_POST    "post"
#define MQTT_STR_REPLY   "post_reply"
#define MQTT_STR_SET     "set"
#define MQTT_STR_PUBEND  "\\,\\\"version\\\":\\\"1.0.0\\\"}\",1,0\r\n"
//--end mqtt->thing-communication titlestring--------------------------------------------------end---

#define __DlyMs_Mqtt   (uint16_t)400

typedef enum{
	Mqtt_Disconn = 0, //Mqtt disconnect
	Mqtt_Conn    = 1, //Mqtt connect
	Mqtt_IsSubs  = 2, //Mqtt subscribes msg from hosturl successfully
}emMqttState_t;

typedef struct {
	char devname[36];
	char ssid[16];
	char pwd_ap[16];
	char cipsntp[24];
	char productkey[24];
	char mqtt_usr[36];
  char mqtt_pwd[128];	
	char hosturl[72];
	char clientid [160];
	
	//Topic:user-defined: check Public examples-> product-> topic lists->user-defined
  char topic_usr_subs[64];	
	char topic_usr_pub[64];
	
  //Topic: thing->property post: check Public examples-> product-> topic lists-> thing-model
  char topic_tpp_subs[64]; 
	char topic_tpp_pub[64]; 

  //Topic: thing->property set: check Public examples-> product-> topic lists-> thing-model
  char topic_tpset[64]; 
	
	emEspSmartConfig_t  smartconfig;
	emEsp8266CWMODE_t   sta_cwm ;
	emWIFI_DevState_t   sta_dev;
	emMqttState_t       sta_mqtt;
}sttMqtt_DevParas_t;

///--exp0,(validated)-----------------------------------------------------------------------------------
//TB1->broker1{product:wifi-iot; device: esp8266}
extern sttMqtt_DevParas_t g_atkmoudle_esp_dev0 ;
///--end exp0 -----------------------------------------------------------------------------------end----

///--exp1,(validated)-----------------------------------------------------------------------------------
//TB1->broker2{product:product1; device: adcdev1}
extern sttMqtt_DevParas_t g_atkmoudle_esp_dev1 ;
///--end exp1 -----------------------------------------------------------------------------------end----

///--exp3,(validated)-----------------------------------------------------------------------------------
//TB1->broker3{product:smarthome1; device: home1}
extern sttMqtt_DevParas_t g_atkmoudle_mqttdev_home1;

//identifiers of thing	
extern const char* thing_idr1;
extern float current  ;

extern const char* thing_idr2;
extern float volt     ;

//true-->open; false-->close
extern const char* thing_idr3;
extern uint8_t pwrswh    ; 

extern const char* thing_idr4;
extern uint8_t temperature ;
		
///--end exp3 -----------------------------------------------------------------------------------end----

///--exp4,(validating...)-------------------------------------------------------------------------------
//TB1->broker3{product:smarthome1; device: home1}
extern sttMqtt_DevParas_t g_atkmoudle_mqttdev_airdtr1;

/**
  * 1 idr == identifier
  * 2 var == variable
  * 3 temp == temperature
  * 4 hmd  ==  humidity
  */
//true-->open; false-->close
extern const char thing_swh_idr[];
extern uint8_t     thing_swh_var;

extern sc8_t  thing_SO2_idr[];
extern float  thing_SO2_var ;

extern sc8_t  thing_temp_idr[];
extern int    thing_temp_var;

extern sc8_t  thing_hmd_idr[];
extern int    thing_hmd_var  ;

extern sc8_t  thing_HCHO_idr[];
extern float  thing_HCHO_var ;

extern sc8_t   thing_pm2p5_idr[];
extern u8_t    thing_pm2p5_var ;

///--end exp4 ----------------------------------------------------------------------------------end----

///--mqtt-exp5,(validated)-----------------------------------------------------------------------------------
//TB1->broker5{product:smarthome2; device: SmartLight1}
//exp5,
//Communication between ÔÆÖÇÄÜapp on Aliyun Living IoT and target board(ATK-DMF407)
// https://living.aliyun.com/project/a123DkwaszFiH6aA/dev/product/a1L8UZw4OZc/productdetail
extern sttMqtt_DevParas_t g_atkmoudle_mqttdev_smtlgt1  ;

/*******************************************
  * 1 idr == identifier
  * 2 var == variable
  * 3 temp == temperature
  * 4 hmd  ==  humidity
  * thg == thing
  ******************************************/
//validated Aliyun Living IoT thing->property
//true-->open; false-->close
extern const char thg5_swh_idr[] ; 
extern     uint8_t thg5_swh_var;  

//thing property: brightness
extern const char  thg5_lux_idr[] ;
extern uint16_t     thg5_lux_var ; //Lux

extern const char thg5_clrtemp_idr[] ;
extern int        thg5_clrtemp_var;  // Kelvin

typedef struct _rgbpara {int Red; int Green; int Blue; } sttTHG5_RGBvar_t;
extern const char thg5_RGB_idr[] ;
extern sttTHG5_RGBvar_t thg5_RGB_var ;

typedef struct _localtimer {char Timer[48]; uint8_t Enable; uint8_t IsValid; } sttLocTim_t;
extern const char thg5_loctim_idr[] ;
extern sttLocTim_t  thg5_loctim_var ;  


///--end mqtt-exp5 ----------------------------------------------------------------------------------end----


///==End MQTT->paras=====================================================================================End====

#endif
/*----Endline : Full file-------------------------------------------------------------------------------All_End-----*/																		 