#ifndef _MODBUS_H_
#define _MODBUS_H_
#include "mcu_sys_head.h"
#include MCU_SYS
#include MCU_URT
#include "crc16bit.h"

/*modbus 字符之间空闲间隔参数MdbPrm_IdleChr
 *                                    MCU主频 
 *   MdbPrm_IdleChr = 1.5 * ——————————————————
                              RS485总线波特率 * 实效系数(10)
 */
#define MdbPrm_IdleChr  (mdb_idle_chr * SystemCoreClock / (100 * PJTPRM_RS485_BAUD))  //(mdb_idle_chr * SystemCoreClock / (10 * DEFPRM_RS485_BAUD))

/*modbus帧之间空闲间隔参数MdbPrm_IdleFrm
 *                                   MCU主频 
 *   MdbPrm_IdleFrm = 3.5 * —————————————————
                               RS485总线波特率 * 实效系数(10)
 */
#define MdbPrm_IdleFrm  (mdb_idle_frm * SystemCoreClock / (100 * PJTPRM_RS485_BAUD))  // (mdb_idle_frm * SystemCoreClock / (10 * DEFPRM_RS485_BAUD)) 

extern void bdf_impdly_free(__IO uint32_t nCount);
#define MdbPrm_dly        0x10     //modbus 非精确延时数，
#define Mdb_impDly        bdf_impdly_free(MdbPrm_IdleChr * MdbPrm_dly ) //modbus 非精准字符间延时
#define Mdb_impDly_Chr    bdf_impdly_free(MdbPrm_IdleChr) //modbus 非精准字符间延时，约1个字符数据时间
#define Mdb_impDly_Frm    bdf_impdly_free(MdbPrm_IdleFrm) //modbus 非精准帧间隔延时，约3.5个字符数据时间

//modbus request-cmd tablet: modbus总线，请求命令表
typedef enum _em_mdbcmdtab{
	  mdbcmd_void    = 0,   //空指令
	  mdbcmd_chg_devid,    //更改modbus目标设备的id(报文帧的首字节-> addr)
		mdbcmd_rd_devinfo,   //读取目标设备的信息数据
	
	  mdbcmd_rst ,         //reset 复位
    mdbcmd_rsm_fac	 ,    //resume factory setting ，恢复出厂设置

	  mdbcmd_tst_ledg = 5,  //测试命令: switch green led       
  	mdbcmd_tst_ledr = 6 ,  //测试命令: switch red led 
	
}tdf_em_mdbtab_reqcmd;

//modbus tablet for error
typedef enum _em_mdberr{
	  mdberr_none        = 0,   //无错误，工作正常
	  mdberr_rspd_void,        //应答空无
	  mdberr_rspdr_hst,         //从设备节点id与host主站冲突
		mdberr_rspdr_bdc,         //从设备节点id与广播地址冲突了
	  mdberr_exc_datas ,    
	  mdberr_req_nocmd ,      //访问请求命令错误：不存在此命令	
	  mdberr_reqexc_ctlr ,   //访问越界错误：request controllers exceeded  ，控制器(如继电器设备)地址访问越界
	  mdberr_reqexc_sreg ,   //访问越界错误：request status-reg exceeded  ， 状态寄存器(如继电器设备)地址访问越界	
	  mdberr_reqexc_anlg ,   //访问越界错误：request analog-reg exceeded  ， 模拟量寄存器(如继电器设备)地址访问越界	
	  mdberr_init,
	  mdberr_crc,            //crc16bit 校验失败
	  mdberr_busy        = 0xe0 ,   //modbus总线繁忙
	  mdberr_devid       = 0xe0 + (uint8_t)mdbcmd_chg_devid ,   //modbus 响应(被访问目标)节点id错误
	
}tdf_em_mdbtab_err;

//modbus dev parameter 基于modbus通信的设备参数结构体
typedef struct _stt_prm_mdbdev{

	  uint8_t  locdev_id ;       //(仅用于responder)modbus本地设备id序列号，即modbus帧第一字节addr，
	  uint8_t  locdev_id_nsa;    //(仅用于responder)Nonvolatile storage address, locdev_id存储在非易失性存储器(默认是e2prom-at24cxx)上的地址
	  uint8_t* locdev_ver;       // modbus本地设备固件版本号,使用ascii text，如 "dvp-21-01"
		uint8_t  locdev_param;     // modbus本地设备，参数信息
		uint32_t locdev_ctrl;      // modbus本地设备，controller控制器(如继电器设备)变量，一个bit代表一个控制器
		uint16_t locdev_anlg;      // modbus本地设备，模拟量采集数据(如继电器设备)指针地址
		uint16_t locdev_sreg[16];  // modbus本地设备，状态寄存器(如继电器设备)指针地址
	  uint32_t urt_baudrate ;    // modbus基于usart端口通信时，USART的波特率，可以直接赋值给USART的频率参数
	  uint8_t  urt_bscfg[4] ;     /* usart port basic configuration ：modbus基于usart端口通信时 ,USART的基础通信配置(该数组数据是RO只读的)
	                                   [0]-->数据位：
	                                           = 0--> 8bits(默认初始值)
	                                          != 0--> 7bits
	                                   [1]-->校验位：= 0 
	                                           = 0--> 无校验(默认初始值)
	                                           = 1--> 奇校验even	
	                                           = 2--> 偶校验odd	
	                                   [2]-->停止位
	                                           = 0--> 1bit(默认初始值)
	                                           = 1--> 1.5bit	
	                                           = 2--> 2bit
	                                   [3]-->硬件流控制：
	                                           = 0--> 无(默认初始值)
	                                           = 1--> 硬件	
	                                           = 2--> Xoff/Xon 
                                  */															 
}tdf_stt_mdbdev_param;

