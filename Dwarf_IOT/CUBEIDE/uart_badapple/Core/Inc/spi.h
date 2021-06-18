#ifndef _SPI_H_
#define _SPI_H_

#include "main.h"

extern uint8_t SPI2_BSY ;//SPI2占用标志位，使用中置位，释放后置低

void SPI1_Init();
void SPI2_Init();

#endif
