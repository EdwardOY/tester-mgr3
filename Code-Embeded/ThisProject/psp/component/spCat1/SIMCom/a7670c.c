/******************************************************************************************************
 * @file        A7670C.c
 * @brief       Mqtt base using ESPdev-->esp8266 drive src using serialport(UART/USART)-interface
 * @author      Edwoy
 * @version     validated,[+] Aliyun Living IoT(云智能app)
 * @date        V1.3,validated,2023.6.29
 * @license     Copyright (c) 2020-2038
 ****************************************************************************************************
 * @attention
       1  Add below int-defs to HAL_UART_MspInit() in usart.c
			      only __HAL_UART_ENABLE_IT(uartHandle, UART_IT_RXNE); 
			 2 Basic dependency
					2.1 res_uart.h/c, resdrv_iot_uart.h/c, shell_uart.h/c, usart.h/c(by cubemx)
					2.2 utyBtBle.h/c	
			 3 Esp8266
			   Download the Ai-thinker Mqtt-firmware v1112 to esp8266
         3.1 app_cat1_devgpios_init must add AKM_PWR_ON();  
             otherwise the espdev keeps in download mode
				 3.2 If the espdev has been restored to factory settings() using app_cat1dev_restore()
				     it is necessary to first set the device's cwmode using app_cat1_set_cwmode()
						 and then relink the routeAP entering network 
				 3.3 	If the espdev hasn`t  been restored	,espdev and mqtt paras are all retain
				     (it automatically link the routeAP entering network )
				 3.4 Link route AP
				    Successfully set the cwmode at first,and then use app_cat1_link_ap()/app_cat1_link_ap_v2()
         3.5 smartconfig
    		   3.5.1 Before performing this func, must set up the cwmode at first 
		       3.5.2 After successfully running this func once, it cannot be run again. 
				      If need to run it again,  must reset espdev at first ,then set up the cwmode				 
       4 Mqtt,Aliyun iot platform
			   4.1 Default enable auto-connect network
				 4.2 Aliyun Living(飞燕平台-云智能app)
				   4.2.1 产品信息-> 产品类型选网关，联网方式选蜂窝，模组选其他
					 4.2.2 使用"阿里云物联平台配置 32.exe"，填入飞燕平台 设备证书三元素
					       生成 clientid/mqtt_usr/mqtt_pwd
					4.2.3 mqtt_pwd 是 DeviceSecret 经过 "阿里云物联平台配置 32.exe" 的Method加密选项机密后生成的
					4.2.4 云智能app扫码配网二维码，只能连上面板界面，而不能连routeAP，因此如果连新的路由
					     仍需 smartconfig 联网 
       5 apis
			   5.1 Recommend using app_atkmodule_printf() instead of unusing app_cat1_send_at_cmd()
       6			 
 ****************************************************************************************************
 * @note
 *    1 Default hard
          platform: ATK-DMF407
          module : Esp8266        					
			2 validated mqtt-exps(in res_esp.h/c):
		 	 2.1 Aliyun iot platform user-defined 
			   2.1.1 mqtt-exp1
				 2.1.2 mqtt-exp2,TB1->broker2{product:product1; device: adcdev1}			
		   2.2 Aliyun IoT Studio Webapp
   			  mqtt-exp3
		      study video,https://www.bilibili.com/video/BV1Rv4y1P7M3/?spm_id_from=333.337.search-card.all.
				                  click&vd_source=08eea1805655250a87b323b6cedd4b01 
		  2.3 mqtt-exp 
		     study video,https:https://www.bilibili.com/video/BV1vP411X7RZ/?
				             spm_id_from=333.999.0.0&vd_source=08eea1805655250a87b323b6cedd4b01      		 
 ****************************************************************************************************
 * @update
     V1.3,validated,2023.6.29, add __ARMCC_VERSION judgment
     V1.2,validated,2023.6.20,Aliyun Living IoT(云智能app)
     V1.1,validated,2023.6.4,[+] smartconfig app_mqtt_init_v2
     V1.0,validated, 2023.5.26,MQTT & Aliyun base

 ****************************************************************************************************
 */
 
#include "ThisProj_Glb.h"
#include CPT_CAT1_HEAD  //  "./component/spCat1/SIMCom/a7670c.h"
#include DLY_HEAD
#include UART_HEAD
#include GPIO_HEAD      // for RED_LED_TGG()
#include BSP_GPIO_HEAD
#include RES_GPIO_HEAD 

///==MQTT============================================================================================
///--MQTTdrvs------------------------------------------------------------------------------------
/************************************************************************
 * @brief  (validated) config MQTT-CIPSNTP
 * @param   cip,MQTT-CIPSNTP
              "ntp1.aliyun.com" , Aliyun   
 * @retval  Err_CAT1_NONE  : success
 *          Err_CAT1_ERROR: fail
 ***********************************************************************
	ret = app_mqtt_cfg_cipsntp("ntp1.aliyun.com");
 ************************************************************************/
uint8_t app_mqtt_cfg_cipsntp(char* cip)
{
	uint8_t ret = 0;
	char cmd[64] = {0};
	
	sprintf(cmd,"AT+CIPSNTPCFG=1,8,\"%s\"\r\n",cip);

	app_atkmodule_printf(cmd);
	stkdly_ms(__DlyMs_Mqtt);
	
	if (NULL == app_atkmodule_rxmsg()){
			return Err_CAT1_ERROR;
	}else{
		  app_atkmodule_uartrxmsg_poll();
			return Err_CAT1_NONE; 
	}
}

/************************************************************************************
 * @brief (validated) config MQTT-USER 
           scheme only use TCP           
 * @param  username,expBroker1-->"esp8266&a1QSdqL2OX7"
           password,expBroker1--->
              "5569e8ebe8c0da77826a95d3078853455360e9c78b1ef2e4a6dd81db876856f4"  
 * @notice
     -1-,client_id is fixed "NULL"
     -2-,expBroker1,https://iot.console.aliyun.com/devices/a1QSdqL2OX7/esp8266/1
         prodect--> wifi-iot ; device-->esp8266
         check the "username" and "password" of MQTT connection parameters 
 * @retval  Err_CAT1_NONE  : success
 *          Err_CAT1_ERROR: fail
 ***********************************************************************
	ret = app_mqtt_cfg_usr("esp8266&a1QSdqL2OX7", \
  "5569e8ebe8c0da77826a95d3078853455360e9c78b1ef2e4a6dd81db876856f4");
 ************************************************************************************/
uint8_t app_mqtt_cfg_usr(char* username,char* password)
{
	uint8_t ret = 0;
	char cmd[256] = {0};
	
	sprintf(cmd,"AT+MQTTUSERCFG=0,1,\"NULL\",\"%s\",\"%s\",0,0,\"\"\r\n",username,password);
	app_atkmodule_printf(cmd);
	stkdly_ms(__DlyMs_Mqtt);
	
	if (NULL == app_atkmodule_rxmsg()){
			return Err_CAT1_ERROR;
	}else{
			app_atkmodule_uartrxmsg_poll();
			return Err_CAT1_NONE; 
	}
}

/************************************************************************************
 * @brief (validated) config MQTT-Client id          
 * @param  client_id,expBroker1-->
     "a1QSdqL2OX7.esp8266|securemode=2\,signmethod=hmacsha256\,timestamp=1684598696978|"
 * @notice
	   -3-, Mqtt network-portnumber is 1883 fixed    	
     -2-,add '\' before ','
     -1-,expBroker1,https://iot.console.aliyun.com/devices/a1QSdqL2OX7/esp8266/1 
         check the "clientId" of MQTT connection parameters 
 * @retval  Err_CAT1_NONE  : success
 *          Err_CAT1_ERROR: fail
 ********************************************************************
	ret = app_cat1_send_at_cmd(cmd,"OK",__DlyMs_Mqtt);
 ************************************************************************************/
uint8_t app_mqtt_cfg_clientid(char* client_id)
{
	uint8_t ret = 0;
	char cmd[256] = {0};
	
	sprintf(cmd,"AT+MQTTCLIENTID=0,\"%s\"\r\n",client_id);

	app_atkmodule_printf(cmd);
	stkdly_ms(__DlyMs_Mqtt);
	
	if (NULL == app_atkmodule_rxmsg()){
			return Err_CAT1_ERROR;
	}else{
	  	app_atkmodule_uartrxmsg_poll();
			return Err_CAT1_NONE; 
	}
}

