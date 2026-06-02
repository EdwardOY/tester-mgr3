/******************************************************************************************************
 * @file        lmbt.c
 * @brief       Bluetooth&BLE drive api src using serialport(UART/USART)-interface
 * @author      Edwoy
 * @version     V1.0
 * @date        2021-10-27
 * @license     Copyright (c) 2020-2032
 ****************************************************************************************************
 * @attention
       1  Add below int-defs to HAL_UART_MspInit() in usart.c
			      __HAL_UART_ENABLE_IT(uartHandle, UART_IT_RXNE); 
			 2 Basic dependency
					2.1 res_lmbt_uart.h/c, shell_uart.h/c, usart.h/c(by cubemx)
					2.2 utyBtBle.h	
			 3 BT-11
         3.1 max valid uart-baudrate is 115200bps	
				 3.2 Get the datas returned by bt11 waiting at least 4ms after sending cmd to bt11  
         3.2 Upper(PC-dbcom or cellphone BLEassist app) unlinks,and then links BtBle dev
       4				 
 ****************************************************************************************************
 * @note
 *    1 Default hard
          platform: ATK-DMF407
          module : BT-11 of LM(www.lbluetooth.com)		
      2 
 ****************************************************************************************************
 * @update
 *   V1.0 20211027 the orgn version from ATK-DMF407
 *
 ****************************************************************************************************
 */
 
#include "ThisProj_Glb.h"
#include CPT_BTBLE_HEAD  // "./component/spBtBle/lmbt/lmbt.h"
#include DLY_HEAD

///====BSP-BTBLE==========================================================================================
/********************************************************
 * @brief  (validated)bsp-init for lmbt-devs
 * @param       buadrate: ATK-MODULE UART通讯波特率
 * @retval      Err_BTBLE_NONE  : ATK-MODULE初始化成功
 *              Err_BTBLE_ERROR: ATK-MODULE初始化失败
 ********************************************************/
void bsp_lmbt_devs_init(void)
{
	 app_lmbt_exit_deepsleep() ;	
   stkdly_ms(__DlyMs_Lmbt);
	
	 app_lmbt_exit_lowpower() ;
   stkdly_ms(__DlyMs_Lmbt);
	
 	 app_lmbt_check_wkmd();
	 stkdly_ms(__DlyMs_Lmbt);
	
	 app_lmbt_set_powermode(CHECK_CMD_BTBLE) ; 
   stkdly_ms(__DlyMs_Lmbt);
	
   app_lmbt_setwkmd_dualslv_sppble(); //set workmode to dual-slave(spp&ble)
   stkdly_ms(__DlyMs_Lmbt);
	
	 app_lmbt_check_powermode() ;
   stkdly_ms(__DlyMs_Lmbt); 
	
	 app_lmbt_disconnect();
	 stkdly_ms(__DlyMs_Lmbt); 
	
   app_atkmodule_uartrx_polltst();
	 app_handle_lmbtdevsta_poll(g_atkmodule_rxbuff, &g_atkmoudle_lmbt_dev0);
}

/***************************************************
 * @brief  (validated) 
 * @param  void
 * @retval void
 ***************************************************/
uint8_t task_lmbt_rxmsg_poll(void)
{	
	static emBTBLE_DevState_t ret = BTBLE_Disconnect;
  static uint8_t *buf = g_atkmodule_rxbuff;
  static sttLMBT_DevParas_t* tmpdev = &g_atkmoudle_lmbt_dev0;	

  app_handle_lmbtdevsta_poll(buf, tmpdev); // get lmbt dev state
  if(True == g_atkmodule_rxtkn_ovr)
	{
		switch(tmpdev->state)
		{
			case BTBLE_Connect:
				buf = g_atkmodule_rxbuff;
				printf("TTconn-RxMsg:{%s}\r\n",buf);  
				break;
			
			case BTBLE_Ready:
			case BTBLE_Disconnect:

			  buf = app_atkmodule_get_uartrx_frame();
				printf("Disconn-RxMsg:{%s}\r\n",buf);  
				break;			
			
			default : break;
		}			
		
		app_atkmodule_uartrx_rst(); 
  }
	return ret;
}

