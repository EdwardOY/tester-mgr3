/*
*********************************************************************************************************
*                                           OS和系统库
*********************************************************************************************************
*/
#include "ThisProj_Glb.h"
#include SYS_HEAD
#include "cmsis_os2.h"
#include <stdio.h>
#include <stdint.h>

#ifdef _RLTCPNET_   //Options->C/C++-->Define
#include "rl_net.h"    

#elif defined(_LWIP_)
#include "lwip/dhcp.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/priv/tcpip_priv.h"
#include "lwip/priv/tcp_priv.h"
#include "netif/etharp.h"
#include "ethernetif.h"
#include "lwip/sys.h"
#include "lwip/api.h"
extern struct netif netif;
#endif //<end,#ifdef _RLTCPNET_>

#define PORT_NUM       1001    /* TCP服务器监听端口号 */

#if 1
	#define printf_eth printf
#else
	#define printf_debug(...)
#endif


extern uv8_t  g_ucEthLinkStatus ;  

extern void net_init (void) ;
extern void LwIPTest(void);