/********************************************************************************************************
*
*	模块名称 : 主程序模块
*	文件名称 : main.c
*	版    本 : V1.0
*	说    明 : 按键检测（软件滤波和FIFO机制）。
*              实验目的：
*                1. 学习按键的按下，弹起，长按和组合键的实现。
*              实验内容：
*                1、启动一个自动重装软件定时器，每100ms翻转一次LED2。
*              实验内容：
*                1、3个独立按键和5向摇杆按下时均有串口消息打印。
*                2、5向摇杆的左键和右键长按时，会有连发的串口消息。
*                3、独立按键K1和K2按键按下，串口打印消息。
*              注意事项：
*                1. 本实验推荐使用串口软件SecureCRT查看打印信息，波特率115200，数据位8，奇偶校验位无，停止位1。
*                2. 务必将编辑器的缩进参数和TAB设置为4来阅读本文件，要不代码显示不整齐。
*
*	修改记录 :
*		版本号   日期         作者        说明
*		V1.0    2018-12-12   Eric2013     1. CMSIS软包版本 V5.4.0
*                                         2. HAL库版本 V1.3.0
*
*	Copyright (C), 2018-2030, 安富莱电子 www.armfly.com
*
********************************************************************************************************/	
#include "ThisProj_Glb.h"

void PrintfLogo(void);
void PrintfHelp(void);


/********************************************************************************************************
*	                                   查询阻塞式---示意代码
********************************************************************************************************/
void ButtonConfig(void)
{
	GPIO_InitTypeDef gpio_init;

	// 第1步：打开GPIO时钟 
	__HAL_RCC_GPIOI_CLK_ENABLE();

	// 第2步：配置所有的按键GPIO为浮动输入模式(实际上H7上电复位后是模拟输入) 
	gpio_init.Mode = GPIO_MODE_INPUT;   		  // 设置输入 
	gpio_init.Pull = GPIO_NOPULL;                 // 上下拉电阻不使能 
	gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;  // GPIO速度等级 
	gpio_init.Pin = GPIO_PIN_8;

	HAL_GPIO_Init(GPIOI, &gpio_init);	
}

void ButtonScan(void)
{
    // 检查是否按下 
    if((GPIOI->IDR & GPIO_PIN_8) == 0)
    {
        // 去抖 
        HAL_Delay(20);
        
        // 再次判断是否按下 
        if((GPIOI->IDR & GPIO_PIN_8) == 0)
        {
            printf("K1按下\r\n");
            
            // 等待松手 
            while((GPIOI->IDR & GPIO_PIN_8) == 0);
        }
    }
}

/********************************************************************************************************
*	                                   中断阻塞式---示意代码
********************************************************************************************************/
void ButtonConfigInt(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

	__HAL_RCC_GPIOI_CLK_ENABLE();

	// 配置GPIO，并开启下降沿中断 
	GPIO_InitStructure.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Pin = GPIO_PIN_8;
	HAL_GPIO_Init(GPIOI, &GPIO_InitStructure);

	// 设置中断优先级并开启中断 
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

	 // 设置设置滴答中断优先级，抢占优先级高于EXTI    
	HAL_NVIC_SetPriority(SysTick_IRQn, 1, 0);    
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_8)
	{
        // 中断里面做延迟，实际代码别这么用，我们这里仅仅式举例 
		HAL_Delay(20);
        
         // 再次判断是否按下 
        if((GPIOI->IDR & GPIO_PIN_8) == 0)
        {
            printf("K1按下\r\n");
            
            // 等待松手 
            while((GPIOI->IDR & GPIO_PIN_8) == 0);
        }
	}
}

void EXTI9_5_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
}


/*******************************************************************************************************
*	函 数 名: copied from armfly v007-keys-fir-fifo`s main
*	功能说明: c程序入口
*	形    参: 无
*	返 回 值: 错误代码(无需处理)

int sample_afl_keys(X_GPIO_T *pKeys)
********************************************************************************************************/

