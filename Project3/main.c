#include "SmartX3.h"
#include "math.h"
#include "ctype.h"
#include "string.h"
#include "stdlib.h"
/************************************************
*�ⲿ����:	��Ӧ������б�����ӳ��,
*			��ֵ�ı仯�ᷴӦ��Ӧ�������Ӧ������.
************************************************/
extern char               Param1;


/************************************************
*ȫ�ֱ���:  ��������ʹ�õı���,
*			��֧�ֶ���ʱ��ʼ��,
*			�����������г�ʼ��.
************************************************/
//�˴�����ȫ�ֱ���(�ɲ�����)


/************************************************
*������:  �������. 
************************************************/
int main(void)
{
	HANDLE l_hfile;
	int l_ret = 0;	
	unsigned long	  g_positon=0;
	unsigned long	  g_len = 5 ;	
	unsigned char      src[5];
	 int j,i,n,temp;
    l_hfile = smart_open_file(0);
	smart_read_file(l_hfile, g_positon, g_len, src);
	 n = 5;
     for(i=0 ; i<n ; i++)
     {
       for(j=0 ; j<n-i-1 ; j++)
       {
        if(src[j]>src[j+1]) 
        {
              temp=src[j];
              src[j]=src[j+1];
              src[j+1]=temp;
        }
       }
     }
    l_ret = smart_write_file(l_hfile, g_positon, g_len, src);
  	return (l_ret);			// д���ַ��� ��5
}
