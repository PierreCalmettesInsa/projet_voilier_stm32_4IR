#include "Servo.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 
#include "MyTimer.h"


int pulse_servo_motor ;

void servo_pin_conf_io(void) {
	
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
	
	
	LL_GPIO_InitTypeDef pin8A ;
	pin8A.Pin = LL_GPIO_PIN_8 ;
	pin8A.Mode = LL_GPIO_MODE_OUTPUT;
	pin8A.Speed = LL_GPIO_SPEED_FREQ_LOW;
	pin8A.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	pin8A.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOA,&pin8A);
	
	
		
	LL_GPIO_InitTypeDef pin8B ;
	pin8B.Pin = LL_GPIO_PIN_8 ;
	pin8B.Mode = LL_GPIO_MODE_ALTERNATE;
	pin8B.Speed = LL_GPIO_SPEED_FREQ_LOW;
	pin8B.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	pin8B.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOB,&pin8B);
	
	
}

// Le pulse se situe entre 5 et 10%, 5% : servo au minimum, 10% : servo au maximum

void servo_init_pwm(void){
	//PWM sur ch3 de tim4 (arr 1439, psc 999) pulse = 10
	create_pwm(TIM4,3,1439,999,5);
	pulse_servo_motor = 5 ;
	
}


void change_motor(int pulse){
	
	pwm_set_duty_cycle(TIM4,pulse,3);
	pulse_servo_motor = pulse ;
	
}




void choquer_voile(void){
	pulse_servo_motor -= 1 ;
	pwm_set_duty_cycle(TIM4,pulse_servo_motor,3);
}



















