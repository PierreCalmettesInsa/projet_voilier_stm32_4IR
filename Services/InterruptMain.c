#include "InterruptMain.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_adc.h" 
#include "stm32f1xx_ll_dma.h" 
#include "stm32f1xx_ll_tim.h" 
#include "MyTimer.h"
#include "Accelero.h"
#include "Girouette.h"
#include "Servo.h"




static TIM_TypeDef * Interrupt_Timer=TIM2; // init par d�faut au cas o� l'utilisateur ne lance pas interrupt_start avant toute autre fct.

// d�claration callback appel� toute les 10ms
void Verif_sail_50ms(void);



void interrupt_start(void){
		//ajout d'un timer
	// R�glage Timer pour un d�bordement � 10ms
	MyTimer_Conf(Interrupt_Timer,999, 719);
	
	// R�glage interruption du Timer avec callback : Chrono_Task_10ms()
	MyTimer_IT_Conf(Interrupt_Timer, Verif_sail_50ms,3);
	
			// Validation IT
	MyTimer_IT_Enable(Interrupt_Timer);
	
	MyTimer_Start(Interrupt_Timer);

	
}


void Verif_sail_50ms(void){
	
	
	//On v�rifie d'abord la girouette
	int angle = gir_get_inc();
	
	//On change le servo-moteur
	if (angle != 0){
	change_motor(angle);
	}
	
	
	//Puis on v�rifie le roulis
	float * result = Verif_roulis_50ms();
	float x = result[0];
	float y = result[1] ;
	
	if (x > 1.0 && y > 1.00){
		choquer_voile();
	}
	
	
	
}













