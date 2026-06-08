/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SW1_Pin GPIO_PIN_2
#define SW1_GPIO_Port GPIOA
#define SW2_Pin GPIO_PIN_4
#define SW2_GPIO_Port GPIOA
#define SW3_Pin GPIO_PIN_5
#define SW3_GPIO_Port GPIOA
#define PRIMERO_Pin GPIO_PIN_8
#define PRIMERO_GPIO_Port GPIOD
#define TERCERO_Pin GPIO_PIN_9
#define TERCERO_GPIO_Port GPIOD
#define SEGUNDO_Pin GPIO_PIN_11
#define SEGUNDO_GPIO_Port GPIOD
#define CUARTO_Pin GPIO_PIN_12
#define CUARTO_GPIO_Port GPIOD
#define SEXTO_Pin GPIO_PIN_13
#define SEXTO_GPIO_Port GPIOD
#define QUINTO_Pin GPIO_PIN_15
#define QUINTO_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
