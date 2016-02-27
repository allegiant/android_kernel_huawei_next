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


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "TTFUtil.h"
#include "PsTypeDef.h"
#include "TTFComm.h"


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_TTF_UTIL_C
/*lint +e767*/



/******************************************************************************
   2 外部函数变量声明
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
******************************************************************************/
TTF_COPYLINK_DL_STRU                       g_stTtfCopyLinkDL;
TTF_COPYLINK_UL_STRU                       g_stTtfCopyLinkUL;


/******************************************************************************
   5 函数实现
******************************************************************************/
/*lint -save -e958 */

VOS_VOID TTF_QLink(VOS_UINT32 ulPid, VOS_VOID *pItem, TTF_Q_LINK_ST *pLink)
{
    if (VOS_NULL_PTR == pLink)
    {
        return;
    }

    pLink->pNext  = VOS_NULL_PTR;
} /* TTF_QLink */

VOS_VOID TTF_QInit(VOS_UINT32 ulPid, TTF_Q_ST *pQ)
{
    if (VOS_NULL_PTR == pQ)
    {
        return;
    }

    pQ->stHdr.pHead     = (TTF_Q_LINK_ST *)(&pQ->stHdr);
    pQ->stHdr.pTail     = (TTF_Q_LINK_ST *)(&pQ->stHdr);
    pQ->ulCnt           = 0;

} /* TTF_QInit */

VOS_UINT32 TTF_QIsEmpty(VOS_UINT32 ulPid, TTF_Q_ST *pQ)
{
    if (VOS_NULL_PTR == pQ)
    {
        return VOS_YES;
    }

    if (0 == pQ->ulCnt)
    {
        return VOS_YES;
    }

    return VOS_NO;
} /*TTF_QIsEmpty*/

VOS_UINT32 TTF_QCnt(VOS_UINT32 ulPid, TTF_Q_ST *pQ)
{
    if (VOS_NULL_PTR == pQ)
    {
        return 0;
    }

    return (pQ->ulCnt);
} /* TTF_QCnt */


#ifndef PCLINT_MEM
VOS_UINT32 TTF_QIn(VOS_UINT32 ulPid, TTF_Q_ST *pQ, TTF_Q_LINK_ST *pLink)
{

    if ( (VOS_NULL_PTR == pQ) || (VOS_NULL_PTR == pLink ))
    {
        return VOS_ERR;
    }

    pLink->pNext            = (TTF_Q_LINK_ST *)&pQ->stHdr;
    pQ->stHdr.pTail->pNext  = pLink;
    pQ->stHdr.pTail         = pLink;
    pQ->ulCnt++;

    return VOS_OK;
} /*TTF_QIn*/

VOS_VOID *TTF_QOut(VOS_UINT32 ulPid, TTF_Q_ST *pQ)
{
    TTF_Q_LINK_ST  *pLink;
    TTF_Q_LINK_ST  *pRtn    = VOS_NULL_PTR;


    if (VOS_NULL_PTR == pQ)
    {
        return VOS_NULL_PTR;
    }

    pLink = pQ->stHdr.pHead;

    if ( pQ->ulCnt > 0 )
    {
        pQ->stHdr.pHead = pLink->pNext;

        if (pLink->pNext == (TTF_Q_LINK_ST *)pQ)
        {
            pQ->stHdr.pTail = (TTF_Q_LINK_ST *)(&pQ->stHdr);
        }

        pQ->ulCnt--;

        pLink->pNext = VOS_NULL_PTR;
        pRtn = pLink;
    }

    return (VOS_VOID *)pRtn;
} /* TTF_QOut */

TTF_MBUF_ST *TTF_MbufNew(VOS_UINT32 ulPid, VOS_UINT16 usLen)
{
    TTF_MBUF_ST    *pMbuf;


    /*========================*/    /*参数检查*/
    if (0 == usLen)
    {
        return VOS_NULL_PTR;
    }

    /*========================*/    /*申请内存*/
    pMbuf = (TTF_MBUF_ST *)VOS_MemAlloc(ulPid, DYNAMIC_MEM_PT,
        sizeof(TTF_MBUF_ST) + usLen);

    if (VOS_NULL_PTR == pMbuf)
    {
        return VOS_NULL_PTR;
    }


    /*========================*/    /*设置内存单元的参数*/
    (VOS_VOID)VOS_MemSet(pMbuf, 0, sizeof(TTF_MBUF_ST) + usLen);
    TTF_QLink(ulPid, (VOS_VOID *)pMbuf, &pMbuf->stLink);
    pMbuf->pNext    = VOS_NULL_PTR;
    pMbuf->usLen    = usLen;
    pMbuf->usUsed   = 0;
    pMbuf->pData    = (VOS_UINT8 *)(pMbuf + 1);

    return pMbuf;
} /*TTF_MbufNew*/



