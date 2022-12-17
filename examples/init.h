#include<lcd.h>

void initDisplay()
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0); //  Backlight -
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,  1); //  Backlight +
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,  0); //  R/W always 0
    HAL_Delay(50);

    setData(0, 0b0010);       // Function set ( 4 bit mode )
    instruction(0b00101000);  // Function set ( 4 bit mode, 2 lines, 5x8 )
    instruction(0b00001110);  // Display control ( display on, cursor on, blinking off )
    instruction(0b00000110);  // Entry mode set ( increment, display shift off )

    setCursor(0, 0);
    letters("Imana");
    setCursor(0, 1);
    letters("<3 <3 <3");
}

void loopDisplay()
{
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
    HAL_Delay(10);
}