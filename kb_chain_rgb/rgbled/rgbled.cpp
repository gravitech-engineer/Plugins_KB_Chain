#ifndef __RGBLED_CPP__
#define __RGBLED_CPP__

#include "rgbled.h"

RGBLED::RGBLED(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = 100;
}

void RGBLED::init(void) {
	// clear error flag
	error = true;
	// set initialized flag
	initialized = false;
	
	// Set new timeout of i2c
	i2c_set_timeout(I2C_NUM_1, 100E3);
	
	state = s_detect;
}

int RGBLED::prop_count(void) {
	// not supported
	return 0;
}

bool RGBLED::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool RGBLED::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool RGBLED::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool RGBLED::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool RGBLED::prop_write(int index, char *value) {
	// not supported
	return false;
}
// --------------------------------------

void RGBLED::process(Driver *drv) {
	i2c = (I2CDev *)drv;
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				tickcnt = get_tickcnt();
				state = s_read;
			} else {
				state = s_error;
			}
			break;
		
		case s_read: {
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				tickcnt = get_tickcnt();
				
				if (i2c->detect(channel, address) != ESP_OK) {
					state = s_error;
				}
			}
		}
		
		case s_wait:
			if (error) {
				// wait polling_ms timeout
				if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
					state = s_detect;
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

	}
}

// Method
void RGBLED::setColor(uint8_t i, uint32_t c) {
	colors[i - 1] = c;
	updataColor();
}

void RGBLED::setColor(uint8_t i, uint8_t r, uint8_t g, uint8_t b) {
	colors[i - 1] = ((uint32_t)r<<16)|((uint32_t)g<<8)|(uint32_t)b;
	updataColor();
}

void RGBLED::updataColor() {
	uint8_t buffSize = (4 * 3) + 1;
	uint8_t buff[buffSize];
	buff[0] = 0x02;
	uint8_t a = 1;
	for (int i=0;i<4;i++) {
		buff[a++] = (colors[i]>>16)&0xFF;
		buff[a++] = (colors[i]>>8)&0xFF;
		buff[a++] = (colors[i])&0xFF;
	}
	i2c->write(channel, address, buff, buffSize);
}

#endif