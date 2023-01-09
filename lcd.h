#ifndef __LCD_H
#define __LCD_H

#include "stm32f1xx_hal.h"

//DISPLAY INSTRUCTIONS
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

//DISPLAY BUILTIN FUNCTIONS
void setCursor(uint8_t x, uint8_t y)
{
  instruction(0b10000000 | y << 6 | x);
}

void clearDisplay()
{
  instruction(0b00000001);
}

void returnHome()
{
  instruction(0b00000010);
}

void shiftDisplay(uint8_t direction)
{
  instruction(0b00010000 | direction << 3);
}

//DRAWING FUNCTIONS
void letter(char c)
{
  setData(1, c>>4);
  setData(1, c);
}

void letters(char* s)
{
  int i = 0;
  while(s[i] != 0)
  {
    letter(s[i++]);
  }
}

void introduce(const char* message)
{
  clearDisplay();
  returnHome();
  int i = 0;
  while(message[i])
  {
    letter(message[i++]);
    HAL_Delay(500);
  }
}

char msg[17] = { [0 ... 16] = 0 };
void scroll(const char* message, int* off, int direction, int line)
{
  int size = 0;
  while(message[size]) size++;

  setCursor(0, line);
  if(direction == 1)
  {
    for(int i = 0; i < 16; i++)
    {
      msg[i] = message[(i + *off) % size];
    }
  }
  else if(direction == -1)
  {
    for(int i = 0; i < 16; i++)
    {
      int ofic = i + (size-(*off % size));
      msg[i] = message[ofic % size];
    }
  }
  letters(msg);
  (*off)++;
}

#endif
