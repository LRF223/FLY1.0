#include "Motor.h"
#include "Usart.h"
#include "Pwm.h"
#include "Timer.h"
#include "Tasks.h"
#include "MPU6050.h"
#include "Control.h"
#include "struct_all.h"
#include "Rc.h"
#include "Filter.h"
#include "Maths.h"
#include "IMU.h"

uint8_t Bsp_Int_Ok = 0;

/******************************************************************************
����ԭ�ͣ�	void Nvic_Init(void)
��    �ܣ�	NVIC��ʼ��
*******************************************************************************/ 
void Nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//NVIC_PriorityGroup 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ȼ�����
	//Timer3
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************************
����ԭ�ͣ�	void BSP_Int(void)
��    �ܣ�	Ӳ��������ʼ��
*******************************************************************************/ 
void BSP_Init(void)
{
	RCC_Configuration(); 														//ʱ������
	Timer3_Init(1000);															//Timer3�ж�1KHZ
	Nvic_Init();																		//�ж����ȼ���ʼ��	
	TIM4_PWM_Init(2000-1,72-1); 										//PWMʱ��Ƶ��=72 000 KHZ/(2000)*(72) = 500 HZ 		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2,2λ��ռ���ȼ�,2λ��Ӧ���ȼ�
	USART1_Init(115200); 														//���ڳ�ʼ��Ϊ115200
	TIM2_Cap_Init(0XFFFF,72-1);											//��1Mhz��Ƶ�ʼ��� 
	I2C_MPU6050_Init();															//I2C���߳�ʼ��
	while( MPU6050_Init() != 1);										//��MPU6050��ʼ�����ɹ����������������
	FLASH_Unlock();																	//Flash����
	EEPROM_INIT();																	//��ʼ��ģ���EEPROM����ȡ����
	Bsp_Int_Ok = 1;
	USART1_printf("\r\n Bsp Init Finish"); 	
}

/******************************************************************************
����ԭ�ͣ�	void Task_1000HZ(void)
��    �ܣ�	��ѭ��������Ƶ��Ϊ1000HZ����
*******************************************************************************/ 
void Task_1000HZ(void)
{
	if( MPU6050_SequenceRead()==0 )//��������ȡ6050���ݼĴ���ʧ��
	{
		I2C_Erro++;//ͳ��I2C�������
		MPU6050_SingleRead();//�ִζ�MPU6050���ݼĴ���
	}
	MPU6050_Compose();//6050���ݺϳ�
	ACC_IIR_Filter(&acc,&filter_acc);//��acc��IIR�˲�
	Gyro_Filter(&gyro,&filter_gyro);//��gyro�������˲�
	Get_Radian(&filter_gyro,&SI_gyro);//���ٶ�����תΪ����	
	IMUupdate(SI_gyro.x,SI_gyro.y,SI_gyro.z,filter_acc.x,filter_acc.y,filter_acc.z);//��̬����	
		
	Rc_Recive();//����ң�����ź�	
//	Manual_Fly_Mode();	
		
}
/******************************************************************************
����ԭ�ͣ�	void Task_500HZ(void)
��    �ܣ�	��ѭ��������Ƶ��Ϊ500HZ����
*******************************************************************************/ 
void Task_500HZ(void)
{
	Control_Gyro(&SI_gyro,&Rc,Rc_Lock);//�ڻ�����
}

/******************************************************************************
����ԭ�ͣ�	void Task_250HZ(void)
��    �ܣ�	��ѭ��������Ƶ��Ϊ250HZ����
*******************************************************************************/ 
void Task_250HZ(void)
{
	Get_Eulerian_Angle(&out_angle);//��Ԫ��תŷ����
	Control_Angle(&out_angle,&Rc);//�⻷����
}