void TTF_MbufFree(VOS_UINT32 ulPid, TTF_MBUF_ST *pMbuf)
{
    TTF_MBUF_ST    *pNext;
    TTF_MBUF_ST    *pFree   = pMbuf;


    while(VOS_NULL_PTR != pFree)
    {
        pNext = pFree->pNext;
        (VOS_VOID)VOS_MemFree(ulPid, pFree);
        pFree = pNext;
    }
} /*TTF_MbufFree*/
#endif /* PCLINT_MEM */



VOS_UINT16 TTF_MbufGetLen(VOS_UINT32 ulPid, TTF_MBUF_ST *pMbuf)
{
    VOS_UINT16      usLen   = 0;
    TTF_MBUF_ST    *pTmp    = pMbuf;


    while(VOS_NULL_PTR != pTmp)
    {
        usLen   += pTmp->usUsed;
        pTmp    = pTmp->pNext;
    }

    return usLen;
} /*TTF_MbufGetLen*/


/******************************************************************************
 Function:       TTF_LenStr2IpAddr
 Description:    将字符串格式的IP地址转化为SM协议IP地址格式.完全继承V100R001
 Calls:
 Data Accessed:
 Data Updated:
 Input:          pucStr - 字符串格式的IP地址
 Output:         pucIpAddr - SM协议定义的IP地址
 Return:         TAF_SUCCESS - 转化成功
                 TAF_FAILURE - 转化失败
 Others:
******************************************************************************/
VOS_UINT32  TTF_LenStr2IpAddr(VOS_UINT8* pucStr, VOS_UINT8 *pucIpAddr)
{
    VOS_UINT8 i, j = 0;
    VOS_UINT8 ucValue = 0;

    if (0 == pucStr[0])
    {   /*ADDR长度为0，直接长度赋值返回*/
        pucIpAddr[0] = 0;
        pucIpAddr[1] = 0;
        pucIpAddr[2] = 0;
        pucIpAddr[3] = 0;
        return PS_SUCC;
    }

    if (pucStr[0] == '.')
    {   /*如果第1个有效字符是'.'，IP地址是非法的*/
        return PS_FAIL;
    }


    for (i = 0; (i <= TTF_MAX_IPV4_ADDR_LEN) && (0 != pucStr[i]) ; i++)
    {   /*从第1个有效字符开始检查*/
        if (((pucStr[i] < 0x30) || (pucStr[i] > 0x39)) && (pucStr[i] != '.'))
        {   /*超出'0'-'9'的字符非法*/
            return PS_FAIL;
        }
        if (pucStr[i] != '.')
        {   /*如果是有效字符，转化为数字*/
            if (((ucValue * 10) + (pucStr[i] - 0x30)) <= 255)
            {   /*字符串转化为有效IP段位值*/
                ucValue = (VOS_UINT8)((ucValue * 10) + (pucStr[i] - 0x30));
            }
            else
            {   /*超过255出错*/
                return PS_FAIL;
            }
        }
        else
        {   /*如果字符是'.'，前一位段值已经计算出来*/
            if (j <= 3)
            {   /*本版本只支持IPV4地址*/
                pucIpAddr[j] = ucValue;
                ucValue = 0;
                j++;  /*开始下一个有效字符段的长度累计*/
            }
            else
            {   /*超出4个IP位段，非法*/
                return PS_FAIL;
            }
        }
    }

    if (j == 3)
    {
        pucIpAddr[j] = ucValue;
        return PS_SUCC;
    }
    else
    {
        return PS_FAIL;
    }
}

