//Pierre Calmettes
//Thomas Cotte

#include "stm32f103xb.h" 


/**
	* @brief  Configure USART. 
  * @note   A lancer avant toute autre fonction.
  * @retval None
  */
void Usart_Conf(USART_TypeDef * Usart);



/**
	* @brief  Envoie avec l'USART
  * @note   Lanc� en t�che de fond
	* @Param  char data : message envoy�, Usart : choix USART1,2 ou 3
  * @retval None
  */
void send(char data,USART_TypeDef * Usart);
