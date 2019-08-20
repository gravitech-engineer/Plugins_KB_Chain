#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "lcd_i2c.h"

// vTaskDelay(500 / portTICK_RATE_MS);

LCD_I2C::LCD_I2C(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
}

void LCD_I2C::init(void) {
	state = s_detect;
}

int LCD_I2C::prop_count(void) {
	// not supported
	return 0;
}

bool LCD_I2C::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool LCD_I2C::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool LCD_I2C::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool LCD_I2C::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool LCD_I2C::prop_write(int index, char *value) {
	// not supported
	return false;
}

void LCD_I2C::SEND(uint8_t data) {
	uint8_t dataSend;
	dataSend = (BLACKLIGHT ? BIT_BLACKLIGHT : 0) | (PIN_RS ? BIT_RS : 0) | data;
	i2c->write(channel, address, &dataSend, 1);
	vTaskDelay(1 / portTICK_RATE_MS);
	dataSend = BIT_EN | (BLACKLIGHT ? BIT_BLACKLIGHT : 0) | (PIN_RS ? BIT_RS : 0) | data;
	i2c->write(channel, address, &dataSend, 1);
	vTaskDelay(1 / portTICK_RATE_MS);
	dataSend = (BLACKLIGHT ? BIT_BLACKLIGHT : 0) | (PIN_RS ? BIT_RS : 0) | data;
	i2c->write(channel, address, &dataSend, 1);
	vTaskDelay(1 / portTICK_RATE_MS);
}

void LCD_I2C::CMD(uint8_t data) {
	PIN_RS = false;
	SEND(data&0xF0);
	SEND((data<<4)&0xF0);
	PIN_RS = true;
}

void LCD_I2C::backlight(int val) {
	BLACKLIGHT = val ? true : false;
	CMD(0);
}

int LCD_I2C::backlight(void) {
	return BLACKLIGHT;
}

void LCD_I2C::clear(void) {
	CMD(0x01);
}

void LCD_I2C::process(Driver *drv) {
	i2c = (I2CDev *)drv;

	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				for (int i=0;i<3;i++)
					SEND(0x30);
				for (int i=0;i<2;i++)
					SEND(0x20);
				SEND(0x10);
				SEND(0);
					
				SEND(0x08 | (BLINK ? BIT_BLINK : 0) | (CURSOR ? BIT_CURSOR : 0) | (sDISPLAY ? BIT_DISPLAY : 0));
				CMD(0x28);

				clear();
				
				tickcnt = get_tickcnt();
				
				error = false;
				initialized = true;
				state = s_idle;
			} else {
				state = s_error;
			}
			break;

		case s_idle:
			if (is_tickcnt_elapsed(tickcnt, 1000)) {
				tickcnt = get_tickcnt();
				if (i2c->detect(channel, address) != ESP_OK) {
					state = s_error;
				}
			}
			break;

		case s_error:
			// set error flag
			error = true;
			// clear initialized flag
			initialized = false;
			// get current tickcnt
			tickcnt = get_tickcnt();
			// goto wait and retry with detect state
			state = s_wait;
			break;

		case s_wait:
			// delay 1000ms before retry detect
			if (is_tickcnt_elapsed(tickcnt, 1000)) {
				state = s_detect;
			}
			break;
	}
}

void LCD_I2C::setCursor(int x, int y) {
	uint8_t toCode[] = { 0x80, 0xC0, 0x94, 0xD4 };
	CMD(toCode[y] + x);
}

void LCD_I2C::write(char data) {
	PIN_RS = true;
	SEND(data&0xF0);
	SEND((data<<4)&0xF0);
}

void LCD_I2C::print(uint8_t lcd_column, uint8_t lcd_row, char *buf) {
	setCursor(lcd_column, lcd_row);
	
	int len = strlen(buf);
	for (int i=0;i<len;i++) {
		write(buf[i]);
	}
}

void LCD_I2C::print(uint8_t lcd_column, uint8_t lcd_row, double val) {
	char buf[LCD_MAX_COLUMN + 1];
	int i;

	snprintf(buf, LCD_MAX_COLUMN, "%.2f", val); // default precision = 2
	// check ending zero
	i = strlen(buf) - 1;
	while (i >= 0) {
		if (buf[i] == '0') {
			buf[i] = '\x0';
		}
		else
		if (buf[i] == '.') {
			buf[i] = '\x0';
			break;
		}
		else {
			break; // first occurence of non-zero or dot
		}
		i--;
	}

	print(lcd_column, lcd_row, buf);
}

void LCD_I2C::print(uint8_t lcd_column, uint8_t lcd_row, double val, int precision) {
	char fmt[8];
	char buf[LCD_MAX_COLUMN + 1];

	if (precision < 0) {
		strcpy(fmt, "%.0f");
	}
	else
	if (precision > 6) {
		strcpy(fmt, "%.6f");
	}
	else {
		snprintf(fmt, sizeof(fmt) - 1, "%%.%df", precision);
	}

	snprintf(buf, LCD_MAX_COLUMN, fmt, val);
	print(lcd_column, lcd_row, buf);
}
