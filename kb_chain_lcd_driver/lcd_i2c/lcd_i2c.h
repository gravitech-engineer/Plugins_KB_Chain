#ifndef __LCD_I2C_H__
#define __LCD_I2C_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define LCD_MAX_COLUMN			20
#define LCD_MAX_ROW				4

class LCD_I2C : public Device {
	private:
		enum {
			s_detect, 
			s_idle, 
			s_error, 
			s_wait
		} state;
		TickType_t tickcnt;
		
		I2CDev *i2c;
		
		int _dev_addr = 0;
		
		bool PIN_RS = false;
		
		int BIT_EN = 0x04;
		int BIT_RS = 0x01;
		int BIT_BLACKLIGHT = 0x08;
		
		int BIT_BLINK = 0x01;
		int BIT_CURSOR = 0x02;
		int BIT_DISPLAY = 0x04;
		
		bool BLINK = false;
		bool CURSOR = false;
		bool sDISPLAY = true;
		bool BLACKLIGHT = true;
		
		
		void SEND(uint8_t data) ;
		void CMD(uint8_t data) ;
		void upCr() ;
		
		void write(char data) ;
		void setCursor(int x, int y) ;

	public:
		// constructor
		LCD_I2C(int bus_ch, int dev_addr);
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		// method
		int backlight(void); // get backlight status
		void backlight(int val); // set backlight status
		void clear(void);
		void print(uint8_t lcd_column, uint8_t lcd_row, char *buf);
		void print(uint8_t lcd_column, uint8_t lcd_row, double val);
		void print(uint8_t lcd_column, uint8_t lcd_row, double val, int precision);
};

#endif