/************************************************************************************
 * @brief (validated) connect MQTT-hosturl
           
 * @param  host,expBroker1-->
         "a1QSdqL2OX7.iot-as-mqtt.cn-shanghai.aliyuncs.com" 
 * @notice
     -2-,add '\' before ','
     -1-,expBroker1,https://iot.console.aliyun.com/devices/a1QSdqL2OX7/esp8266/1 
         check the "mqttHostUrl" of MQTT connection parameters 
 * @retval  Err_CAT1_NONE  : success
 *          Err_CAT1_ERROR: fail
 ************************************************************************
ret = app_mqtt_cfg_clientid("a1QSdqL2OX7.esp8266|securemode=2\\,signmethod=hmacsha256\\,timestamp=1684598696978|");	
 ************************************************************************************/
uint8_t app_mqtt_conn_host(char* host)
{
	uint8_t ret = 0;
	char cmd[256] = {0};
	
	sprintf(cmd,"AT+MQTTCONN=0,\"%s\",1883,1\r\n",host);
	app_atkmodule_printf(cmd);
	stkdly_ms(2 * __DlyMs_Mqtt);
	
	if (NULL == app_atkmodule_rxmsg()){
			return Err_CAT1_ERROR;
	}else{
		  app_atkmodule_uartrxmsg_poll();
			return Err_CAT1_NONE; 
	}
}

/************************************************************************************
 * @brief (validated) config subscribe for espdev getting msg from hosturl
 * @param  topic,subscribe-topic 
           expBroker1-->"/a1QSdqL2OX7/esp8266/user/get"
 * @notice
     -2-,add '\' before ','
     -1-,expBroker1,https://iot.console.aliyun.com/devices/a1QSdqL2OX7/esp8266/1 
         check the custom subscribe-topic from Topic list

 * @retval  Err_CAT1_NONE  : success
 *          Err_CAT1_ERROR: fail
 ***************************************************************
	ret = app_cat1_send_at_cmd(cmd,"OK",__DlyMs_Mqtt);
  app_mqtt_cfg_subs("/a1QSdqL2OX7/esp8266/user/get");
	sprintf(cmd,"AT+MQTTSUB=0,\"%s\",1\r\n",topic);
 ************************************************************************************/
uint8_t app_mqtt_cfg_subs(char* topic)
{
	uint8_t ret = 0;
	char cmd[256] = {0};
	
	sprintf(cmd,"AT+MQTTSUB=0,\"%s\",1\r\n",topic);
	app_atkmodule_printf(cmd);
	stkdly_ms(__DlyMs_Mqtt);
	
	if (NULL == app_atkmodule_rxmsg()){
			return Err_CAT1_ERROR;
	}else{
			return Err_CAT1_NONE; 
	}
}

/************************************************************************************
 * @brief (validated) pubulish free Json-msg to hosturl           
 * @param  topic,publish-topic 
           expBroker1-->"/a1QSdqL2OX7/esp8266/user/update"
 * @notice
     -2-,add '\' before ','
     -1-,expBroker1,https://iot.console.aliyun.com/devices/a1QSdqL2OX7/esp8266/1 
         check the custom publish-topic from Topic list
 * @retval  Err_CAT1_NONE  : success
 *          Err_CAT1_ERROR: fail
 ***************************************************************
	ret = app_cat1_send_at_cmd(cmd,"OK", __DlyMs_Mqtt);

  app_mqtt_publish_freemsg("/a1QSdqL2OX7/esp8266/user/update","targetBoard testmsg");
{\\\"method\\\":\\\"thing.event.property.post\\\"\\,\\\"params\\\":{\\\"%s\\\":%d\\,\\\"%s\\\":%d\\,\\\"%s\\\":%d\\,\\\"%s\\\":%d}}
 ************************************************************************************/
uint8_t app_mqtt_publish_freemsg(char* topic,char* msg)
{
	uint8_t ret = 0;
	char cmd[256] = {0};
	
	sprintf(cmd,"AT+MQTTPUB=0,\"%s\",\"%s\",1,0\r\n",topic,msg);
	app_atkmodule_printf(cmd);
	stkdly_ms(__DlyMs_Mqtt);
	
	if (NULL == app_atkmodule_rxmsg()){
			return Err_CAT1_ERROR;
	}else{
			return Err_CAT1_NONE; 
	}
}

/************************************************************************************
 * @brief (validated) pubulish user-defined Json-msg to hosturl       
 * @param  mqttdev
           expBroker1-->publish.topic "/a1QSdqL2OX7/esp8266/user/update"
 * @notice
     -2-,add '\' before ','
     -1-,expBroker1,https://iot.console.aliyun.com/devices/a1QSdqL2OX7/esp8266/1 
         check the custom publish-topic from Topic list
 * @retval  Err_CAT1_NONE  : success
 *          Err_CAT1_ERROR: fail
 ***************************************************************
	ret = app_cat1_send_at_cmd(cmd,"OK", __DlyMs_Mqtt);

  app_mqtt_publish_freemsg("/a1QSdqL2OX7/esp8266/user/update","targetBoard testmsg");
 ************************************************************************************/
uint8_t app_mqtt_publish_usrmsg(sttMqtt_DevParas_t* mqttdev,char* msg)
{
	uint8_t ret = 0;
	char cmd[256] = {0};
	
	sprintf(cmd,"AT+MQTTPUB=0,\"%s\",\"%s\",1,0\r\n",mqttdev->topic_usr_pub,msg);
	app_atkmodule_printf(cmd);
	stkdly_ms(__DlyMs_Mqtt);
	
	if (NULL == app_atkmodule_rxmsg()){
			return Err_CAT1_ERROR;
	}else{
			return Err_CAT1_NONE; 
	}
}

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
 * @retval  Err_CAT1_NONE  : success
 *          Err_CAT1_ERROR: fail
 ***************************************************************

 ************************************************************************************/
uint8_t app_mqtt_tpset(sttMqtt_DevParas_t* mqttdev)
{
	uint8_t ret = 0;
	char cmd[256] = {0};
	
	sprintf(cmd,"AT+MQTTPUB=0,\"%s\",1\r\n",mqttdev->topic_tpset);
	app_atkmodule_printf(cmd);
	stkdly_ms(3000);
	
	if (NULL == app_atkmodule_rxmsg()){
			return Err_CAT1_ERROR;
	}else{
			return Err_CAT1_NONE; 
	}
}


/**********************************************************************
 * @brief (validated) init mqtt 
          (unrecommended, retain) 
 * @param mqttdev
 * @return 
 ************************************************ 
 **********************************************************************/						
