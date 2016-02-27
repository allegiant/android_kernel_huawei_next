

#ifndef __BASTETWRLCINTERFACE_H__
#define __BASTETWRLCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_WRLC_PDU_NUM_MAX     ( 0x7FFFFFFF )
#define BST_WCDMA_BAND_WIDTH     ( 234 * 1000 )        /*wcdma网络默认带宽值，为234k bit/s */

typedef VOS_UINT32 ( *BST_WRLC_SEND_TRS_FUNC )(
    VOS_UINT32           *pulTotPktNumber,
    VOS_UINT32           *pulRtxPktNumber );

typedef VOS_UINT32 ( *BST_WRLC_SEND_QUE_FUNC )(
    VOS_UINT32           *pulQueLength,
    VOS_UINT32           *pulBandWith );

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  枚举名    : BASTET_WRLC_MSG_TYPE_ENUM
  协议表格  :
  ASN.1描述 :
  枚举说明  : WRLC给Bastet模块发送消息定义
*****************************************************************************/
enum BASTET_WRLC_MSG_TYPE_ENUM
{
    /* 消息名称 */                              /* 消息ID */                  /*备注*/
    ID_WRLC_BASTET_TRANS_INQUIRE                   = 0x1,                     /* _H2ASN_MsgChoice BST_WRLC_REG_TRS_CB_STRU */ 

    ID_WRLC_BASTET_MSG_TYPE_BUTT
};
typedef VOS_UINT32 BASTET_WRLC_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;          /*_H2ASN_Skip*/
    VOS_UINT32                          ulPid;
    BST_WRLC_SEND_TRS_FUNC              pfSendCb;
    BST_WRLC_SEND_QUE_FUNC              pfSendQueCb;
} BST_WRLC_REG_TRS_CB_STRU;

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/


/*****************************************************************************
  6 消息头定义
*****************************************************************************/


/*****************************************************************************
  7 消息定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/
/*****************************************************************************
  H2ASN顶级消息结构定义
*****************************************************************************/
typedef struct
{
    BASTET_WRLC_MSG_TYPE_ENUM_UINT32    enMsgID;    /*_H2ASN_MsgChoice_Export BASTET_WRLC_MSG_TYPE_ENUM_UINT32*/

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          BASTET_WRLC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}BASTET_WRlc_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    BASTET_WRlc_MSG_DATA                stMsgData;
}BastetWRlcInterface_MSG;


/*****************************************************************************
  10 函数声明
*****************************************************************************/


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

#endif /* end of BastetWRlcinterface.h */
