#include "Motor.h"
#include "Usart.h"
#include "Pwm.h"
#include "Timer.h"
#include "Tasks.h"
#include "MPU6050.h"
#include "GPIO.h"
#include "Control.h"
#include "struct_all.h"
#include "Rc.h"


/******************************************************************************
����ԭ�ͣ�	void BSP_Int(void)
��    �ܣ�	Ӳ��������ʼ��
*******************************************************************************/ 
void BSP_Init(void)
{
	RCC_Configuration(); 								//ʱ������
	TIM4_PWM_Init(2000-1,72-1); 						//PWMʱ��Ƶ��=72 000 KHZ/(2000)*(72) = 500 HZ 
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2,2λ��ռ���ȼ�,2λ��Ӧ���ȼ�
	USART1_Init(115200); 	 //���ڳ�ʼ��Ϊ115200
	TIM2_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ��� 	
	I2C_MPU6050_Init();
	GPIO_Funtion_Init();
	
}

/******************************************************************************
����ԭ�ͣ�	void Task_loop(void)
��    �ܣ�	��ѭ������������
*******************************************************************************/ 
void Task_Loop(void)
{
	Rc_Recive();//����ң�����ź�	
	Manual_Fly_Mode();
	
	
}

