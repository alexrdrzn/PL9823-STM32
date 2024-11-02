/*
 * pl9823.h
 *
 *  Created on: Oct 31, 2024
 *      Author: alexrdrzn
 */

#ifndef INC_PL9823_H_
#define INC_PL9823_H_

#include <stdint.h>
#include "main.h"

#define MAX_LEDS 4
#define PI 3.14159265
#define TIM_HANDLER htim1

enum color
{
	red, green, blue, white, black, purple, orange
};

extern TIM_HandleTypeDef htim1;
extern uint8_t LED_Data[][4];
extern uint16_t pwmData[];
extern uint8_t datasentflag;
extern const uint32_t colors[];

void setLED(int ledNumber, uint32_t color);
void resetLEDs();
void sendData();


#endif /* INC_PL9823_H_ */
