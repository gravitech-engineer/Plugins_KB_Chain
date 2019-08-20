#ifndef __OLED_128X64_I2C_H__
#define __OLED_128X64_I2C_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define OLED_I2C_WIDTH				128
#define OLED_I2C_HEIGHT				64

typedef struct {
	int command;
	int data;
} oled_i2c_init_t;

typedef enum oled_chipset_struct {
	ocs_ssd1306, ocs_sh1106
} oled_chipset_t;

class OLED_128X64_I2C : public Device {
	private:
		enum {
			s_detect, s_cmd_init, s_idle, s_error, s_wait
		} state;
		TickType_t tickcnt;
		uint8_t vram[OLED_I2C_WIDTH * (OLED_I2C_HEIGHT / 8)];
		oled_i2c_init_t *init_ptr;
		uint8_t flag, set_flag, clr_flag;
		oled_chipset_t chipset;
		bool valid_column_row(uint8_t lcd_column, uint8_t lcd_row);
		bool valid_column_row_big(uint8_t lcd_column, uint8_t lcd_row);
		esp_err_t render(I2CDev *i2c);
	public:
		// constructor
		OLED_128X64_I2C(oled_chipset_t oled_chipset, int bus_ch, int dev_addr);
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
		void clear(void);
		void putch(uint8_t lcd_column, uint8_t lcd_row, char val);
		void putstr(uint8_t lcd_column, uint8_t lcd_row, char *str);
		void putstr(uint8_t lcd_column, uint8_t lcd_row, double val);
		void putstr(uint8_t lcd_column, uint8_t lcd_row, double val, int precision);
		void puthex(uint8_t lcd_column, uint8_t lcd_row, int val);
		void putch_big(uint8_t lcd_column, uint8_t lcd_row, char val);
		void putstr_big(uint8_t lcd_column, uint8_t lcd_row, char *str);
		void putstr_big(uint8_t lcd_column, uint8_t lcd_row, double val);
		void putstr_big(uint8_t lcd_column, uint8_t lcd_row, double val, int precision);
};

#endif
