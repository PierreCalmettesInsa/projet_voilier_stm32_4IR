#include "RFEmetteur.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_usart.h" 
#include "stm32f1xx_LL_tim.h"
#include "MyTimer.h"

#ifndef _RF_INPUT_ANGLE_RANGE
#define _RF_INPUT_ANGLE_RANGE	10.0
#endif

static TIM_TypeDef *RFInputTimer;


/* RF Input works with PB6 or PB7 */
static void rf_input_init(void) {
	

	/* Input use GPIOB6 */
	LLGPIO_struct.Pin = LL_GPIO_PIN_6;
	LLGPIO_struct.Mode = LL_GPIO_MODE_FLOATING;
	LLGPIO_struct.Pull = LL_GPIO_PULL_DOWN;

}