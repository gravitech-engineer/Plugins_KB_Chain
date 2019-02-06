#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "BH1745NUC.h"

BH1745NUC::BH1745NUC(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = BH1745NUC_POLLING_MS;
}

void BH1745NUC::init(void) {
	state = s_detect;
}

int BH1745NUC::prop_count(void) {
	return 0;
}

bool BH1745NUC::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool BH1745NUC::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool BH1745NUC::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool BH1745NUC::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool BH1745NUC::prop_write(int index, char *value) {
	// not supported
	return false;
}

void BH1745NUC::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	
	switch (state) {
		case s_detect:
			// stamp polling tickcnt
			polling_tickcnt = get_tickcnt();
			
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {	
				if (validID(i2c)) {
					if (config(i2c)) {
						state = s_read;
					} else {
						state = s_error;
					}
				} else {
					state = s_error;
				}
			} else {
				state = s_error;
			}
			break;
		
		case s_read:
			if (!readRawData(i2c)) {
				state = s_error;
			}
			
			// set initialized flag
			initialized = true;
				
			// clear error flag
			error = false;
			
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
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_detect;
			}
			break;
	}
}

bool BH1745NUC::write_reg(I2CDev *i2c, uint8_t reg, uint8_t data) {
	uint8_t writeData[] = { reg, data };
	return i2c->write(channel, address, writeData, 2) == ESP_OK;
}

bool BH1745NUC::validID(I2CDev *i2c) {
	uint8_t reg = 0x40;
	uint8_t PartID = 0;
	if (i2c->read(channel, address, &reg, 1, &PartID, 1) != ESP_OK) {
		return false;
	}
	
	return (PartID&0x3F) == 0b001011;
}

bool BH1745NUC::config(I2CDev *i2c) {
	// MODE_CONTROL1 : Measurement time = 160mS
	if (!write_reg(i2c, 0x41, 0)) return false;
	
	// MODE_CONTROL2 : GAIN = 1X, RGBC_EN = 1
	if (!write_reg(i2c, 0x42, 0b00010000)) return false;
	
	// MODE_CONTROL3 : Fix 0x02
	if (!write_reg(i2c, 0x44, 0x02)) return false;
	
	return true;
}

bool BH1745NUC::readRawData(I2CDev *i2c) {
	uint8_t reg = 0x50; // Set offset to RED_DATA_LSBs
	uint8_t dataBuffer[8];
	memset(dataBuffer, 0, 8);
	
	if (i2c->read(channel, address, &reg, 1, dataBuffer, 8) != ESP_OK) {
		return false;
	}
	
	_raw_red   = uint16_t(dataBuffer[1] << 8)|(uint16_t)dataBuffer[0];
	_raw_green = uint16_t(dataBuffer[3] << 8)|(uint16_t)dataBuffer[2];
	_raw_blue  = uint16_t(dataBuffer[5] << 8)|(uint16_t)dataBuffer[4];
	_raw_clear = uint16_t(dataBuffer[7] << 8)|(uint16_t)dataBuffer[6];
	
	return true;
}

uint16_t BH1745NUC::getRawColor(uint8_t color) {
	if (color == 1) {
		return _raw_red * 1.39;
	} else if (color == 2) {
		return _raw_green;
	} else if (color == 3) {
		return _raw_blue * 1.79;
	}
	
	return 0;
}
