#include "Timer.h"
#include "Usart.h"
#include "struct_all.h"

uint32_t Timer3_Count = 0;//��¼Timer3�жϴ���
uint16_t Timer3_Frequency;//Timer3�ж�Ƶ��

TIM_ICInitTypeDef  TIM2_ICInitStructure;

void TIM2_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//ʹ��TIM2ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin  = CH1_Pin | CH2_Pin | CH3_Pin | CH4_Pin;              
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;           
	GPIO_Init(RC_GPIO, &GPIO_InitStructure);
	GPIO_ResetBits(RC_GPIO, CH1_Pin | CH2_Pin  | CH3_Pin | CH4_Pin);						
	
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
 	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
 	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
 	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	
 	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC2S=02 	ѡ������� IC2ӳ�䵽TI2��
  TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
 	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI2��
 	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
 	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC2,ENABLE);//��������ж� ,����CC2IE�����ж�
 	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC3S=03 	ѡ������� IC3ӳ�䵽TI3��
  TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
 	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI3��
 	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
 	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC3,ENABLE);//��������ж� ,����CC3IE�����ж�
 	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC4S=04 	ѡ������� IC4ӳ�䵽TI4��
  TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
 	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI4��
 	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
 	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC4,ENABLE);//��������ж� ,����CC4IE�����ж�	
 	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  	
	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
	
  TIM_Cmd(TIM2,ENABLE ); 	

}


u8  TIM2CH1_CAPTURE_STA=0;		//���벶��״̬		    				
u16	TIM2CH1_CAPTURE_VAL;			//���벶��ֵ

u8  TIM2CH2_CAPTURE_STA = 0;	//���벶��״̬		    				
u16	TIM2CH2_CAPTURE_VAL;			//���벶��ֵ

u8  TIM2CH3_CAPTURE_STA=0;		//���벶��״̬		    				
u16	TIM2CH3_CAPTURE_VAL;			//���벶��ֵ

u8  TIM2CH4_CAPTURE_STA = 0;	//���벶��״̬		    				
u16	TIM2CH4_CAPTURE_VAL;			//���벶��ֵ

void TIM2_IRQHandler(void)
{ 
	/*****************************************
								Time2 CH1
	******************************************/
 	if((TIM2CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)		 
		{	    
			if(TIM2CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM2CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM2CH1_CAPTURE_VAL=0XFFFF;
				}
				else TIM2CH1_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(TIM2CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM2CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
				TIM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM2);
		   	TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}
			else  								//��δ��ʼ,��һ�β���������
			{
				TIM2CH1_CAPTURE_STA=0;			//���
				TIM2CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM2CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
  TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
		
	/*****************************************
								Time2 CH2
	******************************************/
 	if((TIM2CH2_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)		 
		{	    
			if(TIM2CH2_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM2CH2_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM2CH2_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM2CH2_CAPTURE_VAL=0XFFFF;
				}
				else TIM2CH2_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//����1���������¼�
		{	
			if(TIM2CH2_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM2CH2_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
				TIM2CH2_CAPTURE_VAL=TIM_GetCapture2(TIM2);
		   	TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}
			else  								//��δ��ʼ,��һ�β���������
			{
				TIM2CH2_CAPTURE_STA=0;			//���
				TIM2CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM2CH2_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
  TIM_ClearITPendingBit(TIM2, TIM_IT_CC2|TIM_IT_Update); //����жϱ�־λ
	
	/*****************************************
								Time2 CH3
	******************************************/
 	if((TIM2CH3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)		 
		{	    
			if(TIM2CH3_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM2CH3_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM2CH3_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM2CH3_CAPTURE_VAL=0XFFFF;
				}
				else TIM2CH3_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)//����1���������¼�
		{	
			if(TIM2CH3_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM2CH3_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
				TIM2CH3_CAPTURE_VAL=TIM_GetCapture3(TIM2);
		   	TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}
			else  								//��δ��ʼ,��һ�β���������
			{
				TIM2CH3_CAPTURE_STA=0;			//���
				TIM2CH3_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM2CH3_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
  TIM_ClearITPendingBit(TIM2, TIM_IT_CC3|TIM_IT_Update); //����жϱ�־λ
	
	/*****************************************
								Time2 CH4
	******************************************/	
	if((TIM2CH4_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM2CH4_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM2CH4_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM2CH4_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM2CH4_CAPTURE_VAL=0XFFFF;
				}
				else TIM2CH4_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)//����1���������¼�
		{	
			if(TIM2CH4_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM2CH4_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
				TIM2CH4_CAPTURE_VAL=TIM_GetCapture4(TIM2);
		   	TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}
			else  								//��δ��ʼ,��һ�β���������
			{
				TIM2CH4_CAPTURE_STA=0;			//���
				TIM2CH4_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM2CH4_CAPTURE_STA|=0X40;		//��ǲ�����������
				TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC4|TIM_IT_Update); //����жϱ�־λ
 
}

/******************************************************************************
����ԭ�ͣ�	void Timer3_Init(uint16_t Handler_Frequency)
��    �ܣ�	��ʼ����ʱ��3
��    ����   Handler_FrequencyΪTimer3�ж�Ƶ��
*******************************************************************************/ 
void Timer3_Init(uint16_t Handler_Frequency)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	Timer3_Frequency = Handler_Frequency;
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Period = 1000*1000/Handler_Frequency ;//װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;	//��Ƶϵ��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //���ָ�ʱ��
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);//����жϱ�־
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);//ʹ�ܶ�ʱ��3
}



