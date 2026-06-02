/******************************************************************************************************
 * @file        res_esp.c
 * @author      Edwoy
 * @version     V2.0
 * @date        2021-10-27
 * @brief       Bluetooth&BLE resource src 
 * @license     Copyright (c) 2020-2032
 ****************************************************************************************************
 * @attention
      -1-,clientid, 
			     Add '\\' before ',' in codes;
			     Add '\' before ',' in COM assist tool;
			-2-, Mqtt network-portnumber is 1883 fixed    
      -3-, thing property identifier must be char array instead of  pointer
 ****************************************************************************************************
 * @note
 *    1 Default hard
          platform: ATK-DMF407
          module : Esp8266 of ESP
 ****************************************************************************************************
 * @update
 *   V2.0 add mqtt
 *
 ****************************************************************************************************
 */

#include "ThisProj_Glb.h"
#include UART_HEAD
#include RES_CAT1_HEAD

///==Mqtt-devs-paras===========================================================================================
///--mqtt-exp1,(validated)-----------------------------------------------------------------------------------
//TB1->broker1{product:wifi-iot; device: esp8266}
//Aliyun iot platform user-defined 
//https://iot.console.aliyun.com/devices/a1QSdqL2OX7/esp8266/1
sttMqtt_DevParas_t g_atkmoudle_esp_dev0 = {
	.devname   = {"esp8266"}, //espdev0
	.ssid      = {"EDW201X"},
	.pwd_ap    = {"txhd349874"},
	.cipsntp   = {"ntp1.aliyun.com"},
	.productkey = {"a1QSdqL2OX7"},		
	.mqtt_usr  = {"esp8266&a1QSdqL2OX7"},
	.mqtt_pwd  = {"5569e8ebe8c0da77826a95d3078853455360e9c78b1ef2e4a6dd81db876856f4"},
	.clientid  = {"a1QSdqL2OX7.esp8266|securemode=2\\,signmethod=hmacsha256\\,timestamp=1684598696978|"},
	.hosturl   = {"a1QSdqL2OX7.iot-as-mqtt.cn-shanghai.aliyuncs.com"},
	.topic_usr_subs = {"/a1QSdqL2OX7/esp8266/user/get"},	
  .topic_usr_pub  = {"/a1QSdqL2OX7/esp8266/user/update"},	
	.sta_dev = CAT1_Disconnect,
	.sta_cwm = EspCWM_Sta,
	.sta_mqtt = Mqtt_Disconn,
	.smartconfig = SmtCfg_EspTouchAirKiss,
};
///--end mqtt-exp1 -----------------------------------------------------------------------------------end----

///--mqtt-exp2,(validated)-----------------------------------------------------------------------------------
//TB1->broker2{product:product1; device: adcdev1}
//Aliyun iot platform user-defined 
//https://iot.console.aliyun.com/devices/a1OL5KrWqJA/adcdev1/1
sttMqtt_DevParas_t g_atkmoudle_esp_dev1 = {
	.devname   = {"adcdev1"},	 //espdev1
	.ssid      = {"EDW201X"},
	.pwd_ap    = {"txhd349874"},
	.cipsntp   = {"ntp1.aliyun.com"},
	.productkey = {"a1OL5KrWqJA"},		
	.mqtt_usr  = {"adcdev1&a1OL5KrWqJA"},
	.mqtt_pwd  = {"24b4d2d3c476912e0e685786eed41f46c67138d4e3fdd24498ca0da43c5ccaee"},
	.clientid  = {"a1OL5KrWqJA.adcdev1|securemode=2\\,signmethod=hmacsha256\\,timestamp=1685174658300|"},
	.hosturl   = {"a1OL5KrWqJA.iot-as-mqtt.cn-shanghai.aliyuncs.com"},
	.topic_usr_subs = {"/a1OL5KrWqJA/adcdev1/user/get"},	
  .topic_usr_pub  = {"/a1OL5KrWqJA/adcdev1/user/update"},	
	.sta_dev = CAT1_Disconnect,
	.sta_cwm = EspCWM_Sta,
	.sta_mqtt = Mqtt_Disconn,
	.smartconfig = SmtCfg_EspTouchAirKiss,
};

///--end mqtt-exp2 -----------------------------------------------------------------------------------end----

