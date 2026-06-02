/**
 ****************************************************************************************************
 * @file        atk_mw8266d.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ESPDev模块驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 F407电机开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#ifndef _ESP8266_H_
#define _ESP8266_H_

#include "./SYSTEM/sys/sys.h"
#include "./component/spWiFi/ESP/resdrv_iot_uart.h"  //"./BSP/ATK_MW8266D/atk_mw8266d_uart.h"
#include "./component/spWiFi/UTY/utyWiFi.h"
#include "./component/spWiFi/ESP/res_esp.h"

void app_esp_devgpios_init(void);

/* 操作函数 */
void app_espdev_hdrst(void);                                            /* ESPDev硬件复位 */
uint8_t app_esp_send_at_cmd(char *cmd, char *ack, uint32_t timeout);    /* ESPDev发送AT指令 */
uint8_t app_atkmodule_esp_init(void);                                /* ESPDev初始化 */
uint8_t app_espdev_restore(void);                                          /* ESPDev恢复出厂设置 */
uint8_t app_esp_at_test(void);                                          /* ESPDev AT指令测试 */
uint8_t app_esp_set_cwmode(emEsp8266CWMODE_t mode);                                 /* 设置ESPDev工作模式 */
uint8_t app_espdev_sftrst(void);                                         /* ESPDev软件复位 */
uint8_t app_esp_ate_config(uint8_t cfg);                                /* ESPDev设置回显模式 */
uint8_t app_esp_link_ap(char *ssid, char *pwd, uint16_t);                         /* ESPDev连接WIFI */
uint8_t app_esp_get_ip(char *buf);                                      /* ESPDev获取IP地址 */
uint8_t app_esp_connect_tcp_server(char *server_ip, char *server_port); /* ESPDev连接TCP服务器 */
uint8_t app_esp_enter_serialnet(void);                                /* ESPDev进入透传 */
void app_esp_exit_serialnet(void);                                    /* ESPDev退出透传 */
uint8_t app_esp_connect_atkcld(char *id, char *pwd);                    /* ESPDev连接原子云服务器 */
uint8_t app_esp_disconnect_atkcld(void);                                /* ESPDev断开原子云服务器连接 */

/*********************************************************************************
 * @brief  (validated)Poll-proccess for UART/USART rx of LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           used to test atkmodule_uartrx in intterupt  
 * @param  void
 * @retval void
 *********************************************************************************/
uint8_t app_atkmodule_uartrxmsg_poll();

///--drv-v2---------------------------------------------------------------------------------
/************************************************************************************
 * @brief (validated) pubulish Json-msg to hosturl ver2         
 * @param  mqttdev
           expBroker1-->publish.topic "/a1QSdqL2OX7/esp8266/user/update"
 * @notice
     -2-,add '\' before ','
     -1-,expBroker1,https://iot.console.aliyun.com/devices/a1QSdqL2OX7/esp8266/1 
         check the custom publish-topic from Topic list
 * @retval  Err_WIFI_NONE  : success
 *          Err_WIFI_ERROR: fail
 ***************************************************************
	ret = app_esp_send_at_cmd(cmd,"OK", __DlyMs_Mqtt);

  app_mqtt_publish_freemsg("/a1QSdqL2OX7/esp8266/user/update","targetBoard testmsg");
 ************************************************************************************/
uint8_t app_mqtt_publish_usrmsg(sttMqtt_DevParas_t* mqttdev,char* msg);
	
/*********************************************************
 * @brief (validating...) Send cmd by dbcom
           wether got ip
 * @param  mqttdev
 * @retval  
 * @notice 

 *********************************************************/
void etf_dbcomtsk_esp(sttMqtt_DevParas_t* mqttdev);

/********************************************
 * @brief   (validating...) smartconfig to RouteAP
 * @param   smt,check emEspSmartConfig_t in res_esp.h
 * @retval   
 * @notice 
 *******************************************/
uint8_t app_esp_smartconfig(sttMqtt_DevParas_t*);

/**********************************************************
 * @brief   (validating...) stop smartconfig 
       Purpose: Release the memory of espdev 
       to prevent it from being occupied by smartconfig  
 * @param   smt,check emEspSmartConfig_t in res_esp.h
 * @retval   
 * @notice 
 ******************************************************
 *********************************************************/