int sample_afl_keys(void)
{		
	// 按键滤波和检测由后台systick中断服务程序实现，我们只需要调用bsp_GetKey读取键值即可。 
	uint8_t ucKeyCode = bsp_GetKey();	// 读取键值, 无键按下时返回 KEY_NONE = 0 
	if (ucKeyCode != KEY_NONE)
	{
		switch (ucKeyCode)
		{
			case KEY_DOWN_K0:			// K0键按下 
				//printf("K0键按下\r\n");

			 //   pKeys_p[KID_K0].mFunc(pKeys_p[KID_K0].mArg);
			    app_custom_btn0(NULL);
				break;

			case KEY_UP_K0:				// K0键弹起 
				printf("K0键弹起\r\n");

				break;

			case KEY_DOWN_K1:			// K1键按下 
			//	printf("K1键按下\r\n");
			    //pKeys_p[KID_K1].mFunc(pKeys_p[KID_K1].mArg);
				app_custom_btn1(NULL);
				break;

			case KEY_UP_K1:				// K1键弹起 
				printf("K1键弹起\r\n");
				break;

			case KEY_DOWN_K2:			// K2键按下 
			//	printf("K2键按下\r\n");
				app_custom_btn2(NULL);
				break;

			case KEY_UP_K2:				// K2键弹起 
				printf("K2键弹起\r\n");
				break;

			case KEY_DOWN_WKUP:			// K3键按下 
			    app_custom_wkup(NULL);
			//	printf("WKUP键按下\r\n");
			//    pKeys_p[KID_WKUP].mFunc(pKeys_p[KID_WKUP].mArg);
				break;

			case KEY_UP_WKUP:				// K3键弹起 
				printf("WKUP键弹起\r\n");
				break;

				
			case SYS_DOWN_K1K2:			// 摇杆OK键弹起 
				printf("K1和K2组合键按下\r\n");
				break;

			case SYS_DOWN_K2K3:			// 摇杆OK键弹起 
				printf("WKUP和K2组合键按下\r\n");
				break;

			default:
				// 其它的键值不处理 
				break;
		}//<switch (ucKeyCode)>
	}

	return 0;
}

/***************
		switch (ucKeyCode)
		{
			case KEY_DOWN_K0:			// K0键按下 
				printf("K0键按下\r\n");
				break;

			case KEY_UP_K0:				// K0键弹起 
				printf("K0键弹起\r\n");
				break;

			case KEY_DOWN_K1:			// K1键按下 
				printf("K1键按下\r\n");
				break;

			case KEY_UP_K1:				// K1键弹起 
				printf("K1键弹起\r\n");
				break;

			case KEY_DOWN_K2:			// K2键按下 
				printf("K2键按下\r\n");
				break;

			case KEY_UP_K2:				// K2键弹起 
				printf("K2键弹起\r\n");
				break;

			case KEY_DOWN_WKUP:			// K3键按下 
				printf("WKUP键按下\r\n");
				break;

			case KEY_UP_WKUP:				// K3键弹起 
				printf("WKUP键弹起\r\n");
				break;

				
			case SYS_DOWN_K1K2:			// 摇杆OK键弹起 
				printf("K1和K2组合键按下\r\n");
				break;

			case SYS_DOWN_K2K3:			// 摇杆OK键弹起 
				printf("WKUP和K2组合键按下\r\n");
				break;

			default:
				// 其它的键值不处理 
				break;
		}//<switch (ucKeyCode)>

*********************************/

