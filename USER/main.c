#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
#include "dac.h"

int main(void)
{ 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断
	delay_init(168);      //delay初始化，系统主频168MHz
	uart_init(115200);		//USART1波特率设置为115200
	
	Adc_Init(); 				//adc初始化
	Dac1_Init();		 		//DAC初始化
 	
	while(1)
	{
		
	}	
}

