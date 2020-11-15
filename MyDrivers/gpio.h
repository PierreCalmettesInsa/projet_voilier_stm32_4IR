//Pierre Calmettes



#include "stm32f103xb.h" 
#include "stm32f1xx_ll_gpio.h"

/**
	* @brief 	Enable les clocks des GPIO A,B,C et D car ils sont tous utilisés, à lancer au début dans le main, 
  * @note   None
	* @Param  None
  * @retval None
  */
void gpio_clock_init(void);

/**
	* @brief 	Configure un pin en mode analog
  * @note   None
	* @Param  Le pin à configurer et le gpio associé
  * @retval None
  */
void gpio_conf_analog(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO);

/**
	* @brief 	Configure un pin en mode input
  * @note   None
	* @Param  Le pin à configurer et le gpio associé
  * @retval None
  */
void gpio_conf_input(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO);
 
 /**
	* @brief 	Configure un pin en mode floating
  * @note   None
	* @Param  Le pin à configurer et le gpio associé
  * @retval None
  */
void gpio_conf_floating(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO);

/**
	* @brief 	Configure un pin en mode output
  * @note   None
	* @Param  Le pin à configurer et le gpio associé
  * @retval None
  */
void gpio_conf_output(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO);
	
/**
	* @brief 	Configure un pin en mode alternate
  * @note   None
	* @Param  Le pin à configurer et le gpio associé
  * @retval None
  */	
void gpio_conf_alternate(LL_GPIO_InitTypeDef pin,GPIO_TypeDef * GPIO);
