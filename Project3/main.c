#include "SmartX3.h"
#include "math.h"
#include "ctype.h"
#include "string.h"
#include "stdlib.h"
/************************************************
*外部变量:	是应用软件中变量的映射,
*			其值的变化会反应到应用软件对应变量中.
************************************************/
extern char               Param1;


/************************************************
*全局变量:  本程序中使用的变量,
*			不支持定义时初始化,
*			需在主函数中初始化.
************************************************/
//此处定义全局变量(可不定义)


/************************************************
*主函数:  程序入口. 
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
  	return (l_ret);			// 写入字符数 ，5
}
