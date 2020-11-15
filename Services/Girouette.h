//Thomas Cotte
//Pierre Calmettes


#include "stm32f103xb.h" 


/**
	* @brief 	Configuration des pins de la girouette et TIM3 en mode encoder
  * @note   None
	* @Param 	None
  * @retval None
  */
void Girouette_Conf_io(void);


/**
	* @brief 	handler lancé sur détection de l'index
  * @note   None
	* @Param 	None
  * @retval None
  */
void EXTI9_5_IRQHandler(void);

/**
	* @brief 	Configuration de l'interruption avec l'index
  * @note   None
	* @Param 	None
  * @retval None
  */
void IT_conf(void);

/**
	* @brief 	Lance Girouette_Conf_io puis IT_conf
  * @note   None
	* @Param 	None
  * @retval None
  */
void Girouette_Conf(void);


/**
	* @brief 	get le counter du timer pour savoir l'angle par rapport au vent
  * @note   None
	* @Param 	None
  * @retval None
  */
int gir_get_inc(void);



