#include "sys.h"


//********************************************************************************  
void NVIC_Configuration(void)
{
	//NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	//设置NVIC优先级分组为Group2：0-3抢占式优先级，0-3的响应式优先级

}
