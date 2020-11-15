//Pierre Calmettes
//Alexandre Gonzalvez
//Fabrice Fragonas




#include "stm32f103xb.h" 

static uint16_t ticks_scheduler ;


/**
	* @brief 	Lancement de la systick, interruptions toutes les 1 ms
  * @note   None
	* @Param  None
  * @retval None
  */
void init_systick(void);

/**
	* @brief 	handler lancé toutes les 1 ms par la systick
  * @note   None
	* @Param 	None
  * @retval None
  */
void SysTick_Handler(void);

/**
	* @brief 	Tâche qui vérifie la girouette et positionne les voiles
  * @note   None
	* @Param 	None
  * @retval None
  */
void verif_girouette(void);

/**
	* @brief 	Tâche qui vérifie le roulis et positionne les voiles
  * @note   None
	* @Param 	None
  * @retval None
  */
void verif_roulis(void);

/**
	* @brief 	Tâche qui vérifie la télécommande et contrôle le motor cc
  * @note   None
	* @Param 	None
  * @retval None
  */
void verif_teleco(void);

/**
	* @brief 	Tâche qui envoie avec l'UART des datas au pc
  * @note   None
	* @Param 	None
  * @retval None
  */
void send_uart(void);

/**
	* @brief 	Schedule les différentes tâches avec la systick
  * @note   None
	* @Param 	None
  * @retval None
  */
void schedule_sys_tasks(void);

/**
	* @brief  Utilisation d'un timer plutôt que systick (au choix)
  * @note   None
	* @Param 	None
  * @retval None
  */
void interrupt_start(void);

/**
	* @brief 	Lancé par le timer à l'interruption si choix du timer
  * @note   None
	* @Param 	None
  * @retval None
  */
void Verif_sail_50ms(void);

/**
	* @brief 	
  * @note   None
	* @Param 	None
  * @retval return le flag de l'uart : 1 -> dans le main l'uart est activé
  */
int get_uart(void);


/**
	* @brief 	Remet à 0 le flag de l'uart
  * @note   None
	* @Param 	None
  * @retval None
  */
void reset_uart(void);