/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 iSO STM32 开发板 
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "bsp_led.h"

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启GPIOB和GPIOF的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE); 

	/*选择要控制的GPIOB引脚*/															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			//PA8		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	/*设置引脚模式为通用推挽输出*/  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	/*设置引脚速率为50MHz */ 
	GPIO_Init(GPIOA, &GPIO_InitStructure);				/*调用库函数，初始化PA8*/
																   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//PD2
	GPIO_Init(GPIOD, &GPIO_InitStructure);		/*调用库函数，初始化PD2*/	  

	GPIO_ResetBits(GPIOA, GPIO_Pin_8);	/* 关闭所有led灯	*/	
	GPIO_ResetBits(GPIOD, GPIO_Pin_2);	/* 关闭所有led灯	*/
}


/*********************************************END OF FILE**********************/
