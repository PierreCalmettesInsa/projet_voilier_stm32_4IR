#include "stm32f103xb.h" 


void gpio_table_conf(void);

void create_pwm_motor(TIM_TypeDef *TIMER,int channel,int arr, int psc,int pulse);

void init_motor(void);

void changer_sens_motor(int sens);

int choose_motor_pulse(float motor_conf_pwm);
