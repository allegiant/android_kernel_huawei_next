/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : dmac_arp_offload.h
  版 本 号   : 初稿
  作    者   : w00316376
  生成日期   : 2015年6月26日
  最近修改   :
  功能描述   : dmac_arp_offload.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2015年6月26日
    作    者   : w00316376
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DMAC_ARP_OFFLOAD_H__
#define __DMAC_ARP_OFFLOAD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "oal_net.h"
#include "dmac_vap.h"
#include "dmac_user.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_ARP_OFFLOAD_H

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/


/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/



/*****************************************************************************
  4 全局变量声明
*****************************************************************************/
extern    oal_uint32  g_ul_arpoffload_send_arprsp;
extern    oal_uint32  g_ul_arpoffload_drop_frame;



/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern dmac_rx_frame_ctrl_enum_uint8 dmac_ao_process_arp_and_mcast(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_netbuf);
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_arp_offload.h */
