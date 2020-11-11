#include "Accelero.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_adc.h" 
#include "stm32f1xx_ll_dma.h" 
#include "stm32f1xx_ll_tim.h" 
#include "MyTimer.h"


#define ARRAYSIZE 3
#define ADC_CONVERTION 3.3/ 4096.0
#define SENSITIVITY 0.480
#define ZERO_G 1.65

volatile uint16_t ADC_values[ARRAYSIZE];




void adc_conf(void){
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1); // validation horloge ADC1
		
		LL_ADC_InitTypeDef adc1_struct;
		adc1_struct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
		adc1_struct.SequencersScanMode = LL_ADC_SEQ_SCAN_ENABLE;
	
		LL_ADC_Init(ADC1,&adc1_struct);

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
	
		LL_ADC_Enable(ADC1);
		
		LL_ADC_StartCalibration(ADC1);
		while(LL_ADC_IsCalibrationOnGoing(ADC1));

}

void adc_conf_no_dma(void){
		LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1); // validation horloge ADC1
		
		LL_ADC_InitTypeDef adc1_struct;
		adc1_struct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
		adc1_struct.SequencersScanMode = LL_ADC_SEQ_SCAN_DISABLE;
	
		LL_ADC_Init(ADC1,&adc1_struct);

		LL_ADC_REG_InitTypeDef adc1 ;
		adc1.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
		adc1.ContinuousMode = LL_ADC_REG_CONV_SINGLE ;
		adc1.DMATransfer = LL_ADC_REG_DMA_TRANSFER_NONE;
	
		LL_ADC_REG_Init(ADC1,&adc1);
	
		LL_ADC_REG_SetSequencerRanks(ADC1,LL_ADC_REG_RANK_1,LL_ADC_CHANNEL_10);
	
		LL_ADC_Enable(ADC1);
	
		LL_ADC_StartCalibration(ADC1);
		while(LL_ADC_IsCalibrationOnGoing(ADC1));
	

		
}


void dma_conf(void){
		LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1); // validation horloge ADC1
	
		LL_DMA_InitTypeDef dma1 ;
		LL_DMA_DeInit(DMA1, LL_DMA_CHANNEL_1);
	
		dma1.Direction = LL_DMA_DIRECTION_PERIPH_TO_MEMORY;
	
		dma1.Mode = LL_DMA_MODE_CIRCULAR;
	
		dma1.Priority = LL_DMA_PRIORITY_HIGH;
		dma1.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_HALFWORD;
		dma1.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_HALFWORD;
	
		dma1.MemoryOrM2MDstIncMode = LL_DMA_MEMORY_INCREMENT;
		dma1.PeriphOrM2MSrcIncMode = LL_DMA_PERIPH_NOINCREMENT;

		dma1.NbData = ARRAYSIZE ;
 
		dma1.PeriphOrM2MSrcAddress = (uint32_t)LL_ADC_DMA_GetRegAddr(ADC1,LL_ADC_DMA_REG_REGULAR_DATA);

		dma1.MemoryOrM2MDstAddress = (uint32_t)ADC_values ;
	

		LL_DMA_Init(DMA1,LL_DMA_CHANNEL_1, &dma1);
		
		LL_DMA_EnableChannel(DMA1,LL_DMA_CHANNEL_1);
		
		LL_ADC_REG_StartConversionSWStart(ADC1);
		
		
		
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
	
	LL_GPIO_InitTypeDef pin2 ;
	pin2.Pin = LL_GPIO_PIN_2 ;
	pin2.Mode = LL_GPIO_MODE_ANALOG;
	pin2.OutputType = LL_GPIO_OUTPUT_PUSHPULL ;
	pin2.Pull = LL_GPIO_PULL_DOWN;
	pin2.Speed = LL_GPIO_SPEED_FREQ_LOW;
	LL_GPIO_Init(GPIOC,&pin2);
	
}




void start_convert(void){
	
	accelero_pin_conf_io();
	
	adc_conf();
	dma_conf();
		
	//enable dma et ADC
		LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
		LL_ADC_REG_StartConversionSWStart(ADC1);
	
}



void start_convert_no_dma(void){
		accelero_pin_conf_io();
	
		adc_conf_no_dma();
}



float volt_to_g(uint16_t v){
	float value = v ;
	
	value = value * ADC_CONVERTION ;
	value = value - ZERO_G ;
	
	value = value / SENSITIVITY ;
	
	return value ;
	
	
}



float * Verif_roulis_50ms(void)
{
	static float result[2] ;

	float x = volt_to_g(ADC_values[0]);
	float y = volt_to_g(ADC_values[1]);
	
	result[0] = x ;
	result[1] = y;
	
	return result;
	
}


void Verif_roulis_50ms_no_dma(void){
	
		ADC1->CR2 |= ADC_CR2_ADON; // lancement de la conversion
	
    while(!(ADC1->SR & ADC_SR_EOC) ) {} // attente de la fin de conversion
			
    ADC1->SR &= ~ADC_SR_EOC; // validation de la conversion
			
    float x =  volt_to_g(ADC1->DR & ~((0x0F) << 12)); // retour de la conversion
			
		float y = 0.0 ;
}
























