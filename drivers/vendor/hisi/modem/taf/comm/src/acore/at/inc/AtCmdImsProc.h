/*
* Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
* foss@huawei.com
*
* If distributed as part of the Linux kernel, the following license terms
* apply:
*
* * This program is free software; you can redistribute it and/or modify
* * it under the terms of the GNU General Public License version 2 and 
* * only version 2 as published by the Free Software Foundation.
* *
* * This program is distributed in the hope that it will be useful,
* * but WITHOUT ANY WARRANTY; without even the implied warranty of
* * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* * GNU General Public License for more details.
* *
* * You should have received a copy of the GNU General Public License
* * along with this program; if not, write to the Free Software
* * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
*
* Otherwise, the following license terms apply:
*
* * Redistribution and use in source and binary forms, with or without
* * modification, are permitted provided that the following conditions
* * are met:
* * 1) Redistributions of source code must retain the above copyright
* *    notice, this list of conditions and the following disclaimer.
* * 2) Redistributions in binary form must reproduce the above copyright
* *    notice, this list of conditions and the following disclaimer in the
* *    documentation and/or other materials provided with the distribution.
* * 3) Neither the name of Huawei nor the names of its contributors may 
* *    be used to endorse or promote products derived from this software 
* *    without specific prior written permission.
* 
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef __ATCMDIMSPROC_H__
#define __ATCMDIMSPROC_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "AtCtx.h"
#include "AtParse.h"
#include "AtImsaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*AT��IMSAģ�����Ϣ��������ָ��*/
typedef VOS_UINT32 (*AT_IMSA_MSG_PROC_FUNC)(VOS_VOID *pMsg);

/*****************************************************************************
 �ṹ��    : AT_IMSA_MSG_PRO_FUNC_STRU
 �ṹ˵��  : AT��IMSA��Ϣ���Ӧ���������Ľṹ
*****************************************************************************/
typedef struct
{
    AT_IMSA_MSG_TYPE_ENUM_UINT32        ulMsgId;
    AT_IMSA_MSG_PROC_FUNC               pProcMsgFunc;
}AT_IMSA_MSG_PRO_FUNC_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID AT_ProcImsaMsg(AT_IMSA_MSG_STRU *pstMsg);

VOS_UINT32 AT_RcvImsaCiregSetCnf(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCiregQryCnf(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCirepSetCnf(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCirepQryCnf(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaImpuSetCnf(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCirephInd(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCirepiInd(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCireguInd(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCcwaiSetCnf(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaVtPdpActInd(VOS_VOID * pMsg);
VOS_UINT32 AT_RcvImsaVtPdpDeactInd(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaMtStateInd(VOS_VOID * pMsg);

#endif /* end of FEATURE_IMS */

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

#endif /* end of AtCmdImsProc.h */