/*******************************************************************
 * @brief (validated) tx message handle-poll
           1 BTBLE_Connect:	TTconnection,tx msg from dbcom	
			     2 BTBLE_Ready or BTBLE_Disconnect: AT cmds from dbcom
 * @param  void
 * @notice 
        -1-, dbcom rx dose not save "\r\n",usr must add it
 * @retval 
 ***************************************
 printf("ATcmd:%s; dbcom-rxlen = %d\r\n",cmd,g_dbcom_rx_curcnt);
 *******************************************************************/
uint8_t task_lmbt_txmsg_poll(void)
{	
	static emBTBLE_DevState_t ret = BTBLE_Disconnect;
  static uint8_t *buf = g_atkmodule_rxbuff;
  static sttLMBT_DevParas_t* tmpdev = &g_atkmoudle_lmbt_dev0;	

  app_handle_lmbtdevsta_poll(buf, tmpdev);

  if(True == g_dbcom_rxtkn_ovr)
	{
		switch(tmpdev->state)
		{
			case BTBLE_Connect:	 // TTconnection,tx msg from dbcom	
				app_atkmodule_uart_printf((char*)g_dbcom_rxbuff);
				break;			
				
			case BTBLE_Ready:
			case BTBLE_Disconnect: //AT cmds from dbcom
				if(NULL == strncmp((sc8_t*)g_dbcom_rxbuff,"AT+",3)) 
				{
					char cmd[12] = {0};
					sprintf(cmd,"%s\r\n",(char*)g_dbcom_rxbuff);
				  printf("ATcmd:%s; dbcom-rxlen = %d\r\n",cmd,g_dbcom_rx_curcnt);
			    app_atkmodule_uart_printf((char*)cmd);
					app_dbcom_rst(); 
          stkdly_ms(__DlyMs_Lmbt);
				}
        break;
			
			default : break;
		}			
	
    app_dbcom_rst(); 
  }//< if(True == g_dbcom_rxtkn_ovr)>
	
	return ret;
}


///====End BSP-BTBLE===============================================================================End====


///====Codes-LMBT=========================================================================================
///--lmbt-devs setting------------------------------------------------------------------------------
/*********************************************************************************
 * @brief  (validated) Set workmode for LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
 * @param  mode : work mode
								0       |     01    |     02    |        03       |     04     |
				 ---------------|-----------|-----------|-----------------|------------|
				 check workmode | BLE-Slave | SPP-Slave | slave BLE & SPP | BLE-Master |

 * @retval Err_BTBLE_NONE  : success
 *         Err_BTBLE_ERROR: error
 *********************************************************************************/
static uint8_t __lmbt_set_workmode(uint8_t mode)
{
    uint8_t ret;
		
    switch(mode)
		{
			case 0:
        app_atkmodule_uart_printf("AT+MASTER\r\n");  // app_free_printf(&g_atkmodule_hdr, "AT+MASTER\r\n", cmd);		
			  stkdly_ms(__DlyMs_Lmbt);
        ret = app_atkmodule_uartrx_polltst();
			  break;
			
			case 1:
			  ret = app_atkmodule_send_at_cmd("AT+MASTER=01", "OK", 1000); //Enable BLE-Slave
			  break;
			
			case 2:
			  ret = app_atkmodule_send_at_cmd("AT+MASTER=02", "OK", 1000); // Enable SPP-Slave
			  break;
			
			case 3:
			  ret = app_atkmodule_send_at_cmd("AT+MASTER=03", "OK", 1000); // Enable double slave, BLE & SPP 
			  break;	

			case 4:
			  ret = app_atkmodule_send_at_cmd("AT+MASTER=04", "OK", 1000); // Enable BLE-Master
			  break;		
			
			default: break;
		}
		
    if (ret != Err_BTBLE_NONE)
    {
        return Err_BTBLE_ERROR;
    }
    
    return Err_BTBLE_NONE;
}


/*********************************************************************************
 * @brief  (validated) Set ble-slave workmode for LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
 * @param  void
 * @retval void
 *********************************************************************************/
uint8_t app_lmbt_setwkmd_bleslv(void)
{
	uint8_t ret = __lmbt_set_workmode(0x1);
	return ret;
}

