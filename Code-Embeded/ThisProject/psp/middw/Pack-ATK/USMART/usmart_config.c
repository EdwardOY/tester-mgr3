#include "usmart.h"
#include "usmart_str.h"

/*********************************************************************************
			  ___   _     _____  _____  _   _  _____  _____  _   __
			 / _ \ | |   |_   _||  ___|| \ | ||_   _||  ___|| | / /
			/ /_\ \| |     | |  | |__  |  \| |  | |  | |__  | |/ /
			|  _  || |     | |  |  __| | . ` |  | |  |  __| |    \
			| | | || |_____| |_ | |___ | |\  |  | |  | |___ | |\  \
			\_| |_/\_____/\___/ \____/ \_| \_/  \_/  \____/ \_| \_/

 *	******************************************************************************
 *	本程序只供学习使用，未经作者许可，不得用于其它任何用途
 *	ALIENTEK Pandora STM32L IOT开发板
 *	USMART驱动代码
 *	正点原子@ALIENTEK
 *	技术论坛:www.openedv.com
 *	版本：V3.3
 *	版权所有，盗版必究。
 *	Copyright(C) 广州市星翼电子科技有限公司 2014-2024
 *	All rights reserved
 *	******************************************************************************/

////////////////////////////用户配置区///////////////////////////////////////////////
//这下面要包含所用到的函数所申明的头文件(用户自己添加)
#include "delay.h"
#include "sys.h"
#include "lcd.h"

extern void led_set(uint8_t sta);
extern void test_fun(void(*ledset)(uint8_t),uint8_t sta);	

//函数名列表初始化(用户自己添加)
//用户直接在这里输入要执行的函数名及其查找串
struct _m_usmart_nametab usmart_nametab[] =
{
#if USMART_USE_WRFUNS==1 	//如果使能了读写操作
    (void*)read_addr, "uint32_t read_addr(uint32_t addr)",
    (void*)write_addr, "void write_addr(uint32_t addr,uint32_t val)",
#endif
    (void*)delay_ms, "void delay_ms(uint16_t nms)",
    (void*)delay_us, "void delay_us(uint32_t nus)",

    (void*)LCD_DisplayOn, "void LCD_DisplayOn(void)",
    (void*)LCD_DisplayOff, "void LCD_DisplayOff(void)",
    (void*)LCD_Clear, "void LCD_Clear(uint16_t Color)",
    (void*)LCD_Fill, "void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)",
	(void*)LCD_Draw_Point,"void LCD_Draw_Point(uint16_t x, uint16_t y)",
	(void*)LCD_Draw_ColorPoint,"void LCD_Draw_ColorPoint(uint16_t x, uint16_t y,uint16_t color)",
	(void*)LCD_DrawLine,"void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)",
    (void*)LCD_DrawRectangle, "void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)",	
    (void*)LCD_Draw_Circle, "void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r)",
	(void*)LCD_ShowChar,"void LCD_ShowChar(uint16_t x, uint16_t y, char chr, uint8_t size)",
	(void*)LCD_ShowString, "void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p)",
    (void*)LCD_ShowNum, "void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size)",
    (void*)LCD_ShowxNum, "void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode)",
	(void*)Display_ALIENTEK_LOGO,"void Display_ALIENTEK_LOGO(uint16_t x,uint16_t y)",
		
	(void*)led_set,"void led_set(uint8_t sta)",
	(void*)test_fun,"void test_fun(void(*ledset)(uint8_t),uint8_t sta)",
};
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//函数控制管理器初始化
//得到各个受控函数的名字
//得到函数总数量
struct _m_usmart_dev usmart_dev =
{
    usmart_nametab,
    usmart_init,
    usmart_cmd_rec,
    usmart_exe,
    usmart_scan,
    sizeof(usmart_nametab) / sizeof(struct _m_usmart_nametab), //函数数量
    0,	  	//参数数量
    0,	 	//函数ID
    1,		//参数显示类型,0,10进制;1,16进制
    0,		//参数类型.bitx:,0,数字;1,字符串
    0,	  	//每个参数的长度暂存表,需要MAX_PARM个0初始化
    0,		//函数的参数,需要PARM_LEN个0初始化
};



















