/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   2.4g无线模块/nrf24l01+/slave 测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_spi_nrf.h"
#include "bsp_SysTick.h"
#include "bsp_exti.h"
#include "bsp_led.h"  

u8 status;		 //用于判断接收/发送状态
u8 txbuf[32];	 //发送缓冲（直接用最大值）
u8 rxbuf[32];	 //接收缓冲（直接用最大值）

 /**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	u8 i;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	//配置中断优先级分组
	
	LED_GPIO_Config();	//LED初始化
	
	EXTI_PA0_Config();	//PA0外部中断初始化
	EXTI_PC13_Config();	//PC13外部中断初始化
	EXTI_PC1_Config();	//PC1外部中断初始化
	
	/* 串口1初始化 */
	USART1_Config(); 

	/*SPI接口初始化*/   
	SPI_NRF_Init(); 

	printf("\r\n  \r\n");
	printf("\r\n 这是一个 NRF24L01 无线传输实验 \r\n");
	printf("\r\n 这是无线传输 从机端 的反馈信息\r\n");
	printf("\r\n   正在检测NRF与MCU是否正常连接。。。\r\n");

	/*检测NRF模块与MCU的连接*/
	status = NRF_Check();   		
	if(status == SUCCESS)
	{
		printf("\r\n      NRF与MCU连接成功\r\n");
	}
	else
	{
		printf("\r\n   连接失败。。。\r\n");
		while(1);
	}
	
	//进入接收模式
	printf("\r\n 从机端 进入接收模式\r\n");
	printf("\r\n NRF默认数据包长度32字节 \r\n");
	printf("\r\n 两个灯：32字节 \r\n");
	printf("\r\n 一个灯：4字节 \r\n");
	printf("\r\n 用WK_UP和KEY1切换 \r\n");
	NRF_RX_Mode();

	while(1)
	{
		/*等待接收数据*/
		status = NRF_Rx_Dat(rxbuf);	//每次读回来DATA_WIDTH个字节

		/*判断接收状态*/
		if(status == RX_DR)
		{
			for(i=0;i<RX_PLOAD_WIDTH;i++)
			{	
				//printf("\r\n 从机端 接收到 主机端 发送的数据为：%d \r\n",);
				
				USART_SendData(USART1, rxbuf[i]);
				while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
			}
		}
	}
}
/*********************************************END OF FILE**********************/
