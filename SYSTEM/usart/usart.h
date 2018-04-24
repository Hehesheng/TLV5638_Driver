#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
#include "settings"
	
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
extern u8 USART_Select;					//选择串口标志

#define USART1_printf(string)	USART_Select = 1;printf(string)//串口1的专用printf函数
#define USART2_printf(string)	USART_Select = 2;printf(string)//串口2的专用printf函数

void uart_init(u32 bound);
#endif


