#include "uart.h"

void UART1_Init()
{
	LL_USART_InitTypeDef USART_InitStruct = {0};
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);//使能串口1时钟
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);//使能GPIOB时钟
	/**USART1 GPIO Configuration
	PB6   ------> USART1_TX
	PB7   ------> USART1_RX
	*/
	GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;//替换模式(外设io复用模式)
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;//龟速io
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;//推挽模式
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;//无内部上下拉
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;//使用AF0 IO复用设置
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);//初始化GPIO
	GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	USART_InitStruct.PrescalerValue = LL_USART_PRESCALER_DIV1;//分频器1倍
	USART_InitStruct.BaudRate = 2000000;//波特率
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;//数据位数
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;//1停止位
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;//无校验
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;//传输方向双向
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;//硬件控制无
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;//过采样以防干扰
	LL_USART_Init(USART1, &USART_InitStruct);//初始化串口

	LL_USART_ConfigAsyncMode(USART1);//设置为异步模式
	LL_USART_EnableDMAReq_RX(USART1);//使能串口DMA接收
	LL_USART_Enable(USART1);//使能串口
}

void UART1_DMA_TXRX_Init()//串口发送接收DMA初始化
{
	//打开DMA时钟
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	//设置DMA模式
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MODE_CIRCULAR);
	//DMA设置通道优先级
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PRIORITY_MEDIUM);
	//DMA设置传输方向
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	//DMA设置传输数据的长度（一次DMA传输的量）
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, OLED_SHOW_BUFF_BYTES_NUMBER);//512字节
	//DMA设置内存的地址
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_2, (uint32_t)&OLED_SHOW_BUFF);
	//设置内存储存单位的大小
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MDATAALIGN_BYTE);
	//设置内存地址增量模式
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MEMORY_INCREMENT);
	//设置外设地址
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_2, (uint32_t)&USART1->RDR);
	//设置外设存寄存器单位大小
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MDATAALIGN_BYTE);
	//设置外设地址增量模式
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MEMORY_NOINCREMENT);
	//设置外设请求
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_2, LL_DMAMUX_REQ_USART1_RX);

	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);//使能传输完成中断

	NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0);
	NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
}

void UART1_DMA_ReadStart()//DMA开始自动搬运串口数据
{
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, OLED_SHOW_BUFF_BYTES_NUMBER);//设置数据长度
	LL_DMA_EnableChannel(DMA1,LL_DMA_CHANNEL_2);//开启通道
}

void DMA1_Channel2_3_IRQHandler()//搬运512字节完成
{
	LL_DMA_ClearFlag_TC2(DMA1);//清除中断标志
	//LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);//关闭通道
	OLED_SCANALL();//把刚获取的512字节数据更新到屏幕（运行屏幕SPI DMA）
	LL_USART_TransmitData8(USART1,'F');//发送一帧成功信号
}
