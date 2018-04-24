#ifndef __AD9834_H 
#define __AD9834_H 
#include "sys.h"

#define Triangle_Wave    0x2002 
#define Sine_Wave  0x2008 
#define Square_Wave 0x2028
/* AD9834晶振频率 */ 

#define AD9834_SYSTEM_COLCK     75000000UL 
// B6 FS  B5 PS    B7 FSY   B8 SCK   B9 SDA B10 RST 

/* AD9834 控制引脚 */ 
#define Control_Port  GPIOA
#define FSYNC  GPIO_Pin_3    //A3
#define SCLK   GPIO_Pin_4			//A4
#define SDATA  GPIO_Pin_5 		//A5
#define RESET  GPIO_Pin_6		//A6
#define FS  	GPIO_Pin_0		//A0
#define PS		GPIO_Pin_1		//A1

#define FSYNC_SET   GPIO_SetBits(Control_Port ,FSYNC) 

#define FSYNC_CLR   GPIO_ResetBits(Control_Port ,FSYNC) 

#define SCLK_SET   GPIO_SetBits(Control_Port ,SCLK) 

#define SCLK_CLR   GPIO_ResetBits(Control_Port ,SCLK) 

#define SDATA_SET   GPIO_SetBits(Control_Port ,SDATA) 

#define SDATA_CLR   GPIO_ResetBits(Control_Port ,SDATA) 

#define RESET_SET   GPIO_SetBits(Control_Port ,RESET) 

#define RESET_CLR   GPIO_ResetBits(Control_Port ,RESET) 

 

#define FREQ_0      0 

#define FREQ_1      1 

 

#define DB15        0 

#define DB14        0 

#define DB13        B28 

#define DB12        HLB 

#define DB11        FSEL 

#define DB10        PSEL 

#define DB9         PIN_SW 

#define DB8         RESET 

#define DB7         SLEEP1 

#define DB6         SLEEP12 

#define DB5         OPBITEN 

#define DB4         SIGN_PIB 

#define DB3         DIV2 

#define DB2         0 

#define DB1         MODE 

#define DB0         0 

#define CONTROL_REGISTER    (DB15<<15)|(DB14<<14)|(DB13<<13)|(DB12<<12)|(DB11<<11)|(DB10<<10)|(DB9<<9)|(DB8<<8)|(DB7<<7)|(DB6<<6)|(DB5<<5)|(DB4<<4)|(DB3<<3)|(DB2<<2)|(DB1<<1)|(DB0<<0) 

/* AD9834函数声明 */ 

void AD9834_Write_16Bits(unsigned int data) ;  //写一个字到AD9834 

void AD9834_Select_Wave(unsigned int initdata) ; //选择输出波形 

void AD9834_Init(void);  					//初始化配置 

void AD9834_Set_Freq(unsigned char freq_number, unsigned long freq) ;//选择输出寄存器和输出频率值 

#endif /* AD9834_H */ 

