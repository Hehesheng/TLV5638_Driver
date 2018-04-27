#include "TLV5638.h"

/*************************************

����:��ʼ��TLV5638����IO��
������:TLV5638_Init(void);
����:��
����ֵ:��

**************************************/

void TLV5638_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��

    //GPIO��ʼ������
    GPIO_InitStructure.GPIO_Pin = TLV5638_SCLK | TLV5638_DIN | TLV5638_CS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ģʽ
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(TLV5638_Control_Port, &GPIO_InitStructure);//��ʼ��
}

/*************************************

����:��TLV5638��д��16λ����
������:TLV5638_Write_Data(u16 Data);
����:����(u16 Data)
����ֵ:��

**************************************/

void TLV5638_Write_Data(u16 Data)
{
    u16 i = 0;
    TLV5638_CS_Reset;//CS���õ�,����д�뿪ʼ
    for (i = 0; i < 16; ++i)//��ʼ16λ����
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
        Data <<= 1;//��������һλ
        TLV5638_SCLK_Set;//һλ���ݶ�ȡ���
    }
    TLV5638_CS_Set;//CS���ø�,����д�����
}

/*************************************

����:�����ѹд�����ǰ,�ο���ѹѡ��,����ʼ����,Ĭ��ʹ��0xD002,��REF=2.048V,����ģʽ(0b1101000000000010)
������:TLV5638_Control_Reg(void)
����:��
����ֵ:��

**************************************/

void TLV5638_Control_Reg(void)
{
    TLV5638_Write_Data(0xD002);
}

/*************************************

����:DAC_A�����ѹ,��ѹ��Χ 0V ~ 4.096V,��ѹ���㹫ʽV=2*2.048*(CODE/0x1000)(12λ��ѹ�Ĵ���)
������:TLV5638_DAC_A_Output(float Voltage)
����:��ѹ(float Voltage)
����ֵ:��
WARNING:���Զ���BUFFER�ж�ȡ��ֵ,����DAC_B���ܻᵼ�²���������

**************************************/

void TLV5638_DAC_A_Output(float Voltage)
{
    u16 CODE = 0x0000;
    TLV5638_Control_Reg();
    CODE = (u16)(Voltage/4.096*0x1000);//ת����ѹΪ12λ��������
    CODE |= 0xC000;//Mode����,Write data to DAC A and update DAC B with BUFFER content
    TLV5638_Write_Data(CODE);
}

/*************************************

����:DAC_B�����ѹ,��ѹ��Χ 0V ~ 4.096V,��ѹ���㹫ʽV=2*2.048*(CODE/0x1000)(12λ��ѹ�Ĵ���)
������:TLV5638_DAC_B_Output(float Voltage)
����:��ѹ(float Voltage)
����ֵ:��
WARNING:�����BUFFER,������

**************************************/

void TLV5638_DAC_B_Output(float Voltage)
{
    u16 CODE = 0x0000;
    TLV5638_Control_Reg();
    CODE = (u16)(Voltage/4.096*0x1000);//ת����ѹΪ12λ��������
    CODE |= 0x8000;//Mode����,Write data to DAC B and BUFFER
    TLV5638_Write_Data(CODE);
}

/*************************************

����:DAC_A_B�ֱ������ѹ,��ѹ��Χ 0V ~ 4.096V,��ѹ���㹫ʽV=2*2.048*(CODE/0x1000)(12λ��ѹ�Ĵ���)
������:TLV5638_DAC_A_AND_B_Output(float VoltageA, float VoltageB)
����:A��ѹ(float VoltageA),B��ѹ(float VoltageB)
����ֵ:��

**************************************/

void TLV5638_DAC_A_AND_B_Output(float VoltageA, float VoltageB)
{
    u16 CODE_A = 0x0000, CODE_B = 0x0000;
    TLV5638_Control_Reg();
    CODE_A = (u16)(VoltageA/4.096*0x1000);//ת����ѹAΪ12λ��������
    CODE_A |= 0xC000;//Write data to DAC A and update DAC B with BUFFER content
    CODE_B = (u16)(VoltageB/4.096*0x1000);//ת����ѹBΪ12λ��������
    CODE_B |= 0x5000;//Write data to BUFFER
    TLV5638_Write_Data(CODE_B);//updata buffer
    TLV5638_Write_Data(CODE_A);//updata A and B
}












