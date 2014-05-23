#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "delay.h"
#include "stm32f10x_i2c.h"
#include "I2C.h"


//для I2C
GPIO_InitTypeDef i2c_gpio;
I2C_InitTypeDef i2c;

void init_I2C1(void)
{
    // Включаем тактирование нужных модулей
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    // А вот и настройка I2C
    i2c.I2C_ClockSpeed = 100000;
    i2c.I2C_Mode = I2C_Mode_I2C;
    i2c.I2C_DutyCycle = I2C_DutyCycle_2;
    // Адрес я тут взял первый пришедший в голову
    i2c.I2C_OwnAddress1 = 0x15;
    i2c.I2C_Ack = I2C_Ack_Enable;
    i2c.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &i2c);

    // I2C использует две ноги микроконтроллера, их тоже нужно настроить
    i2c_gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    i2c_gpio.GPIO_Mode = GPIO_Mode_AF_OD;
    i2c_gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &i2c_gpio);

    // Ну и включаем, собственно, модуль I2C1
    I2C_Cmd(I2C1, ENABLE);
}

/*******************************************************************/
void I2C_StartTransmission(I2C_TypeDef* I2Cx, uint8_t transmissionDirection,  uint8_t slaveAddress)
{
    // На всякий слуыай ждем, пока шина осовободится
    while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
    // Генерируем старт - тут все понятно )
    I2C_GenerateSTART(I2Cx, ENABLE);
    // Ждем пока взлетит нужный флаг
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
    // Посылаем адрес подчиненному  //возможно тут нужен сдвиг влево  //судя по исходникам - да, нужен сдвиг влево
    //http://microtechnics.ru/stm32-ispolzovanie-i2c/#comment-8109
    I2C_Send7bitAddress(I2Cx, slaveAddress<<1, transmissionDirection);
    // А теперь у нас два варианта развития событий - в зависимости от выбранного направления обмена данными
    if(transmissionDirection== I2C_Direction_Transmitter)
    {
    	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    }
    if(transmissionDirection== I2C_Direction_Receiver)
    {
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    }
}

/*******************************************************************/
void I2C_WriteData(I2C_TypeDef* I2Cx, uint8_t data)
{
    // Просто вызываем готоваую функцию из SPL и ждем, пока данные улетят
    I2C_SendData(I2Cx, data);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}



/*******************************************************************/
uint8_t I2C_ReadData(I2C_TypeDef* I2Cx)
{
    // Тут картина похожа, как только данные пришли быстренько считываем их и возвращаем
    while( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) );
    uint8_t data;
    data = I2C_ReceiveData(I2Cx);
    return data;
}

