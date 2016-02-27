

#ifndef __DMAC_MGMT_CLASSIFIER_H__
#define __DMAC_MGMT_CLASSIFIER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_vap.h"
#include "hal_ext_if.h"
#include "dmac_user.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MGMT_CLASSIFIER_H
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DMAC_DEFAULT_STA_BEACON_WAIT_TIME     20     //单位ms
#define DMAC_DEFAULT_STA_INTER_TBTT_OFFSET    1200    //单位us
/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


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
extern oal_uint32  dmac_rx_mgmt_classify(
                frw_event_mem_stru             *pst_event_mem,
                frw_event_hdr_stru             *pst_event_hdr,
                mac_vap_stru                   *pst_vap,
                oal_netbuf_stru                *pst_netbuf);
extern oal_uint32  dmac_rx_process_mgmt(
                frw_event_mem_stru             *pst_event_mem,
                frw_event_hdr_stru             *pst_event_hdr,
                hal_to_dmac_device_stru        *pst_hal_device,
                oal_netbuf_stru                *pst_netbuf);
extern oal_uint32  dmac_tx_process_action_event(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_rx_process_sync_event(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_rx_process_priv_req_event(frw_event_mem_stru *pst_event_mem);
#if 0
extern oal_uint32  dmac_tx_complete_security_ap(dmac_user_stru *pst_dmac_user, hal_tx_dscr_stru *pst_dscr, oal_netbuf_stru *pst_buf);
#endif
extern oal_uint32  dmac_tx_complete_mgmt_notify(hal_to_dmac_device_stru *pst_hal_device, dmac_user_stru *pst_dmac_user, hal_tx_dscr_stru *pst_dscr, oal_netbuf_stru *pst_buf);
extern oal_uint32  dmac_mgmt_tx_event_process(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_join_set_reg_event_process(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_join_set_dtim_reg_event_process(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_asoc_set_reg_event_process(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_WLAN_FEATURE_SMPS
extern oal_uint32  dmac_set_smps_process(frw_event_mem_stru *pst_event_mem);
#endif
extern oal_uint32  dmac_mgmt_conn_result_event(frw_event_mem_stru *pst_event_mem);
extern oal_void  dmac_mgmt_connect_set_channel(
                mac_device_stru    *pst_mac_device,
                mac_vap_stru       *pst_up_vap,
                mac_channel_stru   *pst_channel);




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_mgmt_classifier.h */
