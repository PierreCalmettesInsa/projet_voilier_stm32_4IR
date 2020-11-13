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
#include "RFRecepteur.h"
#include "Table.h"



static TIM_TypeDef * Interrupt_Timer=TIM1; // init par défaut au cas où l'utilisateur ne lance pas interrupt_start avant toute autre fct.

// déclaration callback appelé toute les 10ms
void Verif_sail_50ms(void);



void interrupt_start(void){
		//ajout d'un timer
	// Réglage Timer pour un débordement à 10ms
	MyTimer_Conf(Interrupt_Timer,999, 719);
	
	// Réglage interruption du Timer avec callback : Chrono_Task_10ms()
	MyTimer_IT_Conf(Interrupt_Timer, Verif_sail_50ms,3);
	
			// Validation IT
	MyTimer_IT_Enable(Interrupt_Timer);
	
	MyTimer_Start(Interrupt_Timer);

	
}


void Verif_sail_50ms(void){
	
	
	//On vérifie d'abord la girouette
	int angle = gir_get_inc();
	
	//On change le servo-moteur
	if (angle != 0){
	change_motor(angle);
	}
	
	
	//Puis on vérifie le roulis
	float * result = Verif_roulis_50ms();
	float x = result[0];
	float y = result[1] ;
	
	if (x > 1.0 && y > 1.00){
		choquer_voile();
	}
	
	
	
	//On regarde la pwm de la télécommande
	float motor_conf_pwm =  rf_input_get_angle(); // On récupère l'angle
	
	if (motor_conf_pwm <0){ // Détection du sens
		changer_sens_motor(-1);
		motor_conf_pwm = - motor_conf_pwm; // On prend la valeur absolue si négatif		
	} else if (motor_conf_pwm > 0){
				changer_sens_motor(1);
	}
	
	int pulse = choose_motor_pulse(motor_conf_pwm); // 

	create_pwm_motor(TIM2,2,199,17,pulse);
	
	
}













