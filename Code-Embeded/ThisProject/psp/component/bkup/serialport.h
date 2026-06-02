/**
  ******************************************************************************
  * @file    serialport.h
  * @author  EDW¡¤OY
  * @brief   Header file of serialport devs.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 
#ifndef _SERIALPORT_H_
#define _SERIALPORT_H_

#include "ThisProj_Glb.h"
#include SYS_HEAD
#include BSP_RES_HEAD

void bsp_dbcom_init(void);
void bsp_dbcom_rstrx(void);
void bsp_dbcomdma_ovrf_tx(void);
void DBCOM_IRQHandler(void);
void DBCOM_DMA_RX_IRQHandler(void);	
void DBCOM_DMA_TX_IRQHandler(void);	


void bsp_serialport_init(u8_t sort);
void USART2_IRQHandler(void);
void bsp_serialport_rstrx(u8_t sort);

#endif /*-----EndLine: Full File---------*/