/*****************************************************************************
 Function   : TTF_Write32RegByBit
 Description: set value to register in position from startBit to endBit
 Input      : ulRegAddr -- address of SOC or BBP
            : ucStartBit -- startBit in 32bit,lower edge
            : ucEndBit  --- endBit in 32bit,upper edge
            : ulSetValue -- the value to set
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID TTF_Write32RegByBit(VOS_UINT32 ulRegAddr, VOS_UINT8 ucStartBit, VOS_UINT8 ucEndBit,VOS_UINT32 ulSetValue)
{
    VOS_UINT32                          ulOrgValue;
    VOS_UINT32                          ulOrgMask;
    VOS_UINT32                          ulDataMask;


    /*check parameter*/

    if ( (VOS_NULL_PTR == ulRegAddr) || (ucStartBit > ucEndBit) || (ucStartBit > TTF_REG_MAX_BIT) || (ucEndBit > TTF_REG_MAX_BIT) )
    {
        (VOS_VOID)LogPrint4("TTF_Write32RegByBit para err ,regAddr 0x%x, startBit %d, endBit %d, value %d\r\n",
            (VOS_INT32)ulRegAddr, ucStartBit, ucEndBit, (VOS_INT32)ulSetValue);
        return;
    }

    /*read original value*/
    ulOrgValue = (VOS_UINT32)(*((VOS_UINT32 *)(VOS_UINT_PTR)(ulRegAddr)));

    /*to get the mask form startBit to endbit*/
    ulDataMask  = 0xFFFFFFFF;
    ulDataMask  = ulDataMask >> (ucStartBit);
    ulDataMask  = ulDataMask << (TTF_REG_MAX_BIT - (ucEndBit - ucStartBit));
    ulDataMask  = ulDataMask >> (TTF_REG_MAX_BIT - ucEndBit);
    ulOrgMask   = ~ulDataMask;

    /*set 0 from startBit to endBit*/
    ulOrgValue  &= ulOrgMask;

    /*move setValue to position*/
    ulSetValue  = ulSetValue << ucStartBit;
    ulSetValue &= ulDataMask;

    /*set value to reg*/
    ulSetValue |= ulOrgValue;

    *((VOS_UINT32 *)(VOS_UINT_PTR)(ulRegAddr)) = ulSetValue;
}/* TTF_Write32RegByBit */


/*****************************************************************************
 Function   : TTF_Read32RegByBit
 Description: read value from register in position from startBit to endBit
 Input      : ulRegAddr -- address of SOC or BBP
            : ucStartBit -- startBit in 32bit,lower edge
            : ucEndBit  --- endBit in 32bit,upper edge
 Return     : value
 Other      :
 *****************************************************************************/
VOS_UINT32 TTF_Read32RegByBit(VOS_UINT32 ulRegAddr, VOS_UINT8 ucStartBit, VOS_UINT8 ucEndBit)
{
    VOS_UINT32                          ulOrgValue;
    VOS_UINT32                          ulOrgMask;


    /*check parameter*/

    if ( (VOS_NULL_PTR == ulRegAddr) || (ucStartBit > ucEndBit) || (ucStartBit > TTF_REG_MAX_BIT) || (ucEndBit > TTF_REG_MAX_BIT) )
    {
        (VOS_VOID)LogPrint3("TTF_Read32RegByBit para err ,regAddr 0x%x, startBit %d, endBit %d\r\n",
            (VOS_INT32)ulRegAddr, ucStartBit, ucEndBit);
        return 0;
    }

    /*read original value*/
    ulOrgValue = (VOS_UINT32)(*((VOS_UINT32 *)(VOS_UINT_PTR)(ulRegAddr)));

    /*to get the mask form startBit to endbit*/
    ulOrgMask  = 0xFFFFFFFF;
    ulOrgMask  = ulOrgMask >> (ucStartBit);
    ulOrgMask  = ulOrgMask << (TTF_REG_MAX_BIT - (ucEndBit - ucStartBit));
    ulOrgMask  = ulOrgMask >> (TTF_REG_MAX_BIT - ucEndBit);

    /*get value from startBit to endBit*/
    ulOrgValue  &= ulOrgMask;

    return (ulOrgValue >> ucStartBit);
}/* TTF_Read32RegByBit */

VOS_UINT32 TTF_CopyLink_DL_Init(TTF_COPYLINK_DL_STRU *pstTtfCpyLink)
{
    pstTtfCpyLink->ulCopyNodeCnt   = 0;

    return PS_SUCC;
}/* TTF_CopyLink_Init */

