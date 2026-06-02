/**
 * @file main.c
 * @author EDWOY
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, EDWOY Technologies Inc. All rights reserved.
 */
#include "ThisProj_Glb.h"
#include GPIO_HEAD
#include UART_HEAD
#include DLY_HEAD

/**
 * @brief Enable GPIOx`s Rcc-Clock
          wait for validating 
 * @notice 
       -1-, GPIO_Mode  = GPIO_MODE_OUTPUT_OD;
 * @param GPIOx x can be A to E to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
static void _f_gpio_rccclk_en(STT_GPIO_BK_T* GPIOx)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));

#if defined(USE_HAL_DRIVER)     
	if(GPIOx == GPIOA)  
		__HAL_RCC_GPIOA_CLK_ENABLE();
	
	else if(GPIOx == GPIOB)  
		__HAL_RCC_GPIOB_CLK_ENABLE();
	
	else if(GPIOx == GPIOC)
		__HAL_RCC_GPIOC_CLK_ENABLE();

	else if(GPIOx == GPIOD)   
		__HAL_RCC_GPIOD_CLK_ENABLE();
 
	else if(GPIOx == GPIOE)   
		__HAL_RCC_GPIOE_CLK_ENABLE();

#if  THIS_BOARD  == G_ATK_APL429IG_V1 
	else if(GPIOx == GPIOF)   
		__HAL_RCC_GPIOF_CLK_ENABLE();	
	
	else if(GPIOx == GPIOG)   
		__HAL_RCC_GPIOG_CLK_ENABLE();		

	else if(GPIOx == GPIOH)   
		__HAL_RCC_GPIOH_CLK_ENABLE();	
#endif // #if THIS_BOARD  == G_ATK_APL429IG_V1		
#endif // #if defined(USE_HAL_DRIVER)
}//<static void _f_gpio_rccclk_en(STT_GPIO_BK_T* GPIOx)>

void app_gpio_rcc_clk_en(STT_GPIO_BK_T* GPIOx)
{
	 _f_gpio_rccclk_en(GPIOx);
}

/**
 * @brief Disable GPIOx`s Rcc-Clock
          wait for validating 
 * @notice 
       -1-, GPIO_Mode  = GPIO_MODE_OUTPUT_OD;
 * @param GPIOx x can be A to E to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
static void _f_gpio_rccclk_dis(STT_GPIO_BK_T* GPIOx)
{
	/* Check the parameters */
	assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
#if defined(USE_HAL_DRIVER)     
	/* Enable the GPIO Clock */
	if(GPIOx == GPIOA)  
		__HAL_RCC_GPIOA_CLK_DISABLE();
	
	else if(GPIOx == GPIOB)  
		__HAL_RCC_GPIOB_CLK_DISABLE();
	
	else if(GPIOx == GPIOC)
		__HAL_RCC_GPIOC_CLK_DISABLE();

	else if(GPIOx == GPIOD)   
		__HAL_RCC_GPIOD_CLK_DISABLE();
 
	else if(GPIOx == GPIOE)   
		__HAL_RCC_GPIOE_CLK_DISABLE();
#if  THIS_BOARD  == G_ATK_APL429IG_V1 
	else if(GPIOx == GPIOF)   
		__HAL_RCC_GPIOF_CLK_DISABLE();	
	
	else if(GPIOx == GPIOG)   
		__HAL_RCC_GPIOG_CLK_DISABLE();		

	else if(GPIOx == GPIOH)   
		__HAL_RCC_GPIOH_CLK_DISABLE();			
#endif // #if THIS_BOARD  == G_ATK_APL429IG_V1		
#endif // #if defined(USE_HAL_DRIVER)				
}//<static void _f_gpio_rccclk_dis(STT_GPIO_BK_T* GPIOx)>

void app_gpio_rcc_clk_dis(STT_GPIO_BK_T* GPIOx)
{
	 _f_gpio_rccclk_dis(GPIOx);
}


/**
 * @brief Configures GPIO in od output mode
          verified
 * @notice 
       -1-, GPIO_Mode  = GPIO_MODE_OUTPUT_PP,
       -2-  GPIO_NOPULL
 * @param GPIOx x can be A to E to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void app_gpio_out_od_np_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin)
{
  GPIO_InitTypeDef tSttGpioInit;
  _f_gpio_rccclk_en(GPIOx);
	
	/* Configure the GPIO pin */
	if(Pin <= GPIO_PIN_All)
	{
    tSttGpioInit.Pin   = Pin;                   /* LED0引脚 */
    tSttGpioInit.Mode  = GPIO_MODE_OUTPUT_OD;   /* 开漏输出 */
    tSttGpioInit.Pull  = GPIO_NOPULL;           /* no pull*/
    tSttGpioInit.Speed = GPIO_SPEED_HIGH;       /* 高速 */
    API_PRP_GPIO_INIT(GPIOx, &tSttGpioInit);         /* 初始化LED0引脚 */
	}
}

