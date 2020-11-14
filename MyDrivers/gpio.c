#include "gpio.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_gpio.h"




void gpio_clock_init(void){
	
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
}


void gpio_conf_analog(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO){
		
	pin.Mode = LL_GPIO_MODE_ANALOG;
	pin.Speed = LL_GPIO_SPEED_FREQ_LOW;
	pin.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	pin.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIO,&pin);

}


 void gpio_conf_input(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO){
	 
	pin.Mode=LL_GPIO_MODE_INPUT;
	pin.Speed=LL_GPIO_SPEED_FREQ_LOW;
	pin.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
	pin.Pull=LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIO,&pin);
	 
	 
 }
 
 void gpio_conf_floating(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO){
	 
	pin.Mode = LL_GPIO_MODE_FLOATING;
	pin.Pull = LL_GPIO_PULL_DOWN;
	pin.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	pin.Speed = LL_GPIO_SPEED_FREQ_LOW;
	LL_GPIO_Init(GPIO,&pin);
	 
	 
	 
}
 

 void gpio_conf_output(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO){
	 
	pin.Mode = LL_GPIO_MODE_OUTPUT;
	pin.Pull = LL_GPIO_PULL_DOWN;
	pin.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	pin.Speed = LL_GPIO_SPEED_FREQ_LOW;
	LL_GPIO_Init(GPIO,&pin);
	 
	 
	 
}
 

 void gpio_conf_alternate(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO){
	 
	pin.Mode = LL_GPIO_MODE_ALTERNATE;
	pin.Pull = LL_GPIO_PULL_DOWN;
	pin.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	pin.Speed = LL_GPIO_SPEED_FREQ_LOW;
	LL_GPIO_Init(GPIO,&pin);
	 
	 
	 
}
 

////



 
 
 
 