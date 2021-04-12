#include "sys.h"
#include "Control.h"
#include "struct_all.h"
#include "Rc.h"
//#include "Usart.h"

extern u32 M1_Output = 0; 
extern u32 M2_Output = 0; 
extern u32 M3_Output = 0; 
extern u32 M4_Output = 0; 

int k = 1;

void Manual_Fly_Mode(void)
{
	M1_Output = M2_Output = M3_Output = M4_Output = CH3;
	
	CH1 -=1500;
	CH2 -=1500;
	if(CH1 > 10)//横滚杆打右
	{
	M1_Output = M4_Output = k*(CH3 - CH1);
	M3_Output = M2_Output = k*(CH3 + CH1);	
	}
	if(CH1 < -10)//横滚杆打左
	{
	M1_Output = M4_Output = k*(CH3 - CH1);
	M3_Output = M2_Output = k*(CH3 + CH1);	
	}
	if(CH2 > 10)//俯仰杆打上
	{
	M1_Output = M3_Output = k*(CH3 - CH2);
	M4_Output = M2_Output = k*(CH3 + CH2);	
	}
	if(CH2 < -10)//俯仰杆打下
	{
	M1_Output = M3_Output = k*(CH3 - CH2);
	M4_Output = M2_Output = k*(CH3 + CH2);	
	}
	
	if(CH3<900)//失控保护
	{
		TIM_SetCompare1(TIM4, 0);+
		
		TIM_SetCompare2(TIM4, 0);
		TIM_SetCompare3(TIM4, 0);
		TIM_SetCompare4(TIM4, 0);	
	}
	
	TIM_SetCompare1(TIM4, M1_Output);
	TIM_SetCompare2(TIM4, M2_Output);
	TIM_SetCompare3(TIM4, M3_Output);
	TIM_SetCompare4(TIM4, M4_Output);
//	USART1_printf("\r\n M1_Output=%d	",M1_Output);
//	USART1_printf("M2_Output=%d	",M2_Output);
//	USART1_printf("M3_Output=%d	",M3_Output);	
//	USART1_printf("M4_Output=%d	",M4_Output);
}



