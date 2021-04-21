#include "Rc.h"
#include "Usart.h"
#include "struct_all.h"

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
    Rc.ROLL	=	TIM2CH1_CAPTURE_STA&0X3F;
		Rc.ROLL	*=	65536;		//���ʱ���ܺ�
		Rc.ROLL	+=	TIM2CH1_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
    TIM2CH1_CAPTURE_STA = 0;        
  }	
	//ͨ�����źŽ���
	if(TIM2CH2_CAPTURE_STA&0X80)		//�ɹ�������һ��������
	{
    Rc.PITCH =  TIM2CH2_CAPTURE_STA&0X3F;
		Rc.PITCH *= 65536;		//���ʱ���ܺ�
		Rc.PITCH += TIM2CH2_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
    TIM2CH2_CAPTURE_STA = 0;        
  }
	//ͨ�����źŽ���
	if(TIM2CH3_CAPTURE_STA&0X80)		//�ɹ�������һ��������
	{
    Rc.THROTTLE = TIM2CH3_CAPTURE_STA&0X3F;
		Rc.THROTTLE *= 65536;		//���ʱ���ܺ�
		Rc.THROTTLE += TIM2CH3_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
    TIM2CH3_CAPTURE_STA = 0;     
  }
	//ͨ�����źŽ���
  if(TIM2CH4_CAPTURE_STA&0X80)		//�ɹ�������һ��������
	{
    Rc.YAW	=		TIM2CH4_CAPTURE_STA&0X3F;
		Rc.YAW	*=	65536;		//���ʱ���ܺ�
		Rc.YAW	+=	TIM2CH4_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
    TIM2CH4_CAPTURE_STA = 0;        
  }		
//  USART1_printf("Rc.ROLL:%d	",Rc.ROLL); 
//	USART1_printf("Rc.PITCH:%d	",Rc.PITCH); 
//	USART1_printf("Rc.THROTTLE:%d	",Rc.THROTTLE); 	
//	USART1_printf("Rc.YAW:%d\r\n",Rc.YAW); 	
}