/*********************************************************************************
 * @brief  (validated) Set ble-master workmode for LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
 * @param  void
 * @retval Err_BTBLE_NONE  : success
 *         Err_BTBLE_ERROR: error
 *********************************************************************************/
uint8_t app_lmbt_setwkmd_blemtr(void)
{
	uint8_t ret = __lmbt_set_workmode(0x4);
	return ret;
}

/*********************************************************************************
 * @brief  (validated) Set SPP-Slave workmode for LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
 * @param  void
 * @retval Err_BTBLE_NONE  : success
 *         Err_BTBLE_ERROR: error
 *********************************************************************************/
uint8_t app_lmbt_setwkmd_sppslv(void)
{
	uint8_t ret = __lmbt_set_workmode(0x2);
	return ret;
}

/*********************************************************************************
 * @brief  (validated) Set SPP-BLE-Slave double workmode for LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
 * @param  void
 * @retval Err_BTBLE_NONE  : success
 *         Err_BTBLE_ERROR: error
 *********************************************************************************/
uint8_t app_lmbt_setwkmd_dualslv_sppble(void)
{
	uint8_t ret = __lmbt_set_workmode(0x3);
	return ret;
}

/*********************************************************************************
 * @brief  (validated) Check workmode for LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
 * @param  void
 * @retval void
 *********************************************************************************/
uint8_t app_lmbt_check_wkmd(void)
{
	uint8_t ret = __lmbt_set_workmode(0x00);
	return ret;
}

/**
 * @brief       设置ATK-MODULE b-type name
 * @param       name: 蓝牙名称
                  NULL,check namb
                  others,b-type name
 * @retval      Err_BTBLE_NONE  : 设置ATK-MODULE蓝牙名称成功
 *              Err_BTBLE_ERROR: 设置ATK-MODULE蓝牙名称失败
 */
uint8_t app_lmbt_set_name(char *name)
{
    uint8_t ret;
    char cmd[64];

    if(name == NULL){
			app_atkmodule_uart_printf("AT+NAME\r\n")		;
		  stkdly_ms(__DlyMs_Lmbt);
			ret = app_atkmodule_uartrx_polltst();
			
		}else{			
			sprintf(cmd, "AT+NAME=%s", name);
			ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);
		}	

    if (ret != Err_BTBLE_NONE)
    {
        return Err_BTBLE_ERROR;
    }
    
    return Err_BTBLE_NONE;
}


/**
 * @brief       设置ATK-MODULE b-type name
 * @param       name: 蓝牙名称
                  NULL,check namb
                  others,b-type name
 * @retval      Err_BTBLE_NONE  : 设置ATK-MODULE蓝牙名称成功
 *              Err_BTBLE_ERROR: 设置ATK-MODULE蓝牙名称失败
 */
uint8_t app_lmbt_set_namb(char *name)
{
    uint8_t ret;
    char cmd[64];

    if(name == NULL){
			app_atkmodule_uart_printf("AT+NAMB\r\n")		;
			stkdly_ms(__DlyMs_Lmbt);
			ret = app_atkmodule_uartrx_polltst();
			
		}else{			
			sprintf(cmd, "AT+NAMB=%s", name);
			ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);
		}	

    if (ret != Err_BTBLE_NONE)
    {
        return Err_BTBLE_ERROR;
    }
    
    return Err_BTBLE_NONE;
}

/*********************************************************************************
 * @brief  (validated) Set powermode and check it for LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
 * @param  dptm,
             0,Auto enter lowpower mode
             1, normal power mode
             others,Err_BTBLE_INVAL
 * @retval Err_BTBLE_NONE  : success
 *         Err_BTBLE_ERROR: error
           Err_BTBLE_INVAL , error 
 ******************************************************************			
	    case LMBT_PwrMd_CHK     :  // check power mode
					app_atkmodule_uart_printf("AT+PWRM\r\n");  
					stkdly_us(100);
					if(True == g_atkmodule_rxtkn_ovr)
					{
             if(NULL != strstr((sc8_t*)g_atkmodule_rxbuff,"+PWRM=0")){
							 g_atkmoudle_lmbt_dev0.state = BTBLE_LowPower;
						 }
						 app_atkmodule_uartrx_rst();
					}						
          break;	
 *********************************************************************************/
