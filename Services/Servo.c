#include "Servo.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 
#include "MyTimer.h"
#include "gpio.h"


float pulse_servo_motor ;

void servo_pin_conf_io(void) {
	
	LL_GPIO_InitTypeDef pin8A ;
	pin8A.Pin = LL_GPIO_PIN_8 ;
	gpio_conf_alternate(pin8A,GPIOA);

	LL_GPIO_InitTypeDef pin8B ;
	pin8B.Pin = LL_GPIO_PIN_8 ;
	gpio_conf_alternate(pin8B,GPIOB);

}

// Le pulse se situe entre 5 et 10%, 5% : servo au minimum, 10% : servo au maximum

//resolution de 1/72000 soit 72 pas pour 1 ms (étant donné que notre pulse se situe entre 1 et 2ms)
//Le pas de 5 ° est donc respecté
void servo_init_pwm(void){
	//PWM sur ch1 de tim1 (arr 1439, psc 999) pulse = 5
	create_pwm(TIM1,1,1439,999,9.7);
	pulse_servo_motor = 9.7 ;
	
}


void change_motor(float pulse){
	
	pwm_set_duty_cycle(TIM1,pulse,1);
	pulse_servo_motor = pulse ;
	
}




void choquer_voile(void){
	//Il y a du roulis lorsqu'on est au près donc pour savoir de quel côté se trouve la voile il suffit de regarder si le servo est d'un côté ou de l'autre

	pulse_servo_motor -= 1.0 ;
	pwm_set_duty_cycle(TIM1,pulse_servo_motor,1);
	if (pulse_servo_motor <= 5.4){
		pulse_servo_motor = 5.4 ;
	}
}



















