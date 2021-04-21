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
函数原型：	void Nvic_Init(void)
功    能：	NVIC初始化
*******************************************************************************/ 
void Nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//NVIC_PriorityGroup 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级分组
	//Timer3
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//先占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//从占优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/******************************************************************************
函数原型：	void BSP_Int(void)
功    能：	硬件驱动初始化
*******************************************************************************/ 
void BSP_Init(void)
{
	RCC_Configuration(); 														//时钟设置
	Timer3_Init(1000);															//Timer3中断1KHZ
	Nvic_Init();																		//中断优先级初始化	
	TIM4_PWM_Init(2000-1,72-1); 										//PWM时钟频率=72 000 KHZ/(2000)*(72) = 500 HZ 		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2,2位抢占优先级,2位响应优先级
	USART1_Init(115200); 														//串口初始化为115200
	TIM2_Cap_Init(0XFFFF,72-1);											//以1Mhz的频率计数 
	I2C_MPU6050_Init();															//I2C总线初始化
	while( MPU6050_Init() != 1);										//若MPU6050初始化不成功，则程序不向下运行
	FLASH_Unlock();																	//Flash解锁
	EEPROM_INIT();																	//初始化模拟的EEPROM，读取参数
	Bsp_Int_Ok = 1;
	USART1_printf("\r\n Bsp Init Finish"); 	
}

/******************************************************************************
函数原型：	void Task_1000HZ(void)
功    能：	主循环中运行频率为1000HZ任务
*******************************************************************************/ 
void Task_1000HZ(void)
{
	if( MPU6050_SequenceRead()==0 )//若连续读取6050数据寄存器失败
	{
		I2C_Erro++;//统计I2C出错次数
		MPU6050_SingleRead();//分次读MPU6050数据寄存器
	}
	MPU6050_Compose();//6050数据合成
	ACC_IIR_Filter(&acc,&filter_acc);//对acc做IIR滤波
	Gyro_Filter(&gyro,&filter_gyro);//对gyro做窗口滤波
	Get_Radian(&filter_gyro,&SI_gyro);//角速度数据转为弧度	
	IMUupdate(SI_gyro.x,SI_gyro.y,SI_gyro.z,filter_acc.x,filter_acc.y,filter_acc.z);//姿态解算	
		
	Rc_Recive();//接收遥控器信号	
//	Manual_Fly_Mode();	
		
}
/******************************************************************************
函数原型：	void Task_500HZ(void)
功    能：	主循环中运行频率为500HZ任务
*******************************************************************************/ 
void Task_500HZ(void)
{
	Control_Gyro(&SI_gyro,&Rc,Rc_Lock);//内环控制
}

/******************************************************************************
函数原型：	void Task_250HZ(void)
功    能：	主循环中运行频率为250HZ任务
*******************************************************************************/ 
void Task_250HZ(void)
{
	Get_Eulerian_Angle(&out_angle);//四元数转欧拉角
	Control_Angle(&out_angle,&Rc);//外环控制
}