uint8_t app_lmbt_set_powermode(emLMBT_PwrMd_t pwr) 
{
    uint8_t ret;
    char cmd[16];
    assert_param(IS_VALID_PWRMD_LMBT(pwr)	);
	
    switch(pwr)
		{
      case LMBT_PwrMd_AutoLow :  // enable lowpower mode
					sprintf(cmd, "AT+PWRM=%d",pwr); 
					ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);				 
          break;			
			
      case LMBT_PwrMd_Normal  :  // enable normal power mode
					sprintf(cmd, "AT+PWRM=%d",pwr); 
					ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);				 				
          break;					

			
      default	:
				  ret = Err_BTBLE_INVAL;
          break;					
		}			

    
    return ret;
}

/*******************************************************************
 * @brief       Set RF-power grade for LM`s bluetooth&ble dev 
                using serialport(UART/USART)-interface
                LM(www.lbluetooth.com)
 * @param       pwr, enum RF-power grade
                    check it in res_spBTBLE.h
 * @retval      Err_BTBLE_NONE  : 
 *              Err_BTBLE_ERROR:
 *************************************************************/
uint8_t app_lmbt_set_rfpower(emLMBT_PwrGrd_t pwr)
{
    uint8_t ret;
    char cmd[16];
		
		if(CHECK_CMD_BTBLE == pwr){
			app_atkmodule_uart_printf("AT+POWE\r\n");
			stkdly_ms(4);
			ret = app_atkmodule_uartrx_polltst();			
			
		}else{
			assert_param(IS_VALID_PWRGRD_LMBT(pwr));
			sprintf(cmd, "AT+POWE=%d", pwr); // BT-11,
			ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);			
		}

    if (ret != Err_BTBLE_NONE)
    {
        return Err_BTBLE_ERROR;
    }
    
    return Err_BTBLE_NONE;
}

/*********************************************************************************
 * @brief  Set time entering lowpower for LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
 * @param  tm,time after that enter lowpower
             0,error
             others,enter lowpower after dptm s
 * @retval Err_BTBLE_NONE  : success
 *         Err_BTBLE_ERROR: error
  
 *********************************************************************************/
uint8_t app_lmbt_settime_intolowpower( uint8_t tm) 
{
    uint8_t ret;
    char cmd[16];
	  
	  if(tm == 0){
			ret = Err_BTBLE_INVAL;
			
		}else{
			sprintf(cmd, "AT+AST=%d",tm);   // enter normal power mode 
			ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);	
		}

    return ret;	
}
///--end lmbt-devs setting-------------------------------------------------------------------end----

///---lmbt-devs handle------------------------------------------------------------------------------

/********************************************
 * @brief       ATK-MODULE AT test
 * @param       无
 * @retval      Err_BTBLE_NONE     : success
 *              Err_BTBLE_TIMEOUT: error
 ********************************************/
uint8_t app_lmbt_at_test(void)
{
    uint8_t ret;
    uint8_t loop;
    
    for (loop=0; loop<10; loop++)
    {
        ret = app_atkmodule_send_at_cmd("AT+CMD", "OK", 100);
        if (ret == Err_BTBLE_NONE)
        {
            return Err_BTBLE_NONE;
        }
    }
    
    return Err_BTBLE_ERROR;
}


/*********************************************************************************
 * @brief   Disconnect LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
 * @param  void
 * @retval Err_BTBLE_NONE  : success
 *         Err_BTBLE_ERROR: error
 *********************************************************************************/
uint8_t app_lmbt_disconnect(void) 
{
    uint8_t ret;
    char cmd[16];

		sprintf(cmd, "AT+DSCET=1"); 
		ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);			

    if (ret != Err_BTBLE_NONE)
    {
        return Err_BTBLE_ERROR;
    }
    
    return Err_BTBLE_NONE;
}


/*********************************************************************************
 * @brief  (validated) Check powermode  for LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
 * @param  void
 * @retval Err_BTBLE_NONE  : success
 *        
 *********************************************************************************/
