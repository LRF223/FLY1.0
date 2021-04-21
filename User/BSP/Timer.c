#include "Timer.h"
#include "Usart.h"
#include "struct_all.h"

uint32_t Timer3_Count = 0;//记录Timer3中断次数
uint16_t Timer3_Frequency;//Timer3中断频率

TIM_ICInitTypeDef  TIM2_ICInitStructure;

void TIM2_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能TIM2时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin  = CH1_Pin | CH2_Pin | CH3_Pin | CH4_Pin;              
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;           
	GPIO_Init(RC_GPIO, &GPIO_InitStructure);
	GPIO_ResetBits(RC_GPIO, CH1_Pin | CH2_Pin  | CH3_Pin | CH4_Pin);						
	
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
 	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
 	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
 	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
 	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC2S=02 	选择输入端 IC2映射到TI2上
  TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
 	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI2上
 	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
 	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC2,ENABLE);//允许更新中断 ,允许CC2IE捕获中断
 	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC3S=03 	选择输入端 IC3映射到TI3上
  TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
 	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI3上
 	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
 	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC3,ENABLE);//允许更新中断 ,允许CC3IE捕获中断
 	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	TIM2_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC4S=04 	选择输入端 IC4映射到TI4上
  TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
 	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI4上
 	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
 	TIM2_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
	TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC4IE捕获中断	
 	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  	
	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级2级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
  TIM_Cmd(TIM2,ENABLE ); 	

}


u8  TIM2CH1_CAPTURE_STA=0;		//输入捕获状态		    				
u16	TIM2CH1_CAPTURE_VAL;			//输入捕获值

u8  TIM2CH2_CAPTURE_STA = 0;	//输入捕获状态		    				
u16	TIM2CH2_CAPTURE_VAL;			//输入捕获值

u8  TIM2CH3_CAPTURE_STA=0;		//输入捕获状态		    				
u16	TIM2CH3_CAPTURE_VAL;			//输入捕获值

u8  TIM2CH4_CAPTURE_STA = 0;	//输入捕获状态		    				
u16	TIM2CH4_CAPTURE_VAL;			//输入捕获值

void TIM2_IRQHandler(void)
{ 
	/*****************************************
								Time2 CH1
	******************************************/
 	if((TIM2CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)		 
		{	    
			if(TIM2CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM2CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM2CH1_CAPTURE_VAL=0XFFFF;
				}
				else TIM2CH1_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM2CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM2CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM2);
		   	TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}
			else  								//还未开始,第一次捕获上升沿
			{
				TIM2CH1_CAPTURE_STA=0;			//清空
				TIM2CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM2CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
  TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
		
	/*****************************************
								Time2 CH2
	******************************************/
 	if((TIM2CH2_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)		 
		{	    
			if(TIM2CH2_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM2CH2_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM2CH2_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM2CH2_CAPTURE_VAL=0XFFFF;
				}
				else TIM2CH2_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//捕获1发生捕获事件
		{	
			if(TIM2CH2_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM2CH2_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM2CH2_CAPTURE_VAL=TIM_GetCapture2(TIM2);
		   	TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}
			else  								//还未开始,第一次捕获上升沿
			{
				TIM2CH2_CAPTURE_STA=0;			//清空
				TIM2CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM2CH2_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
  TIM_ClearITPendingBit(TIM2, TIM_IT_CC2|TIM_IT_Update); //清除中断标志位
	
	/*****************************************
								Time2 CH3
	******************************************/
 	if((TIM2CH3_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)		 
		{	    
			if(TIM2CH3_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM2CH3_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM2CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM2CH3_CAPTURE_VAL=0XFFFF;
				}
				else TIM2CH3_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)//捕获1发生捕获事件
		{	
			if(TIM2CH3_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM2CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM2CH3_CAPTURE_VAL=TIM_GetCapture3(TIM2);
		   	TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}
			else  								//还未开始,第一次捕获上升沿
			{
				TIM2CH3_CAPTURE_STA=0;			//清空
				TIM2CH3_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM2CH3_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
  TIM_ClearITPendingBit(TIM2, TIM_IT_CC3|TIM_IT_Update); //清除中断标志位
	
	/*****************************************
								Time2 CH4
	******************************************/	
	if((TIM2CH4_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM2CH4_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM2CH4_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM2CH4_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM2CH4_CAPTURE_VAL=0XFFFF;
				}
				else TIM2CH4_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)//捕获1发生捕获事件
		{	
			if(TIM2CH4_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM2CH4_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
				TIM2CH4_CAPTURE_VAL=TIM_GetCapture4(TIM2);
		   	TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}
			else  								//还未开始,第一次捕获上升沿
			{
				TIM2CH4_CAPTURE_STA=0;			//清空
				TIM2CH4_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);
				TIM2CH4_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC4|TIM_IT_Update); //清除中断标志位
 
}

/******************************************************************************
函数原型：	void Timer3_Init(uint16_t Handler_Frequency)
功    能：	初始化定时器3
参    数：   Handler_Frequency为Timer3中断频率
*******************************************************************************/ 
void Timer3_Init(uint16_t Handler_Frequency)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	Timer3_Frequency = Handler_Frequency;
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Period = 1000*1000/Handler_Frequency ;//装载值
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;	//分频系数
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //不分割时钟
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);//清除中断标志
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);//使能定时器3
}



