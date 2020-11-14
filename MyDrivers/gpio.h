#include "stm32f103xb.h" 
#include "stm32f1xx_ll_gpio.h"


void gpio_clock_init(void);

void gpio_conf_analog(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO);


void gpio_conf_input(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO);
 
 
void gpio_conf_floating(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO);
 
void gpio_conf_output(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO);
	
void gpio_conf_alternate(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO);