uint8_t app_lmbt_check_powermode(void) 
{
    uint8_t ret = Err_BTBLE_NONE;
    char cmd[16];
	
    ret = app_lmbt_check_wkmd();
   	stkdly_ms(__DlyMs_Lmbt);
	  app_atkmodule_uartrx_rst();
		app_atkmodule_uart_printf("AT+PWRM\r\n");  
		stkdly_ms(__DlyMs_Lmbt);
    
		if(True == g_atkmodule_rxtkn_ovr)
		{  
			
			 //Auto entering lowpower mode
			 if(NULL != strstr((sc8_t*)g_atkmodule_rxbuff,"\r\n+PWRM=0")){
				 g_atkmoudle_lmbt_dev0.state = BTBLE_LowPower;
			   printf("PwrMd-->AutoEnter Lowpower>>\r\n");
				 
				//Normal power mode 
			 }else if(NULL != strstr((sc8_t*)g_atkmodule_rxbuff,"\r\n+PWRM=1")){
				 g_atkmoudle_lmbt_dev0.state = BTBLE_Normal;
				 printf("PwrMd-->Enter Normalpower>>\r\n");
			 }
			 app_atkmodule_uartrx_rst();
		}						
   
    return ret;
}


/*********************************************************************************
 * @brief  (validated)Exit lowpower mode for LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
 * @param  void
 * @retval Err_BTBLE_NONE  : success
 *         Err_BTBLE_ERROR: error
  
 *********************************************************************************/
uint8_t app_lmbt_exit_lowpower(void) 
{
    uint8_t ret;
    char cmd[16];
	
		app_atkmodule_uart_printf("AT+ADVDATA\r\n"); //查询广播内容
    stkdly_ms(__DlyMs_Lmbt);  
		ret = app_atkmodule_uartrx_polltst();	
	
		sprintf(cmd, "AT+PWRM=1");   // enter normal power mode 
		ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);
    stkdly_ms(__DlyMs_Lmbt);  	
    printf("BTBLE has exit from lowpower-mode\r\n\r\n");
	
    if (ret != Err_BTBLE_NONE)
    {
        return Err_BTBLE_ERROR;
    }
    return Err_BTBLE_NONE;
}


/*********************************************************************************
 * @brief   Enter deepsleep and check dptim for LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
 * @param  dptm,time to enter deepsleep
             0,error
             0xcf,=CHECK_CMD_BTBLE,check how many seconds to enter deep sleep
             others(IS_VALID_DEEPSLP_LMBT) ,enter deepsleep after dptm s
 * @retval Err_BTBLE_NONE  : success
 *         Err_BTBLE_ERROR: error
  
 *********************************************************************************/
uint8_t app_lmbt_enter_deepsleep( uint8_t dptm) 
{
    uint8_t ret;
    char cmd[16];
	  		
		if(dptm < LMBT_DeepSleep_Min){
		  printf("Error para,at line%d-<file:%s>,<func:%s>!!!!  \r\n", \
			                      __LINE__,__FILE__,__FUNCTION__);
			return Err_BTBLE_INVAL;
			
		}else if(IS_VALID_DEEPSLP_LMBT(dptm)){
			
			sprintf(cmd, "AT+AUST=%d",dptm); 
			ret = app_atkmodule_send_at_cmd(cmd, "OK", 70);
			if(ret == Err_BTBLE_TIMEOUT){
				 ret = Err_BTBLE_ERROR;
				
			}else{		
					printf("BTBLE will enter deepsleep after %d s\r\n",dptm);	
					stkdly_s((uint8_t)dptm);
					g_atkmoudle_lmbt_dev0.state = BTBLE_DeepSleep;
					printf("BTBLE entered deepsleep.\r\n");	   				
			}
			
		}else if(dptm == CHECK_CMD_BTBLE){
			app_atkmodule_uart_printf("AT+AUST\r\n");  
			stkdly_ms(__DlyMs_Lmbt);
			ret = app_atkmodule_uartrx_polltst();					
		}

    if (ret != Err_BTBLE_NONE)
    {
        return Err_BTBLE_ERROR;
    }
    
    return Err_BTBLE_NONE;
}

/*********************************************************************************
 * @brief  (validated)Exit deepsleep for LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
 * @param  void
 * @retval Err_BTBLE_NONE  : success
 *         Err_BTBLE_ERROR: error
 *******************************************************************************
  g_atkmoudle_lmbt_dev0.state ,app_atkmodule_get_uartrx_frame
 *********************************************************************************/
