/*****
* @Filename : utility_def.c
* @Mcu : all mcus
*	@Platform �� all development platforms 
* @brief : Defines common variables and parameters 
              for all development platforms             
* @Author : EDW.OY
* @version V2.1
* @StartDate : 2022.7.24 
* @Copyright(C)  SAE Magnetics (H.K) LTD.  2014-2024  All rights released	
*****************************************************************************
* @attention : 
    0 Common info
		  0.1 Based on NEC PWM prot
*   1 Devellop platform : Pandora STM32L475VET6(LQFP100)
*     1.1 
*     1.2
*   2 Devellop platform : Apollo STM32G457QEL(LQFP128)         
      2.1
	  3 Glb_Var32Ex glbf_mkvar32_ex 
		4
	*****************************************************************************			
	@Update:  
	  V2.1 2022.7.24 line353~line404,Imprecise delay
	  V2.0 2021.5.10  Glb_Var32_Ex PJTPRM_NUM_GLBVAR_EX(ThisProj_Glb.h)
	  2021.1.16, �� Glb_Var32��ص�apis ���и�������
	  2020.12.14  add apis umf_set_glbvar3232bit & umf_setbit_glbvar32_ex
		               ��Glb_Var32(Ex)����λ����
								getbit_glbvar32 ��ȡָ��bit��ֵ
	  2020.12.7 , add Glb_Var32Ex,glbf_mkvar(),and glbf_mkvar32_ex() 
		2020.11.24, expand array-Glb_Var32 members to  GLBVARn_DFT; 
		            umf_set_glbvar32( u8_t no, u32_t val) ��������u32_t��ֵ
    	
*/	
#include "ThisProj_Glb.h"

#include UTY_TYP_HEAD
#include UTY_DEF_HEAD


// ATK LCD params
u16_t Color_Pre   = 0;
u16_t	POINT_COLOR = BLACK;	//LCD default point color�� black default
u16_t	BACK_COLOR 	= WHITE;	//LCD backlight color

/** XcomToken: ATK Xcom(serialport debug port) token
  *----------------------------------------------------------------
  *  Bit |   31~16  |   15   |   14  | 13 | 12 |  11~ 0
	* -----|----------|--------|-------|-------------------------------
	* Func | reserved |  RxFsh | Rx1st | rx-datas num(Reserved unused)
  *----------------------------------------------------------------
	*/
unsigned int XcomToken ;

// Global 8bit variables
u8_t  ErrCode_8bit = 0xef ;

/*pjDlpGrlId = General ID of project development 项目开发总代号， 
 * const long double类型,128bit
 */
fc128_t pjDlpGrlId;  
fc64_t H_pjDlpGrlId;  //pjDlpGrlId`s High 64bit
fc64_t L_pjDlpGrlId;  //pjDlpGrlId`s Low  64bit

/**
  *@brief utility api: 求log(2)X
  *@param: num-->目标数值
	*@return 以2为底，Num的对数
  *@update 2022.10.30,
 */
double ulf_log2(u32_t num)
{	
//	static double x,y;
//	x = log(num);
//	y = log(2);
//	x /= y;
  return log(num) / log(2);   
}


/************
 Global 32bit variables
 (MCU internal SRAM ), 
 used for usmt setting
***************/
u32_t Glb_Var32[GLBVARn_DFT] = {0}; // MCU internal SRAM ,orgn GLBVARn_DFT

/*
*@brief usmart api: 设置存储在MCU内部sram内的数组成员Glb_Var32[x] 的值
*@param: no-->数组Glb_Var32成员序号； 
         val-->设置的目标值
 @return val 设置成功返回值全部为val，
             设置失败 高8位是0xef
*@update 
   2020.12.14,created
*/
u32_t umf_set_glbvar32( u8_t no, u32_t val)
{
	
	if(no <= GLBVARn_DFT)
	   Glb_Var32[no] = val;
	else 
	   return (u32_t)(0xef << 24);
	
	return val;
}

