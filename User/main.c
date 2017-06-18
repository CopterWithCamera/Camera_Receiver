/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   2.4g����ģ��/nrf24l01+/slave ����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_spi_nrf.h"
#include "bsp_SysTick.h"
#include "bsp_exti.h"
#include "bsp_led.h"  

u8 status;		 //�����жϽ���/����״̬
u8 txbuf[32];	 //���ͻ��壨ֱ�������ֵ��
u8 rxbuf[32];	 //���ջ��壨ֱ�������ֵ��

 /**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	u8 i;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	//�����ж����ȼ�����
	
	LED_GPIO_Config();	//LED��ʼ��
	
	EXTI_PA0_Config();	//PA0�ⲿ�жϳ�ʼ��
	EXTI_PC13_Config();	//PC13�ⲿ�жϳ�ʼ��
	EXTI_PC1_Config();	//PC1�ⲿ�жϳ�ʼ��
	
	/* ����1��ʼ�� */
	USART1_Config(); 

	/*SPI�ӿڳ�ʼ��*/   
	SPI_NRF_Init(); 

	printf("\r\n  \r\n");
	printf("\r\n ����һ�� NRF24L01 ���ߴ���ʵ�� \r\n");
	printf("\r\n �������ߴ��� �ӻ��� �ķ�����Ϣ\r\n");
	printf("\r\n   ���ڼ��NRF��MCU�Ƿ��������ӡ�����\r\n");

	/*���NRFģ����MCU������*/
	status = NRF_Check();   		
	if(status == SUCCESS)
	{
		printf("\r\n      NRF��MCU���ӳɹ�\r\n");
	}
	else
	{
		printf("\r\n   ����ʧ�ܡ�����\r\n");
		while(1);
	}
	
	//�������ģʽ
	printf("\r\n �ӻ��� �������ģʽ\r\n");
	printf("\r\n NRFĬ�����ݰ�����32�ֽ� \r\n");
	printf("\r\n �����ƣ�32�ֽ� \r\n");
	printf("\r\n һ���ƣ�4�ֽ� \r\n");
	printf("\r\n ��WK_UP��KEY1�л� \r\n");
	NRF_RX_Mode();

	while(1)
	{
		/*�ȴ���������*/
		status = NRF_Rx_Dat(rxbuf);	//ÿ�ζ�����DATA_WIDTH���ֽ�

		/*�жϽ���״̬*/
		if(status == RX_DR)
		{
			for(i=0;i<RX_PLOAD_WIDTH;i++)
			{	
				//printf("\r\n �ӻ��� ���յ� ������ ���͵�����Ϊ��%d \r\n",);
				
				USART_SendData(USART1, rxbuf[i]);
				while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	
			}
		}
	}
}
/*********************************************END OF FILE**********************/