/**
 * @brief  Configures GPIO in PP output mode and up pull
 * @notice 
       -1-, GPIO_Mode  = GPIO_MODE_OUTPUT_PP,
       -2-  GPIO_NOPULL
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void app_gpio_out_pp_np_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin)
{
  GPIO_InitTypeDef tSttGpioInit;
  _f_gpio_rccclk_en(GPIOx);

	/* Configure the GPIO pin */
	if(Pin <= GPIO_PIN_All)
	{
    tSttGpioInit.Pin   = Pin;                   /* LED0引脚 */
    tSttGpioInit.Mode  = GPIO_MODE_OUTPUT_PP ;  /* 推挽输出 */
    tSttGpioInit.Pull  = GPIO_NOPULL;           /* no pull */
    tSttGpioInit.Speed = GPIO_SPEED_HIGH;       /* 高速 */
    API_PRP_GPIO_INIT(GPIOx, &tSttGpioInit);         /* 初始化LED0引脚 */
	}
}

/**
 * @brief  Configures GPIO in PP output mode and pulldown
 * @notice 
       -1-, GPIO_Mode  = GPIO_MODE_OUTPUT_PP,
       -2-  GPIO_NOPULL
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void app_gpio_out_pp_dn_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin)
{
  GPIO_InitTypeDef tSttGpioInit;
  _f_gpio_rccclk_en(GPIOx);

	/* Configure the GPIO pin */
	if(Pin <= GPIO_PIN_All)
	{
    tSttGpioInit.Pin   = Pin;                   /* LED0引脚 */
    tSttGpioInit.Mode  = GPIO_MODE_OUTPUT_PP ;  /* 推挽输出 */
    tSttGpioInit.Pull  = GPIO_PULLDOWN;           /* no pull */
    tSttGpioInit.Speed = GPIO_SPEED_HIGH;       /* 高速 */
    API_PRP_GPIO_INIT(GPIOx, &tSttGpioInit);         /* 初始化LED0引脚 */
	}
}


/**
 * @brief  Configures GPIO in PP output mode and no pull
 * @notice 
       -1-, GPIO_Mode  = GPIO_MODE_OUTPUT_PP,
       -2-  GPIO_NOPULL
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void app_gpio_out_pp_up_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin)
{
	GPIO_InitTypeDef tSttGpioInit;
	_f_gpio_rccclk_en(GPIOx);

	/* Configure the GPIO pin */
	if(Pin <= GPIO_PIN_All)
	{
		tSttGpioInit.Pin   = Pin;                   /* LED0引脚 */
		tSttGpioInit.Mode  = GPIO_MODE_OUTPUT_PP ;  /* 推挽输出 */
		tSttGpioInit.Pull  = GPIO_PULLUP ;           /* no pull */
		tSttGpioInit.Speed = GPIO_SPEED_HIGH;       /* 高速 */
	    API_PRP_GPIO_INIT(GPIOx, &tSttGpioInit);         /* 初始化LED0引脚 */
	}
}

/**
 * @brief Configures  GPIO in pull-down input mode
       -1-, GPIO_Mode  = GPIO_MODE_INPUT,
       -2-  GPIO_PULLDOWN
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void app_gpio_ipd_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin)
{
	STT_GPIO_INIT_T tSttGpioInit;
	_f_gpio_rccclk_en(GPIOx);
	/* Configure the GPIO pin */
	if(Pin <= GPIO_PIN_All)
	{
		tSttGpioInit.Pin   = Pin;                   /* LED0引脚 */
		tSttGpioInit.Mode  = GPIO_MODE_INPUT ;            /* 推挽输出 */
		tSttGpioInit.Pull  = GPIO_PULLDOWN;       
		tSttGpioInit.Speed = GPIO_SPEED_HIGH;          /* 高速 */
	API_PRP_GPIO_INIT(GPIOx, &tSttGpioInit);       /* 初始化LED0引脚 */
	}
}