/********************************************************************
		switch (ucKeyCode)
		{
			case KEY_DOWN_K0:			// K0键按下 
				printf("K0键按下\r\n");
				break;

			case KEY_UP_K0:				// K0键弹起 
				printf("K0键弹起\r\n");
				break;

			case KEY_DOWN_K1:			// K1键按下 
				printf("K1键按下\r\n");
				break;

			case KEY_UP_K1:				// K1键弹起 
				printf("K1键弹起\r\n");
				break;

			case KEY_DOWN_K2:			// K2键按下 
				printf("K2键按下\r\n");
				break;

			case KEY_UP_K2:				// K2键弹起 
				printf("K2键弹起\r\n");
				break;

			case KEY_DOWN_WKUP:			// K3键按下 
				printf("K3键按下\r\n");
				break;

			case KEY_UP_WKUP:				// K3键弹起 
				printf("K3键弹起\r\n");
				break;

			case JOY_DOWN_U:			// 摇杆UP键按下 
				printf("摇杆上键按下\r\n");
				break;

			case JOY_DOWN_D:			// 摇杆DOWN键按下 
				printf("摇杆下键按下\r\n");
				break;

			case JOY_DOWN_L:			// 摇杆LEFT键按下 
				printf("摇杆左键按下\r\n");
				break;
			
			case JOY_LONG_L:            // 摇杆LEFT键长按 
				printf("摇杆左键长按\r\n");
				break;

			case JOY_DOWN_R:			// 摇杆RIGHT键按下 
				printf("摇杆右键按下\r\n");
				break;
			
			case JOY_LONG_R:            // 摇杆RIGHT键长按 
				printf("摇杆右键长按\r\n");
				break;

			case JOY_DOWN_OK:			// 摇杆OK键按下 
				printf("摇杆OK键按下\r\n");
				break;

			case JOY_UP_OK:				// 摇杆OK键弹起 
				printf("摇杆OK键弹起\r\n");
				break;
				
			case SYS_DOWN_K1K2:			// 摇杆OK键弹起 
				printf("K1和K2组合键按下\r\n");
				break;

			default:
				// 其它的键值不处理 
				break;
		}//<switch (ucKeyCode)>	
		

 ********************************************************************/

/********************************************************************************************************
*	函 数 名: PrintfHelp
*	功能说明: 打印操作提示
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************/
void PrintfHelp(void)
{
	printf("操作提示:\r\n");
	printf("1. 启动一个自动重装软件定时器，每100ms翻转一次LED2\r\n");
	printf("2. 3个独立按键和5向摇杆按下时均有串口消息打印\r\n");
	printf("3. 5向摇杆的左键和右键长按时，会有连发的串口消息\r\n");	
    printf("4. 独立按键K1和K2按键按下，串口打印消息\r\n");	
}

/********************************************************************************************************
*	函 数 名: PrintfLogo
*	功能说明: 打印例程名称和例程发布日期, 接上串口线后，打开PC机的超级终端软件可以观察结果
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************/
void PrintfLogo(void)
{
	printf("*************************************************************\n\r");
	
	// 检测CPU ID 
	{

#if G_THIS_PCR_FRAME  ==  ARM_CORTEX_M7
		uint32_t CPU_Sn0, CPU_Sn1, CPU_Sn2;		
		CPU_Sn0 = *(__IO uint32_t*)(0x1FF1E800);
		CPU_Sn1 = *(__IO uint32_t*)(0x1FF1E800 + 4);
		CPU_Sn2 = *(__IO uint32_t*)(0x1FF1E800 + 8);

		printf("\r\nCPU : STM32H743XIH6, BGA240, 主频: %dMHz\r\n", SystemCoreClock / 1000000);
		printf("UID = %08X %08X %08X\n\r", CPU_Sn2, CPU_Sn1, CPU_Sn0);
#endif // #if G_THIS_PCR_FRAME  ==  ARM_CORTEX_M7		
	}

	printf("\n\r");
	printf("*************************************************************\n\r");
	printf("* 例程名称   : %s\r\n", EXAMPLE_NAME);	// 打印例程名称 
	printf("* 例程版本   : %s\r\n", DEMO_VER);		// 打印例程版本 
	printf("* 发布日期   : %s\r\n", EXAMPLE_DATE);	// 打印例程日期 

	// 打印ST的HAL库版本 
	printf("* HAL库版本  : V1.3.0 (STM32H7xx HAL Driver)\r\n");
	printf("* \r\n");	// 打印一行空格 
	printf("*************************************************************\n\r");
}


