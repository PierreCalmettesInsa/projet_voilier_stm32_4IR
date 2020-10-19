#include "Servo.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 



void servo_pin_conf_io(void) {
	
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

	
	
	LL_GPIO_InitTypeDef pin8A ;
	pin8A.Pin = LL_GPIO_PIN_8 ;
	pin8A.Mode = LL_GPIO_MODE_OUTPUT;
	pin8A.Speed = LL_GPIO_SPEED_FREQ_LOW;
	pin8A.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	pin8A.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOA,&pin8A);
	
	
		
	LL_GPIO_InitTypeDef pin8B ;
	pin8B.Pin = LL_GPIO_PIN_8 ;
	pin8B.Mode = LL_GPIO_MODE_OUTPUT;
	pin8B.Speed = LL_GPIO_SPEED_FREQ_LOW;
	pin8B.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	pin8B.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOA,&pin8B);
	
	
}