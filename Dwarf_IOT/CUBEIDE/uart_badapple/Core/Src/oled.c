#include "oled.h"

//开辟一个显存空间
uint8_t OLED_SHOW_BUFF[OLED_Page_Number][OLED_Resolution_Column];

//切换信号模式
//OLED_DataSignal数据模式，OLED_ComSignal指令模式
void OLED_SignalMode(uint8_t MODE)
{
	if(MODE)
		OLED_DC_RESET();//指令模式
	else
		OLED_DC_SET();//数据模式
}

//切换屏幕使能
//OLED_CSON使能屏幕，OLED_CSOFF失能屏幕
void OLED_CS(uint8_t ONOFF)
{
	if(ONOFF)
		OLED_CS_RESET();//使能屏幕，可以通讯
	else
		OLED_CS_SET();//失能屏幕，停止通讯
}

//OLED硬件复位
void OLED_RESET()
{
	OLED_RES_RESET();
	OLED_Delay(2);
	OLED_RES_SET();
	OLED_Delay(2);
}

//OLED上电初始化设置
void OLED_Init()
{
	OLED_GPIO_Init();//初始化OLED功能IO口
	OLED_CS(OLED_CSON);//使能屏幕
	OLED_RESET();//复位OLED
	OLED_SignalMode(OLED_ComSignal);//指令信号模式

	//设置行寻址模式(使用SPI全屏更新,数据指针从第1页第1列移动到最后1页最后1列再回到始点)
	OLED_Write_Byte(0x20);
	OLED_Write_Byte(0x00);
	//列地址范围与偏移像素设置
	OLED_Write_Byte(0x21);
	OLED_Write_Byte(0x00);
	OLED_Write_Byte((uint8_t)(OLED_Resolution_Column-1));
	//设置页行地址范围为0到屏幕最大页数
	OLED_Write_Byte(0x22);
	OLED_Write_Byte(0x00);//从0页
	OLED_Write_Byte((uint8_t)OLED_Page_Number-1);//到最大页数
	//设置对比度（最大）
	OLED_Write_Byte(0x81);
	OLED_Write_Byte(0xFF);
	//设置屏幕刷新率（最高频率）
	OLED_Write_Byte(0xD5);
	OLED_Write_Byte(0xF0);
	//设置复用率32根COM线，详情请翻阅SSD1306手册40页
	OLED_Write_Byte(0xA8);
	OLED_Write_Byte(OLED_Resolution_Row-1);
	//设置COM脚硬件配置(COM脚按物理顺序，禁用左右映射)
	OLED_Write_Byte(0xDA);
	OLED_Write_Byte(0x02);
	//设置左右翻转
	OLED_Write_Byte(0xA1);
	//设置上下翻转(从COM高位向低位扫描)
	OLED_Write_Byte(0xC8);
	//开启电荷泵
	OLED_Write_Byte(0x8d);
	OLED_Write_Byte(0x14);

	//清屏
	OLED_SignalMode(OLED_DataSignal);//数据信号模式
	for(uint16_t i=0;i<512;i++)
		OLED_Write_Byte(0x00);//填充空数据

	//指令信号模式
	OLED_SignalMode(OLED_ComSignal);
	OLED_Write_Byte(0xAF);//开启显示
	OLED_Delay(100);//等待屏幕运行稳定
	OLED_CS(OLED_CSOFF);//失能屏幕
}

void OLED_PointerReset()//指针复位到原点
{
	OLED_SignalMode(OLED_ComSignal);//指令信号模式
	OLED_Write_Byte(0x00);//设置指针光标列低4位地址0
	OLED_Write_Byte(0x10);//设置指针列高4位地址0
	OLED_Write_Byte(0xB0);//设置指针页地址0
	OLED_SignalMode(OLED_DataSignal);//数据信号模式
}

uint8_t OLED_SCANALL()//DMA开始一次全屏刷新
{
	if(SPI2_BSY == 0)
	{
		SPI2_BSY = 1 ;//表示我即将占用SPI2
		OLED_CS(OLED_CSON);//使能屏幕
		OLED_PointerReset();//指针复位到屏幕左上角原点
		LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, OLED_SHOW_BUFF_BYTES_NUMBER);//设置数据长度
		LL_DMA_EnableChannel(DMA1,LL_DMA_CHANNEL_1);//开启通道
		return 1 ;//刷新成功返回1
	}
	else
		return 0 ;//刷新失败返回0
}

void DMA1_Channel1_IRQHandler()//完成一次DMA传输回到此处，复位显示指针，关闭SPI占用
{
	LL_DMA_ClearFlag_TC1(DMA1);//清除中断标志
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);//关闭通道
	OLED_CS(OLED_CSOFF);//失能屏幕
	SPI2_BSY = 0 ;//释放SPI占用标志位
}

void OLED_DMA_Init()//OLED DMA初始化
{
	//打开DMA时钟
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
	//设置DMA模式
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_NORMAL);
	//DMA设置通道优先级
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_LOW);
	//DMA设置传输方向
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	//DMA设置传输数据的长度（一次DMA传输的量）
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, OLED_SHOW_BUFF_BYTES_NUMBER);
	//DMA设置内存的地址
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&OLED_SHOW_BUFF);
	//设置内存储存单位的大小
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_BYTE);
	//设置内存地址增量模式
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);
	//设置外设地址
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&SPI2->DR);
	//设置外设存寄存器单位大小
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_BYTE);
	//设置外设地址增量模式
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_NOINCREMENT);
	//设置外设请求
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_SPI2_TX);
	//使能传输完成中断
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);

	NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

void OLED_GPIO_Init()//OLED GPIO初始化函数，可修改为各固件库版本
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_6);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
