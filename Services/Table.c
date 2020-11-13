#include "Table.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 
#include "MyTimer.h"



void gpio_table_conf(void){
	
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	
	
	LL_GPIO_InitTypeDef pin1 ;
	pin1.Pin = LL_GPIO_PIN_1 ;
	pin1.Mode = LL_GPIO_MODE_ALTERNATE;
	pin1.Speed = LL_GPIO_SPEED_FREQ_LOW;
	pin1.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	pin1.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOA,&pin1);
	
	
	LL_GPIO_InitTypeDef pin2 ;
	pin2.Pin = LL_GPIO_PIN_2 ;
	pin2.Mode = LL_GPIO_MODE_OUTPUT;
	pin2.Speed = LL_GPIO_SPEED_FREQ_LOW;
	pin2.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	pin2.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOA,&pin2);
	
	
	
	
	
}






void create_pwm_motor(TIM_TypeDef *TIMER,int channel,int arr, int psc,int pulse){
	
	create_pwm(TIMER,channel,arr,psc,pulse);
	
}

void init_motor(void){
	
	gpio_table_conf();
	
	create_pwm_motor(TIM2,2,199,17,0);
	
	
}


void changer_sens_motor(int sens){
	
	if (sens == -1){
		GPIOA->ODR &= ~GPIO_ODR_ODR2 ;
	}
	else {
				GPIOA->ODR |= GPIO_ODR_ODR2 ;
	}
}