extern const tdf_stt_mdbdev_param mdbrtu_locdev_facset; //基于modbus-rtu通信的本地设备之出厂设置参数

//extern uint8_t mdbdev_prminfo[64]; //modbus dev

/*** protocol param group for modbus-rtu *****
 *modbus-rtu 帧协议参数结构体
************/
typedef struct _ppg_mdbrtu{
	 uint8_t tkn_req   ;         /*modbus-token for requster 请求者发送请求通信标志，
	                                = 0, requester处于空闲待命状态;
	                                = 1，发起req请求帧的节点向目标节点发送命令请求
	                                = 2，req请求帧发送完毕
	                                = 3，(经历3.5个字节时间的停顿，才做判断)
	                             */
   uint8_t tkn_rspd ; /*modbus-token for responder，响应者应答通信标志，	
	                                = 0, responder处于空闲待命状态;
	                                = 1，被访问目标节点，接收到req请求帧
	                                = 2，被访问目标节点，执行完req请求帧的命令
	                                = 3，被访问目标节点，(经历3.5个字节时间的停顿，才做判断)
	                             */
	 uint16_t tkn_var_step ; /* 步骤记录器(预留未用)
	                                = 0, 空闲待命状态;	
	                    */
	 uint8_t mdbrtu_devtype;  /* modbus-token: device type,
	                                = 0, requester，请求者(一般是host主站)，发起req请求帧的节点站(一般是主站);
	                               != 0，responder，响应者/应答者(一般是从设备节点)，被请求的目标节点站(一般是从设备)              
                       */  
	// uint8_t  cmmu_rxcnt_pre;   communication port`s previous counter (USART or tcp/ip), 通信端口前次接收数据计数
	                   // 和hurt->UrtRx_Cnt计数相比较，两者值相等时间如果超过3.5个字节时间，代表一帧结束
	 uint8_t  frm_length ;   // modbus-rtu frame length
	 uint8_t  txbuf[mdbdef_len_frm]; //requester发送命令或responder发送反馈帧的缓充区
	 uint16_t reqr_w_crc16  ; 
	 uint16_t rspdr_w_crc16 ;
   uint16_t tmo_cmmu ;    //timeout of communication
	 uint32_t err_mdbrtu;   //error变量，和tdf_em_mdbtab_err联用
	 tdf_ppg_urt* purt;              //uart 参数组
	 tdf_stt_mdbdev_param  mdb_devparam; //modbus device parameter,本地设备参数
	
	 tdf_em_mdbtab_err (*rspdcbk_chgid) (struct _ppg_mdbrtu * pmdbr);  //内置respond callback函数，响应
	 tdf_em_mdbtab_err (*rspdcbk_rsmfac)(struct _ppg_mdbrtu * pmdbr);	
}tdf_ppg_mdbrtu;

extern  tdf_ppg_mdbrtu  ppg_mdbrtu_urt_def;

//	 uint8_t locdev_param[16] ;            //本机设备参数信息，记录(被访问时，做应答用)
//	 uint8_t datas_num ;                  //预处理数据的个数，单位：字节
//	 uint8_t datas_buf[mdbrtu_maxLength]; //预处理数据的缓存区
//	 uint8_t crc_orgL;                    //预留未用，crc校验原始默认数据，低字节
//	 uint8_t crc_orgH;                    //预留未用，crc校验原始默认数据，高字节
//	 uint8_t* plocdev_param;      // modbus本地设备，参数信息(如继电器设备)指针地址
//	 uint8_t* plocdev_ctrl;       // modbus本地设备，控制器(如继电器设备)指针地址
//	 uint8_t* plocdev_anlg;       // modbus本地设备，控制器(如继电器设备)指针地址
//	 uint8_t* plocdev_sreg;       // modbus本地设备，状态寄存器(如继电器设备)指针地址


/*+++++++++++++ 一, ModBus Rtu ++++++++++++++++++++*/

