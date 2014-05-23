#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_i2c.h"
#include "delay.h"
//#include "USART.h" 
#include "I2C.h"
#include "LiquidCrystal_I2C.h"

uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
uint8_t retarrow[8] = {0x1,0x1,0x5,0x9,0x1f,0x8,0x4};

uint8_t habr1[8] = {0x0,0x0,0x2,0x3,0xd,0x7,0x7,0xf};
uint8_t habr2[8] = {0x0,0x1,0x7,0x1b,0x1e,0xf,0x1f, 0x1f};
uint8_t habr3[8] = {0x10,0x9,0x17,0x1c,0xc,0x1f,0xd, 0x1d};
uint8_t habr4[8] = {0x0,0x10,0x0,0x0,0x10,0x0,0x14,0x18};

uint8_t habr5[8] = {0x15,0xd,0xb,0xd,0x5,0x3,0x5, 0x6};
uint8_t habr6[8] = {0x1f,0x1f,0x1f,0x1f,0x1f,0x7,0x19, 0xe};
uint8_t habr7[8] = {0x1d,0x1d,0x1d,0x1a,0x1b, 0xd,0x19, 0x8};
uint8_t habr8[8] = {0x18,0x10,0x2,0x1c,0x1f,0x0,0x0,0x0};

uint8_t habr9[8] =  {0x1, 0x1,0x3, 0x3,0x1,0x0,0x0, 0x0};
uint8_t habr10[8] = {0x18,0x8,0x18,0x4,0x8,0x8,0x10,0x0};
uint8_t habr11[8] = {0x18,0x10,0x10,0x0,0x0,0x0,0x0, 0x0};

// Function declarations
// typedef __w64 unsigned int size_t
int strlen(const char *);
char *strrev(char *);
char *itoa(int, char *, int);

int strlen(const char *str) {
	const char *s;

	s = str;
	while (*s)
		s++;
	return s - str;
}

char *strrev(char *str) {
	char *p1, *p2;

	if (!str || !*str)
		return str;

	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}

	return str;
}

char *itoa(int n, char *s, int b) {
	static char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int i=0, sign;

	if ((sign = n) < 0)
		n = -n;

	do {
		s[i++] = digits[n % b];
	} while ((n /= b) > 0);

	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	return strrev(s);
}


void displayKeyCodes(void) {
  uint8_t i = 0;
  while (1) {
    LCDI2C_clear();
    LCDI2C_setCursor(2,2);
    LCDI2C_write_String("Hello Habrahabr !");
    LCDI2C_setCursor(0, 0);
	char buf[10];
	itoa(i, buf, 10);
    LCDI2C_write_String("Codes 0x"); LCDI2C_write_String(buf);
	itoa(i+19, buf, 10);
    LCDI2C_write_String("-0x"); LCDI2C_write_String(buf);
    LCDI2C_setCursor(0, 1);
    int j;
    for (j=0; j<20; j++) {
      LCDI2C_write(i+j);
    }
    i+=16;
    if (i<15) break;
    Delay(2000);
  }
}

int main()
{
//  USART1_Init(); //Вызов функции инициализации периферии

  uint8_t data;
    //дождались команды и начали работу
/*  while(1)
  {
    if((USART1->SR & USART_SR_RXNE)) //Проверяем поступление данных от компьютера
    {
      data = USART1->DR; //Считываем принятые данные
    //  Usart1_Send_symbol(data); //И тут же отсылаем их обратно
      break;
    }
  }*/
  Delay(3000);
//  Usart1_Send_String("Start");

  LCDI2C_init(0x27,20,4);
  // ------- Quick 3 blinks of backlight  -------------
  int i;
  for( i = 0; i< 3; i++)
  {
    LCDI2C_backlight();
    Delay(250);
    LCDI2C_noBacklight();
    Delay(250);
  }
  LCDI2C_backlight(); // finish with backlight on


  LCDI2C_write(53);
//  Usart1_Send_String("End");
  Delay(2000);
  LCDI2C_clear();

  displayKeyCodes();

  Delay(2000);
/*
  LCDI2C_createChar(0, bell);
//  Usart1_Send_String("char1");
  LCDI2C_createChar(1, note);
  LCDI2C_createChar(2, clock);
  LCDI2C_createChar(3, heart);
  LCDI2C_createChar(4, duck);
  LCDI2C_createChar(5, check);
  LCDI2C_createChar(6, cross);
  LCDI2C_createChar(7, retarrow);
  LCDI2C_clear();
//  Usart1_Send_String("endchar");

//    int i;
  for (i=0; i<8; i++) {
        LCDI2C_write(i);
  }

  Delay(3000);*/
    //установим кляксу
  LCDI2C_createChar(0, habr1);
  LCDI2C_createChar(1, habr2);
  LCDI2C_createChar(2, habr3);
  LCDI2C_createChar(3, habr4);
  LCDI2C_createChar(4, habr5);
  LCDI2C_createChar(5, habr6);
  LCDI2C_createChar(6, habr7);
  LCDI2C_createChar(7, habr8);

  LCDI2C_clear();
  LCDI2C_write_String("Hello Habrahabr");
  LCDI2C_setCursor(16,0);
  LCDI2C_write(0);
  LCDI2C_write(1);
  LCDI2C_write(2);
  LCDI2C_write(3);
  LCDI2C_setCursor(16,1);
  LCDI2C_write(4);
  LCDI2C_write(5);
  LCDI2C_write(6);
  LCDI2C_write(7);
  LCDI2C_setCursor(16,2);
  LCDI2C_write(201);
  LCDI2C_write(177);
  LCDI2C_write(162);


}
