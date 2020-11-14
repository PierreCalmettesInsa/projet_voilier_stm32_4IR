#include "RFEmetteur.h"
#include "UART.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_usart.h"
#include "Accelero.h"
#include "gpio.h"

void emetteur_conf(void){
	
	Usart_Conf(USART1);
	
	LL_GPIO_InitTypeDef pin11 ;
	pin11.Pin = LL_GPIO_PIN_11 ;
	gpio_conf_alternate(pin11,GPIOA);

	
	
}



void send_all(int roulis){
	
	GPIOA->ODR |= GPIO_ODR_ODR11 ;
	
	
	
	//get tension batterie
	float batterie = get_batterie_volt();
	
	
	//Batterie entre 0 et 3.3V (pont diviseur de tension), on envoie si batterie inférieure à 50%
	if (batterie < 1.6){
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







