#include"DELAY.H"
#include "intrins.h"
void delay_5us(unsigned char us)
{
  unsigned char i=0;
  for(;us;us--)
  for(i=0;i<14;i++);
}


void Delay2(unsigned long cnt)
{
   for(;cnt;cnt--)
   delay_5us(200);
}
