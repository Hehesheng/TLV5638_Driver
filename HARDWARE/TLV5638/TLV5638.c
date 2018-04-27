#include "TLV5638.h"

/*************************************

功能:初始化TLV5638所需IO口
函数名:TLV5638_Init(void);
参数:无
返回值:无

**************************************/

void TLV5638_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟

    //GPIO初始化设置
    GPIO_InitStructure.GPIO_Pin = TLV5638_SCLK | TLV5638_DIN | TLV5638_CS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(TLV5638_Control_Port, &GPIO_InitStructure);//初始化
}

/*************************************

功能:向TLV5638中写入16位数据
函数名:TLV5638_Write_Data(u16 Data);
参数:数据(u16 Data)
返回值:无

**************************************/

void TLV5638_Write_Data(u16 Data)
{
    u16 i = 0;
    TLV5638_CS_Reset;//CS口置低,数据写入开始
    for (i = 0; i < 16; ++i)//开始16位传输
    {
        if (Data & 0x8000)
        {
            TLV5638_DIN_Set;
        }
        else
        {
            TLV5638_DIN_Reset;
        }
        TLV5638_SCLK_Reset;
        Data <<= 1;//数据左移一位
        TLV5638_SCLK_Set;//一位数据读取完毕
    }
    TLV5638_CS_Set;//CS口置高,数据写入完成
}

/*************************************

功能:负责电压写入控制前,参考电压选择,及初始设置,默认使用0xD002,即REF=2.048V,高速模式(0b1101000000000010)
函数名:TLV5638_Control_Reg(void)
参数:无
返回值:无

**************************************/

void TLV5638_Control_Reg(void)
{
    TLV5638_Write_Data(0xD002);
}

/*************************************

功能:DAC_A输出电压,电压范围 0V ~ 4.096V,电压计算公式V=2*2.048*(CODE/0x1000)(12位电压寄存器)
函数名:TLV5638_DAC_A_Output(float Voltage)
参数:电压(float Voltage)
返回值:无
WARNING:会自动从BUFFER中读取数值,更新DAC_B可能会导致不正常工作

**************************************/

void TLV5638_DAC_A_Output(float Voltage)
{
    u16 CODE = 0x0000;
    TLV5638_Control_Reg();
    CODE = (u16)(Voltage/4.096*0x1000);//转换电压为12位二进制码
    CODE |= 0xC000;//Mode设置,Write data to DAC A and update DAC B with BUFFER content
    TLV5638_Write_Data(CODE);
}

/*************************************

功能:DAC_B输出电压,电压范围 0V ~ 4.096V,电压计算公式V=2*2.048*(CODE/0x1000)(12位电压寄存器)
函数名:TLV5638_DAC_B_Output(float Voltage)
参数:电压(float Voltage)
返回值:无
WARNING:会更新BUFFER,需留意

**************************************/

void TLV5638_DAC_B_Output(float Voltage)
{
    u16 CODE = 0x0000;
    TLV5638_Control_Reg();
    CODE = (u16)(Voltage/4.096*0x1000);//转换电压为12位二进制码
    CODE |= 0x8000;//Mode设置,Write data to DAC B and BUFFER
    TLV5638_Write_Data(CODE);
}

/*************************************

功能:DAC_A_B分别输出电压,电压范围 0V ~ 4.096V,电压计算公式V=2*2.048*(CODE/0x1000)(12位电压寄存器)
函数名:TLV5638_DAC_A_AND_B_Output(float VoltageA, float VoltageB)
参数:A电压(float VoltageA),B电压(float VoltageB)
返回值:无

**************************************/

void TLV5638_DAC_A_AND_B_Output(float VoltageA, float VoltageB)
{
    u16 CODE_A = 0x0000, CODE_B = 0x0000;
    TLV5638_Control_Reg();
    CODE_A = (u16)(VoltageA/4.096*0x1000);//转换电压A为12位二进制码
    CODE_A |= 0xC000;//Write data to DAC A and update DAC B with BUFFER content
    CODE_B = (u16)(VoltageB/4.096*0x1000);//转换电压B为12位二进制码
    CODE_B |= 0x5000;//Write data to BUFFER
    TLV5638_Write_Data(CODE_B);//updata buffer
    TLV5638_Write_Data(CODE_A);//updata A and B
}












