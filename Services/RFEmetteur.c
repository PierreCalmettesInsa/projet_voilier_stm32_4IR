#include "RFEmetteur.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_usart.h" 

/* RF Input works with PB6 and PB7 */
static void rf_input_init(void) {
	
/*channel config required*/

	/* GPIOB6 or GPIOB7 depending on the channel */
	if	(RFInputChannel == 1) { LLGPIO_struct.Pin = LL8GPIO_PIN_6; }
	else if (RFInputChannel == 2) { LLGPIO_struct.Pin = LL_GPIO_PIN_7; }
	
	LLGPIO_struct.Mode = LL_GPIO_MODE_FLOATING;
	LLGPIO_struct.Pull = LL_GPIO_PULL_DOWN;

}