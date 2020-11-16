#include "Girouette.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 
#include "gpio.h"

unsigned char var_a=0, var_b=0, var=0; //variables globales




//remet l'angle que ressort la girouette à 0
void IT_reset(void);

//configuration au niveau du gpio 
void Girouette_Conf_io(void){
	
	//Pin de la channel d'index (recalibrage)
	LL_GPIO_InitTypeDef pin5;
	pin5.Pin=LL_GPIO_PIN_5;
	gpio_conf_input(pin5,GPIOA);

	
	
	//en mode pull down pour pouvoir voir front montant et descandants
	LL_GPIO_InitTypeDef pin6;
	pin6.Pin=LL_GPIO_PIN_6;
	gpio_conf_input(pin6,GPIOA);

	
	LL_GPIO_InitTypeDef pin7;
	pin7.Pin=LL_GPIO_PIN_7;
	gpio_conf_input(pin7,GPIOA);

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	
	LL_GPIO_AF_EnableRemap_TIM3();
	
	LL_TIM_ENCODER_InitTypeDef tim3En ;
	tim3En.EncoderMode = LL_TIM_ENCODERMODE_X4_TI12;
	tim3En.IC1Polarity = LL_TIM_IC_POLARITY_RISING;
	tim3En.IC1ActiveInput = LL_TIM_ACTIVEINPUT_DIRECTTI;
	tim3En.IC1Prescaler = LL_TIM_ICPSC_DIV1;
	tim3En.IC1Filter = LL_TIM_IC_FILTER_FDIV1;
	tim3En.IC2Polarity =LL_TIM_IC_POLARITY_RISING;
	tim3En.IC2ActiveInput = LL_TIM_ACTIVEINPUT_DIRECTTI;
	tim3En.IC2Prescaler = LL_TIM_ICPSC_DIV1;
	tim3En.IC2Filter = LL_TIM_IC_FILTER_FDIV1;

	LL_TIM_ENCODER_Init(TIM3, &tim3En);
	
	
}



/* code gérant l'index */
//handler pour la ligne 5 
void EXTI9_5_IRQHandler(void){
	EXTI->PR|=EXTI_PR_PR5_Msk;
	LL_TIM_DisableCounter(TIM3);
	LL_TIM_SetCounter(TIM3, 0);
	LL_TIM_EnableCounter(TIM3);
}
void IT_conf(void){
	//priorité interruption 
	int prio=10;
	//on laisse faire les interruption à partir de pa5
	EXTI->IMR|=EXTI_IMR_MR5_Msk;
	
	//on enable la clock de l'afio
	RCC->APB2ENR|=RCC_APB2ENR_AFIOEN_Msk;
	//on selectionne la source pour l'interruption ici celui correspondant gpioa 
	AFIO->EXTICR[1]&=~AFIO_EXTICR2_EXTI5;
	AFIO->EXTICR[1]|=AFIO_EXTICR2_EXTI5_PA;
	
	//on règle la prio et enable l'interruption
	//23 -> EXTI5 à 9
	NVIC->IP[23]=prio;
	//activation interruption
	NVIC->ISER[0]|= (1<<23);
	
	//l'interruption se detecte lorsqu'on a un front montant
	EXTI->RTSR|=EXTI_RTSR_TR5_Msk;
	
}

 
void Girouette_Conf(void){
		
	Girouette_Conf_io();
	IT_conf();
}





int gir_get_inc(void)
{	
 uint32_t gir_count = LL_TIM_GetCounter(TIM3);
	if (gir_count > 10000){
		gir_count =  65536 - gir_count ;
	}
	return (gir_count*360)/1532;
}























