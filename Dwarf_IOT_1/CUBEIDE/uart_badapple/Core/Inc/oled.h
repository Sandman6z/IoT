#ifndef _OLED_H_
#define _OLED_H_

//请调用您的系统头文件，以保证本库函数可以调用您的使用的固件库：
#include "main.h"
#include "string.h"

//*为必须设置，分辨率行列数：
#define OLED_Resolution_Row				32//垂直分辨率*
#define OLED_Resolution_Column			128//水平分辨率*

//重新封装SPI发送函数，请修改成你的SPI发送字节的函数，请根据您的代码做出适应修改：
#define OLED_Write_Byte(OLED_Byte)		LL_SPI_TransmitData8(SPI2, OLED_Byte);//LL库重新封装
//#define OLED_Write_Byte(OLED_Byte)	SPI_I2S_SendData(修改SPIx, OLED_Byte);//标准固件库重新封装
//#define OLED_Write_Byte(OLED_Byte)	HAL_SPI_Transmit(修改*hspi,OLED_Byte,1,128);//HAL库重新封装

//重新封装IO口操作函数，复位线、使能线与数据指令切换线，请修改成您的IO电平控制函数：
#define OLED_RES_SET()					LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_4)
#define OLED_RES_RESET()				LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4)
#define OLED_CS_SET()					LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_6)
#define OLED_CS_RESET()					LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_6)
#define OLED_DC_SET()					LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5)
#define OLED_DC_RESET()					LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5)

//重新封装延时函数：
#define OLED_Delay(DTime)				LL_mDelay(DTime)

//无需修改！！！一些布尔值宏定义和计算常量
#define OLED_DataSignal					0
#define OLED_ComSignal					1
#define OLED_CSOFF						0
#define OLED_CSON						1
#define OLED_Page_Number				(OLED_Resolution_Row/8)
#define OLED_SHOW_BUFF_BYTES_NUMBER		(OLED_Page_Number*OLED_Resolution_Column)
//-----------------------------------------------------------------------------------------

//申明屏幕内容缓存数组，也就是显存
extern uint8_t OLED_SHOW_BUFF[][OLED_Resolution_Column];

#define OLED_SETALLBYTE(BYTE) 			memset(OLED_SHOW_BUFF,BYTE,OLED_SHOW_BUFF_BYTES_NUMBER)//用一个指定数据填充屏幕
#define OLED_Clean() 					memset(OLED_SHOW_BUFF,0x00,OLED_SHOW_BUFF_BYTES_NUMBER)//清理屏幕缓存
void OLED_PointerReset();//指针复位到原点
void OLED_SignalMode(uint8_t MODE);//切换信号类型，传输指令或传输数据
void OLED_CS(uint8_t ONOFF);//使能或失能屏幕
void OLED_RESET();//复位屏幕
void OLED_GPIO_Init();//OLED各GPIO初始化
void OLED_Init();//OLED屏幕初始化函数，请在完成基础外设（GPIO\SPI）初始化后调用本函数
void OLED_PointerReset();//指针复位到原点
void OLED_DMA_Init();//OLED DMA初始化
uint8_t OLED_SCANALL();//触发DMA进行一次全屏扫描

#endif
