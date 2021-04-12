#include "pwm.h"

void TIM4_PWM_Init(u16 arr,u16 psc){  														//TIM4 PWM��ʼ�� arr��װ��ֵ pscԤ��Ƶϵ��
    GPIO_InitTypeDef    		 GPIO_InitStrue;
    TIM_OCInitTypeDef    		 TIM_OCInitStrue;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStrue;
      
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);						//ʹ��TIM4�����GPIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);					//ʹ��GPIOBʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);						//ʹ��AFIOʱ��(��ʱ��3ͨ��3��Ҫ��ӳ�䵽BP5����)
    
    GPIO_InitStrue.GPIO_Pin= M1_Pin | M2_Pin | M3_Pin | M4_Pin;		
    GPIO_InitStrue.GPIO_Mode=GPIO_Mode_AF_PP;											//��������
    GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;										//�����������ٶ�
    GPIO_Init(PWM_GPIO,&GPIO_InitStrue);													//GPIO�˿ڳ�ʼ������
	      
    TIM_TimeBaseInitStrue.TIM_Period=arr;    											//�����Զ���װ��ֵ
    TIM_TimeBaseInitStrue.TIM_Prescaler=psc;        		  				//Ԥ��Ƶϵ��
    TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;     //�������������
    TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;         //����Ƶ
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStrue);        				//TIM4��ʼ������(����PWM������)

    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        						//PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;						//���ü���-��Ч��ƽΪ���ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;				//���ʹ��		
    TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);      			  //ʹ��Ԥװ�ؼĴ���
    TIM_OC1Init(TIM4,&TIM_OCInitStrue);  			

    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        						//PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;						//���ü���-��Ч��ƽΪ���ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;				//���ʹ��
    TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);      			  //ʹ��Ԥװ�ؼĴ���
    TIM_OC2Init(TIM4,&TIM_OCInitStrue);  		

    TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;        						//PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;						//���ü���-��Ч��ƽΪ���ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;				//���ʹ��
    TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);      			  //ʹ��Ԥװ�ؼĴ���
    TIM_OC3Init(TIM4,&TIM_OCInitStrue);  		
		
		TIM_OCInitStrue.TIM_OCMode=TIM_OCMode_PWM1;										//PWMģʽ1:CNT < CCRʱ�����Ч��ƽ
    TIM_OCInitStrue.TIM_OCPolarity=TIM_OCPolarity_High;						//���ü���-��Ч��ƽΪ���ߵ�ƽ
    TIM_OCInitStrue.TIM_OutputState=TIM_OutputState_Enable;				//���ʹ��
    TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);      			  //ʹ��Ԥװ�ؼĴ���
    TIM_OC4Init(TIM4,&TIM_OCInitStrue);        										
		
		TIM_Cmd(TIM4,ENABLE);																					//ʹ��TIM4
    
}
