#include "RFRecepteur.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_usart.h" 
#include "stm32f1xx_LL_tim.h"
#include "MyTimer.h"
#include "gpio.h"

#define RF_INPUT_ARR		1439
#define RF_INPUT_PSC		(72000000 / ((RF_INPUT_ARR + 1) * 50) - 1)

#ifndef RF_INPUT_ANGLE_RANGE
#define RF_INPUT_ANGLE_RANGE 10.0
#endif

#define RF_INPUT_MAX_DUTY_CYCLE			(((double)RF_INPUT_ARR / 10.0))
	
#define RF_INPUT_NEUTRAL_DUTY_CYCLE		(((double)RF_INPUT_ARR * 3.0 / 40.0))

static TIM_TypeDef *RFInputTimer;


void rf_input_start(TIM_TypeDef *_RFInputTimer)
{
	RFInputTimer 		= _RFInputTimer;	
	rf_input_init();
}


/* RF Input works with PB6 or PB7 */
void rf_input_init(void) {
	
	/* Servo Engine PIN8 */
	LL_GPIO_InitTypeDef LLGPIO_struct;
	
	LLGPIO_struct.Pin = LL_GPIO_PIN_6;
	gpio_conf_input(LLGPIO_struct,GPIOB);

	
	//config pwm input
	//pwm de 20 ms avec une résolution de 1/72000, soit 72 pas pour 1 ms
	//Donc 36 pas max pour la vitesse ce qui est largement suffisant
	MyTimer_Conf(TIM4,1439,999);
	
	TIM4->CCMR1 |= TIM_CCMR1_CC1S_0; // put CC1S(0) to 1
	TIM4->CCMR1 &= ~(TIM_CCMR1_CC1S_1); // put CC1S(1) to 0
	
	TIM4->CCER &= ~(TIM_CCER_CC1P);
	
	TIM4->CCMR1 &= ~(TIM_CCMR1_CC2S_0); // put CC2S(0) to 1
	TIM4->CCMR1 |= TIM_CCMR1_CC2S_1; // put CC1S(1) to 0
	
	TIM4->CCER |= TIM_CCER_CC2P;
	
	TIM4->SMCR |= TIM_SMCR_TS_0 | TIM_SMCR_TS_2;// put TS(0 & 2) to 1
	TIM4->SMCR &= ~(TIM_SMCR_TS_1);// put TS(1) to 0
	
	TIM4->SMCR &= ~(TIM_SMCR_SMS_0) & ~(TIM_SMCR_SMS_1);// put SMS(0 & 1) to 0
	TIM4->SMCR |= TIM_SMCR_SMS_2;// put SMS(2) to 1
	
	// Enable capture
	TIM4->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;
	
	MyTimer_Start(TIM4);

	
	}


/* Returns an angle in -ange range ; angle range */

float rf_input_get_angle (void) {

	int duty;
	uint32_t period ;
	float frequency ;


	
	//On a choisi le channel 1
	duty = RFInputTimer->CCR2 + 2;
	period = RFInputTimer->CCR1 + 1;
	//frequency = TIM4 ->PSC * (float)period / 72000000 ;
	//float duty_cycle = duty / (72000000 * frequency) ;
	//float period_ms = duty_cycle / frequency * 1000 ;
	int total_period_ms = (1.0/72000000.0)*(TIM4->PSC + 1) * (TIM4->ARR + 1)*1000 + 1;
	float period_ms = (float)duty * total_period_ms / (float)(period) ;
	//angle entre -1 et 1
	float angle = period_ms*2.0 -3.0;
	
	//Au cas ou la pwm input ne fonctionne pas
	if (angle == -3){
		angle = 0 ;
	}
	

	return angle ;
	//return (int)((duty - RF_INPUT_NEUTRAL_DUTY_CYCLE) * RF_INPUT_ANGLE_RANGE / (RF_INPUT_MAX_DUTY_CYCLE - RF_INPUT_NEUTRAL_DUTY_CYCLE));
}




//end_of_file
