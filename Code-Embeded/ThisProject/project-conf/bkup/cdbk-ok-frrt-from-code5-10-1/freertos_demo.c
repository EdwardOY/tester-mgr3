/**
 ****************************************************************************************************
 * @file        freertos_demo.c
                 freeRTOS v10.4.6, heap4			                           
 * @platform    DMF407 STM32F407igt6
 * @brief，validated items       
       -1-，task1 
			    1.1 led0 toggles
					1.2 xQueueSelectFromSet(xQueueSet,time);接收队列集的激活
					  1.2.1 获取二值信号量和接收queue； 
						1.2.2 二值信号量或queue，二者只用其一 便能 解除task1的阻塞 ，激活一次解除一次阻塞
			 -2-，task2，upper通过串口，向dmcu bcom rx发送 指定的字符串文字命令来操作
			    2.1 挂起或恢复task1
			    2.2 向task1，释放二值信号量或 发送 queue1 & queue2 
			 -3-,etf_tsk_home，上位机向dbcom发送字符串命令去操控rtos
			 -4-,etf_tsk3,xQueue2(容纳4条消息，每条消息字符串长度是25bytes且能容纳25个有效字符串)
			     xQueue2是独立的队列，不加入任何队列集
 * @date        2023.3.13
 * @state       validated 
 * @author      Edwoy
 * @version     V1.1
 * @license     Copyright
 ****************************************************************************************************
 * @attention
      -1-,一个任务只能删除一次(重复删除会提示错误，但不会造成死机)
			    且一旦删除，就无法恢复
			-2-,only use AC5 and heap4 ,don`t use cmsis apis
			-3-,task1，xQueueSelectFromSet(xQueueSet,time);
           3.1 time == portMAX_DELAY ,本任务在未得到queueset的激活前，一直阻塞
           3.2 time < portMAX_DELAY , 任务等待time ms后，不管queueset有无响应，本任务都执行一次循环
					      每等待time 个cycle(一般是1ms),执行一次task1
           3.3 队列集等待任务中的queue接收和二值信号量获取函数里的等待时间是无效的，默认一直等待；
					     只有xQueueSelectFromSet(xQueueSet,time)中的time有效
					 3.4 task1 死循环里可以有延迟也可以删除延迟，默认是不要延迟
		  -4-,本项目的queue，长度为1 成功， 长度超过1时，也只传输第一个数据
          发数组的例程：  https://www.cnblogs.com/realiot/p/16279097.html	
      -5-,queueset 只支持queue和semaphore,不支持mutex		
      -6-,Independent queue -> xQueue2(don`t add to queueset),
			    6.1 testStrGrp&queue_recv  must be decorated with (void*)
				       xQueueSend(xQueue2, (void*)testStrGrp[i++],portMAX_DELAY); 	
			         xQueueReceive(xQueue2, (void*)queue_recv, 2000);  in etf_tsk3
          6.2  in etf_tsk3,xQueueReceive 中的等待时间是有效等待时间						 
 ****************************************************************************************************
 * @Knowledge note
      -1-, queue. 
			   1.0  https://blog.csdn.net/thisway_diy/article/details/121468922
			   1.1 queue = xQueueCreate(length , size);
			     1.1.1 size,单条消息的大小，单位byte; 例如 size = 16，则单条消息可以容纳 一条16个字符的字符串 
					 1.1.2 length,队列深度，即本队列 queue 最多存储多少条消息
					       length = 1，适用于不存在多个任务向同一个队列"同时"发送消息的情况。
								 length = n(n > 1), 一般用在多个任务和中断"同时"向同一个队列里发送消息的情况，深度越大，
								           消息队列接收就不会丢失信息。
								         
				 1.2 
 * @Details 
 *    -1-,Burn the same-type stm32 program into the corresponding gd32 , and then execute it.
      -2-,
			-3-,
			-4,
 * 
 ****************************************************************************************************
 * @Update,2023.3.13
 */