uint8_t app_mqtt_init(sttMqtt_DevParas_t* mqttdev)
{
	  uint8_t ret = 0, step = 0;
    char ip_buf[16] = {0};
		
//step0,optional,init espdev`s gpios------------------------------------------- 		
    ret = app_atkmodule_esp_init();
    if (ret == Err_CAT1_NONE)
    {
        printf("Step%d,%s is mounted on ATK-MODLUE) v2 inited++\r\n",step++,mqttdev->devname);

    }else{
        printf("ESP-dev(mounted on ATK-MODLUE) v2 inits failed!\r\n");
        while (1)
        {
            RED_LED_TGG();
            stkdly_ms(200);
        }			
		}

//step1,necessary, reset the espdev by software-------------------------------  				
		ret = app_cat1dev_sftrst();          //软件复位 
		printf("Step%d,reset %s by codes...\r\n",step++,mqttdev->devname);
		if(ret != Err_CAT1_NONE){
			 printf("Err(%d) in app_cat1dev_sftrst()\r\n",ret);
		}	

//step2,necessary, set workmode-----------------------------------------------			
		ret = app_cat1_set_cwmode(mqttdev->sta_cwm);   // Station模, TCP-client
		printf("Step%d,set %s to station...\r\n",step++,mqttdev->devname);
		if(ret != Err_CAT1_NONE){
			 printf("Err(%d) app_cat1_set_cwmode()\r\n",ret);
		}		

//step3,necessary,config mqtt cipsntp------------------------------------------ 				
		ret = app_mqtt_cfg_cipsntp("ntp1.aliyun.com");
		printf("Step%d,Config espdev to Aliyun cipsntp...\r\n",step++);

		if(ret != Err_CAT1_NONE){
			 printf("Err(%d) app_mqtt_cfg_cipsntp()\r\n",ret);
		}		
		
//step4,necessary, connect AP--------------------------------------------------  										
		printf("Step%d,connect to AP->'%s'.....\r\n",step++,mqttdev->ssid);
		ret = app_cat1_link_ap(mqttdev->ssid, mqttdev->pwd_ap,0); // ("EDW201X","txhd349874");	
		if(ret != Err_CAT1_NONE){
			 printf("Err(%d) app_cat1_link_ap()\r\n",ret);
		}		
		
//step5, follow needs,get the ip4-----------------------------------------------		
		printf("Step%d,config mqttuser...\r\n",step++);
		ret = app_mqtt_cfg_usr(mqttdev->mqtt_usr,mqttdev->mqtt_pwd);	
		if(ret != Err_CAT1_NONE){
			 printf("Err(%d)app_mqtt_cfg_usr()\r\n",ret);
		}		

//step6,necessary,config mqtt clientId--------------------------------------------	 
		printf("Step%d,config mqtt clientId...\r\n",step++);
		ret = app_mqtt_cfg_clientid(mqttdev->clientid);	
		if(ret != Err_CAT1_NONE){
			 printf("Err(%d)app_mqtt_cfg_clientid()\r\n",ret);
		}		


//step7,necessary,connect mqtt-hosturl-----------------------------------------------  	 
		printf("Step%d,connect mqtt-hosturl...\r\n",step++);
		ret = app_mqtt_conn_host(mqttdev->hosturl);	
		
		if(ret != Err_CAT1_NONE){
			 printf("Err(%d)app_mqtt_conn_host()\r\n",ret);
		}		

		
//step8,necessary,subscribe msg from mqtt-hosturl------------------------------------  	
		printf("Step%d,subscribe msg from mqtt-hosturl...\r\n",step++);
		ret = app_mqtt_cfg_subs(mqttdev->topic_usr_subs);	
		
		if(ret == Err_CAT1_NONE){
			 mqttdev->sta_mqtt = Mqtt_IsSubs;
			 app_atkmodule_uartrxmsg_poll();
			 printf("Finished v2 Mqtt-config %dsteps+++++++++++++++++++++++++++++++++++\r\n\r\n",step-1);
       return 0;			
		}else{
			 printf("Err(%d) app_mqtt_conn_host()\r\n",ret);
		}	
//steps are finished-----------------------------------------------------------------	

		return 1;
}

///--End MQTTdrvs--------------------------------------------------------------------------End---

///--MQTTapps------------------------------------------------------------------------------------
//--from paidaxin`s friend-----------------------------------------------------------------------------------
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
 * @retval  Err_CAT1_NONE  : success
 *          Err_CAT1_ERROR: fail
 ***************************************************************
 valid SSCOM-cmd--> AT+MQTTPUB=0,"/sys/a1myOVcUdQi/AirDetector1/thing/event/property/post",
                   "{\"params\":{\"Humidity\":50}\,\"version\":\"1.0.0\"}",1,0
 ******************************************************************************
 ************************************************************************************/
uint8_t app_mqtt_publish_tppint(sttMqtt_DevParas_t* mqttdev, const char* identifier, int* var)
{
	char cmd[128] = {0};
	sprintf(cmd,"{\\\"params\\\":{\\\"%s\\\":%d\\}}",
					identifier,*var);		

  app_mqtt_publish_freemsg(mqttdev->topic_tpp_pub,cmd);
	
	return Err_CAT1_NONE;
}

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
 * @retval  Err_CAT1_NONE  : success
 *          Err_CAT1_ERROR: fail
 ***************************************************************
 valid SSCOM-cmd--> AT+MQTTPUB=0,"/sys/a1myOVcUdQi/AirDetector1/thing/event/property/post",
                   "{\"params\":{\"Humidity\":50}\,\"version\":\"1.0.0\"}",1,0
 ******************************************************************************
 ************************************************************************************/
uint8_t app_mqtt_publish_tppflt(sttMqtt_DevParas_t* mqttdev, const char* identifier, float* var)
{
	char cmd[128] = {0};
	sprintf(cmd,"{\\\"params\\\":{\\\"%s\\\":%5.2f\\}}",
					identifier,*var);		

  app_mqtt_publish_freemsg(mqttdev->topic_tpp_pub,cmd);
	return Err_CAT1_NONE;
}

/**********************************************************************
 * @brief (validated) Analyze message from Aliyun Ling App(云智能)
           only used for int/char/bool type thing var 
          (Recommended) 
          mqtt-exp4,https://iot.console.aliyun.com/product/productDetail/a1myOVcUdQi
 * @param mqttdev
 * @return 
 * @attention
       -1-,don`t add app_atkmodule_uartrx_rst()
           don`t add app_atkmodule_uartrxmsg_poll();
 ************************************************ 
 *******************************************************

 **********************************************************************/					
void app_mqtt_alyzmsg_livingapp_swh(sttMqtt_DevParas_t* mqttdev,const char* identifier, int* var)
{
	static char tmp_pubmsg[256]= {0};
	
	if(NULL == strncmp((sc8_t*)g_atkmodule_rxbuff,"+MQTTSUBRECV:",13))
	{
		uint8_t i=0;
		while(g_atkmodule_rxbuff[i++] != '\0')             
		{
			if(NULL == strncmp((sc8_t*)(g_atkmodule_rxbuff + i),identifier,strlen(identifier)))
			{
				while(g_atkmodule_rxbuff[i++] != ':'); 
        				
				if('1' == g_atkmodule_rxbuff[i])
				{
					*var = 1;	
	        printf("Open %s(%d)\r\n",mqttdev->devname,thing_swh_var);
	     	  RED_LED_ON();
				}
				else if('0' == g_atkmodule_rxbuff[i])
				{
					*var = 0;	
					printf("Close %s(%d)\r\n",mqttdev->devname,thing_swh_var);		
	      	RED_LED_OFF();
				}

			} //<if(NULL == strncmp((sc8_t*)(g_atkmodule_rxbuff + i),identifier,strlen(identifier)))>

		} //<while(g_atkmodule_rxbuff[i++] != '\0') >
	  memset(tmp_pubmsg,0,256);
	}//<if(NULL == strncmp((sc8_t*)g_atkmodule_rxbuff,"+MQTTSUBRECV:",13))>
	
}

//--end from paidaxin`s friend-------------------------------------------------------------------------end---

/**********************************************************************
 * @brief (validated) analyze message from webapp(Aliyun IoT Studio)
          (Recommended) used for  only used for int/char/bool type thing var 
          mqtt-exp3,https://developer.aliyun.com/ask/515488?spm=a2c6h.14164896.0.0.63fc33411y6K5p
 * @param mqttdev
 * @return 
 * @attention
       -1-, 
       -2-,don`t add app_atkmodule_uartrx_rst()
           don`t add app_atkmodule_uartrxmsg_poll();
 ************************************************ 
	valid broker3: app_mqtt_publish_tppint(mqttdev,thing_idr3,&pwrswh);
	sprintf(tmp_pubmsg,"{\\\"method\\\":\\\"thing_idr.event.property.post\\\"\\,\\\"params\\\":{\\\"%s\\\":%d\\}}",
					thing_idr3,pwrswh);		
	app_mqtt_publish_freemsg( g_atkmoudle_mqttdev_home1.topic_tpp_pub, tmp_pubmsg);		
 *******************************************************

 **********************************************************************/					
