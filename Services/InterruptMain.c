#include "InterruptMain.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_adc.h" 
#include "stm32f1xx_ll_dma.h" 
#include "stm32f1xx_ll_tim.h" 
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_cortex.h"
#include "MyTimer.h"
#include "Accelero.h"
#include "Girouette.h"
#include "Servo.h"
#include "RFRecepteur.h"
#include "Table.h"
#include "RFEmetteur.h"


//static TIM_TypeDef * Interrupt_Timer=TIM1; // init par défaut au cas où l'utilisateur ne lance pas interrupt_start avant toute autre fct.

// déclaration callback appelé toute les 10ms
//void Verif_sail_50ms(void);

int roulis ;
int uart_on ;

void init_systick(void){
	
	ticks_scheduler = 0 ;
	uart_on = 0 ;
	LL_Init1msTick(72000000);
	LL_SYSTICK_EnableIT();
	
}

void SysTick_Handler(void)
{
	schedule_sys_tasks();
	ticks_scheduler++ ;
  if(ticks_scheduler ==100)
      ticks_scheduler=0;    
	
}


void verif_girouette(void){
	//On vérifie d'abord la girouette
	int angle = gir_get_inc();
	int angle_voile = 0 ;
	
	//On change le servo-moteur
	if (angle > 180){
		angle -= 180 ;
	}
	
	if ((angle >= 45) && (angle <= 180))
	{
		angle_voile = ((float)angle-45.0)*(90.0/(180.0-45.0));
	}
	

	float pulse = ((float)angle_voile*((9.7-5.4)/90.0))+5.4;
	
	
	change_motor(pulse);

}


void verif_roulis(void){
	roulis = 0 ;
		//Puis on vérifie le roulis
	float * result = Verif_roulis_50ms();
	float x = result[0];
	float y = result[1] ;
	
	if ((x < -0.67 && y < 1.0) || (x<-0.10 && y<0.049)){
		choquer_voile();
		roulis = 1;
	}
}




void verif_teleco(void){
		//On regarde la pwm de la télécommande
	float motor_conf_pwm =  rf_input_get_angle(); // On récupère l'angle
	
	if (motor_conf_pwm <0){ // Détection du sens
		changer_sens_motor(-1);
		motor_conf_pwm = - motor_conf_pwm; // On prend la valeur absolue si négatif		
	} else if (motor_conf_pwm > 0){
				changer_sens_motor(1);
	}
	
	float pulse = choose_motor_pulse(motor_conf_pwm); // 

	pwm_set_duty_cycle(TIM2,pulse,2);
}



void send_uart(void){
	send_all(roulis);
}



void schedule_sys_tasks(void){
	
	if (ticks_scheduler%30 == 0){
		verif_girouette();
	}

	if (ticks_scheduler%40 == 0){
		verif_roulis();

	}
	
	if (ticks_scheduler%50 == 0){
		verif_teleco();
	}
	
	if (ticks_scheduler%70 == 0){
		uart_on = 1 ;
	}
		
}


/*

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
	verif_girouette();
	int angle = gir_get_inc();
	
	//On change le servo-moteur
	if (angle != 0){
	change_motor(angle);
	}
	
	verif_roulis();

	verif_teleco();

	send_uart();	
	
}

*/

int get_uart(void){
	
	return uart_on ;
}


void reset_uart(void){
	uart_on = 0 ;
}






