/*
*@brief usmart api: 
        对Glb_Var32[x](存储在MCU内部sram) 进行位操作
*@param: no-->数组Glb_Var32Ex成员序号；
         bit-->成员变量目标操作位数
         val-->成员变量目标操作值(0,1)大于1则设置成1
 @return Glb_Var32[no]
*@update 
   2021.1.16, oldname 'umf_set_glbvar32bit' ->
              newname 'umf_setbit_glbvar32'
   2020.12.14, created
*/
u32_t umf_setbit_glbvar32( u8_t no,u8_t bit, u8_t val)
{	
	if(no >= GLBVARn_DFT  )
	   no  = GLBVARn_DFT - 1 ;
	if(bit > 31)	
		 bit = 31;	
	
	if(val){
     Glb_Var32[no] |=  1 << bit;			
	} else {
     u32_t v_t = ~(1 << bit );   
     Glb_Var32[no] &= v_t;	   
	}
	return Glb_Var32[no];
}

/*
*@brief 获取Glb_Var32[x] (存储在MCU内部sram的数组成员) bit位的值
*@param: no-->数组Glb_Var32成员序号；
         bit-->成员变量目标操作位数
 @return Glb_Var32[no].bit
*@update 
   2021.5.10 用PJTPRM_NUM_GLBVAR_EX去约束存储在外扩ram上的 glbvar32
   2021.1.16, oldname 'get_glbvar32bit' ->
              newname 'getbit_glbvar32'
   2020.12.14, created
*/
u8_t getbit_glbvar32(u8_t no,u8_t bit)
{
	if(no >= GLBVARn_DFT  )
	   no  = GLBVARn_DFT - 1 ;
	
	if(bit > 31)	
		 bit = 31;
	
	return (0x01 & Glb_Var32[no] >> bit);
}


#if CMPL_PJTTL_MLC 
#include MLC_HEAD


/************
 Global 32bit variables
 (MCU Fmc External extend SDRAM), 
 used for usmt setting
***************/

u32_t* Glb_Var32Ex = NULL;   //  external extend RAM

#if  PJTPRM_NUM_GLBVAR_EX 
/*
*@brief Global api:��ָ����ʽ����ȫ�ֹ�����32bit����,
                   �洢��FMC��չSDRAM��
*@param: num-->������Ŀ
*@attenion :				 
*@update 
   2020.12.8,created
*/
u32_t* glbf_mkvar32_ex(u8_t num)
{	
	Glb_Var32Ex = (u32_t*)api_malloc(sFmcSdm,4 * num);		
	return  Glb_Var32Ex;
}

/*
*@brief usmart api: ���ô洢���ⲿram�ڵ������ԱGlb_Var32Ex[x] ��ֵ
*@param: no-->����Glb_Var32Ex��Ա��ţ� 
         val-->���õ�Ŀ��ֵ
 @return val
*@update 
   2020.12.8 created

*/

u32_t umf_set_glbvar32_ex( u8_t no, u32_t val)
{
	
	if(no >= PJTPRM_NUM_GLBVAR_EX )
	   no  = PJTPRM_NUM_GLBVAR_EX - 1 ;
	
	Glb_Var32Ex[no] = val;
	
	return val;
}


/*
*@brief usmart api: 
        ��Glb_Var32Ex[x](�洢��FMC��չSDRAM�ڵ������Ա) ����λ����
*@param: no-->����Glb_Var32Ex��Ա��ţ�
         bit-->��Ա����Ŀ�����λ
         val-->��Ա����Ŀ�����ֵ(0,1)����1�����ó�1
 @return Glb_Var32Ex[no]
*@update 
   2021.1.16, oldname 'umf_set_glbvar32bit_ex' ->
              newname 'umf_setbit_glbvar32_ex'
   2020.12.14, created
     u32_t v_t = ~(1 << bit );   
     Glb_Var32Ex[no] &= v_t;	  
*/
u32_t umf_setbit_glbvar32_ex( u8_t no,u8_t bit, u8_t val)
{	
	if(no >= PJTPRM_NUM_GLBVAR_EX )
	   no  = PJTPRM_NUM_GLBVAR_EX - 1 ;
	if(bit > 31)	
		 bit = 31;	
	
	if(val){
     Glb_Var32Ex[no] |=  1 << bit;			
	} else {
     Glb_Var32Ex[no] &= ~(1 << bit );	   
	}
	
	return Glb_Var32Ex[no];
}

