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
	* @brief 	handler lanc� toutes les 1 ms par la systick
  * @note   None
	* @Param 	None
  * @retval None
  */
void SysTick_Handler(void);

/**
	* @brief 	T�che qui v�rifie la girouette et positionne les voiles
  * @note   None
	* @Param 	None
  * @retval None
  */
void verif_girouette(void);

/**
	* @brief 	T�che qui v�rifie le roulis et positionne les voiles
  * @note   None
	* @Param 	None
  * @retval None
  */
void verif_roulis(void);

/**
	* @brief 	T�che qui v�rifie la t�l�commande et contr�le le motor cc
  * @note   None
	* @Param 	None
  * @retval None
  */
void verif_teleco(void);

/**
	* @brief 	T�che qui envoie avec l'UART des datas au pc
  * @note   None
	* @Param 	None
  * @retval None
  */
void send_uart(void);

/**
	* @brief 	Schedule les diff�rentes t�ches avec la systick
  * @note   None
	* @Param 	None
  * @retval None
  */
void schedule_sys_tasks(void);

/**
	* @brief  Utilisation d'un timer plut�t que systick (au choix)
  * @note   None
	* @Param 	None
  * @retval None
  */
void interrupt_start(void);

/**
	* @brief 	Lanc� par le timer � l'interruption si choix du timer
  * @note   None
	* @Param 	None
  * @retval None
  */
void Verif_sail_50ms(void);

/**
	* @brief 	
  * @note   None
	* @Param 	None
  * @retval return le flag de l'uart : 1 -> dans le main l'uart est activ�
  */
int get_uart(void);


/**
	* @brief 	Remet � 0 le flag de l'uart
  * @note   None
	* @Param 	None
  * @retval None
  */
void reset_uart(void);