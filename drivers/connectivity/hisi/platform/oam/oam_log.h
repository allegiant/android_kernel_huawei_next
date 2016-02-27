

#ifndef __OAM_LOG_H__
#define __OAM_LOG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "oal_ext_if.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define OAM_LOG_PARAM_MAX_NUM           4                                       /* 可打印最多的参数个数 */
#define OAM_LOG_PRINT_DATA_LENGTH       512                                     /* 每次写入文件的最大长度 */

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
extern oal_uint32  oam_log_init(oal_void);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oam_log.h */
