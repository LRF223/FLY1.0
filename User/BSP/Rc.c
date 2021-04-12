#include "Rc.h"
#include "Usart.h"

extern u8   TIM2CH1_CAPTURE_STA;	//输入捕获状态		    				
extern u16	TIM2CH1_CAPTURE_VAL;	//输入捕获值
extern u8   TIM2CH2_CAPTURE_STA;	//输入捕获状态		    				
extern u16	TIM2CH2_CAPTURE_VAL;	//输入捕获值
extern u8   TIM2CH3_CAPTURE_STA;	//输入捕获状态		    				
extern u16	TIM2CH3_CAPTURE_VAL;	//输入捕获值
extern u8   TIM2CH4_CAPTURE_STA;	//输入捕获状态		    				
extern u16	TIM2CH4_CAPTURE_VAL;	//输入捕获值

extern int32_t CH1=0; 
extern int32_t CH2=0; 
extern u32 CH3=0; 
extern u32 CH4=0; 

void Rc_Recive(void)
{	
	//通道一信号接收
	if(TIM2CH1_CAPTURE_STA&0X80)		//成功捕获到了一次上升沿
	{
    CH1=TIM2CH1_CAPTURE_STA&0X3F;
		CH1*=65536;		//溢出时间总和
		CH1+=TIM2CH1_CAPTURE_VAL;		//得到总的高电平时间
    USART1_printf("CH1:%d	",CH1); 
    TIM2CH1_CAPTURE_STA = 0;        
  }	
	//通道二信号接收
	if(TIM2CH2_CAPTURE_STA&0X80)		//成功捕获到了一次上升沿
	{
    CH2=TIM2CH2_CAPTURE_STA&0X3F;
		CH2*=65536;		//溢出时间总和
		CH2+=TIM2CH2_CAPTURE_VAL;		//得到总的高电平时间
    USART1_printf("CH2:%d	",CH2); 
    TIM2CH2_CAPTURE_STA = 0;        
  }
	//通道三信号接收
	if(TIM2CH3_CAPTURE_STA&0X80)		//成功捕获到了一次上升沿
	{
    CH3=TIM2CH3_CAPTURE_STA&0X3F;
		CH3*=65536;		//溢出时间总和
		CH3+=TIM2CH3_CAPTURE_VAL;		//得到总的高电平时间
    USART1_printf("CH3:%d		",CH3); 
    TIM2CH3_CAPTURE_STA = 0;     
  }
	//通道四信号接收
  if(TIM2CH4_CAPTURE_STA&0X80)		//成功捕获到了一次上升沿
	{
    CH4=TIM2CH4_CAPTURE_STA&0X3F;
		CH4*=65536;		//溢出时间总和
		CH4+=TIM2CH4_CAPTURE_VAL;		//得到总的高电平时间
    USART1_printf("CH4:%d\r\n",CH4); 
    TIM2CH4_CAPTURE_STA = 0;        
  }		
}
