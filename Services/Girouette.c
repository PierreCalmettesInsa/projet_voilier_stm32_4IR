#include "Girouette.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h" 


// variable priv�e de type int qui m�morise l'angle mesur�e
static int angle;	// rem : static rend la visibilit� de la variable Chrono_Time limit�e � ce fichier 

// variable priv�e qui m�morise pour le module le timer utilis� par d�faut sur les pin 6 et 7
static TIM_TypeDef * Girouette_Timer=TIM1; 
//remet l'angle que ressort la girouette � 0
void IT_reset(void);

//configuration au niveau du gpio 
void Girouette_Conf_io(void){
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	
	//Pin de la channel d'index (recalibrage)
	LL_GPIO_InitTypeDef pin5;
	pin5.Pin=LL_GPIO_PIN_5;
	pin5.Mode=LL_GPIO_MODE_INPUT;
	pin5.Speed=LL_GPIO_SPEED_FREQ_LOW;
	pin5.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
	pin5.Pull=LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOA,&pin5);
	
	
	//en mode pull down pour pouvoir voir front montant et descandants
	LL_GPIO_InitTypeDef pin6;
	pin6.Pin=LL_GPIO_PIN_6;
	pin6.Mode=LL_GPIO_MODE_INPUT;
	pin6.Speed=LL_GPIO_SPEED_FREQ_LOW;
	pin6.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
	pin6.Pull=LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOA,&pin6);
	
	LL_GPIO_InitTypeDef pin7;
	pin7.Pin=LL_GPIO_PIN_7;
	pin7.Mode=LL_GPIO_MODE_INPUT;
	pin7.Speed=LL_GPIO_SPEED_FREQ_LOW;
	pin7.OutputType=LL_GPIO_OUTPUT_PUSHPULL;
	pin7.Pull=LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOA,&pin7);
}
//fonction retourne true si retourne signal sinon false
// LL_GPIO_IsInputPinSet(GPIOA,LL_GPIO_PIN_6);

//r�glage angle 
void Girouette_Conf(void){
		
	Girouette_Conf_io();
}

//handler pour la ligne 5 
void EXTI5_IRQHandler(void){
	angle=0;
}

void IT_conf(void){
	//priorit� interruption 
	int prio=10;
	//on laisse faire les interruption � partir de pa5
	EXTI->IMR|=EXTI_IMR_MR5_Msk;
	
	//on selectionne la source pour l'interruption ici gpioa 
	AFIO->EXTICR[1]|=AFIO_EXTICR2_EXTI5_PA;
	//on enable la clock de l'afio
	RCC->APB2ENR|=RCC_APB2ENR_AFIOEN_Msk;
	//on r�gle la prio 
	//23 -> EXTI5 � 9
	NVIC->IP[23]=prio;
	//activation interruption
	NVIC->ISER[0]|= (1<<23);
	
}