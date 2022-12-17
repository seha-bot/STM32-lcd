#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f1xx_hal.h"

void tick(uint8_t RS)
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,  0);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,  0);
  
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,  1);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,  RS);
  
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6,  0);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,  0);
  HAL_Delay(1);
}

void setData(uint8_t RS, uint8_t data)
{
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,  data>>3&1);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, data>>2&1);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, data>>1&1);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, data>>0&1);
  tick(RS);
}

void instruction(uint8_t data)
{
  setData(0, data>>4);
  setData(0, data);
}

void letters(char* s)
{
  int i = 0;
  while(s[i] != 0)
  {
    setData(1, s[i]>>4);
    setData(1, s[i++]);
  }
}

void setCursor(uint8_t x, uint8_t y)
{
  instruction(0b10000000 | y << 6 | x);
}

#ifdef __cplusplus
}
#endif

#endif