/*
*@brief ��ȡGlb_Var32Ex[x] (�洢���ⲿram�ڵ������Ա) bitλ��ֵ
*@param: no-->����Glb_Var32Ex��Ա��ţ�
         bit-->��Ա����Ŀ�����λ��
 @return Glb_Var32Ex[no].bit
*@update
   2021.1.16, oldname 'get_glbvar32bit_ex' ->
              newname 'getbit_glbvar32_ex'
   2020.12.14,created
*/
u8_t getbit_glbvar32_ex(u8_t no,u8_t bit)
{
	if(no >= PJTPRM_NUM_GLBVAR_EX )
	   no  = PJTPRM_NUM_GLBVAR_EX - 1 ;
	
	if(bit > 31)	
		 bit = 31;
	
	return (0x01 & Glb_Var32Ex[no] >> bit);
}

#endif  //<end: PJTPRM_NUM_GLBVAR_EX >

#endif  //<end:CMPL_PJTTL_MLC >



sc32_t  LcdColorTabAtk[LcdColorsNum_Atk] = {	
	          BLACK,   BLUE,     BRED,    WHITE,     GRED,  GBLUE,    RED,  
          	MAGENTA, GREEN,    CYAN,    YELLOW,    BROWN, BRRED,    GRAY,
	          DARKBLUE,LIGHTBLUE,GRAYBLUE,LIGHTGREEN,LGRAY, LGRAYBLUE,LBBLUE
          };


// ����ң��������ֵ
u8_t AtkIfrd_Tab_Vlu[AtkIfrd_Btn_Num ] = {
        162,   98,     2,   194,   34,   224,  
	      168,   144,   104,  152,   176,  48,   
	      24,    122,   16,   56,    90,   66,   
      	82,    226,		0	
};

//����ң����������Ӧ���ַ�
u8_t AtkIfrd_Tab_Str[AtkIfrd_Btn_Num][16] = {
    "Power",  "Up",     "PLAY",   "RIGHT",  "LEFT",  "VOL-", 
   	"DOWN",   "VOL+",   "1",       "2",       "3",     "4",    
   	"5",      "6",      "7",       "8",       "9",     "0",     
	  "DELETE", "EDWOY",  "None"
};	
				

//�����������ò��Ժ���
void umf_vluled(void(*ledset)(u8_t),u8_t sta)
{
	ledset(sta);
} 

/************************
*@brief  Global api: Mcu���ʽ���ָʾ��
*@update 2020.12.6, old ver->subfun_mcu_pace
**************************/
//void glbf_mcupace()
//{
//	static u32_t pace = 0;
//#if   (THIS_BOARD  == BRD_ATK_PDR475)
//  u16_t y = 222;	 
//#elif (THIS_BOARD  == BRD_ATK_APLO429)
//	u16_t y = 302;
//#elif (THIS_BOARD  == BSP_BD_ATK_APLO_F767)
//  u16_t y = 580;
//#endif	
//	
//	if(!(pace % 30)){
//		SysRun_LedTgg ;	
//		pace = 0x0;
//		
//	}
//	if(pace ++ > 0xffffee)
//		pace = 0;
//	
//#if CMPL_RTC && CMPL_PJT_LCD 
//   	lcd_display_rtc(3,y, 127 , DARKBLUE ); 
//#endif		
//		
//}

/***
*@brief ADC1 ��������
*@update 2021.8.30
***/
float Data_McuTemp; //MCU��װ����¶�
float Data_Vbat ;   //Vbat ��ѹֵ
float Data_Vrefint ;   //Vrefint��ѹֵ
//PrmV_ChOccu_Adc = Parameter-variables for ADC channel occupancy��ADCͨ��ռ�õǼǱ���
unsigned int   PrmV_ChOccu_Adc1 = 0;
unsigned short PrmV_ChOccu_Adc2 = 0;
unsigned short PrmV_ChOccu_Adc3 = 0;

