/**
 * @file shell_gpio.h
 * @author EDWOY
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, EDWOY Technologies Inc. All rights reserved.
 */
#ifndef _SHELL_GPIO_H_
#define _SHELL_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ThisProj_Conf.h"
#include "convert_path.h"
#include MCU_HEAD
#include SYS_HEAD
#include UTY_TYP_HEAD
#include RES_GPIO_HEAD

typedef struct _prm_gpio{ 
     emClkPos_t            mClkPos;    //gpio`s rcc clock sortnumber
     uint16_t              mPin;    //gpio`s detail pin
     uv32_t*               mGpio ;       //仅适用于支持gpio位段的mcu
	   
     STT_GPIO_BK_T*         mGpioBank_p;     // gpio bank，_GpioPrp is GPIO_TypeDef 
     STT_GPIO_INIT_T        mGpioInit;   // STT_GPIO_INIT_T is GPIO_InitTypeDef
//     STT_GPIO_INIT_T*     gpio_mod_p;  //gpio_mod的指针，预留未用
}sttPrp_Gpio_t ;



/**
 * @brief Read  level of the selected output-gpio
 */
#define app_gpio_rd_out 

/**
 * @brief Read  level of the selected input-gpio_bank
 */
#define _gpiobk_rd_in  

/**
 * @brief Read  level of the selected output-gpio_bank
 */
#define _gpiobk_rd_out  
/**
 * @brief The  selected  gpio-bank(exp:GPIOA) outputs freely.
 */
#define _gpiobk_out  



/**
 * @brief  Turns the selected gpio high.
 */
#define app_gpio_high(port,pin)  HAL_GPIO_WritePin(port,pin,GPIO_PIN_SET)

/**
 * @brief Turns the selected gpio low.
 */
#define app_gpio_low(port,pin)   HAL_GPIO_WritePin(port,pin,GPIO_PIN_RESET)

/**
 * @brief The  selected  gpio outputs freely.
 */
#define app_gpio_out        HAL_GPIO_WritePin

/**
 * @brief Read  level of the selected input-gpio
 */
#define app_gpio_rd_in           HAL_GPIO_ReadPin

/**
 * @brief  Toggles the selected gpio
 */
#define app_gpio_tgg            HAL_GPIO_TogglePin


/**
 * @brief Configures GPIO in od output mode
          verified
 * @notice 
       -1-, GPIO_Mode  = GPIO_MODE_OUTPUT_PP,
       -2-  GPIO_NOPULL
 * @param GPIOx x can be A to E to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void app_gpio_out_od_np_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin);

/**
 * @brief  Configures GPIO in PP output mode and no pull
 * @notice 
       -1-, GPIO_Mode  = GPIO_MODE_OUTPUT_PP,
       -2-  GPIO_NOPULL
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void app_gpio_out_pp_np_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin);

/**
 * @brief  Configures GPIO in PP output mode and pulldown
 * @notice 
       -1-, GPIO_Mode  = GPIO_MODE_OUTPUT_PP,
       -2-  GPIO_NOPULL
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void app_gpio_out_pp_dn_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin);

/**
 * @brief  Configures GPIO in PP output mode and up pull
 * @notice 
       -1-, GPIO_Mode  = GPIO_MODE_OUTPUT_PP,
       -2-  GPIO_NOPULL
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void app_gpio_out_pp_up_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin);


/**
 * @brief Configures input GPIO in pull-down input mode
 */
void app_gpio_ipd_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin);

/**
 * @brief Configures input GPIO in pull-up input mode
 */
void app_gpio_ipu_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin);

/**
 * @brief Configures GPIO in float input mode
 */
void app_gpio_ifl_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin);
	
/**
 * @brief  Configures GPIO in PP output mode and no pull
 * @notice 
       -1-, GPIO_Mode  = GPIO_MODE_OUTPUT_PP,
       -2-  GPIO_NOPULL
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void app_gpio_out_pp_up_init(STT_GPIO_BK_T* GPIOx, uint16_t Pin);
																 
/**
 * @brief  Configures GPIO .
 */
void app_gpio_para_init_p(sttPrp_Gpio_t* pgpio);

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
void app_gpio_para_init(sttPrp_Gpio_t* pgpio,STT_GPIO_INIT_T* initp);

/**
 * @brief  outputs GPIO with lvl freely
 * @param  sttPrp_Gpio_t
 * @param iomod,gpio`s mode
 */
void app_gpio_para_out(sttPrp_Gpio_t* pgpio,  Level lvl);

/**
 * @brief toggle GPIO 
 * @param  sttPrp_Gpio_t
 * @param iomod,gpio`s mode
 */
void app_gpio_para_tgg(sttPrp_Gpio_t* pgpio);


void app_gpio_rcc_clk_en(STT_GPIO_BK_T* GPIOx) ;
void app_gpio_rcc_clk_dis(STT_GPIO_BK_T* GPIOx) ;

#ifdef __cplusplus
}
#endif

///====CodesAdding edwoy=========================================================================================


///====End CodesAdding edwoy=====================================================================================

#endif 
/*----Endline : Full file---------------------------------------------------------------------------*/
