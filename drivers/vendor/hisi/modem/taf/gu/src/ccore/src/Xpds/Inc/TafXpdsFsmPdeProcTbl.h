/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXpdsFsmPdeProcTbl.h
  版 本 号   : 初稿
  作    者   : x00314862
  生成日期   : 2014年11月07日
  功能描述   : TafXpdsFsmPdeProcTbl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2014年10月31日
    作    者   : x00314862
    修改内容   : 创建文件
******************************************************************************/

#ifndef _TAF_XPDS_FSM_PDE_PROC_TBL_H_
#define _TAF_XPDS_FSM_PDE_PROC_TBL_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "TafFsm.h"
#include  "TafXpdsCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : TAF_XPDS_L2_PDE_PROC_STA_ENUM
 枚举说明  : L2 PDE状态机ID枚举定义
 1.日    期   : 2015年08月21日
   作    者   : x00314862
   修改内容   : 新建
*****************************************************************************/
enum TAF_XPDS_L2_PDE_PROC_STA_ENUM
{
    TAF_XPDS_L2_PDE_PROC_STA_INIT,                      /* 初始化状态*/
    TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_ASSIST_INFO,  /* MSA流程中等待PDE的辅助数据 */
    TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_GPS_PSEUDO_INFO,  /* MSA流程中等待GPS的伪距数据 */
    TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP,      /* MSA流程中等待PDE的定位结果 */
    TAF_XPDS_L2_PDE_PROC_STA_MSB_WAIT_PDE_DATA,         /* MSB流程中等待PDE的星历、年历数据 */

    TAF_XPDS_L2_PDE_PROC_STA_BUTT
};
typedef VOS_UINT32 TAF_XPDS_L2_PDE_PROC_STA_ENUM_UINT32;

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
VOS_UINT32 TAF_XPDS_GetL2PdeProcStaTblSize( VOS_VOID );
TAF_STA_STRU* TAF_XPDS_GetL2PdeProcStaTblAddr( VOS_VOID );
TAF_FSM_DESC_STRU* TAF_XPDS_GetL2PdeProcFsmDescAddr( VOS_VOID );



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafXsmsMoFsmMainTbl.h */





