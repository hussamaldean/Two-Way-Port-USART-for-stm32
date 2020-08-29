#include "stm32f4xx.h"                  // Device header
#include "stdio.h"
//#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
void UART2_Init(void);
int  USART2_write(int ch);
void USART_write(int ch);
void delay(int delayms);

int main (void){
	int n;
char str[100];
UART2_Init();
delay(100);
USART_write('h');
USART_write('i');
USART_write('\r');
USART_write('\n');
printf("hello from the other side\r\n");
fprintf(stdout,"test for stdout\r\n");
fprintf(stderr,"test for error");
while(1)
{
	//USART_write('h');
//USART_write('i');
	printf("How old are you?");
	scanf("%d",&n);
	printf("Your age is : %d\r\n",n);	
	printf("Enter your first name :");
	gets(str);
	printf(" I like your style");
	puts(str);
	printf("\r\n");
}
}

void UART2_Init(void){
	RCC->AHB1ENR |=1; //Enable GPIOA clock
	RCC->APB1ENR|=0x20000; //Enable USART clock
	//configure PA3 as alternative function 
	GPIOA->AFR[0]|=0x07700; //ALT7 for UART2
	//GPIOA->AFR[1]|=0x07700;
	GPIOA->MODER|=0x00A0;  //enable PA3 as alternate function
	//GPIOA->MODER|=0x0020; //enable PA2 as alterate fuction
	USART2->BRR=0x0683; // set baud rate
	USART2->CR1|=0x000C; //enable RX-TX
	//USART2->CR1|=0x0008; // enable tx
	USART2->CR1|=0x2000; //enable USART2	
}

int USART2_write(int ch ){
while(!(USART2->SR&0x0080)){;}
	USART2->DR =(ch&0xFF);
	return ch;
	
}
int USART2_read(void){
while(!(USART2->SR&0x0020)){;} //wait for the character; 
	return USART2->DR;

}
struct __FILE{int handle;};
FILE __stdin   ={0};
FILE __stdout  ={1};
FILE __stderr  ={2};


int fgetc(FILE *f){
char c;
	c=USART2_read();
	if(c=='\r'){USART2_write(c);c='\n';}
USART2_write(c);
return c;
}

int inputc(int c, FILE *f){
return USART2_write(c);
}

void USART_write(int ch){
while(!(USART2->SR&0x0080)){
}
USART2->DR=(ch&0xFF);
	
}
void delay(int delayms){
int i;
	for(; delayms>0;delayms--){
	for(i=0;i<3192;i++);
	}
}
