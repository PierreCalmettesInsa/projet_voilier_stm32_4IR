#include "RFRecepteur.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_usart.h" 
#include "stm32f1xx_LL_tim.h"
#include "MyTimer.h"

#define RF_INPUT_ARR		1439
#define RF_INPUT_PSC		(72000000 / ((RF_INPUT_ARR + 1) * 50) - 1)

#ifndef RF_INPUT_ANGLE_RANGE
#define RF_INPUT_ANGLE_RANGE 10.0
#endif

#define RF_INPUT_MAX_DUTY_CYCLE			(((double)RF_INPUT_ARR / 10.0))
	
#define RF_INPUT_NEUTRAL_DUTY_CYCLE		(((double)RF_INPUT_ARR * 3.0 / 40.0))

static TIM_TypeDef *RFInputTimer;

static void rf_input_init(void);

void rf_input_start(TIM_TypeDef *_RFInputTimer, int channel)
{
	RFInputTimer 		= _RFInputTimer;	
	rf_input_init();
}


/* RF Input works with PB6 or PB7 */
static void rf_input_init(void) {
	
	/* Servo Engine PIN8 */
	LL_GPIO_InitTypeDef LLGPIO_struct;
	
	LLGPIO_struct.Pin = LL_GPIO_PIN_6;
	LLGPIO_struct.Mode = LL_GPIO_MODE_FLOATING;
	LLGPIO_struct.Pull = LL_GPIO_PULL_DOWN;
	LLGPIO_struct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LLGPIO_struct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	
	LL_GPIO_Init(GPIOB,&LLGPIO_struct);
	
	//config pwm input
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
	
	}


/* Returns an angle in -ange range ; angle range */

int rf_input_get_angle (void) {

	int duty;
	uint32_t period ;
	float frequency ;

	/*
	if (RFInputChannel == 1)
		val = RFInputTimer->CCR2;
	else if (RFInputChannel == 2)
		val = RFInputTimer->CCR1;
	*/
	
	//On a choisi le channel 1
	duty = RFInputTimer->CCR2;
	period = RFInputTimer->CCR1;
	frequency = TIM4 ->PSC * period / 72000000 ;
	float duty_cycle = duty / (72000000 * frequency) ;
	float period_ms = duty_cycle / frequency * 1000 ;
	//angle entre -1 et 1
	float angle = period_ms*2 -3;

	return angle ;
	//return (int)((duty - RF_INPUT_NEUTRAL_DUTY_CYCLE) * RF_INPUT_ANGLE_RANGE / (RF_INPUT_MAX_DUTY_CYCLE - RF_INPUT_NEUTRAL_DUTY_CYCLE));
}

	
	










	
	
	
	
	
	