uint8_t app_lmbt_exit_deepsleep(void) 
{
    uint8_t ret;
    char cmd[16];
	
		app_atkmodule_uart_printf("AT+MASTER\r\n");  //check name on daul-workmode 
    stkdly_ms(__DlyMs_Lmbt); 
		ret = app_atkmodule_uartrx_polltst();	
	
		sprintf(cmd, "AT+AUST=0"); 
		ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);
	  stkdly_ms(__DlyMs_Lmbt); 
    printf("BTBLE has exit from deepsleep\r\n\r\n");
	
    if (ret != Err_BTBLE_NONE)
    {
        return Err_BTBLE_ERROR;
    }
    
    return Err_BTBLE_NONE;
}

/****************************************************************
 * @brief  (validated)Reset the btble-dev
 * @param       void
 * @retval      Err_BTBLE_NONE  : 设置ATK-MODULE蓝牙名称成功
 *              Err_BTBLE_ERROR: 设置ATK-MODULE蓝牙名称失败
 **************************************************************/
uint8_t app_lmbt_dev_rst(void)
{
    uint8_t ret;
    char cmd[64];

		sprintf(cmd, "AT+RESET");
		ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);
	  
	  stkdly_ms(__DlyMs_Lmbt);
    ret = app_atkmodule_uartrx_polltst();
	
    if (ret != Err_BTBLE_NONE)
    {
        return Err_BTBLE_ERROR;
    }
    
    return Err_BTBLE_NONE;
}

/***************************************************
 * @brief  Poll, handle lmbt dev`s state polly
           validated 
 * @param  void
 * @notice 
        -1-, must disable app_atkmodule_uartrx_polltst()
             
 * @retval invalid value
 *******************************************
 app_atkmodule_uartrx_rst();
 ***************************************************/
uint8_t app_handle_lmbtdevsta_poll(uint8_t* buf,sttLMBT_DevParas_t* dev)
{	
	static uint8_t ret = 0;
	
	if((BTBLE_Connect != dev->state ) && \
		 (NULL != strstr((const char *)buf, "IM_CONN"))) 
	{
			dev->state = BTBLE_Connect;
			printf("LmbtDev is connected\r\n\r\n");
		
	}
	else if ((BTBLE_Ready != dev->state )  && \
					 (NULL != strstr((const char *)buf, "IM_READY")))
	{
			dev->state = BTBLE_Ready;		
			printf("LmbtDev is ready\r\n\r\n");
		
	}
	else if ((BTBLE_Disconnect != dev->state )  &&  \
					 (NULL != strstr((const char *)buf, "IM_DISC")) )
	{
			dev->state = BTBLE_Disconnect;
			printf("LmbtDev is disconnected\r\n\r\n");		
	}	

//	switch(dev->state)
//	{
//		case BTBLE_Connect :
//			
//		default :break;
//	}
	return ret;
}


///--end lmbt-devs handle--------------------------------------------------------------------end----


///--lmbt-devs uart---------------------------------------------------------------------------------
/*******************************************************************
 * @brief       Set uart`s baudrate for LM`s bluetooth&ble dev 
                using serialport(UART/USART)-interface
                LM(www.lbluetooth.com)
 * @param       baudrate, checked em_lmbt_uart_baud_t 
                in res_spBTBLE.h
 * @retval      Err_BTBLE_NONE  : 
 *              Err_BTBLE_ERROR: 
 ******************************************************************/
uint8_t app_lmbt_set_uart_baud(em_lmbt_uart_baud_t  baudrate)
{
    static uint8_t ret = 0;
    char cmd[24];
    assert_param(IS_VALID_UART_BAUDRATE_LMBT(baudrate));
    	
	  if(baudrate == CHECK_CMD_BTBLE){
			app_atkmodule_uart_printf("AT+BAUD\r\n");
			stkdly_ms(__DlyMs_Lmbt);
			ret = app_atkmodule_uartrx_polltst();			

		}else {			
			sprintf(cmd,"AT+BAUD=%d",baudrate)		;
			ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);
    }
		
    if (ret != Err_BTBLE_NONE)
    {
        return Err_BTBLE_ERROR;
    }
    
    return Err_BTBLE_NONE;
}

