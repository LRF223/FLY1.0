#include "Rc.h"
#include "Usart.h"

extern u8   TIM2CH1_CAPTURE_STA;	//���벶��״̬		    				
extern u16	TIM2CH1_CAPTURE_VAL;	//���벶��ֵ
extern u8   TIM2CH2_CAPTURE_STA;	//���벶��״̬		    				
extern u16	TIM2CH2_CAPTURE_VAL;	//���벶��ֵ
extern u8   TIM2CH3_CAPTURE_STA;	//���벶��״̬		    				
extern u16	TIM2CH3_CAPTURE_VAL;	//���벶��ֵ
extern u8   TIM2CH4_CAPTURE_STA;	//���벶��״̬		    				
extern u16	TIM2CH4_CAPTURE_VAL;	//���벶��ֵ

extern int32_t CH1=0; 
extern int32_t CH2=0; 
extern u32 CH3=0; 
extern u32 CH4=0; 

void Rc_Recive(void)
{	
	//ͨ��һ�źŽ���
	if(TIM2CH1_CAPTURE_STA&0X80)		//�ɹ�������һ��������
	{
    CH1=TIM2CH1_CAPTURE_STA&0X3F;
		CH1*=65536;		//���ʱ���ܺ�
		CH1+=TIM2CH1_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
    USART1_printf("CH1:%d	",CH1); 
    TIM2CH1_CAPTURE_STA = 0;        
  }	
	//ͨ�����źŽ���
	if(TIM2CH2_CAPTURE_STA&0X80)		//�ɹ�������һ��������
	{
    CH2=TIM2CH2_CAPTURE_STA&0X3F;
		CH2*=65536;		//���ʱ���ܺ�
		CH2+=TIM2CH2_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
    USART1_printf("CH2:%d	",CH2); 
    TIM2CH2_CAPTURE_STA = 0;        
  }
	//ͨ�����źŽ���
	if(TIM2CH3_CAPTURE_STA&0X80)		//�ɹ�������һ��������
	{
    CH3=TIM2CH3_CAPTURE_STA&0X3F;
		CH3*=65536;		//���ʱ���ܺ�
		CH3+=TIM2CH3_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
    USART1_printf("CH3:%d		",CH3); 
    TIM2CH3_CAPTURE_STA = 0;     
  }
	//ͨ�����źŽ���
  if(TIM2CH4_CAPTURE_STA&0X80)		//�ɹ�������һ��������
	{
    CH4=TIM2CH4_CAPTURE_STA&0X3F;
		CH4*=65536;		//���ʱ���ܺ�
		CH4+=TIM2CH4_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
    USART1_printf("CH4:%d\r\n",CH4); 
    TIM2CH4_CAPTURE_STA = 0;        
  }		
}
