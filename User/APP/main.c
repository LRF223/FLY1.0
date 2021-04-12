#include "stm32f10x.h" 
#include "Sys.h"
#include "Delay.h"
#include "Tasks.h"
#include <math.h>
#include "Usart.h"
#include "Rc.h"
#include "struct_all.h"
#include "GPIO.h"
#include "Control.h"



int main (void)
{	
	BSP_Init();
	MPU6050_Init();
		
	while(1)
	{			
		Task_Loop();		
		
	}
}
