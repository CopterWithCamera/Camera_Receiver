/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "bsp_led.h"

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOB��GPIOF������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE); 

	/*ѡ��Ҫ���Ƶ�GPIOB����*/															   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			//PA8		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	/*��������ģʽΪͨ���������*/  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	/*������������Ϊ50MHz */ 
	GPIO_Init(GPIOA, &GPIO_InitStructure);				/*���ÿ⺯������ʼ��PA8*/
																   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//PD2
	GPIO_Init(GPIOD, &GPIO_InitStructure);		/*���ÿ⺯������ʼ��PD2*/	  

	GPIO_ResetBits(GPIOA, GPIO_Pin_8);	/* �ر�����led��	*/	
	GPIO_ResetBits(GPIOD, GPIO_Pin_2);	/* �ر�����led��	*/
}


/*********************************************END OF FILE**********************/
