/**
 ****************************************************************************************************
 * @file        can.c
 * @brief       CAN 驱动代码 
 * @author      Edwoy
 * @version     V2.0
 * @date        2023.2.27
 * @license     实验平台：ApolloF429igtb
 ****************************************************************************************************
 * @attention
        
        -3-,切换can的模式时,要注意是否改变了can总线的波特率
        -2-,Filter config
				   2.1 FilterXXX = ,must be less than or equal to 0xffff
					 2.2  Filter 都默认绑定 FIFO0
           2.3  Filter0 is default broadcast id					 
 *      -1-,
 ****************************************************************************************************     
 * @note
      -1- ,can params and filter id&mask
			   1.1.1 can params
									g_can1_hdr.Init.TimeTriggeredMode = DISABLE;   //是否使能时间触发通信模式 
																																				 //DISABLE->禁止(default) ; 
																																				 //ENABLE-->使能
								
									g_can1_hdr.Init.AutoBusOff = ENABLE;         //CAN总线自动离线状态 的退出方式
																																				 // DISABLE ->软件编程方式(CAN->MCR-bit0 INRQ，先置位再清零) ; 
																																				 // ENABLE-->(default)硬件自动退出,
								
									g_can1_hdr.Init.AutoWakeUp = ENABLE;        //从睡眠模式中唤醒起来的方式 , atkorgn DISABLE
																																				//DISABLE->软件编程方式(清除CAN->MCR-bit1 Sleep位，退出睡眠模式);
																																				//ENABLE-->硬件自动唤醒(default),一旦监测到CAN消息就退出睡眠模式
								
									g_can1_hdr.Init.AutoRetransmission  = DISABLE;     //是否禁止自动重发？一般用于报文发送失误时的处理	
																																					 //DISABLE->(default)禁止自动重发,报文仅发送一次，不管是否发送成功
																																					 //ENABLE-->支持自动重发，一直重发，直到发送成功 ;  
																																					 
									g_can1_hdr.Init.ReceiveFifoLocked   = DISABLE;   //3个接收FIFO溢满后,是否锁定FIFO报文？
																																					//DISABLE->(default)不锁定,新来的覆盖旧的 ;
																																					 //ENABLE-->锁定，下一条丢弃
											
									g_can1_hdr.Init.TransmitFifoPriority = DISABLE;  //Tx邮箱中的报文，被发送出去的优先级判定： 
																																						//DISABLE ->由ID标识符决定(default，ID数值越小优先级越高) ; 
																																						//ENABLE-->由请求的时间先后顺序决定				 
         1.1.2  id > 0 && msk > 0: 
					  |-----------------------|--------------------------------|
						|                       |         Filter寄存器           |  
						|-----------------------|--------------------------------|
            |FtrScale|     |FtrMode | high16bit word | low16bit word |  
            |--------|-----|--------|----------------|---------------|
            |        |     | IDMask |     stdmsk1    |               |
						|				 | FR1 |--------|----------------|    stdid1     |
						|				 |     | IDList |     stdid3     |               |
            |  16BIT |-----|--------|----------------|---------------|
            |        |     | IDMask |    stdmsk2     |               |
						|				 | FR2 |--------|----------------|    stdid2     |
						|				 |	   | IDList |     stdid4     |							 |	 
            |--------|-----|--------|--------------------------------|
            |        | FR1 |  None  |               exid             |
            |        |-----|--------|--------------------------------|
            |  32BIT |     | IDMask |               exmsk            |  
						|				 | FR2 |--------|--------------------------------|
	          |        |     | IDList |               extid2           |  									 
            ----------------------------------------------------------					
			-2-,steps process
			   2.1 cubemx generates codes  
				 2.2 add srcs and incs 
			   2.3 app_can_init(),
				     filterbank0,idlist,32bit,default broadcast 
				 2.3  
		  -3-,Can双机通信测试要点
					3.1	双机无论何时改变can的参数，都要确保总线上所有节点的波特率必须相同
					3.2	节点1向 节点2发送数据，node1 发送 extid 数据一定要对应得到node2的filter组中有32bit长匹配的filter 
						  发 id用 CAN_ID_EXT ， 接收的filter是16bit 就错l。 正确做法是 发 extid 对 32bit filter； 发stdid 对 16bit filter
			   	3.3	Node1 和 node2 有相同配置的filter， 不管谁loop测试 向这个filter发数据，node1 和 node2 都能接收到相同的数据
		 
 ****************************************************************************************************			
 * @update
       V2.0
 *     V1.0 20211027 ATK-MtrCtrl orgn
 *
 ****************************************************************************************************
 */