uint8_t app_esp_stop_smartconfig(sttMqtt_DevParas_t* mqttdev);


/************************************************************************
 * @brief  (validating...) enable or disable auto-connect network			
 * @param  swh,switch
             Ture-->enable auto-connect network
             False-->disable auto-connect network	
 * @retval      无
 * @notice 
 ******************************************************
 *************************************************************************/
uint8_t app_esp_autoconn_swh(bool swh);

#define app_esp_autoconn_enable()   app_esp_autoconn_swh(true)
#define app_esp_autoconn_disable()  app_esp_autoconn_swh(false)	
	
/*********************************************************
 * @brief (validating...) check wether espdev got IP
           wether got ip
 * @param  mqttdev
 * @retval  
 * @notice 
 *********************************************************/
emWIFI_DevState_t app_espdev_linksta_poll(sttMqtt_DevParas_t* mqttdev);

/********************************************
 * @brief  (validating...) check netwwork-linking status	
 * @param  swh,switch
             Ture-->enable auto-connect network
             False-->disable auto-connect network	
 * @retval      无
 * @notice 
 *******************************************/
emWIFI_DevState_t app_esp_cipstatus(sttMqtt_DevParas_t* mqttdev);

/********************************************
 * @brief  (validating...) netwwork-linking status poll 
 * @param  swh,switch
             Ture-->enable auto-connect network
             False-->disable auto-connect network	
 * @retval      无
 * @notice 

 *******************************************/
uint8_t etf_tskpoll_mqttstatus(sttMqtt_DevParas_t* mqttdev);



/********************************************************************
 * @brief  (validated)ESPDev恢复出厂设置
 * @param       无
 * @retval      Err_WIFI_NONE  : 恢复出场设置成功
 * @notice  
       -1-,Once this operation is performed, 
          all wifi configs in espdev will be cleared
       -2-,need delay >= 400ms
 **************************************************************

 ********************************************************************/
emWIFI_DevState_t app_espdev_restore_v2(sttMqtt_DevParas_t* mqttdev);

/*****************************************************************
 * @brief (validating...) Reset ESPDev using codes
           [+] app_esp_cipstatus(mqttdev);
 * @param  mqttdev,
           cipsta,Switch network-linking judgment
           wether add app_esp_cipstatus(mqttdev)?    
                false--> no  
                others--> yes
 * @retval  
       -1-,cipsta = true,emWIFI_DevState_t
       -2-,cipsta = false,
         Err_WIFI_NONE  : 软件复位成功
         Err_WIFI_ERROR: 软件复位失败
 * @notice 
       -1-,need delay more time
 ***************************
 *******************************************************************/
emWIFI_DevState_t app_espdev_sftrst_v2(sttMqtt_DevParas_t* mqttdev);

/********************************************************************
 * @brief  (validated)ESPDev links RouteAP
           [+] smartconfig
 * @param  mqttdev
 * @retval      Err_WIFI_NONE  : WIFI is link
 *              Err_WIFI_ERROR: WIFI is unlink
 * @notice
     The prerequisite for connecting to AP 
     is to successfully set the cwmode first
 *******************************************************************/
uint8_t app_esp_link_ap_v2(sttMqtt_DevParas_t* mqttdev,uint16_t);

/**********************************************************************
 * @brief (validating...) init mqtt ,[+] smartconfig
          (Recommended) 
 * @param mqttdev
 * @return 
 ************************************************ 
  ret = app_esp_link_ap(mqttdev->ssid, mqttdev->pwd_ap,0); // ("EDW201X","txhd349874");	
 **********************************************************************/						
uint8_t app_mqtt_init_v2(sttMqtt_DevParas_t* mqttdev);

///--end drv-v2---------------------------------------------------------------------------end----

///==MQTT============================================================================================
///--MQTTdrvs------------------------------------------------------------------------------------
/************************************************************************
 * @brief   config MQTT-CIPSNTP
 * @param   cip,MQTT-CIPSNTP
              "ntp1.aliyun.com" , Aliyun   
 ************************************************************************/