#include "freertos_demo.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/LED/led.h"
/*FreeRTOS*********************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

///==ATK-DMF407 codes===========================================================================================

///--Thread/Task paras-----------------------------------------------------------------------------------
/* START_TASK 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define START_TASK_PRIO 1                   /* 任务优先级 */
#define START_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            StartTask_Handler;  /* 任务句柄 */
void start_task(void *pvParameters);        /* 任务函数 */

/* TASK1 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK1_PRIO      2                   /* 任务优先级 */
#define TASK1_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task1Task_Handler;  /* 任务句柄 */
void task1(void *pvParameters);             /* 任务函数 */

/* TASK2 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK2_PRIO      3                   /* 任务优先级 */
#define TASK2_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task2Task_Handler;  /* 任务句柄 */
void task2(void *pvParameters);             /* 任务函数 */

//--AddingCodes Edwoy------------------------------------------------------------------------------------
char* testStrGrp[5] = {"EdwardOY","QueueSet","DMF407","FreeRTOSv10.4.6","2023.3.13"};

// etf_tsk_home 任务 配置----------------------------------------------------
#define Prio_TskHome     4                   /* 任务优先级 */
#define StkSize_TskHome  128                 /* 任务堆栈大小 */
TaskHandle_t             Hdr_TskHome;  /* 任务句柄 */
void etf_tsk_home(void *pvParameters);             /* 任务函数 */
// End etf_tsk_home 任务 配置--------------------------------------End-------

// etf_tsk3 任务 配置--------------------------------------------------------
#define Prio_Tsk3       4                   /* 任务优先级 */
#define StkSize_Tsk3    128                 /* 任务堆栈大小 */
TaskHandle_t             Hdr_Tsk3;        /* 任务句柄 */
void etf_tsk3(void *pvParameters);             /* 任务函数 */
// End etf_tsk3 任务 配置------------------------------------------End-------
//--queue2-------------------------------------------------------------------
QueueHandle_t         xQueue2;        //队列2 hdr
#define xQue2_Len     1 //队列深度，即队列最大一次可以存多少条消息
#define xQue2_Size    (25 * sizeof(char))
//--End queue2------------------------------------------------------End------
//--End AddingCodes Edwoy-------------------------------------------------------------------------End----

///--End Thread/Task paras----------------------------------------------------------------------------End------

///--QuequeSet membersparas------------------------------------------------------------------------------
static QueueSetHandle_t xQueueSet;          /* 定义队列集 */
QueueHandle_t            xQueue1;            /* 定义队列1 */
SemaphoreHandle_t        xSemaphore;         /* 定义二值信号量 */

#define QUEUE_LENGTH            1                                         /* 队列支持的消息个数 */
#define QUEUE_ITEM_SIZE         sizeof(uint32_t)                         /* 队列中每条消息的大小 */
#define SEMAPHORE_BINARY_LENGTH 1                                         /* 二值信号量的有效长度 */
#define QUEUESET_LENGTH         (QUEUE_LENGTH + SEMAPHORE_BINARY_LENGTH)  /* 队列集支持的消息个数 */
///--End QuequeSet membersparas-------------------------------------------------------------------End----

///--Enter Functions-------------------------------------------------------------------------------------------
/**
 * @brief       FreeRTOS例程入口函数
 * @param       无
 * @retval      无
 */
void freertos_demo(void)
{
    lcd_show_string(10, 10, 220, 32, 32, "STM32", RED);
    lcd_show_string(10, 47, 220, 24, 24, "Queue set", RED);
    lcd_show_string(10, 76, 220, 16, 16, "ATOM@ALIENTEK", RED);
    
    xTaskCreate((TaskFunction_t )start_task,            /* 任务函数 */
                (const char*    )"start_task",          /* 任务名称 */
                (uint16_t       )START_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )START_TASK_PRIO,       /* 任务优先级 */
                (TaskHandle_t*  )&StartTask_Handler);   /* 任务句柄 */
    vTaskStartScheduler();
}