VOS_UINT32 TTF_CopyLink_DL_Reg
(
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucRegDataDst,
    VOS_UINT8                          *pucRegDataSrc,
    VOS_UINT16                          usRegDataLen,
    TTF_COPYLINK_DL_STRU               *pstTtfCpyLink
)
{
    TTF_COPYLINK_NODE_STRU             *pstCopyLinkNode;

    if (pstTtfCpyLink->ulCopyNodeCnt >= TTF_COPYLINK_DL_MAX_NUM)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
            "TTF, TTF_CopyLink_Excute, WARNING, NodeCnt <1>",
            (VOS_INT32)(pstTtfCpyLink->ulCopyNodeCnt));

        return PS_FAIL;
    }

    pstCopyLinkNode = &(pstTtfCpyLink->astCopyLinkNodes[pstTtfCpyLink->ulCopyNodeCnt]);

    pstCopyLinkNode->pucDstData  = pucRegDataDst;
    pstCopyLinkNode->pucSrcData  = pucRegDataSrc;
    pstCopyLinkNode->ulDataLen   = usRegDataLen;

    pstTtfCpyLink->ulCopyNodeCnt++;


    return PS_SUCC;
}/* TTF_CopyLink_Reg */

VOS_UINT32 TTF_CopyLink_DL_Execute(VOS_UINT32 ulPid, TTF_COPYLINK_DL_STRU *pstTtfCpyLink)
{
    VOS_UINT32                          ulCopyNodeLoop;
    TTF_COPYLINK_NODE_STRU             *pstCopyLinkNode;

    if (pstTtfCpyLink->ulCopyNodeCnt > TTF_COPYLINK_DL_MAX_NUM)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
            "TTF, TTF_CopyLink_Excute, WARNING, NodeCnt <1>",
            (VOS_INT32)(pstTtfCpyLink->ulCopyNodeCnt));

        pstTtfCpyLink->ulCopyNodeCnt = 0;
        return PS_FAIL;
    }

    for (ulCopyNodeLoop = 0;
        ulCopyNodeLoop < pstTtfCpyLink->ulCopyNodeCnt;
        ulCopyNodeLoop++)
    {
        pstCopyLinkNode = &(pstTtfCpyLink->astCopyLinkNodes[ulCopyNodeLoop]);

        (VOS_VOID)mdrv_memcpy(pstCopyLinkNode->pucDstData,
            pstCopyLinkNode->pucSrcData,
            pstCopyLinkNode->ulDataLen);
    }

    pstTtfCpyLink->ulCopyNodeCnt = 0;

    return PS_SUCC;
}/* TTF_CopyLink_Execute */


/*****************************************************************************
 函 数 名  : TTF_CopyLink_Rel
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月24日
    作    者   : huangfei
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TTF_CopyLink_DL_Rel( TTF_COPYLINK_DL_STRU *pstTtfCpyLink )
{
    pstTtfCpyLink->ulCopyNodeCnt = 0;
} /* TTF_CopyLink_Rel */

VOS_UINT32 TTF_CopyLink_UL_Init(TTF_COPYLINK_UL_STRU *pstTtfCpyLink)
{
    pstTtfCpyLink->ulCopyNodeCnt   = 0;

    return PS_SUCC;
}/* TTF_CopyLink_Init */

VOS_UINT32 TTF_CopyLink_UL_Reg
(
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucRegDataDst,
    VOS_UINT8                          *pucRegDataSrc,
    VOS_UINT16                          usRegDataLen,
    TTF_COPYLINK_UL_STRU               *pstTtfCpyLink
)
{
    TTF_COPYLINK_NODE_STRU             *pstCopyLinkNode;

    if (pstTtfCpyLink->ulCopyNodeCnt >= TTF_COPYLINK_UL_MAX_NUM)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
            "TTF, TTF_CopyLink_Excute, WARNING, NodeCnt <1>",
            (VOS_INT32)(pstTtfCpyLink->ulCopyNodeCnt));

        return PS_FAIL;
    }

    pstCopyLinkNode = &(pstTtfCpyLink->astCopyLinkNodes[pstTtfCpyLink->ulCopyNodeCnt]);

    pstCopyLinkNode->pucDstData  = pucRegDataDst;
    pstCopyLinkNode->pucSrcData  = pucRegDataSrc;
    pstCopyLinkNode->ulDataLen   = usRegDataLen;

    pstTtfCpyLink->ulCopyNodeCnt++;


    return PS_SUCC;
}/* TTF_CopyLink_Reg */