/**
 * @brief	init_mdbrtu
          初始化modbus-rtu
 */
extern uint32_t init_mdbrtu(tdf_ppg_mdbrtu *pmdbr);

/**
 * @brief	mdbrtu_reqr_bdc ,broadcast
          主站向所有节点广播命令， 0xbc 即广播地址
          仅用于requester
 */
extern uint32_t mdbrtu_reqr_tst(tdf_ppg_mdbrtu* pmdbr,uint8_t idaddr, uint32_t cmd , uint8_t swh,uint16_t crc);                	

/**
 * @brief	mdbrtu_reqr_bdc ,broadcast
          主站向所有节点广播命令， 0xbc 即广播地址
          仅用于requester
 */
extern uint32_t mdbrtu_reqr_bdc(tdf_ppg_mdbrtu* pmdbr, uint8_t cmd , uint8_t afdata,uint16_t crc) ;               	

/**
 * @brief	mdbrtu_reqr_chgdevid: modbus-rtu  request-->change srcid to newid 
          requester请求者向原应答者srcid发送更改新id号的命令，
          仅用于requester
 */
extern tdf_em_mdbtab_err mdbrtu_reqr_chgdevid(tdf_ppg_mdbrtu* pmdbr, uint8_t srcid, uint8_t newid) ;               	

/**
 * @brief	mdbrtu_rspdcbk_chgdevid: modbus-rtu callback api responding to mdbrtu_reqr_chgdevid() 
 */
extern tdf_em_mdbtab_err mdbrtu_rspd_chgdevid(tdf_ppg_mdbrtu* pmdbr);

/**
 * @brief	mdbrtu_rspdr_exereq: responder executes the request-cmd form requester
          modbus-rtu responder-api：responder执行 requester 发来的命令请求
          仅用于responder
 * @param pmdbr，modbus-rtu 参数组，它代表了一个modbus-rtu通信接口(一般是指rs485)
 * @return tdf_em_mdbtab_err 
 */
extern uint32_t mdbrtu_rspdr_exereq(tdf_ppg_mdbrtu* pmdbr);               	


/**
 * @brief	mdbrtu_rspdr_rspd: modbus-rtu ：responder responds frame to requester
          modbus-rtu responder-api：：responder向 requester发送应答帧
          仅用于responder
 * @param pmdbr，modbus-rtu 参数组，它代表了一个modbus-rtu通信接口(一般是指rs485)
 * @return tdf_em_mdbtab_err 
 */
extern uint32_t mdbrtu_rspdr_rspd(tdf_ppg_mdbrtu* pmdbr) ;  

/**
 * @brief	mdbrtucbk_frm_end: modbus-rtu frame-end process api
          modbus-rtu帧尾判定处理,即判定一帧结束
          一个完整的modbus-rtu通信流程：至少有一次请求帧+一次应答帧
          requester & responder共用
 */
extern void mdbrtu_frm_end(tdf_ppg_mdbrtu* pmdbr)  ;              	


/**
 * @brief	mdbrtucbk_cmmu_end: modbus-rtu communication end-process 
          modbus-rtu 通信完整全流程结束处理
          requester & responder共用
 */
extern void mdbrtu_cmmu_end(tdf_ppg_mdbrtu* pmdbr);

/*+++++++++++++2 Apis V2++++++++++++++++++++*/
/**
 * @brief	(未验证)mdb_clear:modbus-rtu 模块清空
 */
void mdb_clear(tdf_ppg_mdbrtu* pmdbr);

/**
 * @brief	mdbrtu_reqr_chgdevid: modbus-rtu  request-->change srcid to newid 
          requester请求者向原应答者srcid发送更改新id号的命令，
          仅用于requester
 */
tdf_em_mdbtab_err mdbrtu_reqr_chgdevid(tdf_ppg_mdbrtu* pmdbr, uint8_t srcid, uint8_t newid) ;    

/**
 * @brief	(待验证)mdbrtu_reqr_tstdemo ,resquester 测试命令
          主站向idaddr节点发送测试命令
          仅用于requester
 */
tdf_em_mdbtab_err mdbrtu_reqr_tstdemo(tdf_ppg_mdbrtu* pmdbr,uint8_t idaddr, uint32_t cmd,uint16_t data );

/**
 * @brief	 mdbrtu_poll: modbus-rtu总线轮询处理
           requester & responder共用          
 * @param  pmdbr，modbus-rtu 参数组，它代表了一个modbus-rtu通信接口(一般是指rs485)
 * @return tdf_em_mdbtab_err 
 */
tdf_em_mdbtab_err mdbrtu_poll(tdf_ppg_mdbrtu* pmdbr);

/*---------endline2 Apis V2-------------*/

/*--------------- endline:一, ModBus Rtu ----------------*/


#endif  //<end,#ifndef _MODBUS_H_>

/*--------------- endline:the overall file ----------------*/
