#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"

#define RC_GPIO GPIOA
#define CH1_Pin GPIO_Pin_0 
#define CH2_Pin GPIO_Pin_1 
#define CH3_Pin GPIO_Pin_2
#define CH4_Pin GPIO_Pin_3 
#define CH5_Pin GPIO_Pin_11 

/******************************************************************************
							全局变量声明
*******************************************************************************/ 
extern uint32_t Timer3_Count;
extern uint16_t Timer3_Frequency;
extern uint8_t Count_1ms,Count_2ms,Count_4ms;

/******************************************************************************
							全局函数声明
*******************************************************************************/ 
void Timer3_Init(uint16_t Handler_Frequency);
void TIM2_Cap_Init(u16 arr,u16 psc);

#endif
