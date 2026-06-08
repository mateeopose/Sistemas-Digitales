/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TREBOTES 20
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int modo = 0;
int velocidad = 1;
int led_activo = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void ActualizarModo(void);
void ActualizarVelocidad(void);
void ApagarTodosLosLeds(void);
void EncenderTodosLosLeds(void);
void EncenderLedIndividual(int numero_led);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  uint32_t ultimo_tiempo_led = 0;
  uint16_t retraso_ms = 300;
  bool estado_parpadeo = false;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    ActualizarModo();
    ActualizarVelocidad();

    if (HAL_GPIO_ReadPin(SW3_GPIO_Port, SW3_Pin) == GPIO_PIN_RESET) {//interrupcion de secuencia
        continue;
    }

    switch (velocidad)//seleccion velocidad
    {
        case 0:
            retraso_ms = 600; break;// Velocidad lenta
        case 1:
            retraso_ms = 300; break;// Velocidad media
        case 2:
            retraso_ms = 100;  break;// Velocidad rápida
    }

    uint32_t tiempo_actual = HAL_GetTick();
    if ((tiempo_actual - ultimo_tiempo_led) >= retraso_ms)
    {
        ultimo_tiempo_led = tiempo_actual;

        if (modo == 0)//modo horario
        {
            ApagarTodosLosLeds();
            EncenderLedIndividual(led_activo);
            led_activo = (led_activo + 1) % 6;
        }
        else if (modo == 1)//modo antiohorario
        {
            ApagarTodosLosLeds();
            EncenderLedIndividual(led_activo);
            led_activo = (led_activo - 1 + 6) % 6;
        }
        else
        {
            estado_parpadeo = !estado_parpadeo;//parpadeo
            if (estado_parpadeo) {
                EncenderTodosLosLeds();
            } else {
                ApagarTodosLosLeds();
            }
        }
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, PRIMERO_Pin|TERCERO_Pin|SEGUNDO_Pin|CUARTO_Pin
                          |SEXTO_Pin|QUINTO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SW1_Pin SW2_Pin SW3_Pin */
  GPIO_InitStruct.Pin = SW1_Pin|SW2_Pin|SW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PRIMERO_Pin TERCERO_Pin SEGUNDO_Pin CUARTO_Pin
                           SEXTO_Pin QUINTO_Pin */
  GPIO_InitStruct.Pin = PRIMERO_Pin|TERCERO_Pin|SEGUNDO_Pin|CUARTO_Pin
                          |SEXTO_Pin|QUINTO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void ActualizarModo(void) {
    static GPIO_PinState ultima_lectura = GPIO_PIN_SET;
    GPIO_PinState lectura1 = HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin);

    if (lectura1 != ultima_lectura) {
        HAL_Delay(TREBOTES);
        GPIO_PinState lectura2 = HAL_GPIO_ReadPin(SW1_GPIO_Port, SW1_Pin);

        if (lectura2 == lectura1) {
            ultima_lectura = lectura2;
            if (ultima_lectura == GPIO_PIN_RESET) {
                modo++;
                if (modo > 2) {
                    modo = 0;
                }
                ApagarTodosLosLeds();
                led_activo = 0;
            }
        }
    }
}

void ActualizarVelocidad(void) {
    static GPIO_PinState ultima_lectura = GPIO_PIN_SET;
    GPIO_PinState lectura1 = HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin);

    if (lectura1 != ultima_lectura) {
        HAL_Delay(TREBOTES);
        GPIO_PinState lectura2 = HAL_GPIO_ReadPin(SW2_GPIO_Port, SW2_Pin);

        if (lectura2 == lectura1) {
            ultima_lectura = lectura2;
            if (ultima_lectura == GPIO_PIN_RESET) {
                velocidad++;
                if (velocidad > 2) {
                    velocidad = 0;
                }
            }
        }
    }
}

void ApagarTodosLosLeds(void) {
    HAL_GPIO_WritePin(GPIOD, PRIMERO_Pin|SEGUNDO_Pin|TERCERO_Pin|CUARTO_Pin|QUINTO_Pin|SEXTO_Pin, GPIO_PIN_RESET);
}

void EncenderTodosLosLeds(void) {
    HAL_GPIO_WritePin(GPIOD, PRIMERO_Pin|SEGUNDO_Pin|TERCERO_Pin|CUARTO_Pin|QUINTO_Pin|SEXTO_Pin, GPIO_PIN_SET);
}

void EncenderLedIndividual(int numero_led) {
    switch(numero_led) {
        case 0: HAL_GPIO_WritePin(PRIMERO_GPIO_Port, PRIMERO_Pin, GPIO_PIN_SET); break;
        case 1: HAL_GPIO_WritePin(SEGUNDO_GPIO_Port, SEGUNDO_Pin, GPIO_PIN_SET); break;
        case 2: HAL_GPIO_WritePin(TERCERO_GPIO_Port, TERCERO_Pin, GPIO_PIN_SET); break;
        case 3: HAL_GPIO_WritePin(CUARTO_GPIO_Port,  CUARTO_Pin,  GPIO_PIN_SET); break;
        case 4: HAL_GPIO_WritePin(QUINTO_GPIO_Port,  QUINTO_Pin,  GPIO_PIN_SET); break;
        case 5: HAL_GPIO_WritePin(SEXTO_GPIO_Port,   SEXTO_Pin,   GPIO_PIN_SET); break;
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  * where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