VOS_UINT32 TTF_CopyLink_UL_Execute(VOS_UINT32 ulPid, TTF_COPYLINK_UL_STRU *pstTtfCpyLink)
{
    VOS_UINT32                          ulCopyNodeLoop;
    TTF_COPYLINK_NODE_STRU             *pstCopyLinkNode;

    if (pstTtfCpyLink->ulCopyNodeCnt > TTF_COPYLINK_UL_MAX_NUM)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
            "TTF, TTF_CopyLink_Excute, WARNING, NodeCnt <1>",
            (VOS_INT32)(pstTtfCpyLink->ulCopyNodeCnt));

        pstTtfCpyLink->ulCopyNodeCnt = 0;
        return PS_FAIL;
    }

    for (ulCopyNodeLoop = 0;
        ulCopyNodeLoop < pstTtfCpyLink->ulCopyNodeCnt;
        ulCopyNodeLoop++)
    {
        pstCopyLinkNode = &(pstTtfCpyLink->astCopyLinkNodes[ulCopyNodeLoop]);

        (VOS_VOID)mdrv_memcpy(pstCopyLinkNode->pucDstData,
            pstCopyLinkNode->pucSrcData,
            pstCopyLinkNode->ulDataLen);
    }

    pstTtfCpyLink->ulCopyNodeCnt = 0;

    return PS_SUCC;
}/* TTF_CopyLink_Execute */


/*****************************************************************************
 函 数 名  : TTF_CopyLink_Rel
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年5月24日
    作    者   : huangfei
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TTF_CopyLink_UL_Rel( TTF_COPYLINK_UL_STRU *pstTtfCpyLink )
{
    pstTtfCpyLink->ulCopyNodeCnt = 0;
} /* TTF_CopyLink_Rel */



/*****************************************************************************
 函 数 名  : TTF_InsertSortAsc16bit
 功能描述  : 将元素类型为VOS_UINT16的数组，按照升序排序
 输入参数  :

 输出参数  :

 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月28日
    作    者   : Huangfei & Hefeng
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TTF_InsertSortAsc16bit
(
    VOS_UINT32                          ulPid,
    VOS_UINT16                          ausSortElement[],
    VOS_UINT32                          ulElementCnt,
    VOS_UINT32                          ulMaxCnt
)
{
    VOS_UINT16                          usTemp;
    VOS_UINT32                          ulElementCntLoop;
    VOS_INT32                           j;


    if ( 0 == ulElementCnt )
    {
        TTF_LOG(ulPid, 0, PS_PRINT_NORMAL,
            "TTF_InsertSortAsc16bit::ulElementCnt is zero!");
        return;
    }

    if ( ulElementCnt> ulMaxCnt  )
    {
        TTF_LOG2(ulPid, 0, PS_PRINT_NORMAL,
            "TTF_InsertSortAsc16bit::ulElementCnt is more than MaxCnt!<1>ulElementCnt,<2>ulMaxCnt",
            (VOS_INT32)ulElementCnt, (VOS_INT32)ulMaxCnt);
        ulElementCnt    = ulMaxCnt;
    }

    for ( ulElementCntLoop = 1; ulElementCntLoop < ulElementCnt; ulElementCntLoop++ )
    {
        if( ausSortElement[ulElementCntLoop] < ausSortElement[ulElementCntLoop-1] )/* 后一个数 < 前一个数 */
        {
            usTemp  = ausSortElement[ulElementCntLoop];
            j       = (VOS_INT32)(ulElementCntLoop - 1);

            do
            {
                ausSortElement[j+1]= ausSortElement[j];
                j--;
            }while ( (usTemp < ausSortElement[j]) && ( 0 <= j ) );

            ausSortElement[j+1]  = usTemp;
        }
    }

}