/*******************************************************************
 * @brief       Set uart`s baudrate for LM`s bluetooth&ble dev 
                using serialport(UART/USART)-interface
                LM(www.lbluetooth.com)
 * @param       baudrate, checked em_lmbt_uart_baud_t 
                in res_spBTBLE.h
 * @retval      Err_BTBLE_NONE  : ATK-MODULE进入配置模式成功
 *              Err_BTBLE_ERROR: ATK-MODULE进入配置模式失败
 ******************************************************************/
uint8_t app_lmbt_set_uart_stop(em_lmbt_uart_stop_t stop)
{
    uint8_t ret = 0;
    char cmd[16];

    if(stop == CHECK_CMD_BTBLE){
			app_atkmodule_uart_printf("AT+STOP\r\n");
			stkdly_ms(__DlyMs_Lmbt);
			ret = app_atkmodule_uartrx_polltst();		
			
		}else {			
			sprintf(cmd,"AT+STOP=%d",stop)		;
			ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);
    }
		
    if (ret != Err_BTBLE_NONE)
    {
        return Err_BTBLE_ERROR;
    }
    
    return Err_BTBLE_NONE;
}


/*******************************************************************
 * @brief       设置ATK-MODULE串口参数
 * @param       baudrate: 波特率
 *              data    : 数据位
 *              pari    : 校验位
 *              stop    : 停止位
 * @retval      Err_BTBLE_NONE   : 设置ATK-MODULE串口参数成功
 *              Err_BTBLE_ERROR : 设置ATK-MODULE串口参数失败
 *              Err_BTBLE_INVAL: 函数参数错误
                           em_lmbt_uart_pari_t     pari,     \
                           em_lmbt_uart_stop_t     stop
 ******************************************************************/
uint8_t app_lmbt_set_uart_flow(em_lmbt_uart_stop_t flow)
{
    uint8_t ret = 0 ;
    char cmd[16];
		
    if(flow == CHECK_CMD_BTBLE){
			app_atkmodule_uart_printf("AT+FLOW\r\n");
			stkdly_ms(__DlyMs_Lmbt);
			ret = app_atkmodule_uartrx_polltst();		
			
		}else {			
			sprintf(cmd,"AT+FLOW=%d",flow)		;
			ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);
    }
		
    if (ret != Err_BTBLE_NONE)
    {
        return Err_BTBLE_ERROR;
    }
    
    return Err_BTBLE_NONE;
}


/*******************************************************************
 * @brief       设置ATK-MODULE串口参数
 * @param       baudrate: 波特率
 *              data    : 数据位
 *              pari    : 校验位
 *              stop    : 停止位
 * @retval      Err_BTBLE_NONE   : 设置ATK-MODULE串口参数成功
 *              Err_BTBLE_ERROR : 设置ATK-MODULE串口参数失败
 *              Err_BTBLE_INVAL: 函数参数错误
                           em_lmbt_uart_pari_t     pari,     \
                           em_lmbt_uart_stop_t     stop
 ******************************************************************/
uint8_t app_lmbt_set_uart_parity(em_lmbt_uart_stop_t pari)
{
    uint8_t ret = 0;
    char cmd[16];	

    if(CHECK_CMD_BTBLE == pari){
			app_atkmodule_uart_printf("AT+PARI\r\n")		;
			stkdly_ms(__DlyMs_Lmbt);
			ret = app_atkmodule_uartrx_polltst();
			
		}else{			
			sprintf(cmd,"AT+PARI=%d",pari)		;
			ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);
		}
		
    if (ret != Err_BTBLE_NONE)
    {
        return Err_BTBLE_ERROR;
    }
    
    return Err_BTBLE_NONE;		
}

/**************************************************************
 * @brief       (validated)设置ATK-MODULE串口参数
 * @param       baudrate: 波特率
 *              data    : 数据位
 *              pari    : 校验位
 *              stop    : 停止位
                flow ,   hardflow
 * @retval      Err_BTBLE_NONE   : 设置ATK-MODULE串口参数成功
 *              Err_BTBLE_ERROR : 设置ATK-MODULE串口参数失败
 *              Err_BTBLE_INVAL: 函数参数错误
 **************************************************
ret = app_atkmodule_uartrx_polltst()
 ***************************************************************/