void app_mqtt_alyzmsg_webapp_swh(sttMqtt_DevParas_t* mqttdev)
{
	static char tmp_pubmsg[256]= {0};
	if(NULL == strncmp((sc8_t*)g_atkmodule_rxbuff,"+MQTTSUBRECV:",13))
	{
		uint8_t i=0;
		while(g_atkmodule_rxbuff[i++] != '\0')             
		{
			if(NULL == strncmp((sc8_t*)(g_atkmodule_rxbuff + i),thing_idr3,strlen(thing_idr3)))
			{
				while(g_atkmodule_rxbuff[i++] != ':'); 
        				
				if('1' == g_atkmodule_rxbuff[i])
				{
					pwrswh = 1;
				}
				else if('0' == g_atkmodule_rxbuff[i])
				{
					pwrswh = 0;
				}
				printf("pwrswh = %d\r\n",pwrswh);
				sprintf(tmp_pubmsg,"{\\\"method\\\":\\\"thing_idr.event.property.post\\\"\\,\\\"params\\\":{\\\"%s\\\":%d\\}}",
			        	thing_idr3,pwrswh);		
				app_mqtt_publish_freemsg(mqttdev->topic_tpp_pub, tmp_pubmsg);		
        
			} 

		}
	  memset(tmp_pubmsg,0,256);
	}
}



/********************************************
 * @brief  (validating...) netwwork-linking status poll 
 * @param  swh,switch
             Ture-->enable auto-connect network
             False-->disable auto-connect network	
 * @retval      无
 * @notice 

 *******************************************/
uint8_t etf_tskpoll_mqttstatus(sttMqtt_DevParas_t* mqttdev)
{
  return 0;
}
/**********************************************************************
 * @brief (validated) init mqtt ,[+] smartconfig
          (Recommended) 
         Refer to Communication between targetboard-esp8266 and  
         Aliyun IoT Studio->Webapp or Living IoT(云智能app)
 * @param mqttdev
 * @return 
 ************************************************ 
  ret = app_cat1_link_ap(mqttdev->ssid, mqttdev->pwd_ap,0); // ("EDW201X","txhd349874");	
 **********************************************************************/						
uint8_t app_mqtt_init_v2(sttMqtt_DevParas_t* mqttdev)
{
	  uint8_t ret = 0, step = 0 , substep = 0;
	  bool tmptkn = false;
    char ip_buf[16] = {0};
	  char tmp_pubmsg[256] = {0};
		
//step0,optional,init espdev`s gpios---------------------------------------------------		
    ret = app_atkmodule_esp_init();
    if (ret == Err_CAT1_NONE)
    {
        printf("Step%d,%s is mounted on ATK-MODLUE v2 inited++\r\n", \
			          step++,mqttdev->devname);

    }else{
        printf("ESP-dev(mounted on ATK-MODLUE)-v2-inits failed!\r\n");
        while (1)
        {
            RED_LED_TGG();
            stkdly_ms(200);
        }			
		}
//step1,necessary, open autoconnent---------------------------------------------------- 	
		printf("Step%d,open autoconn\r\n",step++);	
		app_cat1_autoconn_swh(true); 
		if(ret != Err_CAT1_NONE){
			printf("Err(%d) at step%d in app_mqtt_init_v2\r\n",ret,step - 1);
		}		
    
//step2,necessary,reset the espdev by codes,-------------------------------------------- 	
    printf("Step%d in app_mqtt_init_v2\r\n",step++);
		app_cat1dev_sftrst_v2(mqttdev);
    stkdly_ms(800);

//step3,necessary,check linksta and run smartconfig--------------------------------------
   printf("Step%d switch smartconfig in app_mqtt_init_v2\r\n",step++);
//		if(CAT1_GotIP != app_cat1dev_linksta_poll(mqttdev))
		if(NULL != strstr((sc8_t*)g_atkmodule_rxbuff,"WIFI CONNECTED"))
		{
			 printf("Conneted network,now config mqtt+++\r\n");
		}
		else
		{
//				app_cat1_set_cwmode(EspCWM_Sta);
		  	app_cat1_set_cwmode(EspCWM_StaAp);
				if(Err_CAT1_NONE == app_cat1_smartconfig(mqttdev))
				{
					stkdly_ms(150);
					printf("Step%d smartconfig in app_mqtt_init_v2\r\n",step++);

				}
		}

//step4,necessary,check cipstate-------------------------------------------------	
    printf("Step%d stop smartconfig and check cipstatus in app_mqtt_init_v2\r\n",step++);
		app_cat1_stop_smartconfig(mqttdev);		
    if(Err_CAT1_NONE == app_cat1_cipstatus(mqttdev))
		{
				
		}

//step5,necessary,config mqtt cipsntp------------------------------------------ 				
		ret = app_mqtt_cfg_cipsntp("ntp1.aliyun.com");
		printf("Step%d,Config espdev to Aliyun cipsntp...\r\n",step++);
		if(ret != Err_CAT1_NONE){
			 printf("Err(%d) at step%d in app_mqtt_init_v2\r\n",ret,step - 1);				 
		}	

		
//step6, follow needs,get the ip4-----------------------------------------------		
		printf("Step%d,config mqttuser...\r\n",step++);
		ret = app_mqtt_cfg_usr(mqttdev->mqtt_usr,mqttdev->mqtt_pwd);	
		if(ret != Err_CAT1_NONE){
			 printf("Err(%d) at step%d in app_mqtt_init_v2\r\n",ret,step - 1);				 
		}	

//step7,necessary,config mqtt clientId--------------------------------------------	 
		printf("Step%d,config mqtt clientId...\r\n",step++);
		ret = app_mqtt_cfg_clientid(mqttdev->clientid);	
		if(ret != Err_CAT1_NONE){
			 printf("Err(%d) at step%d in app_mqtt_init_v2\r\n",ret,step - 1);				 
		}	

//step8,necessary,connect mqtt-hosturl-----------------------------------------------  	 
		printf("Step%d,connect mqtt-hosturl...\r\n",step++);
		ret = app_mqtt_conn_host(mqttdev->hosturl);		
		if(ret != Err_CAT1_NONE){
			 printf("Err(%d) at step%d in app_mqtt_init_v2\r\n",ret,step - 1);				 
		}	
		
//step9,necessary,subscribe msg from mqtt-hosturl------------------------------------  	
		printf("Step%d,subscribe msg from mqtt-hosturl...\r\n",step++);
		//validated:	ret = app_mqtt_cfg_subs(mqttdev->topic_usr_subs);	//user-defined topic
		ret = app_mqtt_cfg_subs(mqttdev->topic_tpp_subs);	//thing-model property
		
		if(ret == Err_CAT1_NONE){
			 mqttdev->sta_mqtt = Mqtt_IsSubs;
			 app_atkmodule_uartrxmsg_poll();
			 printf("Finished v2 Mqtt-config %dsteps+++++++++++++++++++++++++++++++++++\r\n\r\n",step - 1);
       return 0;			
		}else{
			 printf("Err(%d) at step%d in app_mqtt_init_v2\r\n",ret,step - 1);		
		}	

//All steps are finished-----------------------------------------------------------------	

		return 1;
}//<end,uint8_t app_mqtt_init_v2(sttMqtt_DevParas_t* mqttdev)>

///--End MQTTapps--------------------------------------------------------------------------End---

///==End MQTT================================================================================End====


/*********************************************************
 * @brief (validated) Send cmd by dbcom
           wether got ip
 * @param  mqttdev
 * @retval  
 * @notice 

 *********************************************************/
void etf_dbcomtsk_esp(sttMqtt_DevParas_t* mqttdev)
{
	char tmpstr[24] = {0};
	
  if(True == g_dbcom_rxtkn_ovr)
	{
		if(NULL != strstr((sc8_t*)g_dbcom_rxbuff,"hdrst"))
		{
			printf("app_cat1dev_hdrst(%s)\r\n",g_dbcom_rxbuff);
			app_cat1dev_hdrst();
		}
		
		if(NULL != strstr((sc8_t*)g_dbcom_rxbuff,"sftrst"))
		{
			printf("esp_sftrst(%s)\r\n",g_dbcom_rxbuff);
			app_cat1dev_sftrst();
		}	
		
		if(NULL != strstr((sc8_t*)g_dbcom_rxbuff,"cipstatus"))
		{
			app_cat1_cipstatus(mqttdev);
		}

		if(NULL != strstr((sc8_t*)g_dbcom_rxbuff,"restore"))
		{
			app_cat1dev_restore_v2(mqttdev);
		}
				
		if(NULL != strstr((sc8_t*)g_dbcom_rxbuff,"smartconfig"))
		{
			app_cat1_set_cwmode(EspCWM_Sta);
			app_cat1_smartconfig(mqttdev);
			app_atkmodule_uartrxmsg_poll();
		}

		if(NULL != strstr((sc8_t*)g_dbcom_rxbuff,"smartconfig stop"))
		{
			app_cat1_stop_smartconfig(mqttdev);
		}

		if(NULL != strstr((sc8_t*)g_dbcom_rxbuff,"initv2"))
		{
			app_mqtt_init_v2(mqttdev);
		}

		if(NULL != strstr((sc8_t*)g_dbcom_rxbuff,"mqttpub"))
		{	
			app_mqtt_publish_usrmsg(mqttdev,"mqtt-msg***");
		}
    
		//validated temp test----------------
		if(NULL != strstr((sc8_t*)g_dbcom_rxbuff,"pwrswh1"))
		{	
			printf("dbcom:pwrswh= %d\r\n",pwrswh);
		}
		
		app_dbcom_rst();
  }
}


