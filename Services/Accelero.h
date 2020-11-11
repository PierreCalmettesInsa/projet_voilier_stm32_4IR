
#include "stm32f103xb.h" 


void adc_conf(void);

void adc_conf_no_dma(void);

void dma_conf(void);

void accelero_pin_conf_io(void);

void start_convert(void);

void start_convert_no_dma(void);

float volt_to_g(uint16_t v);

float * Verif_roulis_50ms(void);

void Verif_roulis_50ms_no_dma(void);