/**
 * @brief       start_task
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* 进入临界区 */
    /* 创建队列集 */
    xQueueSet = xQueueCreateSet(QUEUESET_LENGTH);
    /* 创建队列 */
    xQueue1 = xQueueCreate(QUEUE_LENGTH, QUEUE_ITEM_SIZE);
    /* 创建二值信号量 */
    xSemaphore = xSemaphoreCreateBinary();
    /* 将队列和二值信号量添加到队列集 */
    xQueueAddToSet(xQueue1, xQueueSet);
    xQueueAddToSet(xSemaphore, xQueueSet);
	
//--Codes Edwoy-------------------------------------------------------
	  xQueue2 = xQueueCreate(xQue2_Len, xQue2_Size);  //(4, 25 * sizeof(char));
		if(NULL == xQueue2) {printf("Create queue2 failed!!\r\n");}
		else                {printf("Create queue2 successfully\r\n");}
//--End Codes Edwoy----------------------------------------End--------				
		
    /* 创建任务1 */
    xTaskCreate((TaskFunction_t )task1,
                (const char*    )"task1",
                (uint16_t       )TASK1_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK1_PRIO,
                (TaskHandle_t*  )&Task1Task_Handler);
    /* 创建任务2 */
    xTaskCreate((TaskFunction_t )task2,
                (const char*    )"task2",
                (uint16_t       )TASK2_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK2_PRIO,
                (TaskHandle_t*  )&Task2Task_Handler);
								
    /* 创建task3*/
    xTaskCreate((TaskFunction_t )etf_tsk3,
                (const char*    )"etf_tsk3",
                (uint16_t       )StkSize_Tsk3,
                (void*          )testStrGrp,   //NULL,
                (UBaseType_t    )Prio_Tsk3,
                (TaskHandle_t*  )&Hdr_Tsk3);
								
    /* 创建task home*/
    xTaskCreate((TaskFunction_t )etf_tsk_home,
                (const char*    )"etf_tsk_home",
                (uint16_t       )StkSize_TskHome,
                (void*          )NULL,
                (UBaseType_t    )Prio_TskHome,
                (TaskHandle_t*  )&Hdr_TskHome);
				
    vTaskDelete(StartTask_Handler); /* 删除开始任务 */
    taskEXIT_CRITICAL();            /* 退出临界区 */
}

/*********************************************************************
 * @brief       task1
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 * @notice
     -1-,xQueueSend(xQueue2,(void*)testStrGrp[i++], portMAX_DELAY)
         testStrGrp必须用(void*)修饰
 *
 *********************************************************************/
void task1(void *pvParameters)
{
    uint8_t key = 0 , i = 0;
 	  uint32_t pace = 0; 
  
    while (1)
    {       
        switch (key_scan(0))
        {
            case KEY0_PRES:                     /* 队列1发送消息 */
            {
							  if(0x08 <= key++) {key = 0;}
                xQueueSend(xQueue1, &key, portMAX_DELAY);
                break;
            }
            case KEY1_PRES:                     /* 释放二值信号量 */
            {
                xSemaphoreGive(xSemaphore);
                break;
            }
            case KEY2_PRES:                    // 队列2发送消息 
            {
							  xQueueSend(xQueue2,(void*)testStrGrp[i++], portMAX_DELAY);
							  if(i >= 5) {i = 0;}
                break;
            }						
            default:
            {
                break;
            }
        }
				
        if(NULL == pace++ % 33)			
		     	LED1_TOGGLE() ;
				
        vTaskDelay(10);
    }
}

/**
 * @brief       task2
 * @param       pvParameters : 传入参数(未用到)
 * @retval      无
 */
