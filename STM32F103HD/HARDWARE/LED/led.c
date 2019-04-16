#include "stm32f10x.h"
#include "led.h"
#include "stm32f10x_iwdg.h"
 /*
 * 函数名： Delay
 * 描述  ：不精确的延时
 * 输入  ：延时参数，
 * 输出  ：无
 */

void LED_Init(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure;
	DBGMCU->CR = DBGMCU->CR & ~((uint32_t)1<<5);
	RCC->APB2ENR = 1 |  (1<<3);  
	AFIO->MAPR = (AFIO->MAPR & ~((uint32_t)0x7 << 24)) | (2 << 24); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;					 //LED0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_14);		

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_3);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

}
//////////////////////////////////////////////////////////////////////////////////	 
//初始化独立看门狗
//prer:分频数:0~7(只有低3位有效!)
//分频因子=4*2^prer.但最大值只能是256!
//rlr:重装载寄存器值:低11位有效.
//时间计算(大概):Tout=((4*2^prer)*rlr)/40 (ms).
void IWDG_Init(u8 prer,u16 rlr) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能对寄存器IWDG_PR和IWDG_RLR的写操作
	
	IWDG_SetPrescaler(prer);  //设置IWDG预分频值:设置IWDG预分频值为64
	
	IWDG_SetReload(rlr);  //设置IWDG重装载值
	
	IWDG_ReloadCounter();  //按照IWDG重装载寄存器的值重装载IWDG计数器
	
	IWDG_Enable();  //使能IWDG
}
//喂独立看门狗
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();//reload										   
}