///--drv-v2---------------------------------------------------------------------------------

/*********************************************************
 * @brief (validated) poll-handle,espdev state of linking-network

 * @param  mqttdev
 * @retval  
 * @notice 
 ******************************************
 *********************************************************/
emCat1_DevState_t app_cat1dev_linksta_poll(sttMqtt_DevParas_t* mqttdev)
{
  __IO static emCat1_DevState_t ret = CAT1_Disconnect ;
  ret	=  mqttdev->sta_dev;
  
	if(True == g_atkmodule_rxtkn_ovr)
	{
		if(NULL != strstr((sc8_t*)g_atkmodule_rxbuff,"ready"))
		{
			ret = mqttdev->sta_dev = CAT1_Ready;
			app_atkmodule_uartrxmsg_poll();
		}
		
		if(NULL != strstr((sc8_t*)g_atkmodule_rxbuff,"WIFI GOT IP"))
		{
			ret = mqttdev->sta_dev = CAT1_GotIP;
			app_atkmodule_uartrxmsg_poll();
		}
    else if(NULL != strstr((sc8_t*)g_atkmodule_rxbuff,"WIFI DISCONECT"))
		{
			ret = mqttdev->sta_dev = CAT1_Disconnect;
			app_atkmodule_uartrxmsg_poll();
		}
		
		if(NULL != strstr((sc8_t*)g_atkmodule_rxbuff,"STATUS:0") || \
			 NULL != strstr((sc8_t*)g_atkmodule_rxbuff,"STATUS:5"))
		{
			 ret = mqttdev->sta_dev = CAT1_Disconnect;	
			 app_atkmodule_uartrxmsg_poll();
		}
		else if(NULL != strstr((sc8_t*)g_atkmodule_rxbuff,"STATUS:2"))
		{
			 ret = mqttdev->sta_dev = CAT1_Connect;	
			 app_atkmodule_uartrxmsg_poll();
		}	
					
  } //<end,if(True == g_atkmodule_rxtkn_ovr)>
	
	return ret; 	
}

/***************************************************************************
 * @brief   (validated) smartconfig to RouteAP
 * @param   smt,check emEspSmartConfig_t in res_esp.h
 * @retval   
 * @notice 
		 -1-,Before performing this func, must set up the cwmode at first 
		 -2-,After successfully running this func once, it cannot be run again. 
				If need to run it again,  must reset espdev at first ,then set up the cwmode
 ***************************************************************************/
uint8_t app_cat1_smartconfig(sttMqtt_DevParas_t* mqttdev)
{
	uint8_t ret = Err_CAT1_ERROR;
	
	if(IS_VALID_SMTCFG_ESP(mqttdev->smartconfig))
	{
		app_atkmodule_printf("AT+CWSTARTSMART=%d\r\n",mqttdev->smartconfig)	;			
	}
  stkdly_ms(__DlyMs_Cat1);

  if(NULL != strstr((sc8_t*)app_atkmodule_rxmsg(),"OK")){
			ret = Err_CAT1_NONE; 
			app_atkmodule_uartrxmsg_poll();
      printf("%s,wait to link routeAp by EspTouch or WeChat->Ai-Thinker....\r\n",__FUNCTION__);
		  while(1)
			{
				if(True == g_dbcom_rxtkn_ovr)
				{
					if(NULL != strstr((sc8_t*)g_dbcom_rxbuff,"exit smtcfg"))
					{
						printf("Exit %s, stop smartconfig\r\n",__FUNCTION__);	
						app_dbcom_rst();	
            break;						
					}
				}
				
				if(NULL != strstr((sc8_t*)g_atkmodule_rxbuff,"WIFI GOT IP"))
				{
					printf("Exit %s, stop smartconfig\r\n",__FUNCTION__);	
					break;								
				}
			}//<end, while(NULL == strstr((sc8_t*)g_atkmodule_rxbuff,"WIFI GOT IP"))>
			
      mqttdev->sta_dev = CAT1_GotIP;
		  printf("Finished %s++\r\n",__FUNCTION__);
			
	}else {
#if __ARMCC_VERSION >= 6010050		
		  printf("EspErr at %s,line%d,file<%s>!!\r\n",__FUNCTION__,__LINE__,__FILE_NAME__);
#else
	   	printf("EspErr at %s,line%d,file!!\r\n",__FUNCTION__,__LINE__);
#endif	
			ret = Err_CAT1_ERROR;
	}	

	return ret;
}

/**********************************************************
 * @brief (validated) stop smartconfig 
       Purpose: Release the memory of espdev 
       to prevent it from being occupied by smartconfig  
 * @param   smt,check emEspSmartConfig_t in res_esp.h
 * @retval   
 * @notice 
 ******************************************************
  if (NULL == app_atkmodule_rxmsg()){
			return Err_CAT1_ERROR;
	}else{
		  app_atkmodule_uartrxmsg_poll();
			return Err_CAT1_NONE; 
	}	
 *********************************************************/
uint8_t app_cat1_stop_smartconfig(sttMqtt_DevParas_t* mqttdev)
{
	uint8_t ret = 0;

	app_atkmodule_printf("AT+CWSTOPSMART\r\n")	;		
  stkdly_ms(__DlyMs_Mqtt);
	
  if (NULL == strstr((sc8_t*)app_atkmodule_rxmsg(),"OK")){
			return Err_CAT1_ERROR;
	}else{
		  app_atkmodule_uartrxmsg_poll();
			return Err_CAT1_NONE; 
	}	
}


/************************************************************************
 * @brief  (validated) enable or disable auto-connect network			
 * @param  swh,switch
             Ture-->enable auto-connect network
             False-->disable auto-connect network	
 * @retval      无
 * @notice 
 ******************************************************
  if (NULL == app_atkmodule_rxmsg()){
			return Err_CAT1_ERROR;
	}else{
		  app_atkmodule_uartrxmsg_poll();
			return Err_CAT1_NONE; 
	}	
 *************************************************************************/
uint8_t app_cat1_autoconn_swh(bool swh)
{
	uint8_t ret = 0;
	
	if(True == swh){
		app_atkmodule_printf("AT+CWAUTOCONN=1\r\n"); // enable auto-connect network			
	}else{
		app_atkmodule_printf("AT+CWAUTOCONN=0\r\n"); //disable auto-connect network						
	}
  stkdly_ms(__DlyMs_Mqtt);
	
  if (NULL == strstr((sc8_t*)app_atkmodule_rxmsg(),"OK")){
			return Err_CAT1_ERROR;
	}else{
		  app_atkmodule_uartrxmsg_poll();
			return Err_CAT1_NONE; 
	}	
}


/********************************************
 * @brief  (validated) check netwwork-linking status	
 * @param  swh,switch
             Ture-->enable auto-connect network
             False-->disable auto-connect network	
 * @retval      无
 * @notice 
 ***************************************

 *******************************************/
emCat1_DevState_t app_cat1_cipstatus(sttMqtt_DevParas_t* mqttdev)
{
  __IO static emCat1_DevState_t ret = CAT1_Disconnect ;
  ret	=  mqttdev->sta_dev;
	
	app_atkmodule_printf("AT+CIPSTATUS\r\n"); 	
  stkdly_ms(__DlyMs_Cat1);
	
	if(NULL == strstr((sc8_t*)g_atkmodule_rxbuff,"OK"))
	{
#if __ARMCC_VERSION >= 6010050		
		printf("EspErr at %s,line%d,file<%s>!!\r\n",__FUNCTION__,__LINE__,__FILE_NAME__);
#else
		printf("EspErr at %s,line%d,file!!\r\n",__FUNCTION__,__LINE__);
#endif	
		ret = Err_CAT1_ERROR;
			 
	}
	else 
  {
    app_cat1dev_linksta_poll(mqttdev);
		ret = Err_CAT1_NONE;
	}			
	
	return ret; 	
}


