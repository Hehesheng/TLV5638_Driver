#ifndef __TLV5638_H 
#define __TLV5638_H 
#include "sys.h"

#define TLV5638_Control_Port	GPIOA//需要去修改Init函数中修改时钟
#define TLV5638_SCLK			GPIO_Pin_5
#define TLV5638_DIN				GPIO_Pin_6
#define TLV5638_CS 				GPIO_Pin_7

#define TLV5638_SCLK_Set		GPIO_SetBits(TLV5638_Control_Port, TLV5638_SCLK)
#define TLV5638_SCLK_Reset		GPIO_ResetBits(TLV5638_Control_Port, TLV5638_SCLK)
#define TLV5638_DIN_Set			GPIO_SetBits(TLV5638_Control_Port, TLV5638_DIN)
#define TLV5638_DIN_Reset		GPIO_ResetBits(TLV5638_Control_Port, TLV5638_DIN)
#define TLV5638_CS_Set 			GPIO_SetBits(TLV5638_Control_Port, TLV5638_CS)
#define TLV5638_CS_Reset 		GPIO_ResetBits(TLV5638_Control_Port, TLV5638_CS)

void TLV5638_Init(void);
void TLV5638_Write_Data(u16 Data);
void TLV5638_Control_Reg(void);
void TLV5638_DAC_A_Output(float Voltage);
void TLV5638_DAC_B_Output(float Voltage);
void TLV5638_DAC_A_AND_B_Output(float VoltageA, float VoltageB);

#endif /* TLV5638_H */ 