///====CodesAdding edwoy===============================================================================
#include "ThisProj_Glb.h"
#include  CAN_HEAD
#include  UART_HEAD
#include  LED_HEAD
#include  DLY_HEAD
static CAN_FilterTypeDef __sFtrCfg_Can;
///==End CodesAdding edwoy=============================================================================

///===ATK-MtrCodes=================================================================ATK-MtrCodes========
//CAN_HandleTypeDef   g_can1_hdr; //moved to res_can.h
static CAN_TxHeaderTypeDef g_canx_txheader;    /* 发送参数句柄 */
static CAN_RxHeaderTypeDef g_canx_rxheader;    /* 接收参数句柄 */
/**
 * @brief       CAN初始化
 * @param       tsjw    : 重新同步跳跃时间单元.范围: 1~3;
 * @param       tbs2    : 时间段2的时间单元.范围: 1~8;
 * @param       tbs1    : 时间段1的时间单元.范围: 1~16;
 * @param       brp     : 波特率分频器.范围: 1~1024;
 *   @note      以上4个参数, 在函数内部会减1, 所以, 任何一个参数都不能等于0
 *              CAN挂在APB1上面, 其输入时钟频率为 Fpclk1 = PCLK1 = 42Mhz
 *              tq     = brp * tpclk1;
 *              波特率 = Fpclk1 / ((tbs1 + tbs2 + 1) * brp);
 *              我们设置 can_init(1, 6, 7, 6, 1), 则CAN波特率为:
 *              42M / ((6 + 7 + 1) * 6) = 500Kbps，atk原程序带宽
 *              42M / ((6 + 7 + 1) * 5) = 600Kbps
 * @param       mode    : CAN_MODE_NORMAL,  普通模式;
                          CAN_MODE_LOOPBACK,回环模式;
 * @retval      0,  初始化成功; 其他, 初始化失败;
 */
uint8_t can_init(uint32_t tsjw, uint32_t tbs2, uint32_t tbs1, uint16_t brp, uint32_t mode)
{
    g_can1_hdr.Instance           = CAN1;
    g_can1_hdr.Init.Prescaler     = brp;                /* 分频系数(Fdiv)为brp+1 */
    g_can1_hdr.Init.Mode          = mode;                    /* 模式设置 */
    g_can1_hdr.Init.SyncJumpWidth = tsjw;           /* 重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位 CAN_SJW_1TQ~CAN_SJW_4TQ */
    g_can1_hdr.Init.TimeSeg1      = tbs1;                /* tbs1范围CAN_BS1_1TQ~CAN_BS1_16TQ */
    g_can1_hdr.Init.TimeSeg2      = tbs2;                /* tbs2范围CAN_BS2_1TQ~CAN_BS2_8TQ */
	
    g_can1_hdr.Init.TimeTriggeredMode = DISABLE;   //是否使能时间触发通信模式 
	                                                         //DISABLE->(default) 禁止; 
																										       //ENABLE-->使能
	
    g_can1_hdr.Init.AutoBusOff = ENABLE;         //CAN总线自动离线状态 的退出方式
																													 // DISABLE ->软件编程方式(CAN->MCR-bit0 INRQ，先置位再清零) ; 
																													 // ENABLE-->(default)硬件自动退出,
	
    g_can1_hdr.Init.AutoWakeUp = ENABLE;        //从睡眠模式中唤醒起来的方式 , atkorgn DISABLE
																													//DISABLE->软件编程方式(清除CAN->MCR-bit1 Sleep位，退出睡眠模式);
																													//ENABLE-->(default)硬件自动唤醒,一旦监测到CAN消息就退出睡眠模式
	
    g_can1_hdr.Init.AutoRetransmission  = DISABLE;     //是否禁止自动重发？一般用于报文发送失误时的处理	
	                                                           //DISABLE->(default)禁止自动重发,报文仅发送一次，不管是否发送成功
	                                                           //ENABLE-->支持自动重发，一直重发，直到发送成功 ;  
																														 
    g_can1_hdr.Init.ReceiveFifoLocked   = DISABLE;   //3个接收FIFO溢满后,是否锁定FIFO报文？
																													  //DISABLE->(default)不锁定,新来的覆盖旧的 ;
																													   //ENABLE-->锁定，下一条丢弃
				
    g_can1_hdr.Init.TransmitFifoPriority = DISABLE;  //Tx邮箱中的报文，被发送出去的优先级判定： 
																															//DISABLE ->由ID标识符决定(default，ID数值越小优先级越高) ; 
																															//ENABLE-->由请求的时间先后顺序决定

    if (HAL_CAN_Init(&g_can1_hdr) != HAL_OK)
    {
        return 1;
    }

#if CAN1_RX0_INT_ENABLE

  /* 使用中断接收 */
  __HAL_CAN_ENABLE_IT(&g_can1_hdr, CAN_IT_RX_FIFO0_MSG_PENDING); /* FIFO0消息挂号中断允许 */
  HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);                          /* 使能CAN中断 */
  HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 1, 0);                  /* 抢占优先级1，子优先级0 */
