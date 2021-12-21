
#include "main.h"
#include "usb_device.h"

#include "usbd_hid.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

extern USBD_HandleTypeDef hUsbDeviceFS;

typedef struct {
	uint8_t MODIFIER;
	uint8_t RESERVED;
	uint8_t KEYCODE1;
	uint8_t KEYCODE2;
	uint8_t KEYCODE3;
	uint8_t KEYCODE4;
	uint8_t KEYCODE5;
	uint8_t KEYCODE6;
} keyboardHID;

keyboardHID keyboardhid = {0,0,0,0,0,0,0,0};

//KEY
#define AH  0x1C
#define BH  0x18
#define CH  0x14
#define DH  0x1A
#define EH  0x08
#define FH  0x15
#define GH  0x17

#define AM  0x0B
#define BM  0x0D
#define CM  0x04
#define DM  0x16
#define EM  0x07
#define FM  0x09
#define GM  0x0A

#define AL  0x11
#define BL  0x10
#define CL  0x1D
#define DL  0x1B
#define EL  0x06
#define FL  0x19
#define GL  0x05

//TEMPO TO TIME MS
#define T4  	435
#define T8  	217
#define T44  	870
#define T48  	652


void OneKey(uint16_t KEY, int TIME) {
	keyboardhid.KEYCODE1 = KEY;
	USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof(keyboardhid));
	HAL_Delay(10);
	keyboardhid.KEYCODE1 = 0x00;
	USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof(keyboardhid));
	HAL_Delay(TIME-10);
}


void loopA() {
	OneKey(DM, T8);
	OneKey(EM, T8);
	OneKey(FM, T8);
	OneKey(GM, T8);
	OneKey(AM, T4);
	OneKey(DH, T8);
	OneKey(CH, T8);
	OneKey(AM, T4);
	OneKey(DM, T4);
	OneKey(AM, T8);
	OneKey(GM, T8);
	OneKey(FM, T8);
	OneKey(EM, T8);
	OneKey(DM, T8);
	OneKey(EM, T8);
	OneKey(FM, T8);
	OneKey(GM, T8);
	OneKey(AM, T4);
	OneKey(GM, T8);
	OneKey(FM, T8);
	OneKey(EM, T8);
	OneKey(DM, T8);
	OneKey(EM, T8);
	OneKey(FM, T8);
	OneKey(EM, T8);
	OneKey(DM, T8);
	OneKey(CM, T8);
	OneKey(FM, T8);
	OneKey(DM, T8);
	OneKey(EM, T8);
	OneKey(FM, T8);
	OneKey(GM, T8);

	OneKey(AM, T4);
	OneKey(DH, T8);
	OneKey(CH, T8);
	OneKey(AM, T4);
	OneKey(DM, T4);
	OneKey(AM, T8);
	OneKey(GM, T8);
	OneKey(FM, T8);
	OneKey(EM, T8);
	OneKey(DM, T8);
	OneKey(EM, T8);
	OneKey(FM, T8);
	OneKey(GM, T8);
	OneKey(AM, T4);
	OneKey(GM, T8);
	OneKey(FM, T8);
	OneKey(EM, T4);
	OneKey(FM, T4);
	OneKey(GM, T4);
	OneKey(AM, T4);

}

void loopB() {
	OneKey(CH, T8);
	OneKey(DH, T8);
	OneKey(AM, T8);
	OneKey(GM, T8);
	OneKey(AM, T4);
	OneKey(GM, T8);
	OneKey(AM, T8);
	OneKey(CH, T8);
	OneKey(DH, T8);
	OneKey(AM, T8);
	OneKey(GM, T8);
	OneKey(AM, T4);
	OneKey(GM, T8);
	OneKey(AM, T8);
	OneKey(GM, T8);
	OneKey(FM, T8);
	OneKey(EM, T8);
	OneKey(CM, T8);
	OneKey(DM, T4);
	OneKey(CM, T8);
	OneKey(DM, T8);
	OneKey(EM, T8);
	OneKey(FM, T8);
	OneKey(GM, T8);
	OneKey(AM, T8);
	OneKey(DM, T4);
	OneKey(GM, T8);
	OneKey(AM, T8);
}

void loopC() {
	OneKey(CH, T8);
	OneKey(DH, T8);
	OneKey(AM, T8);
	OneKey(GM, T8);
	OneKey(AM, T4);
	OneKey(GM, T8);
	OneKey(AM, T8);
	OneKey(CH, T8);
	OneKey(DH, T8);
	OneKey(AM, T8);
	OneKey(GM, T8);
	OneKey(AM, T4);
	OneKey(DH, T8);
	OneKey(EH, T8);
	OneKey(FH, T8);
	OneKey(EH, T8);
	OneKey(DH, T8);
	OneKey(CM, T8);
	OneKey(AM, T4);
	OneKey(GM, T8);
	OneKey(AM, T8);
	OneKey(GM, T8);
	OneKey(FM, T8);
	OneKey(EM, T8);
	OneKey(CM, T8);
	OneKey(DM, T8);
}

int main(void) {

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();

  while (1) {

	  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == 0) {
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);


		  for(int i=0; i<2; i++) {
			  loopA();
		  }

		  for(int i=0; i<2; i++) {
			  loopB();
		  }

		  loopC();
		  OneKey(GM, T8);
		  OneKey(AM, T8);

		  for(int i=0; i<2; i++) {
		  	  loopB();
		  }

		  loopC();

		  keyboardhid.KEYCODE1 = 0x00;
		  USBD_HID_SendReport(&hUsbDeviceFS, &keyboardhid, sizeof(keyboardhid));
		  HAL_Delay(2);

	  }else {
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	  }

  }
}







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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 23;
  RCC_OscInitStruct.PLL.PLLN = 354;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
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
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();
  __GPIOC_CLK_ENABLE();
  __GPIOD_CLK_ENABLE();

  /*Configure GPIO pin : BUTTON_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*LED PC13*/
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
