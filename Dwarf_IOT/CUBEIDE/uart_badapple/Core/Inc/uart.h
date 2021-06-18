#ifndef _UART_H_
#define _UART_H_

#include "main.h"

void UART1_Init();
void UART1_DMA_TXRX_Init();//串口接收DMA初始化
void UART1_DMA_ReadStart();//DMA开始自动搬运串口数据

#endif
