#include "stm32f4xx.h"
#include <math.h>
#include <stdio.h>
void delayMs(int n);
int main(void) {
    RCC->AHB1ENR |=  1;             /* enable GPIOA clock */
    RCC->AHB1ENR |=  2;             /* enable GPIOB clock */
		

    GPIOA->MODER &= ~0xFFFFFFFF;    /* clear pin mode */
		GPIOB->PUPDR = 0X0000AAAA;			/*PULL DOWN*/
    GPIOA->MODER |=  0x55555555;    /* set pins to output mode */
    GPIOB->MODER &= ~0xFFFFFFFF;    /* clear pin mode */
		uint32_t i = 0;
		i = 0XFF;

		while(1){
while (i==GPIOB->IDR);
		i = GPIOB->IDR;
		switch (GPIOB->IDR & 0x000F)
      {
			case 0x0:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b0111111;
         break;

         case 0x1:
				 GPIOA->BSRR=0X007F0000 ;
         GPIOA->BSRR =0b0000110;
         break;

         case 2:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b1011011;
         break;

         case 3:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b1001111;
         break;

         case 4:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b1100110;
         break;

         case 5:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b1101101;
         break;

         case 6:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b1111101;
         break;

         case 7:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b0000111;
         break;

         case 8:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b1111111;
         break;

         case 9:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b1101111;

         break;
		 //hex only 
		 case 10:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b1110111;  //A
         break;
		 case 11:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b1111100;  //b
         break;
		 case 12:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b0111001;  //C
         break;
		 case 13:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b1011110;  //d
         break;
		 case 14:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b1111001;  //E
         break;
		 case 15:
				 GPIOA->BSRR=0X007F0000;
         GPIOA->BSRR =0b1110001;  //F
         break;
		default:
				 GPIOA->BSRR=0X007F0000;
					GPIOA->BSRR =0b0111111;
         break;
					 
      }
			switch (GPIOB->IDR & 0x00F0)
      {
			case 0x0:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b0111111<<7;
         break;

         case 0x1<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b0000110<<7;
         break;

         case 2<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b1011011<<7;
         break;

         case 3<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b1001111<<7;
         break;

         case 4<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b1100110<<7;
         break;

         case 5<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b1101101<<7;
         break;

         case 6<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b1111101<<7;
         break;

         case 7<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b0000111<<7;
         break;

         case 8<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b1111111<<7;
         break;

         case 9<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b1101111<<7;

         break;
		 //hex only 
		 case 10<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b1110111<<7;  //A
         break;
		 case 11<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b1111100<<7;  //b
         break;
		 case 12<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b0111001<<7;  //C
         break;
		 case 13<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b1011110<<7;  //d
         break;
		 case 14<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b1111001<<7;  //E
         break;
		 case 15<<4:
				 GPIOA->BSRR=0XFF800000;
         GPIOA->BSRR =0b1110001<<7;  //F
         break;
		default:
				 GPIOA->BSRR=0XFF800000;
					GPIOA->BSRR =0b0111111<<7;
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