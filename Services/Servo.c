#include "Servo.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 
#include "MyTimer.h"
#include "gpio.h"


int pulse_servo_motor ;

void servo_pin_conf_io(void) {
	
	LL_GPIO_InitTypeDef pin8A ;
	pin8A.Pin = LL_GPIO_PIN_8 ;
	gpio_conf_output(pin8A,GPIOA);

	LL_GPIO_InitTypeDef pin8B ;
	pin8B.Pin = LL_GPIO_PIN_8 ;
	gpio_conf_alternate(pin8B,GPIOB);

}

// Le pulse se situe entre 5 et 10%, 5% : servo au minimum, 10% : servo au maximum

//resolution de 1/72000 soit 72 pas pour 1 ms (étant donné que notre pulse se situe entre 1 et 2ms)
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



