uint8_t app_mqtt_cfg_cipsntp(char* cip);

/************************************************************************************
 * @brief  config MQTT-USER
           
 * @param  username,exp1-->"esp8266&a1QSdqL2OX7"
           password,exp1-->
              "5569e8ebe8c0da77826a95d3078853455360e9c78b1ef2e4a6dd81db876856f4"  
 * @notice
     -1-,client_id is fixed "NULL"
     -2-,exp1,https://iot.console.aliyun.com/devices/a1QSdqL2OX7/esp8266/1
         prodect--> wifi-iot ; device-->esp8266
         check the MQTT connection parameters 
 ************************************************************************************/
uint8_t app_mqtt_cfg_usr(char* username,char* password);

/************************************************************************************
 * @brief  config MQTT-Client id only using in Aliyun
           
 * @param  client_id,expBroker1-->
     "a1QSdqL2OX7.esp8266|securemode=2\,signmethod=hmacsha256\,timestamp=1684598696978|"

 * @notice
     -2-,add '\' before ','
     -1-,expBroker1,https://iot.console.aliyun.com/devices/a1QSdqL2OX7/esp8266/1 
         check the MQTT connection parameters 
 * @retval  Err_WIFI_NONE  : success
 *          Err_WIFI_ERROR: fail
 ************************************************************************************/
uint8_t app_mqtt_cfg_clientid(char* client_id);

/************************************************************************************
 * @brief  connect MQTT-hosturl
           
 * @param  host,expBroker1-->
         "a1QSdqL2OX7.iot-as-mqtt.cn-shanghai.aliyuncs.com" 
 * @notice
     -2-,add '\' before ','
     -1-,expBroker1,https://iot.console.aliyun.com/devices/a1QSdqL2OX7/esp8266/1 
         check the "mqttHostUrl" of MQTT connection parameters 
 * @retval  Err_WIFI_NONE  : success
 *          Err_WIFI_ERROR: fail
 ************************************************************************************/
uint8_t app_mqtt_conn_host(char* host);

/************************************************************************************
 * @brief  config subscribe for espdev getting msg from hosturl
 * @param  topic,subscribe-topic 
           expBroker1-->"/a1QSdqL2OX7/esp8266/user/get"
 * @notice
     -2-,add '\' before ','
     -1-,expBroker1,https://iot.console.aliyun.com/devices/a1QSdqL2OX7/esp8266/1 
         check the custom subscribe-topic from Topic list

 * @retval  Err_WIFI_NONE  : success
 *          Err_WIFI_ERROR: fail
 ***************************************************************
  app_mqtt_cfg_subs("/a1QSdqL2OX7/esp8266/user/get");
 ************************************************************************************/
uint8_t app_mqtt_cfg_subs(char* topic);

/************************************************************************************
 * @brief  pubulish Json-msg to hosturl           
 * @param  topic,publish-topic 
           expBroker1-->"/a1QSdqL2OX7/esp8266/user/update"
 * @notice
     -2-,add '\' before ','
     -1-,expBroker1,https://iot.console.aliyun.com/devices/a1QSdqL2OX7/esp8266/1 
         check the custom publish-topic from Topic list
 * @retval  Err_WIFI_NONE  : success
 *          Err_WIFI_ERROR: fail
 ***************************************************************
  app_mqtt_publish_freemsg("/a1QSdqL2OX7/esp8266/user/update","targetBoard testmsg");
 ************************************************************************************/
uint8_t app_mqtt_publish_freemsg(char* topic,char* msg);

/***********************************************************************************
 * @brief
 * @param void
 * @return void
 
 *******************************************************************************
//step2,optional,restore the espdev------------------------------------------- 		
    ret  += app_espdev_restore();   
		app_atkmodule_uartrxmsg_poll();
		
//step3,optional,AT cmd test--------------------------------------------------  		
    ret += app_esp_at_test();    
    app_atkmodule_uartrxmsg_poll();
************************************************************************************/								
uint8_t app_atkmodule_mqtt_init(char* username, char* password);

/**********************************************************************
 * @brief (validating...) init mqtt 
 * @param void
 * @return void
 
 **********************************************************************/						
