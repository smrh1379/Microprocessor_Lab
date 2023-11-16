#include "stm32f4xx.h"
#include "math.h"
#define RS 0x20     /* Pin mask for reg select (pin 5) */
#define RW 0x40     /* Pin mask for read/write (pin 6) */
#define EN 0x80     /* Pin mask for enable     (pin 7) */
void delayMs(int n); 
void LCD_command(unsigned char command); 
void LCD_data(unsigned char data);
void LCD_init(void);
void PORTS_init(void);
char* convertIntegerToChar(uint32_t N);
void TIM3Config (void);
int i=0;
void Button_INT(void){
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; 
  SYSCFG->EXTICR[0] |=SYSCFG_EXTICR1_EXTI0_PB;    
  EXTI->IMR |= 0x0001;                /* unmask EXTI0 */
	EXTI->RTSR |= 0x0001;               /* select rising edge trigger */
 NVIC_EnableIRQ(EXTI0_IRQn);     /* enable interrupt in NVIC */
 __enable_irq();                     /* global enable IRQs */
}
int main(){
	PORTS_init();
	LCD_init();
	Button_INT();
	TIM3Config();
	LCD_command(1);
while(1){

}
}
void EXTI0_IRQHandler(void) {
i=i+1;
}
void TIM3_IRQHandler(void){
	uint32_t j=i;
	int count=0;
	LCD_command(1);
	while (j>0){
	j=j/10;
	count=count+1;
	}
char* arr = convertIntegerToChar(i);
	for (int t = 0; t < count; t++){
		LCD_data(arr[t]);
	}
}
void delayMs(int n) {
		int j;
    int i;
    for (; n>0; n--)
        for (i = 0; i < 3195; i++) {}
}
void PORTS_init(void) {
		RCC->AHB1ENR |= 1<<1   ;	
		GPIOB->PUPDR |= 0X00000002;
    GPIOB->MODER |= 0x00005500;               /* Initialize needed GPIOs and set ports mode appropriately  */
		RCC->AHB1ENR |= 1<<2;
		GPIOC->MODER = 0x00555555;
}
void TIM3Config (void) {
__disable_irq();
	RCC->APB1ENR |=RCC_APB1ENR_TIM3EN;
	TIM3->PSC = 1600-1;  // 16MHz/16000000 = 1 HZ
	TIM3->ARR = 10000-1;  // MAX ARR value
	TIM3->CR1 |= (1<<0); // Enable the Counter
	TIM3->CNT=0;
	TIM3->DIER |=TIM_DIER_UIE;
  TIM3->CR1 |= (1<<0); // Enable the Counter
	NVIC_EnableIRQ(TIM3_IRQn);
	__enable_irq();
}

void LCD_command(unsigned char command) {
    GPIOB->ODR &= ~(1<<6)  ;                         /* RS = 0, R/W = 0 */
	  GPIOB->ODR &= ~(1<<5)  ;
		GPIOC->BSRR = 0X00FF0000;
	  GPIOC->ODR  = command;                           /* put command on data bus */
    delayMs(0);
	  GPIOB->ODR |= (1<<7);                           /* pulse EN high */
    delayMs(0);
    GPIOB->ODR &= ~(1<<7);                             /* clear EN */

    if (command < 4)
        delayMs(2);         /* command 1 and 2 needs up to 1.64ms */
    else
        delayMs(1);         /* all others 40 us */
}

void LCD_data(unsigned char data) {
		//LCD_ready();
    GPIOB->ODR |= (1<<5)  ;                    /* RS = 1 */
    GPIOB->ODR &= ~(1<<6)  ;                    /* R/W = 0 */
		GPIOC->BSRR = 0X00FF0000;
		GPIOC->ODR = data  ;                 /* put data on data bus */
    GPIOB->ODR |= (1<<7);                   /* pulse EN high */
    delayMs(0);              
    GPIOB->ODR &= ~(1<<7);                   /* clear EN */
    delayMs(1);
}
void LCD_init(void) {
    PORTS_init();
    delayMs(20);            /* initialization sequence */
    LCD_command(0x30);
    delayMs(5);
    LCD_command(0x30);
    delayMs(1);
    LCD_command(0x30);
		delayMs(1);
    LCD_command(0x30);
	  delayMs(1);
    LCD_command(0x38);      /* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0x06);      /* move cursor right after each char */
    LCD_command(0x01);      /* clear screen, move cursor to home */
    LCD_command(0x0F);      /* turn on display, cursor blinking */
}
char* convertIntegerToChar(uint32_t N)
{
 
    // Count digits in number N
    int m = N;
    int digit = 0;
    while (m) {
 
        // Increment number of digits
        digit++;
 
        // Truncate the last
        // digit from the number
        m /= 10;
    }
 
    // Declare char array for result
    char* arr;
 
    // Declare duplicate char array
    char arr1[digit];
 
    // Memory allocation of array
    arr = (char*)malloc(digit);
 
    // Separating integer into digits and
    // accommodate it to character array
    int index = 0;
    while (N) {
 
        // Separate last digit from
        // the number and add ASCII
        // value of character '0' is 48
        arr1[++index] = N % 10 + '0';
 
        // Truncate the last
        // digit from the number
        N /= 10;
    }
 
    // Reverse the array for result
    int i;
    for (i = 0; i < index; i++) {
        arr[i] = arr1[index - i];
    }
 
    // Char array truncate by null
    arr[i] = '\0';
 
    // Return char array
    return (char*)arr;
}