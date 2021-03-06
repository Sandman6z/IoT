#include "main.h"

int main(void)
{
	//系统上电初始化：
	System_Init();
	//进入正常运行循环：
	while(1)
	{

	}
}

void System_Init()
{
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);//打开系统控制器时钟
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);//打开电源管理器时钟
	SystemClock_Config();//初始化系统时钟树
	UART1_Init();//初始化串口
	SPI2_Init();//初始化SPI2
	OLED_Init();//初始化屏幕
	OLED_DMA_Init();//初始化OLED DMA传输
	OLED_Clean();//清空屏幕缓存
	OLED_SCANALL();//将空白数据写入屏幕清屏
	UART1_DMA_TXRX_Init();//串口接收DMA初始化
	UART1_DMA_ReadStart();//DMA开始自动搬运串口数据
	TIM3_Init();//RGB定时器3
}

void SystemClock_Config()
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
	LL_RCC_HSI_Enable();
	while(LL_RCC_HSI_IsReady() != 1);
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_1, 8, LL_RCC_PLLR_DIV_4);
	LL_RCC_PLL_Enable();
	LL_RCC_PLL_EnableDomain_SYS();
	while(LL_RCC_PLL_IsReady() != 1);
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_Init1msTick(64000000);
	LL_SetSystemCoreClock(64000000);
	LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);
}