uint8_t app_mqtt_init(sttMqtt_DevParas_t* mqttdev);

/************************************************************************************
 * @brief (validating...) config mqttdev`s thing->property set    
 * @param  topic,publish-topic 
           expBroker4-->"AirDetector1&a1myOVcUdQi"
 * @notice
     -2-,https://www.bilibili.com/video/BV1j14y1M7BG/?spm_id_from=
        333.337.search-card.all.click&vd_source=08eea1805655250a87b323b6cedd4b01
        12:50
     -1-,expBroker4,https://iot.console.aliyun.com/product/productDetail/a1myOVcUdQi?current=2
         check the thing communication topic from Topic class list
 * @retval  Err_WIFI_NONE  : success
 *          Err_WIFI_ERROR: fail
 ***************************************************************

 ************************************************************************************/
uint8_t app_mqtt_tpset(sttMqtt_DevParas_t* mqttdev);

//--from paidaxin`s friend--------------------------------------------------------------
/************************************************************************************
 * @brief (validated) pubulish Json-msg of tpp(thing property post) to hosturl 
           only used for int/char/bool type thing property
 * @param  topic,publish-topic 
              exp Broker3-->"/sys/a1BQHA5vPYl/home1/thing/event/property/post"
           identifier,
           var,
 * @notice
     -1-,expBroker3,https://iot.console.aliyun.com/devices/a1BQHA5vPYl/home1/1 	
         check the thing module topic from Topics list
 * @retval  Err_WIFI_NONE  : success
 *          Err_WIFI_ERROR: fail
 ***************************************************************
 valid SSCOM-cmd--> AT+MQTTPUB=0,"/sys/a1myOVcUdQi/AirDetector1/thing/event/property/post",
                   "{\"params\":{\"Humidity\":50}\,\"version\":\"1.0.0\"}",1,0
 ******************************************************************************
 ************************************************************************************/
uint8_t app_mqtt_publish_tppint(sttMqtt_DevParas_t* mqttdev, const char* identifier, int* var);

/************************************************************************************
 * @brief (validated) pubulish Json-msg of tpp(thing property post) to hosturl 
           only used for float type thing property
 * @param  topic,publish-topic 
              exp Broker3-->"/sys/a1BQHA5vPYl/home1/thing/event/property/post"
           identifier,
           var,
 * @notice
     -1-,expBroker3,https://iot.console.aliyun.com/devices/a1BQHA5vPYl/home1/1 	
         check the thing module topic from Topics list
 * @retval  Err_WIFI_NONE  : success
 *          Err_WIFI_ERROR: fail
 ***************************************************************
 valid SSCOM-cmd--> AT+MQTTPUB=0,"/sys/a1myOVcUdQi/AirDetector1/thing/event/property/post",
                   "{\"params\":{\"Humidity\":50}\,\"version\":\"1.0.0\"}",1,0
 ******************************************************************************
 ************************************************************************************/
uint8_t app_mqtt_publish_tppflt(sttMqtt_DevParas_t* mqttdev, const char* identifier, float* var);

/**********************************************************************
 * @brief (validated) Analyze message from Aliyun Ling App(云智能)
           only used for int/char/bool type thing var 
          (Recommended) 
         exp4,https://iot.console.aliyun.com/product/productDetail/a1myOVcUdQi
 * @param mqttdev
 * @return 
 * @attention
       -1-,don`t add app_atkmodule_uartrx_rst()
           don`t add app_atkmodule_uartrxmsg_poll();
 ************************************************ 
 *******************************************************

 **********************************************************************/					
void app_mqtt_alyzmsg_livingapp_swh(sttMqtt_DevParas_t* mqttdev,const char* identifier, int* var);

//--end from paidaxin`s friend-----------------------------------------------------end---

///--End MQTTdrvs-------------------------------------------------------------------End----

///--MQTTapps------------------------------------------------------------------------------
void app_mqtt_alyzmsg_webapp_swh(sttMqtt_DevParas_t* mqttdev);
///--End MQTTapps--------------------------------------------------------------------End---

///==End MQTT================================================================================End====

#endif
/*----Endline : Full file-------------------------------------------------------------------------------All_End-----*/		