///--mqtt-exp3,(validated)-----------------------------------------------------------------------------------
//TB1->broker3{product:smarthome1; device: home1}
//Communication between Webapp(Aliyun IoT Studio) and target board(ATK-DMF407)
//https://iot.console.aliyun.com/devices/a1BQHA5vPYl/home1/1
//https://studio.iot.aliyun.com/web/a123dTTZzeeGYWLQ/app/a120MRCRN57qCetJ/edit
sttMqtt_DevParas_t g_atkmoudle_mqttdev_home1 = {
	.devname   = {"home1"},	
	.ssid      = {"EDW201X"},
	.pwd_ap    = {"txhd349874"},
	.cipsntp   = {"ntp1.aliyun.com"},
	.productkey = {"a1BQHA5vPYl"},	
	.mqtt_usr  = {"home1&a1BQHA5vPYl"},
	.mqtt_pwd  = {"8d4fe91dd32ba4152fb9e889b74c3963ff2ff0aebdb56eaf7f998e86d1e7c860"},
	.clientid  = {"a1BQHA5vPYl.home1|securemode=2\\,signmethod=hmacsha256\\,timestamp=1686147606761|"},
	.hosturl   = {"a1BQHA5vPYl.iot-as-mqtt.cn-shanghai.aliyuncs.com"},
	.topic_usr_subs = {"/a1BQHA5vPYl/home1/user/get"},	
  .topic_usr_pub  = {"/a1BQHA5vPYl/home1/user/update"},	
  .topic_tpp_subs = {"/sys/a1BQHA5vPYl/home1/thing/event/property/post_reply"},
	.topic_tpp_pub  = {"/sys/a1BQHA5vPYl/home1/thing/event/property/post"},
	.sta_dev = CAT1_Disconnect,
	.sta_cwm = EspCWM_Sta,
	.sta_mqtt = Mqtt_Disconn,
	.smartconfig = SmtCfg_EspTouchAirKiss,
};

//validated AliyunIoT platform thing->property
//identifiers of thing	
const char* thing_idr1 = "LightCurrent";
float current          = 0.22;

const char* thing_idr2 = "LightVolt";
float volt             = 3.27;

//true-->open; false-->close
const char* thing_idr3 = "PowerSwitch_1";
uint8_t pwrswh          = 0 ; 

const char* thing_idr4 = "temperature";
uint8_t temperature     = 29;

///--end mqtt-exp3 -----------------------------------------------------------------------------------end----

///--mqtt-exp4,(validated)-----------------------------------------------------------------------------------
//TB1->broker4{product:AirDetector1; device: AirDetector1}
//exp4,//https://iot.console.aliyun.com/devices/a1myOVcUdQi/AirDetector1/1
//Communication between 云智能app on Aliyun Living IoT and target board(ATK-DMF407)
//https://living.aliyun.com/project/a123DkwaszFiH6aA/dev/product/a1myOVcUdQi/productdetail
sttMqtt_DevParas_t g_atkmoudle_mqttdev_airdtr1 = {
	.devname   = {"AirDetector1"},	//空气检测仪
	.ssid      = {"EDW201X"},
	.pwd_ap    = {"txhd349874"},
	.cipsntp   = {"ntp1.aliyun.com"},
	.clientid  = {"Edwoy|securemode=3\\,signmethod=hmacsha256|"}, //generated by "阿里云物联平台配置 32.exe",本例使用哈希256加密方式 
	
	.productkey = {"a1myOVcUdQi"},	
	.mqtt_usr  = {"AirDetector1&a1myOVcUdQi"},
	
	 //mqtt_pwd 是 DeviceSecret 经过 "阿里云物联平台配置 32.exe" 的Method加密项机密后生成的，本例使用哈希256加密方式 
	.mqtt_pwd  = {"98CB3C6250899A07863AFBEFA208E6A96F6C494EAFD9C1B8F72B8AE22D4B0F39"}, //generated by "阿里云物联平台配置 32.exe"
	                   
	.hosturl   = {"a1myOVcUdQi.iot-as-mqtt.cn-shanghai.aliyuncs.com"}, //
	.topic_usr_subs = {"/a1myOVcUdQi/AirDetector1/user/get"},	
  .topic_usr_pub  = {"/a1myOVcUdQi/AirDetector1/user/update"},	
	.topic_tpp_pub  = {"/sys/a1myOVcUdQi/AirDetector1/thing/event/property/post"},	
  .topic_tpp_subs = {"/sys/a1myOVcUdQi/AirDetector1/thing/event/property/post_reply"},
	.topic_tpset    = {"/sys/a1myOVcUdQi/AirDetector1/thing/service/property/set" },
	
	.sta_dev = CAT1_Disconnect,
	.sta_cwm = EspCWM_Sta,
	.sta_mqtt = Mqtt_Disconn,
	.smartconfig = SmtCfg_EspTouchAirKiss,	
	
};

/**
  * 1 idr == identifier
  * 2 var == variable
  * 3 temp == temperature
  * 4 hmd  ==  humidity
  */
