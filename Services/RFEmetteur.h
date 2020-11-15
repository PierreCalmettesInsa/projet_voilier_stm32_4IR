//Pierre Calmettes
//Thomas Cotte


#include "stm32f103xb.h" 

/**
	* @brief 	configure l'UART et les pins de l'emetteur
  * @note   None
	* @Param 	None
  * @retval None
  */
void emetteur_conf(void);


/**
	* @brief 	appelle plusieurs fois send_uart pour envoyer au pc différentes datas
  * @note   None
	* @Param 	int roulis : si =1 on envoie 1 pour dire que le roulis a dépassé 40°
  * @retval None
  */
void send_all(int roulis);






