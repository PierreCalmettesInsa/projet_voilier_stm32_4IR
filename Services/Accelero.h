//Pierre Calmettes


#include "stm32f103xb.h" 

/**
	* @brief  Configure l'ADC pour convertir les channels 10,11,12, utilisation de la dma
  * @note   None
	* @Param  None
  * @retval None
  */
void adc_conf(void);



/**
	* @brief  Configure l'ADC pour convertir un channel, sans la dma
  * @note   None
	* @Param  None
  * @retval None
  */
void adc_conf_no_dma(void);


/**
	* @brief  Configure la dma pour recevoir les conversions de l'adc
  * @note   None
	* @Param  None
  * @retval None
  */
void dma_conf(void);



/**
	* @brief  Configure les pins de l'acceleromètre
  * @note   None
	* @Param  None
  * @retval None
  */
void accelero_pin_conf_io(void);

/**
	* @brief  Lance la conversion de l'ADC
  * @note   None
	* @Param  None
  * @retval None
  */
void start_convert(void);

/**
	* @brief  Lance la conversion de l'ADC sans DMA
  * @note   None
	* @Param  None
  * @retval None
  */
void start_convert_no_dma(void);


/**
	* @brief  Résultat de l'ADC -> conversion en g
  * @note   None
	* @Param  None
  * @retval None
  */
float volt_to_g(uint16_t v);


/**
	* @brief  fonction qui vérifie le roulis avec les resultats de l'ADC
  * @note   None
	* @Param  None
  * @retval None
  */
float * Verif_roulis_50ms(void);


/**
	* @brief  fonction qui vérifie le roulis avec les resultats de l'ADC, sans la DMA
  * @note   None
	* @Param  None
  * @retval None
  */
void Verif_roulis_50ms_no_dma(void);


/**
	* @brief 	None
  * @note   None
	* @Param  None
  * @retval return the result of the ADC for the battery
  */
float get_batterie_volt(void);