/************************
*@brief  Global api: Mcu���ʽ���ָʾ�� V2��
*@update 2021.6.14, old ver->subfun_mcu_pace
**************************/
//void glbf_mcupaceV2(u16_t tm)
//{
//	static u32_t pace = 0;
//	u16_t y = 302;

//	if(!(pace % tm)){
//		SysRun_LedTgg ;	
//		pace = 0x0;		
//	}
//	if(pace ++ > 0xffffee)
//		pace = 0;
//	
//#if CMPL_RTC && CMPL_PJT_LCD 
//   	lcd_display_rtc(3,y, 127 , DARKBLUE ); 
//#endif		
//		
//}

/*****************************************************************************
  非精准延时系列 imprecise delay*******
 验证合格
 用LED实测翻转速度(stm32f429-180Mhz/FreeRTOS v10.31.0)约为 18.75Mbps
 举例说明(stm32f429-180Mhz/FreeRTOS v10.31.0)： 
   1 如果要实现一个1ms的非精确延时，那么 nCount 的数值约为 18750
	 2 如果要实现一个1us的非精确延时，那么 nCount 的数值约为 18~20
*****************************************************************************/
/** 
 * @brief Base Imprecise delay
 * @param nCount, delay tick
 * @return void
 */
static void _impdly_bs(uv64_t nCount)
{	
	while(nCount --);
} 

///** 
// * @brief Microsecond Second Imprecise delay
// * @param nCount,μs number
// * @return void
// */
//void ulf_impdly_us(uv32_t nCount)
//{	
//	while(nCount --)
//		_impdly_bs(impdly_us);
//} 

///** 
// * @brief Millisecond Second Imprecise delay
// * @param nCount, ms number 
// * @return void
// */
//void ulf_impdly_ms(uv32_t nCount)
//{
//	while(nCount --)
//		_impdly_bs(impdly_ms);
//} 

///** 
// * @brief Second Imprecise delay
// * @param nCount, s number 
// * @return void
// */
//void ulf_impdly_s(uv16_t nCount)
//{
//	while(nCount --)
//		_impdly_bs(impdly_s);
//} 

/** 
 * @brief Free Imprecise delay
 * @param nCount, cyclic number
 * @return void
 */
void ulf_impdly_free(double nCount)
{
	_impdly_bs(nCount);
} 

///** 
// * @brief Free Imprecise delay
// * @param nCount, cyclic number
// * @return void
// */
//void ulf_impdly_100ns(uv64_t nCount)
//{
//	_impdly_bs(nCount);
//} 

/**********************************************************************************
 * @name: num_to_str
 * @brief: 将传入的数字转化为字符串
 * @param : srcnum ：需要转化数字 cnt:转化数字的位数
            deststr,
 * @rev: 转化好的字符串
 * @note :   
       -1-,from paidaxintaotao
***********************************************************************************/
void num_to_str(unsigned char srcnum, unsigned char *deststr)
{
	if(0 == srcnum )
	{
    deststr[0] = '0';
	}
	else 
	{
		unsigned char num_temp = srcnum;
		unsigned char cnt = 0;
		while(num_temp)
		{
			cnt++;
			num_temp /= 10;
		}
		num_temp = srcnum;
		while(cnt)
		{
			cnt--;
			deststr[cnt] = (num_temp % 10) + 48;
			num_temp /= 10;
		}
		
	}
//	app_atkmodule_printf(num_str);
//  Delay_xms(1000);  //延时
}

/*--EndLine:Full File--------------------------------------------------------------------------------------------End All----*/


/*
*@brief Global api:按指定方式生成全局共用变量,存储在MCU 内部SRAM
*@param: bit-->变量的type或位数； 
         num-->变量数目
*@update 2020.12.6,

void* glbf_mkvar(unsigned char num); 
{	
	void *p = NULL;	
	if(bit == 16){
		p = (u16_t*)api_malloc(sRamIn,2 * num);
	}else if(bit == 32){
		p = (u32_t*)api_malloc(sRamIn,4 * num);		
	}else{
	  p = (u8_t*)api_malloc(sRamIn,num);	
	}
	return (void*)p;
}
*/



