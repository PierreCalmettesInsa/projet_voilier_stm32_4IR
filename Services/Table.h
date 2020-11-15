//Alexandre Gonzalvez
//Fabrice Fragonas
//Pierre Calmettes




#include "stm32f103xb.h" 

/**
	* @brief 	Configuration des pins pour le moteur cc
  * @note   None
	* @Param 	None
  * @retval None
  */
void gpio_table_conf(void);

/**
	* @brief 	création de la pwm pour le moteur cc
  * @note   None
	* @Param 	None
  * @retval None
  */
void init_motor(void);


/**
	* @brief 	Choix du sens du rotation
  * @note   None
	* @Param 	int sens : -1 ou 1
  * @retval None
  */
void changer_sens_motor(int sens);

/**
	* @brief 	Change pulse pwm, variation vitesse de rotation
  * @note   None
	* @Param 	None
  * @retval None
  */
float choose_motor_pulse(float motor_conf_pwm);