#endif

    /*配置CAN过滤器0*/
    __sFtrCfg_Can.FilterBank           = 0;                    // FilterBank0 is default broadcast filter 
    __sFtrCfg_Can.FilterMode           = CAN_FILTERMODE_IDLIST;
    __sFtrCfg_Can.FilterScale          = CAN_FILTERSCALE_32BIT;
		
    __sFtrCfg_Can.FilterFIFOAssignment = CAN_FILTER_FIFO0;    /* 过滤器0关联到FIFO0 */
    __sFtrCfg_Can.FilterActivation     = CAN_FILTER_ENABLE;       /* 激活滤波器0 */
    __sFtrCfg_Can.SlaveStartFilterBank = 20;	
		
	  //Fill broadcast filter 
		__sFtrCfg_Can.FilterIdHigh     = (((0xbadc  << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xFFFF0000) >> 16;
		__sFtrCfg_Can.FilterIdLow      =  ((0xbadc  << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0x0000FFFF ;	
		__sFtrCfg_Can.FilterMaskIdHigh = (((0xbadca << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xFFFF0000) >> 16;		
		__sFtrCfg_Can.FilterMaskIdLow  =  ((0xbadca << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0x0000FFFF ;	

// test 
//		__sFtrCfg_Can.FilterIdHigh     = (((0x0  << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xFFFF0000) >> 16;
//		__sFtrCfg_Can.FilterIdLow      =  ((0x0  << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0x0000FFFF ;	
//		__sFtrCfg_Can.FilterMaskIdHigh = (((0x00 << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xFFFF0000) >> 16;		
//		__sFtrCfg_Can.FilterMaskIdLow  =  ((0x00 << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0x0000FFFF ;	
//		
    // 过滤器配置 
    if(HAL_OK != HAL_CAN_ConfigFilter(&g_can1_hdr, &__sFtrCfg_Can)  )
    {
        return 2;
    }
		
		//配置CAN过滤器1
    __sFtrCfg_Can.FilterBank           = 1;                    // filter1 
    __sFtrCfg_Can.FilterMode           = CAN_FILTERMODE_IDMASK;
    __sFtrCfg_Can.FilterScale          = CAN_FILTERSCALE_16BIT;
		
    __sFtrCfg_Can.FilterFIFOAssignment = CAN_FILTER_FIFO0;    /* 过滤器0关联到FIFO0 */
    __sFtrCfg_Can.FilterActivation     = CAN_FILTER_ENABLE;       /* 激活滤波器0 */
		
		__sFtrCfg_Can.FilterIdHigh     = (0x0429 << 5 | ((CAN_ID_STD | CAN_RTR_DATA) << 3)) & 0xffff ;	
		__sFtrCfg_Can.FilterMaskIdHigh = (0x0fff << 5 | ((CAN_ID_STD | CAN_RTR_DATA) << 3)) & 0xffff ;							
		__sFtrCfg_Can.FilterIdLow      = (0x042d << 5 | ((CAN_ID_STD | CAN_RTR_DATA) << 3)) & 0xffff ;
		__sFtrCfg_Can.FilterMaskIdLow  = (0x0f70 << 5 | ((CAN_ID_STD | CAN_RTR_DATA) << 3)) & 0xffff ;	
	
    // 过滤器配置 
    if (HAL_OK != HAL_CAN_ConfigFilter(&g_can1_hdr, &__sFtrCfg_Can))
    {
        return 2;
    }

				//配置CAN过滤器1
    __sFtrCfg_Can.FilterBank           = 2;                    // filter1 
    __sFtrCfg_Can.FilterMode           = CAN_FILTERMODE_IDMASK;
    __sFtrCfg_Can.FilterScale          = CAN_FILTERSCALE_32BIT;
		
    __sFtrCfg_Can.FilterFIFOAssignment = CAN_FILTER_FIFO0;    /* 过滤器0关联到FIFO0 */
    __sFtrCfg_Can.FilterActivation     = CAN_FILTER_ENABLE;       /* 激活滤波器0 */

		__sFtrCfg_Can.FilterIdHigh     = (((0x342922 << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xFFFF0000) >> 16;
		__sFtrCfg_Can.FilterIdLow      =  ((0x342922 << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0x0000FFFF ;	
		__sFtrCfg_Can.FilterMaskIdHigh = (((0x0fff00 << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xFFFF0000) >> 16;		
		__sFtrCfg_Can.FilterMaskIdLow  =  ((0x0fff00 << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0x0000FFFF ;	
		
    // 过滤器配置 
    if (HAL_OK != HAL_CAN_ConfigFilter(&g_can1_hdr, &__sFtrCfg_Can))
    {
        return 2;
    }

		
    /* 启动CAN外围设备 */
    if (HAL_CAN_Start(&g_can1_hdr) != HAL_OK)
    {
        return 3;
    }

    return 0;
}


/**
 * @brief       CAN 发送一组数据
 *   @note      发送格式固定为: 标准ID, 数据帧
 * @param       id      : 标准ID(11位)
 * @retval      发送状态 0, 成功; 1, 失败;
 */
uint8_t can_send_msg(uint32_t id, uint8_t *msg, uint8_t len)
{
    uint32_t TxMailbox = CAN_TX_MAILBOX0;
    g_canx_txheader.StdId = id;         /* 标准标识符 */
    g_canx_txheader.ExtId = id;         /* 扩展标识符(29位) */
    g_canx_txheader.IDE   = CAN_ID_EXT;   // 标准帧--> CAN_ID_STD ; 扩展帧 --> CAN_ID_EXT;
    g_canx_txheader.RTR   = CAN_RTR_DATA; /* 数据帧 */
    g_canx_txheader.DLC   = len;

    if (HAL_CAN_AddTxMessage(&g_can1_hdr, &g_canx_txheader, msg, &TxMailbox) != HAL_OK) /* 发送消息 */
    {
        return 1;
    }
    while (HAL_CAN_GetTxMailboxesFreeLevel(&g_can1_hdr) != 3); /* 等待发送完成,所有邮箱为空 */
    return 0;
}

/**
 * @brief       CAN 接收数据查询
 *   @note      接收数据格式固定为: 标准ID, 数据帧
 * @param       id      : 要查询的 标准ID(11位)
 * @param       buf     : 数据缓存区
 * @retval      接收结果
 *   @arg       0   , 无数据被接收到;
 *   @arg       其他, 接收的数据长度
 */
uint8_t can_receive_msg(uint32_t id, uint8_t *buf)
{
    if (HAL_CAN_GetRxFifoFillLevel(&g_can1_hdr, CAN_RX_FIFO0) == 0)     /* 没有接收到数据 */
    {
        return 0;
    }

    if (HAL_CAN_GetRxMessage(&g_can1_hdr, CAN_RX_FIFO0, &g_canx_rxheader, buf) != HAL_OK)  /* 读取数据 */
    {
        return 0;
    }
		
    // 不是数据帧 拒绝接收；
    if ( g_canx_rxheader.RTR != CAN_RTR_DATA)      
    {
        return 0;    
    }
    return g_canx_rxheader.DLC;
}
		
///===End ATK-MtrCodes==============================================================End ATK-MtrCodes========

///===CodesAdding edwoy=====================================================================================
/**********************************************************************************
 * @brief       (default use)CAN初始化
                validated 
 * @param       hcan
 * @param       mode : CAN_MODE_NORMAL,  普通模式;
                       CAN_MODE_LOOPBACK,回环模式;  
 * @param       
 * @param       
 * @note  
 *    -2-     based on MX_CANx_Init(void) in can.h/c generated by cubemx
 *    -1-      波特率 = Fpclk1 / ((tbs1 + tbs2 + sjw) * brp);
 *             则CAN波特率为: 45M / ((6 + 8 + 1) * 5) = 600Kbps

 * @retval      0,    success; 
              others ,failed;
 *-------------bkcode-----------------------
#include UART_HEAD 
 printf("canmode = %#x; canprs = %d\r\n",hcan->Init.Mode,hcan->Init.Prescaler); 		
 **********************************************************************************/
uint8_t app_can_init(CAN_HandleTypeDef* hcan,uint32_t mode)
{		
	hcan->Init.Mode        = mode;          
	if(HAL_OK != HAL_CAN_Init(hcan) )
			return 1;  
	
#if CAN1_RX0_INT_ENABLE

  /* 使用中断接收 */
  __HAL_CAN_ENABLE_IT(&g_can1_hdr, CAN_IT_RX_FIFO0_MSG_PENDING); /* FIFO0消息挂号中断允许 */
  HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);                          /* 使能CAN中断 */
  HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 1, 0);                  /* 抢占优先级1，子优先级0 */
#endif

    /*配置CAN过滤器*/
    __sFtrCfg_Can.FilterBank           = 0;     // FilterBank0 is default broadcast filter 
    __sFtrCfg_Can.SlaveStartFilterBank = 20;		
    __sFtrCfg_Can.FilterMode           = CAN_FILTERMODE_IDLIST;
    __sFtrCfg_Can.FilterFIFOAssignment = CAN_FILTER_FIFO0;    /* 过滤器0关联到FIFO0 */
    __sFtrCfg_Can.FilterActivation     = CAN_FILTER_ENABLE;       /* 激活滤波器0 */
    __sFtrCfg_Can.FilterScale          = CAN_FILTERSCALE_32BIT;
   
	  //Fill broadcast filter 
		__sFtrCfg_Can.FilterIdHigh     = (((0xbadc  << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xFFFF0000) >> 16;
		__sFtrCfg_Can.FilterIdLow      =  ((0xbadc  << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0x0000FFFF ;	
		__sFtrCfg_Can.FilterMaskIdHigh = (((0xbadca << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xFFFF0000) >> 16;		
		__sFtrCfg_Can.FilterMaskIdLow  =  ((0xbadca << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0x0000FFFF ;	

////test filter 
//		__sFtrCfg_Can.FilterIdHigh     = (((0x0 << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xFFFF0000) >> 16;
//		__sFtrCfg_Can.FilterIdLow      =  ((0x0 << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0x0000FFFF ;	
//		__sFtrCfg_Can.FilterMaskIdHigh = (((0x0 << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xFFFF0000) >> 16;		
//		__sFtrCfg_Can.FilterMaskIdLow  =  ((0x0 << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0x0000FFFF ;	
        /* 过滤器配置 */
    if (HAL_CAN_ConfigFilter(hcan, &__sFtrCfg_Can) != HAL_OK)
        return 2;

    /* 启动CAN外围设备 */
    if (HAL_CAN_Start(hcan) != HAL_OK)
        return 3;

    return 0;
}


/************************************************************************
 *@brief app_can_config_ftr16bit
         config a filter`s  of a can peripheral
				 validated 
 *@param ftrbk, FilterBank,stm32F4 is (0,27)
 *@param ftrmd, FilterMode ,
                   CAN_FILTERMODE_IDLIST and CAN_FILTERMODE_IDMASK
 *@param hcan, handler of CAN
 *@param hid,lid,hmsk,lmsk 

					  |-----------------------|--------------------------------|
						|                       |         Filter寄存器           |  
						|-----------------------|--------------------------------|
            |FtrScale| reg |FtrMode | high16bit word | low16bit word |  
            |--------|-----|--------|----------------|---------------|
            |        |     | IDMask |      lmsk      |               |
						|				 | FR1 |--------|----------------|      lid      |
						|				 |     | IDList |      id3       |               |
            |  16BIT |-----|--------|----------------|---------------|
            |        |     | IDMask |      hmsk      |               |
						|				 | FR2 |--------|----------------|      hid2     |
						|				 |	   | IDList |      id4       |							 |	 
            |--------|-----|--------|--------------------------------|

 *@retval  0, success; 1 failed
 *@notice note,
       -2-,FilterXXX must must be less than or equal to 0xffff
       -1-,when  FilterMode = CAN_FILTERMODE_IDLIST
			     hmsk and lmsk are two other ids
 *-------bkcode-----------------					 
		  __sFtrCfg_Can.FilterActivation     = CAN_FILTER_DISABLE;     //先关闭 filter
*************************************************************************/
u8_t  app_can_config_ftr16bit(CAN_HandleTypeDef* hcan,   \
                              u32_t ftrbk,u32_t ftrmd,
                              u16_t hid,u16_t hmsk ,   \
                              u16_t lid,u16_t lmsk)
{
//step1,Check the parameters,
    assert_param(IS_CAN_FILTER_MODE(ftrmd));
    assert_param(IS_CAN_FILTER_BANK_DUAL(ftrbk));	
    assert_param(IS_CAN_FILTER_ID_HALFWORD(hid));
    assert_param(IS_CAN_FILTER_ID_HALFWORD(hmsk));
    assert_param(IS_CAN_FILTER_ID_HALFWORD(lid));
    assert_param(IS_CAN_FILTER_ID_HALFWORD(lmsk));
	
//step2,fill the Sscale to filter
    __sFtrCfg_Can.FilterScale          = CAN_FILTERSCALE_16BIT;
    __sFtrCfg_Can.FilterBank           = ftrbk;                
    __sFtrCfg_Can.FilterMode           = ftrmd;	
    __sFtrCfg_Can.FilterFIFOAssignment = 0 ;                     //默认绑定 fifo0	
    __sFtrCfg_Can.FilterActivation     = CAN_FILTER_ENABLE;        // 激活滤波器			
//step3, fill  id and msk
		__sFtrCfg_Can.FilterIdHigh     = (hid  << 5 | ((CAN_ID_STD | CAN_RTR_DATA) << 2)) & 0xffff;	
		__sFtrCfg_Can.FilterMaskIdHigh = (hmsk << 5 | ((CAN_ID_STD | CAN_RTR_DATA) << 2)) & 0xffff;					
		__sFtrCfg_Can.FilterIdLow      = (lid  << 5 | ((CAN_ID_STD | CAN_RTR_DATA) << 2)) & 0xffff;	
		__sFtrCfg_Can.FilterMaskIdLow  = (lmsk << 5 | ((CAN_ID_STD | CAN_RTR_DATA) << 2)) & 0xffff;

//step4, open and config the filter	

    if(HAL_OK != HAL_CAN_ConfigFilter(hcan, &__sFtrCfg_Can))
       return 1;
		
		return 0;
}  

/**************************************************************************
 *@brief (default use)app_can_config_ftr32bit
         config a filter`s  of a can peripheral
				 validated 
 *@param hcan, handler of CAN
 *@param ftrbk, FilterBank,stm32F4 is (0,27)
 *@param ftrmd, FilterMode ,
                CAN_FILTERMODE_IDLIST and CAN_FILTERMODE_IDMASK
 *@param hid,lid,hmsk,lmsk 

					  |-----------------------|--------------------------------|
						|                       |         Filter寄存器           |  
						|-----------------------|--------------------------------|
            |FtrScale| reg |FtrMode | high16bit word | low16bit word |  
            |--------|-----|--------|--------------------------------|
            |        | FR1 |  None  |               exid             |
            |        |-----|--------|--------------------------------|
            |  32BIT |     | IDMask |               exmsk            |  
						|				 | FR2 |--------|--------------------------------|
	          |        |     | IDList |               extid2           |  									 
            ----------------------------------------------------------		

 *@retval  0, success; 1 failed
 *@notice note,
       -2-,FilterXXX must must be less than or equal to 0xffff 
       -1-,when  FilterMode = CAN_FILTERMODE_IDLIST
			     hmsk and lmsk are two other ids
*****************************************************************************/
u8_t  app_can_config_ftr32bit(CAN_HandleTypeDef* hcan,   \
                              u32_t ftrbk,u32_t ftrmd,   \
                              u32_t id,   u32_t msk    )
{
//step1,Check the parameters,
    assert_param(IS_CAN_FILTER_MODE(ftrmd));
    assert_param(IS_CAN_FILTER_BANK_DUAL(ftrbk));	
	
//step2,fill the Sscale to filter
    __sFtrCfg_Can.FilterScale          = CAN_FILTERSCALE_32BIT;
    __sFtrCfg_Can.FilterBank           = ftrbk;                
    __sFtrCfg_Can.FilterMode           = ftrmd;	
    __sFtrCfg_Can.FilterFIFOAssignment = 0 ;                     //默认绑定 fifo0
	  __sFtrCfg_Can.FilterActivation     = CAN_FILTER_ENABLE;      // 激活滤波器		
	
//step3, fill  id and msk
		__sFtrCfg_Can.FilterIdHigh     = (((id  << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xFFFF0000) >> 16;
		__sFtrCfg_Can.FilterIdLow      =  ((id  << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0x0000FFFF ;	
		__sFtrCfg_Can.FilterMaskIdHigh = (((msk << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xFFFF0000) >> 16;		
		__sFtrCfg_Can.FilterMaskIdLow  =  ((msk << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0x0000FFFF ;		
      	
//step4, open and config the filter	
	
    if(HAL_OK != HAL_CAN_ConfigFilter(hcan, &__sFtrCfg_Can))
       return 1;
		
		return 0;
}  

/**************************************************************************
 *@brief app_can_msg_tx
         can tx a message
				 validated 
 *@param hcan, handler of CAN
 *@param ide, extframe or stdframe
              CAN_ID_EXT ,CAN_ID_STD

 *@retval  0, success; 1 failed
 *@notice note,
*****************************************************************************/
uint8_t app_can_msg_tx(CAN_HandleTypeDef* hcan,  u32_t ide, \
                       uint32_t id, uint8_t *msg, uint8_t len)
{
    uint32_t TxMailbox = CAN_TX_MAILBOX0;
    g_canx_txheader.StdId = id;         /* 标准标识符 */
    g_canx_txheader.ExtId = id;         /* 扩展标识符(29位) */
  	g_canx_txheader.IDE   = ide;   // all are ok: 标准帧--> CAN_ID_STD ; 扩展帧 --> CAN_ID_EXT;
    g_canx_txheader.RTR   = CAN_RTR_DATA; /* 数据帧 */
    g_canx_txheader.DLC   = len;

    if (HAL_OK != HAL_CAN_AddTxMessage(&g_can1_hdr, &g_canx_txheader, msg, &TxMailbox)) /* 发送消息 */
        return 1;
		
    while (HAL_CAN_GetTxMailboxesFreeLevel(&g_can1_hdr) != 3)  /* 等待发送完成,所有邮箱为空 */
		    __NOP();
		
    return 0;
}

/**
 * @brief       CAN 接收数据查询
 *@param        hcan, handler of CAN
 * @param       buf     : 接收数据的目标缓存区
 * @retval      接收结果
 *   @arg       0   , 无数据被接收到;
 *   @arg       其他, 接收的数据长度
 *  @note      接收数据格式固定为: 数据帧
 */
uint8_t  app_can_msg_rx(CAN_HandleTypeDef* hcan, uint8_t *buf)
{
    if (HAL_CAN_GetRxFifoFillLevel(hcan, CAN_RX_FIFO0) == 0)     /* 没有接收到数据 */
    {
        return 0;
    }

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &g_canx_rxheader, buf) != HAL_OK)  /* 读取数据 */
    {
        return 0;
    }
		
    // 不是数据帧 拒绝接收；
    if ( g_canx_rxheader.RTR != CAN_RTR_DATA)      
    {
        return 0;    
    }
    return g_canx_rxheader.DLC;
}

///===End CodesAdding edwoy===========================================================================

#if CAN1_RX0_INT_ENABLE /* 使能RX0中断 */

/**
 * @brief       CAN RX0 中断服务函数
 *   @note      处理CAN FIFO0的接收中断
 * @param       无
 * @retval      无
 */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    uint8_t rxbuf[8];
    uint32_t id;
    can_receive_msg(id, rxbuf);
    printf("id:%d\r\n", g_canx_rxheader.StdId);
    printf("ide:%d\r\n", g_canx_rxheader.IDE);
    printf("rtr:%d\r\n", g_canx_rxheader.RTR);
    printf("len:%d\r\n", g_canx_rxheader.DLC);

    printf("rxbuf[0]:%d\r\n", rxbuf[0]);
    printf("rxbuf[1]:%d\r\n", rxbuf[1]);
    printf("rxbuf[2]:%d\r\n", rxbuf[2]);
    printf("rxbuf[3]:%d\r\n", rxbuf[3]);
    printf("rxbuf[4]:%d\r\n", rxbuf[4]);
    printf("rxbuf[5]:%d\r\n", rxbuf[5]);
    printf("rxbuf[6]:%d\r\n", rxbuf[6]);
    printf("rxbuf[7]:%d\r\n", rxbuf[7]);
}

#endif



#ifndef __CAN_H__  //不能与can.c中的冲突
/**
 * @brief       CAN底层驱动，引脚配置，时钟配置，中断配置
                此函数会被HAL_CAN_Init()调用
 * @param       hcan:CAN句柄
 * @retval      无
 */
void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
    if (CAN1 == hcan->Instance)
    {
        CAN_RX_GPIO_CLK_ENABLE();       /* CAN_RX脚时钟使能 */
        CAN_TX_GPIO_CLK_ENABLE();       /* CAN_TX脚时钟使能 */
        __HAL_RCC_CAN1_CLK_ENABLE();    /* 使能CAN1时钟 */

        GPIO_InitTypeDef gpio_init_struct;

        gpio_init_struct.Pin = CAN_TX_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;
        gpio_init_struct.Pull = GPIO_PULLUP;
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
        gpio_init_struct.Alternate = GPIO_AF9_CAN1;
        HAL_GPIO_Init(CAN_TX_GPIO_PORT, &gpio_init_struct); /* CAN_TX脚 模式设置 */

        gpio_init_struct.Pin = CAN_RX_GPIO_PIN;
        HAL_GPIO_Init(CAN_RX_GPIO_PORT, &gpio_init_struct); /* CAN_RX脚 必须设置成输入模式 */
    }
}
#endif  //<#ifndef __CAN_H__>



/* ---Endline:Full File--------------------------------------------------------------------All-End------*/

/*****************************************************************
 *@brief app_can_config_ftrbasepara
         config a filter`s base params of a can peripheral
 *@param hcan, handler of CAN
 *@param ftrmd, FilterBank,stm32F4 is (0,27)
 *@param ftrmd, FilterMode ,
                   CAN_FILTERMODE_IDLIST and CAN_FILTERMODE_IDMASK
 *@param fifo,  FilterFIFOAssignment,
                  CAN_FILTER_FIFO0 and CAN_FILTER_FIFO1
 *@retval  0, success; 1 failed
 *@notice 
       -1-, 一个filter一经设置fifo后，就绑定了此fifo，后续不可再更改
 *------bkcode------------
    __sFtrCfg_Can.FilterActivation     = CAN_FILTER_DISABLE;     //先关闭 filter	
    __sFtrCfg_Can.FilterActivation     = CAN_FILTER_ENABLE;      // 激活 filter

u8_t  app_can_config_ftrbasepara(CAN_HandleTypeDef* hcan, u32_t ftrbk,u32_t ftrmd)
{
//step1,Check the parameters 
    assert_param(IS_CAN_FILTER_MODE(ftrmd));
    assert_param(IS_CAN_FILTER_BANK_DUAL(ftrbk));
	
//step2,fill the base paras

    __sFtrCfg_Can.FilterBank           = ftrbk;                
    __sFtrCfg_Can.FilterMode           = ftrmd;
    __sFtrCfg_Can.FilterFIFOAssignment = 0 ;                     //默认绑定 fifo0

			
    //过滤器配置 
    if(HAL_OK != HAL_CAN_ConfigFilter(hcan, &__sFtrCfg_Can))
       return 1;
		
		return 0;
}    	
******************************************************************/
