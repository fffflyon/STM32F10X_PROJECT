#ifndef __LED_H
#define __LED_H	 
#include "stm32f10x.h"

//LED¶Ë¿Ú¶¨Òå

#define LED0 PCout(14)// 
#define LED1 PBout(3)// 
#define LED2 PAin(11)// 
#define LED3 PAin(12)//

#define SP_On()         GPIO_ResetBits(GPIOB,GPIO_Pin_15)
#define SP_Off()        GPIO_SetBits(GPIOB,GPIO_Pin_15)
void LED_Init(void);

void IWDG_Init(u8 prer,u16 rlr);
void IWDG_Feed(void);		 				    
#endif