/********************************************************************
 * @brief  (validated)ESPDev恢复出厂设置
 * @param   无
 * @retval  Err_CAT1_NONE  : 恢复出场设置成功
 * @notice  
       -1-,Once this operation is performed, 
          all wifi configs in espdev will be cleared
       -2-,need delay >= 300ms
 **************************************************************
 ********************************************************************/
emCat1_DevState_t app_cat1dev_restore_v2(sttMqtt_DevParas_t* mqttdev)
{
  uint8_t tmp = 0;
	emCat1_DevState_t ret = CAT1_Disconnect;

	app_atkmodule_printf("AT+RESTORE\r\n");
	stkdly_ms(__DlyMs_Mqtt);

	if(NULL == strstr((sc8_t*)g_atkmodule_rxbuff,"AT+RESTORE"))
	{
#if __ARMCC_VERSION >= 6010050		
		printf("EspErr at %s,line%d,file<%s>!!\r\n",__FUNCTION__,__LINE__,__FILE_NAME__);
#else
		printf("EspErr at %s,line%d,file!!\r\n",__FUNCTION__,__LINE__);
#endif		
		return Err_CAT1_ERROR;
	}
  else
	{	
		printf("%s successfully.\r\n",__FUNCTION__);
    mqttdev->sta_dev = CAT1_Ready;
		app_atkmodule_uartrx_rst();	
		return Err_CAT1_NONE;
	}
}

/*****************************************************************
 * @brief (validated) Reset ESPDev using codes
           (Recommended) 
 * @param  mqttdev,
           cipsta,Switch network-linking judgment
           wether add app_cat1_cipstatus(mqttdev)?    
                false--> no  
                others--> yes
 * @retval  
       -1-,cipsta = true,emCat1_DevState_t
       -2-,cipsta = false,
         Err_CAT1_NONE  : 软件复位成功
         Err_CAT1_ERROR: 软件复位失败
 * @notice 
       -1-,need delay >= 300ms
 ***************************
		stkdly_ms(50);
		app_cat1dev_linksta_poll(mqttdev);
 *******************************************************************/
emCat1_DevState_t app_cat1dev_sftrst_v2(sttMqtt_DevParas_t* mqttdev)
{ 
	uint8_t tmp = 0;   
	emCat1_DevState_t ret = CAT1_Disconnect;

	app_atkmodule_printf("AT+RST\r\n");
	stkdly_ms(__DlyMs_Mqtt);

	if(NULL == strstr((sc8_t*)g_atkmodule_rxbuff,"OK"))
	{
#if __ARMCC_VERSION >= 6010050		
		printf("EspErr at %s,line%d,file<%s>!!\r\n",__FUNCTION__,__LINE__,__FILE_NAME__);
#else
		printf("EspErr at %s,line%d,file!!\r\n",__FUNCTION__,__LINE__);
#endif	
		return Err_CAT1_ERROR;
	}
  else
	{	
		printf("%s successfully.\r\n",__FUNCTION__);
		app_atkmodule_uartrx_rst();	 // must add it
		return Err_CAT1_NONE;
	}
  
}

/********************************************************************
 * @brief  (validated)ESPDev links RouteAP
           (Recommended) 
 * @param  mqttdev
 * @retval      Err_CAT1_NONE  : WIFI is link
 *              Err_CAT1_ERROR: WIFI is unlink
 * @notice
     The prerequisite for connecting to AP 
     is to successfully set the cwmode first
 *********************************************************
	app_atkmodule_printf(cmd);
	stkdly_ms(ms);

	if (NULL == app_atkmodule_rxmsg()){
			return Err_CAT1_ERROR;
	}else{
			app_atkmodule_uartrxmsg_poll();
			return Err_CAT1_NONE; 
	}
	
 *******************************************************************/
uint8_t app_cat1_link_ap_v2(sttMqtt_DevParas_t* mqttdev,uint16_t ms)
{
	uint8_t ret;
	char cmd[56];
  if(ms < 4700)
	{
		ms = 4700;
	}
	printf("%s is connecting AP.....\r\n",__FUNCTION__);	
	sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", mqttdev->ssid, mqttdev->pwd_ap);		
	app_atkmodule_printf(cmd);

	stkdly_ms(ms);

	if(CAT1_GotIP == app_cat1dev_linksta_poll(mqttdev)){
		 return Err_CAT1_NONE;
			 
	} else{
		 printf("Failed link network ,please check and relink the AP!!!! ");
		 return Err_CAT1_ERROR;
	}
	
}




///--end drv-v2---------------------------------------------------------------------end----

/********************************************
 * @brief   (validated) ESPDev硬件初始化
 * @param       无
 * @retval      无
 * @notice 
        -1-, Must add AKM_PWR_ON();  
             otherwise the espdev keeps in download mode
 *******************************************/
void app_cat1_devgpios_init(void)
{  
    GPIO_InitTypeDef gpio_init_struct;
	
    AKM_RST_GPIO_CLK_ENABLE();
    gpio_init_struct.Pin = AKM_RST_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_OD ;  // GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_NOPULL;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(AKM_RST_GPIO_PORT, &gpio_init_struct);
	
    AKM_PWR_GPIO_CLK_ENABLE();    
    gpio_init_struct.Pin   = AKM_PWR_GPIO_PIN;
    HAL_GPIO_Init(AKM_PWR_GPIO_PORT, &gpio_init_struct);	
	
	  AKM_PWR_ON() ;	  
}

/************************************************
 * @brief  (validated)ESPDev硬件复位
 * @param       无
 * @retval      无
 *********************************************
    AKM_RST_GPIO(0);
    stkdly_ms(100);
    AKM_RST_GPIO(1);
    stkdly_ms(100);
 ************************************************/
void app_cat1dev_hdrst(void)
{
	AKM_RST_EN();
  stkdly_ms(100);	
	AKM_RST_DIS();
  stkdly_ms(100);		
}

/************************************************************************
 * @brief   (validated)ESPDev初始化
 * @param       baudrate: ESPDev UART通讯波特率
 * @retval      Err_CAT1_NONE  : ESPDev初始化成功，函数执行成功
 *              Err_CAT1_ERROR: ESPDev初始化失败，函数执行失败
 ***********************************************************************
 *   app_atkmodule_init(baudrate);  ESPDev UART初始化 
    if (app_cat1_at_test() != Err_CAT1_NONE)  
    {
        return Err_CAT1_ERROR;
    }
   
 ************************************************************************/
uint8_t app_atkmodule_esp_init()
{
    app_cat1_devgpios_init();                  /* ESPDev硬件初始化 */
    app_cat1dev_hdrst();                         /* ESPDev硬件复位 */
	  app_atkmodule_uartrx_rst();
    return Err_CAT1_NONE;
}

/********************************************************************
 * @brief  (validated)ESPDev恢复出厂设置
 * @param       无
 * @retval      Err_CAT1_NONE  : 恢复出场设置成功
 * @notice  
       -1-,Once this operation is performed, 
          all wifi configs in espdev will be cleared
       -2-,need delay >= 300ms
 **************************************************************
  printf("v1Restore\r\n");
 ********************************************************************/
uint8_t app_cat1dev_restore(void)
{
	uint8_t ret = Err_CAT1_ERROR;
	uint8_t tmp = 0;
	
	while(tmp++ < 10)
	{
		app_atkmodule_printf("AT+RESTORE\r\n");
	  stkdly_ms(__DlyMs_Mqtt - __DlyMs_Cat1);

		if(NULL != strstr((sc8_t*)app_atkmodule_rxmsg(),"ready"))
		{
				app_atkmodule_uartrxmsg_poll();
        
				return Err_CAT1_NONE; 
		}	
  }
	return Err_CAT1_TIMEOUT;
}

