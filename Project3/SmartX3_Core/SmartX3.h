#ifndef __SMARTX3_H__
#define __SMARTX3_H__

	#define SMART_LED_OFF			0
	#define SMART_LED_ON			1
	#define SMART_LED_BLINK			2

	#define HANDLE					unsigned long
	#define BOOL					unsigned char

	#define NULL					0
									
	#define TRUE					1
	#define FALSE					0

	#define ERR_DATAS_LEN			-1
	#define ERR_FILE_HANDLE			-2
	#define ERR_WRITE_FILE			-3

	/*加密锁权限操作函数*/
	extern void smart_open(void);

	extern void smart_open_error(void);

	extern void smart_close(void);

	extern BOOL smart_is_opened(void);

	/*LED操作函数*/
	extern void smart_led_control(unsigned long Status);

	extern unsigned long smart_get_ledstatus(void);

	/*Tick获取函数*/	
	extern unsigned long smart_get_tickcount(void);

	/*真随机数获取函数*/
	extern unsigned long smart_get_random(void);
	extern double smart_get_random_float(void);

	/*硬件ID获取函数*/
	extern void smart_get_id(unsigned char Id[32]);

	/*数据运算操作函数*/
	extern void smart_sha1_calc(unsigned char* pInput, int Len, unsigned char Output[20]);

	extern void smart_md5_calc(unsigned char* pInput, int Len, unsigned char Output[16]);

	extern void smart_tdes_setkey(unsigned char Key[24]);
	extern void smart_tdes_setiv(unsigned char Iv[8]);
	extern int smart_tdes_encrypt_ecb(unsigned char* pInput, int Len, unsigned char* pOutput);
	extern int smart_tdes_decrypt_ecb(unsigned char* pInput, int Len, unsigned char* pOutput);
 	extern int smart_tdes_encrypt_cbc(unsigned char* pInput, int Len, unsigned char* pOutput);
	extern int smart_tdes_decrypt_cbc(unsigned char* pInput, int Len, unsigned char* pOutput);

	/*数据文件操作函数*/
	extern HANDLE smart_open_file(unsigned long FileID);
	extern int smart_read_file(HANDLE hFile, unsigned long Position, int Len, void* pDst);
	extern int smart_write_file(HANDLE hFile, unsigned long Position, int Len, void* pSrc);
	extern int smart_get_filesize(HANDLE hFile);
	extern void smart_close_file(HANDLE hFile);

	/*共享缓冲区操作函数*/
	extern void* smart_get_sharedbuffer(void);
	extern int smart_read_sharedbuffer(unsigned long Position, int Len, void* pDst);
	extern int smart_write_sharedbuffer(unsigned long Position, int Len, void* pSrc);
	extern void smart_clear_sharedbuffer(void);

	/*字符串和十六进制数据转换操作函数*/
	extern BOOL fillhexbuff_with_string(char *szStr, unsigned char *hexBuff, long nBuffLen);
	extern BOOL fillstring_with_hexbuff(unsigned char *hexBuff, char *szStr, long nBuffLen);

#endif
