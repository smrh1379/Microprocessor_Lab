#include "stm32f4xx.h"
#include <math.h>
#include <stdio.h>
void delayMs(int n);
int main(void) {
    RCC->AHB1ENR |=  1;             /* enable GPIOA clock */
    RCC->AHB1ENR |=  2;             /* enable GPIOB clock */
    GPIOA->MODER &= ~0xFFFFFFFF;    /* clear pin mode */
		GPIOB->PUPDR = 0X000000AA;			/*PULL DOWN*/
    GPIOA->MODER |=  0x00005555;    /* set pins to output mode */
    GPIOB->MODER &= ~0xFFFFFFFF;    /* clear pin mode */
		uint32_t  i = 0;
		GPIOA->BSRR = 0XFFFF<<16;
		i = 0XFF;
		while(1){
			

		while (i==GPIOB->IDR);
		i = GPIOB->IDR;
		switch (i & 0x000F)
      {
			case 0x0:
         GPIOA->ODR =0b0111111;
         break;

         case 0x1:
					 
         GPIOA->ODR =0b0000110;
         break;

         case 2:
         GPIOA->ODR =0b1011011;
         break;

         case 3:
         GPIOA->ODR =0b1001111;
         break;

         case 4:
         GPIOA->ODR =0b1100110;
         break;

         case 5:
         GPIOA->ODR =0b1101101;
         break;

         case 6:
         GPIOA->ODR =0b1111101;
         break;

         case 7:
         GPIOA->ODR =0b0000111;
         break;

         case 8:
         GPIOA->ODR =0b1111111;
         break;

         case 9:
         GPIOA->ODR =0b1101111;
         break;
		 //hex only 
		 case 10:
         GPIOA->ODR =0b1110111;  //A
         break;
		 case 11:
         GPIOA->ODR =0b1111100;  //b
         break;
		 case 12:
         GPIOA->ODR =0b0111001;  //C
         break;
		 case 13:
         GPIOA->ODR =0b1011110;  //d
         break;
		 case 14:
         GPIOA->ODR =0b1111001;  //E
         break;
		 case 15:
         GPIOA->ODR =0b1110001;  //F
         break;
		default:
					 GPIOA->BSRR =0b0111111;
         break;
					 
      }
		}
}

/* 16 MHz SYSCLK */
void delayMs(int n) {
    int i;
    for (; n > 0; n--)
        for (i = 0; i < 3195; i++) ;
}