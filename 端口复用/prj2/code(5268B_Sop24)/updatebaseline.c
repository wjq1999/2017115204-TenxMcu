//=============================================================================
//Name		:updatebaseline.c
//Purpose	:update touch key baseline
//=============================================================================
#define		UPDATEBASELINE_C
#include	"global.h"
//=============================================================================
// Function:	void UpdateBaseline(void)
// Purpose:		update touch key baseline
// Input:		none
// OutPut:		none
// Author:
// ����ް���(TKSTATUSΪ0)���޸���(RawDataInvalidFlagΪ0)������£��������и��¼�ʱȫ����0Ȼ������
// 1,���TkRawDataArrayֵ���Ӧ��TkBaselineArray��ֵ��һ�µ�����2�������������ֱ������
// 2,��ʼȡ��ǰTkRawDataArrayֵ��Ϊһ����׼��UpdateBasepointArray������ʼ���¼�ʱUpdateCounter��
//   ��������ڸ���ʱ��UpdateCounter�ﵽ����������е�TkRawDataArrayֵ�������ڻ�׼��UpdateBasepointArray�������޷�Χ����������һ��TkRawDataArray��Ϊ�µ�TkBaselineArray,
//   �����ظ�����2
//=============================================================================
void UpdateBaseline(unsigned char uctkcount,unsigned char ucupperlimit,unsigned char ucunderlimit,unsigned int ucupdatetimer)
{
	unsigned char tktemp;
	int i;
	if(UseReferenceTK) uctkcount = uctkcount + 1;
	if(TkStatus || RawDataInvalidFlag)
	{
		for(tktemp = 0;tktemp < uctkcount;tktemp++)
		{
			UpdateCounter[tktemp] = 0;
		}
		return;
	}
	for(tktemp = 0;tktemp < uctkcount;tktemp++)
	{
		if(TkBaselineArray[tktemp] != TkRawDataArray[tktemp])
		{
			if(UpdateCounter[tktemp] < 0x80)
			{
				UpdateCounter[tktemp] = 0x81;
				UpdateBasepointArray[tktemp] = TkRawDataArray[tktemp];
				continue;
			}
			UpdateCounter[tktemp]++;
            i = TkRawDataArray[tktemp] - UpdateBasepointArray[tktemp]; 
			if((i > ucupperlimit)||(i < -ucunderlimit))
			{
				UpdateCounter[tktemp] = 0;
			}
		}
	}
	for(tktemp = 0;tktemp < uctkcount;tktemp++)
	{
		if(UpdateCounter[tktemp] >= ucupdatetimer)
		{
			UpdateCounter[tktemp] = 0;	
			TkBaselineArray[tktemp] = TkRawDataArray[tktemp];
			if(!AllTkBaselineSetFlag)
			{
				if((TkBaselineSetFlag & (1 << tktemp)) == 0)
				{
					TkBaselineSetFlag |= (1 << tktemp);
					TkBaselineSetNum++;
					if(TkBaselineSetNum >= uctkcount){
                        AllTkBaselineSetFlag = 1;
                    } 
                    
				}
			}
		}
	}
}