void task2(void *pvParameters)
{
    QueueSetMemberHandle_t  activate_member = NULL;
    uint32_t                queue_recv      = 0;
    
    while (1)
    {
        activate_member = xQueueSelectFromSet(xQueueSet, portMAX_DELAY);/* 等待队列集中的队列接收到消息 */
        
        if (activate_member == xQueue1)
        {
            xQueueReceive(activate_member, &queue_recv, portMAX_DELAY);
            printf("==>接收到来自xQueue1的消息: %d\r\n", queue_recv);
        }
        else if (activate_member == xSemaphore)
        {
            xSemaphoreTake(activate_member, portMAX_DELAY);
            printf("==>获取到二值信号量: xSemaphore(%#x)\r\n",(uint32_t)xSemaphore);
        }
    }
}
///--Enter Functions---------------------------------------------------------------------------------End-----
///==End ATK-DMF407 codes================================================================================End=====

///--AddingCodes Edwoy-------------------------------------------------------------------------------------------
/**
 * @brief (validated )etf_tsk_home
          Use dbcom to suspend or resume Task1Task_Handler and  xQueueSend xQueue1 xQueue2
 * @param  pvParameters : 传入参数(未用到)
 * @retval  无
 ***************1***********
   int tmp ;
	 tmp = strcmp((char*)g_usart_rx_buf,"Suspend task1");
 ***************2***********

 ***************3***********
      app_dbcom_rxdemo();
 */
void etf_tsk_home(void *pvParameters)
{

    uint8_t i = 0;
    uint8_t tmp_quevlu = 0x47; 
	
    for(;;)
    {

		 if (g_usart_rx_sta & 1 << 15)         /* 接收到了数据? */		
     {
			  printf("In task2,dbcom-rxstring is [%s]\r\n",(char*)g_usart_rx_buf);


			  if(NULL == strcmp((char*)g_usart_rx_buf,"Suspend task1")){
			     vTaskSuspend(Task1Task_Handler);
				
				}else if(NULL == strcmp((char*)g_usart_rx_buf,"Resume task1")){
			     vTaskResume(Task1Task_Handler);

			  }else if(NULL == strcmp((char*)g_usart_rx_buf,"QueSndTo task1")){
			     xQueueSend(xQueue1, &tmp_quevlu,portMAX_DELAY); // 

				}else if(NULL == strcmp((char*)g_usart_rx_buf,"QueSndTo task1")){
			     xQueueSend(xQueue1, &tmp_quevlu,portMAX_DELAY); // 
					
        }else if(NULL == strcmp((char*)g_usart_rx_buf,"QueSndTo task2")){
					 xQueueSend(xQueue2, (void*)testStrGrp[i++],portMAX_DELAY); // 	
					 if(i >= 5)  {i = 0;}		 
					 
				}else if(NULL == strcmp((char*)g_usart_rx_buf,"SemphGiveTo task1")){
			     xSemaphoreGive(xSemaphore);
			  }
				
			  app_dbcom_rst();			 
		 }


		 
     vTaskDelay(5);	
    }
}

/*********************************************************************
 * @brief    (validated ) etf_tsk3
             xQueue2是独立的，未加入队列集
 * @param    arg: 传入参数(未用到)
 * @retval      无
 * @notice
     -1-,xQueueReceive(xQueue2, (void*)queue_recv, 2000);
       1.1 queue_recv必须用(void*)修饰
       1.2 有效延时 2000ms 
 *
 *********************************************************************/
void etf_tsk3(void *arg)
{
  char* queue_recv = (char*)pvPortMalloc(xQue2_Size);  //or char queue_recv[xQue2_Size] = {0};
  BaseType_t osSta = pdFALSE; // = 0
	
	for(;;)
	{
			osSta  = xQueueReceive(xQueue2, (void*)queue_recv, 2000);  //portMAX_DELAY
		  if(pdPASS == osSta){
		   	printf("==>接收到来自xQueue2的消息: \'%s\'\r\n", queue_recv);
				memset(queue_recv,0,xQue2_Size);
				
     	}else{
		   	printf("In etf_tsk3,xQueue2 is idle or err(%#x)\r\n", (uint32_t)osSta);				
				
			}
	}
}
///--End AddingCodes Edwoy------------------------------------------------------------------------------End----