//validated Aliyun Living IoT thing->property
//true-->open; false-->close
const char thing_swh_idr[]  = {"powerstate"};
uint8_t     thing_swh_var  = 0;  

const char thing_temp_idr[] = {"temperature"};
int         thing_temp_var = 29;  // ℃

const char thing_hmd_idr[]  = {"Humidity"};
int         thing_hmd_var =  50;  // %

const char thing_HCHO_idr[]  = {"HCHO"};
float      thing_HCHO_var = 0.02; // mg/m3

const char thing_SO2_idr[]  = {"SO2"};
float      thing_SO2_var = 0.01;  //mg/m3

const char thing_pm2p5_idr[] = {"PM2_5"};
uint8_t     thing_pm2p5_var= 15;  // ug/m3

///--end mqtt-exp4 ----------------------------------------------------------------------------------end----

///--mqtt-exp5,(validated)-----------------------------------------------------------------------------------
//TB1->broker5{product:smarthome2; device: SmartLight1}
//exp5,https://iot.console.aliyun.com/devices/a1BTYOFa85e/SmartLight1/1
//Communication between 云智能app on Aliyun Living IoT and target board(ATK-DMF407)
//https://living.aliyun.com/project/a123DkwaszFiH6aA/dev/product/a1BTYOFa85e/productdetail
sttMqtt_DevParas_t g_atkmoudle_mqttdev_smtlgt1  = {
	.devname   = {"SmartLight1"},	//空气检测仪
	.ssid      = {"EDW201X"},
	.pwd_ap    = {"txhd349874"},
	.cipsntp   = {"ntp1.aliyun.com"},
	.clientid  = {"Edwoy|securemode=3\\,signmethod=hmacsha256|"}, //generated by "阿里云物联平台配置 32.exe",本例使用哈希256加密方式 
	
	.productkey = {"a1BTYOFa85e"},	
	.mqtt_usr  = {"SmartLight1&a1BTYOFa85e"},
	
	 //mqtt_pwd 是 DeviceSecret 经过 "阿里云物联平台配置 32.exe" 的Method加密项机密后生成的，本例使用哈希256加密方式 
	.mqtt_pwd  = {"2ED61BC084BDD00CAE20EF98749232AD28560D7347A6342ACFE78C86017F3DD8"}, //generated by "阿里云物联平台配置 32.exe"
	                   
	.hosturl   = {"a1BTYOFa85e.iot-as-mqtt.cn-shanghai.aliyuncs.com"}, //
	.topic_usr_subs = {"/a1BTYOFa85e/SmartLight1user/get"},	
  .topic_usr_pub  = {"/a1BTYOFa85e/SmartLight1/user/update"},	
	.topic_tpp_pub  = {"/sys/a1BTYOFa85e/SmartLight1/thing/event/property/post"},	
  .topic_tpp_subs = {"/sys/a1BTYOFa85e/SmartLight1/thing/event/property/post_reply"},
	.topic_tpset    = {"/sys/a1BTYOFa85e/SmartLight1/thing/service/property/set" },
	
	.sta_dev = CAT1_Disconnect,
	.sta_cwm = EspCWM_Sta,
	.sta_mqtt = Mqtt_Disconn,
	.smartconfig = SmtCfg_EspTouchAirKiss,	
	
};

/*******************************************
  * 1 idr == identifier
  * 2 var == variable
  * 3 temp == temperature
  * 4 hmd  ==  humidity
  * thg == thing
  ******************************************/
//validated Aliyun Living IoT thing->property
//rw,powerswitch,true-->open; false-->close
const char thg5_swh_idr[]  = {"powerstate"};
uint8_t     thg5_swh_var  = 0;  

//rw,colorTemperature
const char thg5_clrtemp_idr[]  = {"colorTemperatureInKelvin"};
int         thg5_clrtemp_var =  2000;  // Kelvin

//rw,thing property: illumination value 光照值
const char  thg5_lux_idr[] = {"LightLux"} ;
uint16_t     thg5_lux_var = 100;  //Lux

//rw,
const char thg5_RGB_idr[]  = {"RGBColor"};
sttTHG5_RGBvar_t  thg5_RGB_var = { .Red = 32, .Green = 79, .Blue = 12};

const char thg5_loctim_idr[]  = {"LocalTimer"};
sttLocTim_t thg5_loctim_var = {
	.Timer     = {"volid"},
	.Enable    = 1,  //1-->enable; 0-->disable
  .IsValid   = 1,  //1-->valid;  0-->invalid
} ;  


///--end mqtt-exp5 ----------------------------------------------------------------------------------end----

///==End Mqtt-devs-paras==================================================================================end====

/*----Endline : Full file------------------------------------------------------------------------All_End----*/