/*****************************************************************************
 函 数 名  : TTF_RemoveDupElement16bit
 功能描述  : 将元素类型为VOS_UINT16的数组，移除相同,传入数组必须是有序的，且传入原始
              数组大小值
 输入参数  :

 输出参数  :

 返 回 值  :

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月28日
    作    者   : Huangfei & Hefeng
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TTF_RemoveDupElement16bit
(
    VOS_UINT32                          ulPid,
    VOS_UINT16                          ausSortElement[],
    VOS_UINT32                         *pulElementCnt,
    VOS_UINT32                          ulMaxCnt
)
{
    VOS_UINT32                          ulElementCntLoop;
    VOS_UINT32                          ulFilterAfterCnt;
    VOS_UINT32                          ulDupCnt = 0;
    VOS_UINT32                          j;


    if ( 0 == *pulElementCnt )
    {
        TTF_LOG(ulPid, 0, PS_PRINT_NORMAL,
            "TTF_RemoveDupElement16bit::*pulElementCnt is zero!");
        return;
    }

    if ( *pulElementCnt > ulMaxCnt  )
    {
        TTF_LOG2(ulPid, 0, PS_PRINT_NORMAL,
            "TTF_InsertSortAsc16bit::ulElementCnt is more than MaxCnt!<1>ulElementCnt,<2>ulMaxCnt",
            (VOS_INT32)(*pulElementCnt), (VOS_INT32)ulMaxCnt);
        *pulElementCnt  = ulMaxCnt;
    }

    ulFilterAfterCnt    = *pulElementCnt;

    for ( ulElementCntLoop = 1; ulElementCntLoop < ulFilterAfterCnt; ulElementCntLoop++ )
    {
        if ( ausSortElement[ulElementCntLoop] == ausSortElement[ulElementCntLoop-1] )
        {
            for ( j= ulElementCntLoop; j< ulFilterAfterCnt; j++ )
            {
                ausSortElement[j-1] = ausSortElement[j];
            }
            ulElementCntLoop--;
            ulFilterAfterCnt--;
            ulDupCnt++;
        }
    }

    *pulElementCnt  = *pulElementCnt - ulDupCnt;


    return;
}



VOS_VOID TTF_RingBufWrite(VOS_UINT32 ulPid, VOS_UINT32 ulDstRingBufBaseAddr, VOS_UINT16 usOffset,
    VOS_UINT8 *pucSrcData, VOS_UINT16 usDataLen, VOS_UINT16 usModLen)
{
    VOS_UINT16  usBufLeftLen;
    VOS_UINT8  *pucDst;

    if (usDataLen >= usModLen)
    {
        TTF_LOG2(ulPid, PS_SUBMOD_NULL, PS_PRINT_WARNING,
            "TTF_RingBufWrite, ulDataLen <1> wrong with ulModLen <2>",
            usDataLen, usModLen);
        return;
    }

    if (usOffset >= usModLen)
    {
        TTF_LOG2(ulPid, PS_SUBMOD_NULL, PS_PRINT_WARNING,
            "TTF_RingBufWrite, usOffset <1> wrong with ulModLen <2>",
            usOffset, usModLen);
        return;
    }

    usBufLeftLen    = usModLen - usOffset;
    pucDst          = (VOS_UINT8 *)((VOS_UINT_PTR)(ulDstRingBufBaseAddr + usOffset));

    if (usBufLeftLen >= usDataLen)
    {
        (VOS_VOID)mdrv_memcpy(pucDst, pucSrcData, usDataLen);
    }
    else
    {
        (VOS_VOID)mdrv_memcpy(pucDst, pucSrcData, usBufLeftLen);
        (VOS_VOID)mdrv_memcpy((VOS_UINT8 *)(VOS_UINT_PTR)ulDstRingBufBaseAddr, (VOS_UINT8 *)(VOS_UINT_PTR)pucSrcData + usBufLeftLen,
            usDataLen - usBufLeftLen);
    }

    return;
} /* TTF_RingBufWrite */

VOS_VOID TTF_RingBufRead
(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulSrcRingBufBaseAddr,
    VOS_UINT32                          usOffset,
    VOS_UINT8                          *pucDstData,
    VOS_UINT16                          usDataLen,
    VOS_UINT32                          usModLen
)
{
    VOS_UINT32                           usLeft;
    VOS_UINT8                           *pucSrc;

    if (usDataLen >= usModLen)
    {
        TTF_LOG(ulPid, PS_SUBMOD_NULL, PS_PRINT_WARNING,
            "TTF_RingBufRead, ulDataLen wrong with ulModLen ");
        return;
    }

    if (usOffset >= usModLen)
    {
        TTF_LOG(ulPid, PS_SUBMOD_NULL, PS_PRINT_WARNING,
            "TTF_RingBufRead, usOffset wrong with ulModLen ");

        return;
    }

    usLeft = usModLen - usOffset;
    pucSrc = (VOS_UINT8 *)(VOS_UINT_PTR)(ulSrcRingBufBaseAddr + usOffset);

    if (usDataLen > usLeft)
    {

        (VOS_VOID)mdrv_memcpy( pucDstData, pucSrc, usLeft);
        (VOS_VOID)mdrv_memcpy((VOS_UINT8 *)( pucDstData + usLeft),
                      (VOS_UINT8 *)(VOS_UINT_PTR)ulSrcRingBufBaseAddr,
                      (usDataLen - usLeft));
    }
    else
    {
        (VOS_VOID)mdrv_memcpy(pucDstData,pucSrc,usDataLen);
    }

    return;
} /* TTF_RingBufRead */
/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