uint8_t app_lmbt_config_uart(em_lmbt_uart_baud_t      baudrate, \
                             em_lmbt_uart_pari_t      pari,     \
                             em_lmbt_uart_stop_t      stop,     \
                             em_lmbt_uart_hardflow_t  flow      )
{
    uint8_t ret;
    char cmd[24];

	  if(baudrate == CHECK_CMD_BTBLE){
			app_atkmodule_uart_printf("AT+BAUD\r\n");
      stkdly_ms(__DlyMs_Lmbt);
			if(True == g_atkmodule_rxtkn_ovr)
			{
				printf("atkuart-baud<%s>\r\n",g_atkmodule_rxbuff);	
				app_atkmodule_uartrx_rst();
			}

		}else if(IS_VALID_UART_BAUDRATE_LMBT(baudrate)) {			
			sprintf(cmd,"AT+BAUD=%d",baudrate)		;
			ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);
			
    }else {
			ret = Err_BTBLE_INVAL;
		}
		
    if(pari == CHECK_CMD_BTBLE){
			app_atkmodule_uart_printf("AT+PARI\r\n");
			stkdly_ms(__DlyMs_Lmbt);
			if(True == g_atkmodule_rxtkn_ovr)
			{
				printf("atkuart-pari<%s>\r\n",g_atkmodule_rxbuff);
				app_atkmodule_uartrx_rst();
			}
			
		}else if(IS_VALID_UART_PARI_LMBT(baudrate)) {			
			sprintf(cmd,"AT+PARI=%d",pari)		;
			ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);
      
    }else {
			ret = Err_BTBLE_INVAL;
		}
		

    if(stop == CHECK_CMD_BTBLE){
			app_atkmodule_uart_printf("AT+STOP\r\n");
			stkdly_ms(__DlyMs_Lmbt);
			if(True == g_atkmodule_rxtkn_ovr)
			{
				printf("atkuart-stop<%s>\r\n",g_atkmodule_rxbuff);
				app_atkmodule_uartrx_rst();
			}
		
		}else if(IS_VALID_UART_STOP_LMBT(stop)){			
			sprintf(cmd,"AT+STOP=%d",stop)		;
			ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);
			
    }else {
			ret = Err_BTBLE_INVAL;
		}
		
    if(flow == CHECK_CMD_BTBLE){
			app_atkmodule_uart_printf("AT+FLOW\r\n");
			stkdly_ms(__DlyMs_Lmbt);
			if(True == g_atkmodule_rxtkn_ovr)
			{
				printf("atkuart-hdflow<%s>\r\n\r\n",g_atkmodule_rxbuff);
				app_atkmodule_uartrx_rst();
			}
			
		}else if(IS_VALID_UART_FLOW_LMBT(flow)){			
			sprintf(cmd,"AT+FLOW=%d",flow)		;
			ret = app_atkmodule_send_at_cmd(cmd, "OK", 100);
			
    }else{
			ret = Err_BTBLE_INVAL;
		}

    return Err_BTBLE_NONE;
}


/*********************************************************************************
 * @brief  (validated)Poll-proccess for UART/USART rx of LM`s bluetooth&ble dev 
           using serialport(UART/USART)-interface
           LM(www.lbluetooth.com)
           used to test atkmodule_uartrx in intterupt  
 * @param  void
 * @retval void
 *********************************************************************************/
uint8_t app_atkmodule_uartrx_polltst()
{
	  static uint8_t ret = 0;

    if(True == g_atkmodule_rxtkn_ovr){
		   printf("Rec:<%s>\r\n",g_atkmodule_rxbuff);
		   app_atkmodule_uartrx_rst();		
       ret = 	Err_BTBLE_NONE ;		
		}else{
       ret = 	Err_BTBLE_ERROR  ;					 
		}
		
		return ret;
} //<void app_atkmodule_uartrx_polltst()>

///--end lmbt-devs uart----------------------------------------------------------------------end----

///====End Codes-LMBT==============================================================================End====



/*----Endline : Full file--------------------------------------------------------------------------All-End---*/


