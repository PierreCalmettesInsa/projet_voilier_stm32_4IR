#include "RFEmetteur.h"
#include "UART.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_usart.h"
#include "Accelero.h"

void emetteur_conf(void){
	
	Usart_Conf(USART1);
	
		LL_GPIO_InitTypeDef pin11 ;
		pin11.Pin = LL_GPIO_PIN_11 ;
		pin11.Mode = LL_GPIO_MODE_ALTERNATE;
		pin11.Speed = LL_GPIO_SPEED_FREQ_LOW;
		pin11.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
		pin11.Pull = LL_GPIO_PULL_DOWN;
		LL_GPIO_Init(GPIOA,&pin11);
	
	
}



void send_all(int roulis){
	
	GPIOA->ODR |= GPIO_ODR_ODR11 ;
	
	
	
	//get tension batterie
	float batterie = get_batterie_volt();
	
	
	
	if (batterie < 4.0){
		char str[20];
		send(((int)batterie%10)+48,USART1);
		send(44,USART1);
		send(((int)(batterie*10)%10)+48,USART1);
		send(((int)(batterie*100)%10)+48,USART1);
		send(59,USART1);
	}
	
	
	if (roulis == 1){
		
		send(49,USART1);
		send(13,USART1);
	}
	
	
	
	
		GPIOA->ODR &= ~GPIO_ODR_ODR11 ;
	
	
}