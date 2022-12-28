/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define UART_VCP_TX_Pin GPIO_PIN_2
#define UART_VCP_TX_GPIO_Port GPIOA
#define UART_VCP_RX_Pin GPIO_PIN_3
#define UART_VCP_RX_GPIO_Port GPIOA
#define SPI_nCS_nLE_Pin GPIO_PIN_4
#define SPI_nCS_nLE_GPIO_Port GPIOA
#define SPI_SCK_Pin GPIO_PIN_5
#define SPI_SCK_GPIO_Port GPIOA
#define PWM_nBL_Pin GPIO_PIN_6
#define PWM_nBL_GPIO_Port GPIOA
#define SPI_PICO_Pin GPIO_PIN_7
#define SPI_PICO_GPIO_Port GPIOA
#define nPOL_Pin GPIO_PIN_0
#define nPOL_GPIO_Port GPIOB
#define HV_EN_Pin GPIO_PIN_12
#define HV_EN_GPIO_Port GPIOB
#define UART_BL_TX_Pin GPIO_PIN_9
#define UART_BL_TX_GPIO_Port GPIOA
#define UART_BL_RX_Pin GPIO_PIN_10
#define UART_BL_RX_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
