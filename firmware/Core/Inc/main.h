/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ENC_A_Pin GPIO_PIN_0
#define ENC_A_GPIO_Port GPIOA
#define ENC_B_Pin GPIO_PIN_1
#define ENC_B_GPIO_Port GPIOA
#define UART2_VCP_TX_Pin GPIO_PIN_2
#define UART2_VCP_TX_GPIO_Port GPIOA
#define UART2_VCP_RX_Pin GPIO_PIN_3
#define UART2_VCP_RX_GPIO_Port GPIOA
#define SPI_nCS_nLE_Pin GPIO_PIN_4
#define SPI_nCS_nLE_GPIO_Port GPIOA
#define SPI_SCK_Pin GPIO_PIN_5
#define SPI_SCK_GPIO_Port GPIOA
#define PWM_nBL_Pin GPIO_PIN_6
#define PWM_nBL_GPIO_Port GPIOA
#define SPI_PICO_Pin GPIO_PIN_7
#define SPI_PICO_GPIO_Port GPIOA
#define SENSE_12V_Pin GPIO_PIN_0
#define SENSE_12V_GPIO_Port GPIOB
#define SENSE_180V_Pin GPIO_PIN_1
#define SENSE_180V_GPIO_Port GPIOB
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define PG_180V_Pin GPIO_PIN_10
#define PG_180V_GPIO_Port GPIOB
#define DITHOFF_180V_Pin GPIO_PIN_11
#define DITHOFF_180V_GPIO_Port GPIOB
#define EN_180V_Pin GPIO_PIN_12
#define EN_180V_GPIO_Port GPIOB
#define ENC_PB_Pin GPIO_PIN_13
#define ENC_PB_GPIO_Port GPIOB
#define nPOL_Pin GPIO_PIN_14
#define nPOL_GPIO_Port GPIOB
#define EN_12V_Pin GPIO_PIN_15
#define EN_12V_GPIO_Port GPIOB
#define UART1_BL_TX_Pin GPIO_PIN_9
#define UART1_BL_TX_GPIO_Port GPIOA
#define UART1_BL_RX_Pin GPIO_PIN_10
#define UART1_BL_RX_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_15
#define LED_GREEN_GPIO_Port GPIOA
#define LED_RED_Pin GPIO_PIN_4
#define LED_RED_GPIO_Port GPIOB
#define LED_BLUE_Pin GPIO_PIN_5
#define LED_BLUE_GPIO_Port GPIOB
#define SET_ILIM_Pin GPIO_PIN_6
#define SET_ILIM_GPIO_Port GPIOB
#define HW_REV2_Pin GPIO_PIN_7
#define HW_REV2_GPIO_Port GPIOB
#define HW_REV1_Pin GPIO_PIN_8
#define HW_REV1_GPIO_Port GPIOB
#define HW_REV0_Pin GPIO_PIN_9
#define HW_REV0_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
