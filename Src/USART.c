#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "delay.h"
#include "USART.h"

//Структуры для инициализации GPIOA и USART1
GPIO_InitTypeDef    USART_GPIO_InitStruct;
USART_InitTypeDef    USART_InitStruct;

void USART1_Init(void); //Объявление функции инициализации периферии
void Usart1_Send_symbol(uint8_t); //Объявление функции передачи символа
void Usart1_Send_String(char* str); //Объявление функции передачи строки

//Функция инициализации периферии
void USART1_Init(void)
{
  //Включаем тактирование GPIOA, USART1 и альтернативных функций AFIO
  RCC_APB2PeriphClockCmd((RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO), ENABLE);

  //Инициализации вывода PA9 - USART1_Tx
  USART_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9; //Настройки вывода PA9
  USART_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; //Скорость порта
  USART_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; //Режим альтернативной функции, выход Push-Pull
  GPIO_Init(GPIOA, &USART_GPIO_InitStruct); //Заданные настройки сохраняем в регистрах GPIOА

  //Инициализации вывода PA10 - USART1_Rx
  USART_GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10; //Настройки вывода PA10
  USART_GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING; //Input floating
  GPIO_Init(GPIOA, &USART_GPIO_InitStruct); //Заданные настройки сохраняем в регистрах GPIOА

  //Инициализация USART1
  USART_InitStruct.USART_BaudRate = 9600; //Скорость обмена 9600 бод
  USART_InitStruct.USART_WordLength = USART_WordLength_8b; //Длина слова 8 бит
  USART_InitStruct.USART_StopBits = USART_StopBits_1; //1 стоп-бит
  USART_InitStruct.USART_Parity = USART_Parity_No ; //Без проверки четности
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Без аппаратного контроля
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //Включен передатчик и приемник USART1
  USART_Init(USART1, &USART_InitStruct); //Заданные настройки сохраняем в регистрах USART1

  USART_Cmd(USART1, ENABLE); //Включаем USART1
}

//Функция передачи символа
void Usart1_Send_symbol(uint8_t data)
{
  while(!(USART1->SR & USART_SR_TC)); //Проверяем установку флага TC - завершения предыдущей передачи
  USART1->DR = data; //Записываем значение в регистр данных - передаем символ
}

//Функция передачи строки через USART
void Usart1_Send_String(char* str)
{
  uint8_t i=0;
  while(str[i])
  {
    Usart1_Send_symbol(str[i]);
      Delay(400);
    i++;
  }
  Usart1_Send_symbol('\n');
      Delay(400);
  Usart1_Send_symbol('\r');
    Delay(400);
}

