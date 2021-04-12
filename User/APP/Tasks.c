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
函数原型：	void BSP_Int(void)
功    能：	硬件驱动初始化
*******************************************************************************/ 
void BSP_Init(void)
{
	RCC_Configuration(); 								//时钟设置
	TIM4_PWM_Init(2000-1,72-1); 						//PWM时钟频率=72 000 KHZ/(2000)*(72) = 500 HZ 
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2,2位抢占优先级,2位响应优先级
	USART1_Init(115200); 	 //串口初始化为115200
	TIM2_Cap_Init(0XFFFF,72-1);	//以1Mhz的频率计数 	
	I2C_MPU6050_Init();
	GPIO_Funtion_Init();
	
}

/******************************************************************************
函数原型：	void Task_loop(void)
功    能：	主循环中运行任务
*******************************************************************************/ 
void Task_Loop(void)
{
	Rc_Recive();//接收遥控器信号	
	Manual_Fly_Mode();
	
	
}

