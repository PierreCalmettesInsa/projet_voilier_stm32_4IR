#include "stm32f1xx_ll_tim.h"

#define RF_INPUT_ANGLE_RANGE 10.0

void rf_input_start(TIM_TypeDef *_RFInputTimer);


/* RF Input Module can only work with TIM4 */
void rf_input_init(void);

/* Returns an angle in [ - RF_INPUT_ANGLE_RANGE ; RF_INPUT_ANGLE_RANGE] */
int rf_input_get_angle(void);




