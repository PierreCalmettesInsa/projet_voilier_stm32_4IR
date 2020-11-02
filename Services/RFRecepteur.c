#include "RFRecepteur.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_usart.h" 
#include "stm32f1xx_LL_tim.h"
#include "MyTimer.h"

#define RF_INPUT_ARR		
#define RF_INPUT_PSC		/* prescaler décalage arr+1 */

#ifndef RF_INPUT_ANGLE_RANGE
#define RF_INPUT_ANGLE_RANGE 10.0
#endif

#define RF_INPUT_MAX_DUTY_CYCLE
#define RF_INPU_NEUTRAL_DUTY_CYCLE

static TIM_TypeDef *RFInputTimer;

static void rf_input_init(void);

void rf_input_start(TIM_TypeDef *_RFInputTimer)
{
	RFInputTimer 		= _RFInputTimer;
	
	rf_input_init();
}


/* RF Input works with PB6 or PB7 */
static void rf_input_init(void) {
	
	LL_GPIO_InitTypeDef LLGPIO_struct;
	
	/* Timer configuration in PWM input mode */
	Timer_PWM_input_conf(RFInputTimer,
											RF_INPUT_ARR,
											RF_INPUT_PSC);
	

	/* Input use GPIOB6 */
	LLGPIO_struct.Pin = LL_GPIO_PIN_6;
	LLGPIO_struct.Mode = LL_GPIO_MODE_FLOATING;
	LLGPIO_struct.Pull = LL_GPIO_PULL_DOWN;

}

/* Returns an angle in -ange range ; angle range */
int rf_input_get_angle(void) {

	int val = RFInputTimer->CCR2;

	return (int)((val - RF_INPUT_NEUTRAL_DUTY_CYCLE) * RF_INPUT_ANGLE_RANGE / (RF_INPUT_MAX_DUTY_CYCLE - RF_INPUT_NEUTRAL_DUTY_CYCLE));
}