//Pierre Calmettes


#include "stm32f103xb.h" 

/**
	* @brief 	Configuration des pins du servo-moteur
  * @note   None
	* @Param 	None
  * @retval None
  */
void servo_pin_conf_io(void);

/**
	* @brief 	Création de la pwm pour le servo-moteur
  * @note   None
	* @Param 	None
  * @retval None
  */
void servo_init_pwm(void);

/**
	* @brief 	Modification du duty cycle de la pwm, changement de position des voiles
  * @note   None
	* @Param 	int pulse : pourcentage  : 10 -> 10% de la pwm (ex : 20 ms * 10/100 -> 2 ms)
  * @retval None
  */
void change_motor(int pulse);


/**
* @brief 	Si roulis trop important, choque les voiles (diminue le bordage)  
  * @note   (une autre solution serait de lofer : rapprocher le voilier de l'axe du vent (près plus serré) ce qui diminue le roulis)
	* @Param 	None
  * @retval None
  */
void choquer_voile(void);