/**
 * @brief Configures GPIO in pull-up input mode
       -1-, GPIO_Mode  = GPIO_MODE_INPUT,
       -2-  GPIO_PULLUP
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void app_gpio_ipu_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin)
{
	STT_GPIO_INIT_T tSttGpioInit;
	_f_gpio_rccclk_en(GPIOx);
	/* Configure the GPIO pin */
	if(Pin <= GPIO_PIN_All)
	{
		tSttGpioInit.Pin   = Pin;                   /* LED0引脚 */
		tSttGpioInit.Mode  = GPIO_MODE_INPUT ;      /* 推挽输出 */
		tSttGpioInit.Pull  = GPIO_PULLUP;          /* 上拉 */
		tSttGpioInit.Speed = GPIO_SPEED_HIGH;      /* 高速 */
	    API_PRP_GPIO_INIT(GPIOx, &tSttGpioInit);       /* 初始化LED0引脚 */
	}
}

/**
 * @brief Configures GPIO in float input mode
       -1-, GPIO_Mode  = GPIO_MODE_INPUT,
       -2-  GPIO_NOPULL 
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void app_gpio_ifl_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin)
{
	STT_GPIO_INIT_T tSttGpioInit;
  _f_gpio_rccclk_en(GPIOx);
	/* Configure the GPIO pin */
	if(Pin <= GPIO_PIN_All)
	{
    tSttGpioInit.Pin   = Pin;                   /* LED0引脚 */
    tSttGpioInit.Mode  = GPIO_MODE_INPUT ;            /* 推挽输出 */
    tSttGpioInit.Pull  = GPIO_NOPULL ;         
    tSttGpioInit.Speed = GPIO_SPEED_HIGH;          /* 高速 */
    API_PRP_GPIO_INIT(GPIOx, &tSttGpioInit);       /* 初始化LED0引脚 */
	}
}

/**************************************************************
 * @brief free configures GPIO with pointer to init-struct
          wait for validating 
 * @param GPIOx,x can be A to G to select the GPIO port.
 * @param initp, pointer to init-struct
 * @retval none
 * **********************
 * 
		pgpio->mGpioInit.Pull  = initp.Pull;
		pgpio->mGpioInit.Mode	= initp.Mode;
		pgpio->mGpioInit.Speed = initp.Speed;	
 **************************************************************/
void app_gpio_para_init(sttPrp_Gpio_t* pgpio,STT_GPIO_INIT_T* initp)
{
	_f_gpio_rccclk_en(pgpio->mGpioBank_p);	
	pgpio->mGpioInit.Pin  = pgpio->mPin;

	// Configure the GPIO pin 
	if(pgpio->mPin <= GPIO_PIN_All)
	{
		pgpio->mGpioInit = *initp; //直接给结构体
		API_PRP_GPIO_INIT(pgpio->mGpioBank_p, &pgpio->mGpioInit);
	}
}

/**************************************************************
 * @brief  Configures GPIO mode.
 * @param GPIOx,x can be A to G to select the GPIO port.
 * @param Pin,This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 * @param iomod,gpio`s mode
 **************************************************************/
void app_gpio_para_init_p(sttPrp_Gpio_t* pgpio)
{
	STT_GPIO_INIT_T tSttGpioInit;
	_f_gpio_rccclk_en(pgpio->mGpioBank_p);

	pgpio->mGpioInit.Pin   = pgpio->mPin;

	/* Configure the GPIO pin */
	if(pgpio->mPin <= GPIO_PIN_All)
	{
		API_PRP_GPIO_INIT(pgpio->mGpioBank_p, &pgpio->mGpioInit);
	}
}

/**
 * @brief  output GPIO with lvl
 * @param  sttPrp_Gpio_t
 * @param iomod,gpio`s mode
 */
void app_gpio_para_out(sttPrp_Gpio_t* pgpio,  Level lvl)
{
//	if(lvl)
//    app_gpio_out(pgpio->mGpioBank_p,pgpio->mPin,G_GPIO_PIN_SET );
//	else
//    app_gpio_out(pgpio->mGpioBank_p,pgpio->mPin,G_GPIO_PIN_RST );		
} 

/**
 * @brief toggle GPIO 
 * @param  sttPrp_Gpio_t
 * @param iomod,gpio`s mode
 */
void app_gpio_para_tgg(sttPrp_Gpio_t* pgpio)
{
//  app_gpio_tgg(pgpio->mGpioBank_p,pgpio->mPin);

} 

///====CodesAdding edwoy============================================================================


///====End CodesAdding edwoy========================================================================

/*----Endline : Full file---------------------------------------------------------------------------*/
