#include "stm32f103xb.h" 


void gpio_table_conf(void);

void init_motor(void);

void changer_sens_motor(int sens);

int choose_motor_pulse(float motor_conf_pwm);
