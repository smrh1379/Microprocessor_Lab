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
void TIM2Config(void);
void TIM3Config (void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void Button_INT(void);
char* convertIntegerToChar(uint32_t N);
uint32_t i=0;
int clicked=0;
void LCD_clear(){
LCD_command(0x00);
LCD_command(0x10);
}
int main(){
	PORTS_init() ;
 __disable_irq();                    /* global disable IRQs */
LCD_init();
LCD_clear();
Button_INT();
//TIM2Config();
while(1){}
}
void Button_INT(void){
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; 
  SYSCFG->EXTICR[0] |=SYSCFG_EXTICR1_EXTI0_PB;    
  EXTI->IMR |= 0x0001;                /* unmask EXTI0 */
	EXTI->RTSR |= 0x0001;               /* select rising edge trigger */
 NVIC_EnableIRQ(EXTI0_IRQn);     /* enable interrupt in NVIC */
 __enable_irq();                     /* global enable IRQs */
}



void TIM2Config (void) {
__disable_irq();
	RCC->APB1ENR |= (1<<0);  // Enable the timer2 clock
	TIM2->PSC = 16-1;  // 16MHz/1600 = 10 kHZ
	TIM2->ARR = 100-1;  // MAX ARR value
	TIM2->CR1 |= (1<<0); // Enable the Counter
	TIM2->CNT=0;
	TIM2->DIER |=TIM_DIER_UIE;
  TIM2->CR1 |= (1<<0); // Enable the Counter
	NVIC_EnableIRQ(TIM2_IRQn);
	__enable_irq();
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
void EXTI0_IRQHandler(void) {
	if (clicked==0){
	TIM2Config();
	TIM3Config();
	clicked=1;
	}
	else if (clicked==1){
	TIM2->CR1 = 0; // Disabling the Counter
	TIM3->CR1 = 0; // Disabling the Counter
	}
}
void TIM2_IRQHandler(void){
  i=i+1;
	uint32_t j=i;
	int count=0;
	LCD_clear();
	while (j>0){
	j=j/10;
	count=count+1;
	}
char* arr = convertIntegerToChar(i);
	for (int t = 0; t < count; t++){
		LCD_data(arr[t]);
	}
}

void TIM3_IRQHandler(void){
	GPIOA->ODR ^= 0x00000010;
}

void LCD_init(void) {
    PORTS_init();
    delayMs(20);            /* initialization sequence */
    LCD_command(0x30);
    delayMs(5);
    LCD_command(0x30);
    delayMs(1);
    LCD_command(0x30);
    LCD_command(0x20);      
		LCD_command(0x20);     
		LCD_command(0x80);      
		LCD_command(0x0);      
	  LCD_command(0x80);      
		LCD_command(0x0);      
	  LCD_command(0xc0);     
    LCD_command(0x00);      
    LCD_command(0x60);  
	  LCD_command(0x10);      
    LCD_command(0x80); 
    LCD_command(0x00);      
    LCD_command(0x10);    
    LCD_command(0x00);      
    LCD_command(0xF0);    	
}   

void PORTS_init(void) {
		RCC->AHB1ENR |= 1<<1   ;	
		GPIOB->PUPDR |= 0X00000002;
    GPIOB->MODER |= 0x00005500;               /* Initialize needed GPIOs and set ports mode appropriately  */
		RCC->AHB1ENR |= 1<<2;
		GPIOC->MODER = 0x00555555;
		RCC->AHB1ENR |= 1   ;	
		GPIOA->MODER |= 0X00000500;
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
		char low4,high4;
		low4=data & 0x0f;
		high4=data&0xf0;
    GPIOB->ODR |= (1<<5)  ;                    /* RS = 1 */
    GPIOB->ODR &= ~(1<<6)  ;                    /* R/W = 0 */
		GPIOC->BSRR = 0X00FF0000;
		GPIOC->ODR = high4  ;                 /* put data on data bus */
    GPIOB->ODR |= (1<<7);                   /* pulse EN high */
    delayMs(0);              
    GPIOB->ODR &= ~(1<<7);                   /* clear EN */
    delayMs(1);
			GPIOC->ODR = low4<<4  ;                 /* put data on data bus */
    GPIOB->ODR |= (1<<7);                   /* pulse EN high */
    delayMs(0);              
    GPIOB->ODR &= ~(1<<7);                   /* clear EN */
    delayMs(1);
}

char* convertIntegerToChar(uint32_t N)
{
    int m = N;
    int digit = 0;
    while (m) {
        digit++;

        m /= 10;
    }
    char* arr;
    char arr1[digit];
    arr = (char*)malloc(digit);
    int index = 0;
    while (N) {
        arr1[++index] = N % 10 + '0';
 
        N /= 10;
    }
    int i;
    for (i = 0; i < index; i++) {
        arr[i] = arr1[index - i];
    }
    arr[i] = '\0';
    return (char*)arr;
}
/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n) {
		int j;
    int i;
    for (; n>0; n--)
        for (i = 0; i < 3195; i++) {}
}