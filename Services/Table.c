#include "Table.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 
#include "MyTimer.h"
#include "gpio.h"


#define NEUTRAL_ZONE_PWM_MCC 0.1
#define NB_PAS_MCC 10

void gpio_table_conf(void){
	
	LL_GPIO_InitTypeDef pin1 ;
	pin1.Pin = LL_GPIO_PIN_1 ;
	gpio_conf_alternate(pin1,GPIOA);
	
	LL_GPIO_InitTypeDef pin2 ;
	pin2.Pin = LL_GPIO_PIN_2 ;
	gpio_conf_output(pin2,GPIOA);
	
}



//On veut au moins 10 valeurs différentes pour la pwm, on prend un pas de 30, pas trop élevé mais suffisament pour que PSC rentre dans 16 bits
void init_motor(void){
	
	gpio_table_conf();
	
	create_pwm(TIM2,2,29,47999,0);
	
	
}


void changer_sens_motor(int sens){
	
	if (sens == -1){
		GPIOA->ODR &= ~GPIO_ODR_ODR2 ;
	}
	else {
				GPIOA->ODR |= GPIO_ODR_ODR2 ;
	}
}


int choose_motor_pulse(float motor_conf_pwm){
	int pulse;
	float pas_length = (1 - NEUTRAL_ZONE_PWM_MCC)/NB_PAS_MCC;
	for(int pas = 0; pas<NB_PAS_MCC+1;pas++){ // NB_PAS_MCC pas différent linéairement réparti de 0 à 100
			if(motor_conf_pwm<=NEUTRAL_ZONE_PWM_MCC+pas_length*pas){
				pulse = pas * 10 * pas_length;
				break;
			}
	}
	
	
	return pulse;
}












