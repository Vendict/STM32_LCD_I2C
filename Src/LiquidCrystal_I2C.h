//YWROBOT
#ifndef LiquidCrystal_I2C_h
#define LiquidCrystal_I2C_h

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_i2c.h"
#include "delay.h"
#include "I2C.h"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0x04  // Enable bit
#define Rw 0x02  // Read/Write bit
#define Rs 0x01  // Register select bit

typedef struct
{
  uint8_t Addr;
  uint8_t displayfunction;
  uint8_t displaycontrol;
  uint8_t displaymode;
  uint8_t numlines;
  uint8_t cols;
  uint8_t rows;
  uint8_t backlightval;
} LiquidCrystal_I2C_Def;


  void LCDI2C_write(uint8_t value);
  void LCDI2C_init(uint8_t lcd_Addr,uint8_t lcd_cols,uint8_t lcd_rows);
  void LCDI2C_begin(uint8_t cols, uint8_t rows);//, uint8_t charsize = LCD_5x8DOTS ); если у вас другой размер символов - поправьте тут и в описании функции
  void LCDI2C_clear();
  void LCDI2C_home();
  void LCDI2C_noDisplay();
  void LCDI2C_display();
  void LCDI2C_noBlink();
  void LCDI2C_blink();
  void LCDI2C_noCursor();
  void LCDI2C_cursor();
  void LCDI2C_scrollDisplayLeft();
  void LCDI2C_scrollDisplayRight();
  void LCDI2C_printLeft();
  void LCDI2C_printRight();
  void LCDI2C_leftToRight();
  void LCDI2C_rightToLeft();
  void LCDI2C_shiftIncrement();
  void LCDI2C_shiftDecrement();
  void LCDI2C_noBacklight();
  void LCDI2C_backlight();
  void LCDI2C_autoscroll();
  void LCDI2C_noAutoscroll();
  void LCDI2C_createChar(uint8_t location, uint8_t charmap[]);
  void LCDI2C_setCursor(uint8_t col, uint8_t row);
  void LCDI2C_write_String(char* str);
  void LCDI2C_command(uint8_t value);
//  void LCDI2C_init();

////compatibility API function aliases
void LCDI2C_blink_on();						// alias for blink()
void LCDI2C_blink_off();       					// alias for noBlink()
void LCDI2C_cursor_on();      	 					// alias for cursor()
void LCDI2C_cursor_off();      					// alias for noCursor()
void LCDI2C_setBacklight(uint8_t new_val);				// alias for backlight() and nobacklight()
void LCDI2C_load_custom_character(uint8_t char_num, uint8_t *rows);	// alias for createChar()
void LCDI2C_printstr(const char[]);

//void LCDI2C_init_priv();
void LCDI2C_send(uint8_t, uint8_t);
void LCDI2C_write4bits(uint8_t);
void LCDI2C_expanderWrite(uint8_t);
void LCDI2C_pulseEnable(uint8_t);


#endif
