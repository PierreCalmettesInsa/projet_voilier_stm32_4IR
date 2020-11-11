#include "InterruptMain.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_adc.h" 
#include "stm32f1xx_ll_dma.h" 
#include "stm32f1xx_ll_tim.h" 
#include "MyTimer.h"
#include "Accelero.h"




static TIM_TypeDef * Interrupt_Timer=TIM2; // init par défaut au cas où l'utilisateur ne lance pas interrupt_start avant toute autre fct.

// déclaration callback appelé toute les 10ms
void Verif_sail_50ms(void);



void interrupt_start(void){
		//ajout d'un timer
	// Réglage Timer pour un débordement à 10ms
	MyTimer_Conf(Interrupt_Timer,999, 719);
	
	// Réglage interruption du Timer avec callback : Chrono_Task_10ms()
	MyTimer_IT_Conf(Interrupt_Timer, Verif_roulis_50ms,3);
	
			// Validation IT
	MyTimer_IT_Enable(Interrupt_Timer);
	
	MyTimer_Start(Interrupt_Timer);

	
}


void Verif_sail_50ms(void){
	
	
	//On vérifie d'abord la girouette
	
	
	//Puis on vérifie le roulis
	Verif_roulis_50ms();
	
	
	
}













