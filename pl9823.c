/*
 * pl9823.c
 *
 *  Created on: Oct 31, 2024
 *      Author: alexrdrzn
 */
#include "pl9823.h"

uint8_t LED_Data[MAX_LEDS][4];
uint16_t pwmData[(24 * MAX_LEDS) + 50];
uint8_t datasentflag = 0;
const uint32_t colors[] = {
		0xFF0000,
		0x00FF00,
		0x0000FF,
		0xFFFFFF,
		0x000000,
		0xA020F0,
		0xFC6600
};


void setLED(int ledNumber, uint32_t color)
{
	LED_Data[ledNumber][0] = ledNumber;
	LED_Data[ledNumber][1] = (color >> 16) & 0xFF;
	LED_Data[ledNumber][2] = (color >> 8) & 0xFF;
	LED_Data[ledNumber][3] = color & 0xFF;
}

void resetLEDs()
{
	for (int i = 0; i < MAX_LEDS; i++)
	{
		LED_Data[i][0] = i;
		LED_Data[i][1] = 0;
		LED_Data[i][2] = 0;
		LED_Data[i][3] = 0;
	}
}

void sendData()
{
	uint32_t index = 0;
	uint32_t color = 0;

	for (int i = 0; i < MAX_LEDS; i++) 
	{
		color = (LED_Data[i][1] << 16) | (LED_Data[i][2] << 8) | LED_Data[i][3];
		for (int j = 23; j >= 0; j--, index++) 
		{
			pwmData[index] = (color & (1 << j)) ? TIME_ON_HIGH : TIME_ON_LOW;
		}
	}
	for (int i = 0; i < 50; i++, index++) 
	{
		pwmData[index] = 0;
	}

	HAL_TIM_PWM_Start_DMA(&TIM_HANDLER, TIM_CHANNEL_1, (uint32_t*)pwmData, index);

	while (!datasentflag);
	datasentflag = 0;
}


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Stop_DMA(&TIM_HANDLER, TIM_CHANNEL_1);
	datasentflag = 1;
}
