#include "rgb.h"

uint16_t RGB_HUE = 0 , RGB_VALUE = 5 ;//色相0-360和亮度0-10

void HUE2RGB(uint16_t HUE,uint16_t VALUE)
{
	//HUE*VALUE不能大于TIM Autoreload
	uint16_t R , G , B ;
	if(HUE<120)
	{
		R = 120 - HUE ;
		G = HUE ;
		B = 0 ;
	}
	else if(HUE<240)
	{
		R = 0 ;
		G = 240 - HUE ;
		B = HUE - 120 ;
	}
	else
	{
		R = HUE - 240;
		G = 0 ;
		B = 360 - HUE;
	}
	RGB_Set_R(R*VALUE);
	RGB_Set_G(G*VALUE);
	RGB_Set_B(B*VALUE);
}