/******************************************************************
 * @brief  (validated)设置ESPDev工作模式
 * @param   mode: emEsp8266CWMODE_t in res_esp.h
										EspCWM_Sta   = 1, //TCP-Client,station
										EspCWM_Ap    = 2, //TCP-Server,soft AP
										EspCWM_StaAp = 3, // UDP,station & soft AP
 * @retval      Err_CAT1_NONE   : 工作模式设置成功
 *              Err_CAT1_ERROR : 工作模式设置失败
 *              Err_CAT1_INVAL: mode参数错误，工作模式设置失败
 ************************************************************
  ret = app_cat1_send_at_cmd(cmd,"OK",__DlyMs_Cat1);
 ******************************************************************/
uint8_t app_cat1_set_cwmode(emEsp8266CWMODE_t mode)
{
	uint8_t ret = 0;
  char cmd[16]= {0};
	
	assert_param(IS_VALID_CWMODE_ESP(mode));
	if(NULL == IS_VALID_CWMODE_ESP(mode))
	{
		printf("ErrPara(%d)_cwmode in app_cat1_set_cwmode!!!!\r\n",mode);
		return Err_CAT1_INVAL;
	}  	

	sprintf(cmd,"AT+CWMODE=%d\r\n",mode);
	app_atkmodule_printf(cmd);
	stkdly_ms(__DlyMs_Cat1);
	
	if(NULL == strstr((sc8_t*)app_atkmodule_rxmsg(),"OK")){
			return Err_CAT1_ERROR;
	}else{
		  app_atkmodule_uartrxmsg_poll();
			return Err_CAT1_NONE; 
	}
}

/*********************************************************
 * @brief (validated) ESPDev软件复位
 * @param       无
 * @retval      Err_CAT1_NONE  : 软件复位成功
 *              Err_CAT1_ERROR: 软件复位失败
 * @notice
       -1-,need delay >= 400ms
 ****************************************
printf("v1Reset\r\n");
 *********************************************************/
uint8_t app_cat1dev_sftrst(void)
{
	uint8_t ret = Err_CAT1_ERROR;
	uint8_t tmp = 0;
	
	while(tmp++ < 10)
	{
  	app_atkmodule_printf("AT+RST\r\n");
	  stkdly_ms(__DlyMs_Mqtt - __DlyMs_Cat1);

		if(NULL != strstr((sc8_t*)app_atkmodule_rxmsg(),"ready"))
		{
				app_atkmodule_uartrxmsg_poll();
        
				return Err_CAT1_NONE; 
		}	
  }
	return Err_CAT1_TIMEOUT;
}

/*********************************************************
 * @brief   (validated)ESPDev routeAP
 * @param    ssid: route WIFI name
 *           pwd : route WIFI password
             ms, link delay 
 * @retval      Err_CAT1_NONE  : WIFI is link
 *              Err_CAT1_ERROR: WIFI is unlink
 * @notice
       
 *********************************************************
	ret = app_cat1_send_at_cmd(cmd,"WIFI GOT IP",ms);
	if(ret != Err_CAT1_NONE){
		return Err_CAT1_ERROR;		
	}	else {
		app_atkmodule_uartrxmsg_poll();
		return ret;	
	}	
 ********************************************************/
uint8_t app_cat1_link_ap(char *ssid, char *pwd,uint16_t ms )
{
	uint8_t ret;
	char cmd[64];
	if(ms <= 4800)
	{
		ms = 4800;
	}
	
	sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, pwd);

	app_atkmodule_printf(cmd);
	stkdly_ms(ms);

	if (NULL == app_atkmodule_rxmsg()){
			return Err_CAT1_ERROR;
	}else{
			app_atkmodule_uartrxmsg_poll();
			return Err_CAT1_NONE; 
	}
	
}


/**
 * @brief       ESPDev发送AT指令
 * @param       cmd    : 待发送的AT指令
 *              ack    : 等待的响应
 *              timeout: 等待超时时间
 * @retval      Err_CAT1_NONE     : 函数执行成功
 *              Err_CAT1_TIMEOUT: 等待期望应答超时，函数执行失败
 */
uint8_t app_cat1_send_at_cmd(char *cmd, char *ack, uint32_t timeout)
{
    uint8_t *ret = NULL;
    
    app_atkmodule_uartrx_rst();
    app_atkmodule_printf("%s\r\n", cmd);
    
    if ((ack == NULL) || (timeout == 0)){
        return Err_CAT1_NONE;
			
    }else{
        while (timeout > 0)
        {
            ret = app_atkmodule_rxmsg();
            if (ret != NULL)
            {
                if (NULL != strstr((const char *)ret, ack))
                {
                    return Err_CAT1_NONE;
                }
                else
                {
                    app_atkmodule_uartrx_rst();
                }
            }
            timeout--;
            stkdly_ms(1);
        }
        
        return Err_CAT1_TIMEOUT;
    }
}


/**
 * @brief       ESPDev AT指令测试
 * @param       无
 * @retval      Err_CAT1_NONE  : AT指令测试成功
 *              Err_CAT1_ERROR: AT指令测试失败
 */
uint8_t app_cat1_at_test(void)
{
	uint8_t ret;

	for(uint8_t i=0; i<10; i++)
	{
		 app_atkmodule_printf("AT\r\n");
		 if(NULL != app_atkmodule_rxmsg())
		 {
			 printf("%s\r\n",app_atkmodule_rxmsg());
			 return Err_CAT1_NONE;
		 }
	}
	
	return Err_CAT1_TIMEOUT;
}


/**
 * @brief       ESPDev获取IP地址
 * @param       buf: IP地址，需要16字节内存空间
 * @retval      Err_CAT1_NONE  : 获取IP地址成功
 *              Err_CAT1_ERROR: 获取IP地址失败
 */
uint8_t app_cat1_get_ip(char *buf)
{
    uint8_t ret;
    char *p_start;
    char *p_end;
    
    ret = app_cat1_send_at_cmd("AT+CIFSR", "OK", 500);
    if (ret != Err_CAT1_NONE)
    {
        return Err_CAT1_ERROR;
    }
    
    p_start = strstr((const char *)app_atkmodule_rxmsg(), "\"");
    p_end = strstr(p_start + 1, "\"");
    *p_end = '\0';
    sprintf(buf, "%s", p_start + 1);
    
    return Err_CAT1_NONE;
}

/**
 * @brief       ESPDev连接TCP服务器
 *              only in serialnet
 * @param       server_ip  : TCP服务器IP地址
 *              server_port: TCP服务器端口号
 * @retval      Err_CAT1_NONE  : 连接TCP服务器成功
 *              Err_CAT1_ERROR: 连接TCP服务器失败
 */
uint8_t app_cat1_connect_tcp_server(char *server_ip, char *server_port)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n", server_ip, server_port);
    ret = app_cat1_send_at_cmd(cmd, "CONNECT", 5000);
	
    if (ret == Err_CAT1_NONE){
        return Err_CAT1_NONE;
    } else{
        return Err_CAT1_ERROR;
    }
}

/**
 * @brief   ESPDev进入透传
 * @param   无
 * @retval  Err_CAT1_NONE  : 进入透传成功
 *          Err_CAT1_ERROR: 进入透传失败
 */
uint8_t app_cat1_enter_serialnet(void)
{
  uint8_t ret;
    
	ret  = app_cat1_send_at_cmd("AT+CIPMODE=1", "OK", 500);
	ret += app_cat1_send_at_cmd("AT+CIPSEND", ">", 500);
	
	if(ret != Err_CAT1_NONE){
		return Err_CAT1_ERROR;		
	}	else {
		app_atkmodule_uartrxmsg_poll();
		return ret;	
	}	
}

/**
 * @brief       ESPDev退出透传
 * @param       无
 * @retval      无
 */
void app_cat1_exit_serialnet(void)
{
    app_atkmodule_printf("+++");
}

/**
 * @brief       ESPDev设置回显模式
 * @param       cfg: 0，关闭回显
 *                   1，打开回显
 * @retval      Err_CAT1_NONE  : 设置回显模式成功
 *              Err_CAT1_ERROR: 设置回显模式失败
 */
