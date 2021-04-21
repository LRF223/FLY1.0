#include "stm32f10x.h" 
#include "Tasks.h"
#include "struct_all.h"

int main (void)
{	
	BSP_Init();					//µ×²ãÇı¶¯³õÊ¼»¯	
	while(1)
	{
		if(Count_1ms>=1)
		{	
			Count_1ms = 0;
			Task_1000HZ();
		}
		if(Count_2ms>=2)
		{
			Count_2ms = 0;
			Task_500HZ();
		}
		if(Count_4ms>=4)
		{
			Count_4ms = 0;
			Task_250HZ();
		}
	}
}
