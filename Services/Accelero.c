#include "Accelero.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_adc.h" 
#include "stm32f1xx_ll_dma.h" 






void adc_conf(void){
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1); // validation horloge ADC1
	
		LL_ADC_REG_InitTypeDef adc1 ;
		adc1.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
		adc1.SequencerLength = LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS;
		adc1.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
		adc1.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS ;
		adc1.DMATransfer = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;
		LL_ADC_REG_Init(ADC1,&adc1);
	
		LL_ADC_REG_SetSequencerRanks(ADC1,LL_ADC_REG_RANK_1,LL_ADC_CHANNEL_10);
		LL_ADC_REG_SetSequencerRanks(ADC1,LL_ADC_REG_RANK_2,LL_ADC_CHANNEL_11);
		LL_ADC_REG_SetSequencerRanks(ADC1,LL_ADC_REG_RANK_3,LL_ADC_CHANNEL_12);
	
		LL_ADC_Disable(ADC1);
		LL_ADC_StartCalibration(ADC1);
		while(LL_ADC_IsCalibrationOnGoing(ADC1));
		LL_ADC_Enable(ADC1);
	
	
	   /* RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6; // passage de l'horloge ADC1 à 12MHz
    ADC1->CR2|= ADC_CR2_ADON; // démarrage ADC1
    ADC1->SQR1&= ADC_SQR1_L; // reset nb conversion
		ADC1->SQR1|= 1; // fixe à 2
    ADC1->SQR3|= 10; // indique la voie à convertir
		ADC1->SQR3|= 11; // indique la voie à convertir
    ADC1->CR2 |= ADC_CR2_CAL; // debut de la calibration
    while ((ADC1->CR2 & ADC_CR2_CAL)); // attente de la fin de la calibration
	*/

}


void dma_conf(void){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1); // validation horloge ADC1
	
		LL_DMA_InitTypeDef dma1 ;
	dma1.

	
	
}







void accelero_pin_conf_io(void) {
	
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);

	
	
	LL_GPIO_InitTypeDef pin0 ;
	pin0.Pin = LL_GPIO_PIN_0 ;
	pin0.Mode = LL_GPIO_MODE_ANALOG;
	pin0.Speed = LL_GPIO_SPEED_FREQ_LOW;
	pin0.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	pin0.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOC,&pin0);
	
	LL_GPIO_InitTypeDef pin1 ;
	pin1.Pin = LL_GPIO_PIN_1 ;
	pin1.Mode = LL_GPIO_MODE_ANALOG;
	pin1.OutputType = LL_GPIO_OUTPUT_PUSHPULL ;
	pin1.Pull = LL_GPIO_PULL_DOWN;
	pin1.Speed = LL_GPIO_SPEED_FREQ_LOW;
	LL_GPIO_Init(GPIOC,&pin1);
	
	adc_conf();
	
	
}


int convert_accelero(){
	
    ADC1->CR2 |= ADC_CR2_ADON; // lancement de la conversion
	
    while(!(ADC1->SR & ADC_SR_EOC) ) {} // attente de la fin de conversion
			
    ADC1->SR &= ~ADC_SR_EOC; // validation de la conversion
			
    return ADC1->DR & ~((0x0F) << 12); // retour de la conversion
}