uint8_t app_cat1_ate_config(uint8_t cfg)
{
    uint8_t ret;
    
    switch (cfg)
    {
        case 0:
        {
            ret = app_cat1_send_at_cmd("ATE0", "OK", 500);   /* 关闭回显 */
            break;
        }
        case 1:
        {
            ret = app_cat1_send_at_cmd("ATE1", "OK", 500);   /* 打开回显 */
            break;
        }
        default:
        {
            return Err_CAT1_INVAL;
        }
    }
    
    if (ret == Err_CAT1_NONE)
    {
        return Err_CAT1_NONE;
    }
    else
    {
        return Err_CAT1_ERROR;
    }
}

/**
 * @brief       ESPDev连接原子云服务器
 * @param       id : 原子云设备编号
 *              pwd: 原子云设备密码
 * @retval      Err_CAT1_NONE  : 连接原子云服务器成功
 *              Err_CAT1_ERROR: 连接原子云服务器失败
 */
uint8_t app_cat1_connect_atkcld(char *id, char *pwd)
{
    uint8_t ret;
    char cmd[64];
    
    sprintf(cmd, "AT+ATKCLDSTA=\"%s\",\"%s\"\r\n", id, pwd);
    ret = app_cat1_send_at_cmd(cmd, "CLOUD CONNECTED", 10000);
    if (ret == Err_CAT1_NONE)
    {
        return Err_CAT1_NONE;
    }
    else
    {
        return Err_CAT1_ERROR;
    }
}

/**
 * @brief       ESPDev断开原子云服务器连接
 * @param       无
 * @retval      Err_CAT1_NONE  : 断开原子云服务器连接成功
 *              Err_CAT1_ERROR: 断开原子云服务器连接失败
 */
uint8_t app_cat1_disconnect_atkcld(void)
{
    uint8_t ret;
    
    ret = app_cat1_send_at_cmd("AT+ATKCLDCLS", "CLOUD DISCONNECT", 500);
    if (ret == Err_CAT1_NONE)
    {
        return Err_CAT1_NONE;
    }
    else
    {
        return Err_CAT1_ERROR;
    }
}


///==esp-devs handle=====================================================================================

/***********************************************************************************
 * @brief (validated) init mqtt 
           (Not recommended) 
 * @param void
 * @return void
 
 *******************************************************************************
//step2,optional,restore the espdev------------------------------------------- 		
    ret  += app_cat1dev_restore();   
		app_atkmodule_uartrxmsg_poll();
		
//step3,optional,AT cmd test--------------------------------------------------  		
    ret += app_cat1_at_test();    
    app_atkmodule_uartrxmsg_poll();
	
************************************************************************************/								
uint8_t app_atkmodule_mqtt_init(char* username, char* password)
{
	  uint8_t ret = 0;
    char ip_buf[16] = {0};
		
//step0,optional,init espdev`s gpios------------------------------------------- 		
    ret = app_atkmodule_esp_init();
    if (ret == Err_CAT1_NONE)
    {
        printf("ESP-dev(mounted on ATK-MODLUE) inited++\r\n");

    }else{
        printf("ESP-dev(mounted on ATK-MODLUE) inits failed!\r\n");
        while (1)
        {
            RED_LED_TGG();
            stkdly_ms(200);
        }			
		}

//step1,necessary, reset the espdev by software-------------------------------  				
		ret = app_cat1dev_sftrst();          //软件复位 
		printf("Step1,reset espdev0 by codes...\r\n");
		if(ret == Err_CAT1_NONE){
			 app_atkmodule_uartrxmsg_poll(); 				
		}else{
			 printf("Err(%d) in app_cat1dev_sftrst()\r\n",ret);
		}							
		
//step2,necessary, set workmode-----------------------------------------------			
		ret = app_cat1_set_cwmode(EspCWM_Sta);   // Station模, TCP-client
		printf("Step2,set espdev0 to station...\r\n");
		if(ret == Err_CAT1_NONE){
			 app_atkmodule_uartrxmsg_poll(); 				
		}else{
			 printf("Err(%d) app_cat1_set_cwmode()\r\n",ret);
		}		

//step3,necessary,config mqtt cipsntp------------------------------------------ 				
		ret = app_mqtt_cfg_cipsntp("ntp1.aliyun.com");
		printf("Step3,Config espdev to Aliyun cipsntp...\r\n");
		if(ret == Err_CAT1_NONE){
			 app_atkmodule_uartrxmsg_poll(); 				
		}else{
			 printf("Err(%d) app_mqtt_cfg_cipsntp()\r\n",ret);
		}		
								
//step4,necessary, connect AP--------------------------------------------------  										
		printf("Step4,connect to AP->'%s'.....\r\n",username);
		ret = app_cat1_link_ap(username, password,0); // ("EDW201X","txhd349874");								
		if(ret == Err_CAT1_NONE){
		  	g_atkmoudle_esp_dev0.sta_dev = CAT1_Connect;
			  app_atkmodule_uartrxmsg_poll(); 				
		}else{
			 printf("Err(%d) app_cat1_link_ap()\r\n",ret);
		}		
		
//step5, follow needs,get the ip4-----------------------------------------------		
		printf("Step5,config mqttuser...\r\n");
		ret = app_mqtt_cfg_usr("esp8266&a1QSdqL2OX7", \
		"5569e8ebe8c0da77826a95d3078853455360e9c78b1ef2e4a6dd81db876856f4");	
		
		if(ret == Err_CAT1_NONE){
			 app_atkmodule_uartrxmsg_poll(); 				
		}else{
			 printf("Err(%d) app_mqtt_cfg_usr()\r\n",ret);
		}		
		   
//step6,necessary,config mqtt clientId--------------------------------------------	 
		printf("Step6,config mqtt clientId...\r\n");
		ret = app_mqtt_cfg_clientid(  \
		"a1QSdqL2OX7.esp8266|securemode=2\\,signmethod=hmacsha256\\,timestamp=1684598696978|");	
		
		if(ret == Err_CAT1_NONE){
			 app_atkmodule_uartrxmsg_poll(); 				
		}else{
			 printf("Err(%d) app_mqtt_cfg_clientid()\r\n",ret);
		}		

//step7,necessary,connect mqtt-hosturl-----------------------------------------------  	 
		printf("Step7,connect mqtt-hosturl...\r\n");
		ret = app_mqtt_conn_host("a1QSdqL2OX7.iot-as-mqtt.cn-shanghai.aliyuncs.com");	
		
		if(ret == Err_CAT1_NONE){
			 app_atkmodule_uartrxmsg_poll(); 				
		}else{
			 printf("Err(%d) app_mqtt_conn_host()\r\n",ret);
		}		
		
//step8,necessary,subscribe msg from mqtt-hosturl------------------------------------  	
		printf("Step8,subscribe msg from mqtt-hosturl...\r\n");
		ret = app_mqtt_cfg_subs("/a1QSdqL2OX7/esp8266/user/get");	
		
		if(ret == Err_CAT1_NONE){
			 g_atkmoudle_esp_dev0.sta_mqtt = Mqtt_IsSubs;
			 app_atkmodule_uartrxmsg_poll();
			 printf("Finished Mqtt-config steps+++++++++++++++++++++++++++++++++++\r\n\r\n");
       return 0;			
		}else{
			 printf("Err(%d) app_mqtt_conn_host()\r\n",ret);
		}	
//steps are finished-----------------------------------------------------------------	

		return 1;
}

/*********************************************************************************
 * @brief  (validated)Poll-proccess for UART/USART rx of LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           used to test atkmodule_uartrx in intterupt  
 * @param  void
 * @retval void
 *********************************************************************************/
uint8_t app_atkmodule_uartrxmsg_poll()
{
	  static uint8_t ret = 0;

    if(g_atkmodule_rxtkn_ovr){
		 	 printf("Begin##AtkModRec:%s(%dbytes)\r\nEnd##AtkModRec\r\n\r\n", \
			         g_atkmodule_rxbuff,g_atkmodule_rx_curcnt);
		   app_atkmodule_uartrx_rst();		
       ret = 	Err_CAT1_NONE ;		
		}else{
       ret = 	Err_CAT1_ERROR  ;					 
		}
		
		return ret;
} //<void app_atkmodule_uartrxmsg_poll()>

///==end esp-devs handle==========================================================================end====

/*----Endline : Full file-------------------------------------------------------------------------------All_End-----*/		