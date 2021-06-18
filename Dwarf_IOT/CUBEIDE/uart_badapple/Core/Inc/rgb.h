#ifndef _RGB_H_
#define _RGB_H_

#include "main.h"

#define RGB_Set_R(RR)		LL_TIM_OC_SetCompareCH2(TIM3, RR)
#define RGB_Set_G(GG)		LL_TIM_OC_SetCompareCH3(TIM3, GG)
#define RGB_Set_B(BB)		LL_TIM_OC_SetCompareCH4(TIM3, BB)

extern uint16_t RGB_HUE , RGB_VALUE ;//色相和亮度

void HUE2RGB(uint16_t HUE,uint16_t VALUE);

#endif
