#ifndef __MPL3115A2_CPP__
#define __MPL3115A2_CPP__

#include "mpl3115a2.h"

MPL3115A2::MPL3115A2(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = 100;
}

void MPL3115A2::init(void) {
	// clear error flag
	error = true;
	// set initialized flag
	initialized = false;
	
	state = s_detect;
}

int MPL3115A2::prop_count(void) {
	// not supported
	return 0;
}

bool MPL3115A2::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool MPL3115A2::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool MPL3115A2::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool MPL3115A2::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool MPL3115A2::prop_write(int index, char *value) {
	// not supported
	return false;
}
// --------------------------------------

void MPL3115A2::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				uint8_t dataBuff[2];
				
				// Set to Altimeter with an OSR = 128
				dataBuff[0] = 0x26;
				dataBuff[1] = 0xB8;
				i2c->write(channel, address, dataBuff, 2);
				
				// Enable Data Flags in PT_DATA_CFG
				dataBuff[0] = 0x13;
				dataBuff[1] = 0x07;
				i2c->write(channel, address, dataBuff, 2);

				state = s_change_mode;
			} else {
				state = s_error;
			}
			break;
		
		case s_change_mode: {
			uint8_t dataBuff[2];
			
			// Set Active
			dataBuff[0] = 0x26;
			dataBuff[1] = 0x39 | (mode<<7);
			i2c->write(channel, address, dataBuff, 2);
			
			// clear error flag
			error = false;
			// set initialized flag
			initialized = true;
			
			// Go to main state
			state = s_read;
		}
		
		case s_read: {
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				tickcnt = get_tickcnt();
				
				uint8_t reg = 0x00;
				uint8_t data;
				if (i2c->read(channel, address, &reg, 1, &data, 1) == ESP_OK) {
					if ((data&0x08) != 0) {
						reg = 0x01;
						uint8_t dataBuff[5];
						if (i2c->read(channel, address, &reg, 1, dataBuff, 5) == ESP_OK) {
							if (mode == 0) {
								pressure = dataBuff[0]; // OUT_P_MSB
								pressure <<= 8;
								pressure |= dataBuff[1]; // OUT_P_CSB
								pressure <<= 8;
								pressure |= dataBuff[2]; // OUT_P_LSB
								pressure >>= 4;
							} else {
								alt = ((uint32_t)dataBuff[0]) << 24;  // receive DATA
								alt |= ((uint32_t)dataBuff[1]) << 16; // receive DATA
								alt |= ((uint32_t)dataBuff[2]) << 8;  // receive DATA
							}
							
							int16_t t;
							t = dataBuff[3]; // OUT_T_MSB
							t <<= 8;
							t |= dataBuff[4]; // OUT_T_LSB
							t >>= 4;

							if (t & 0x800) {
								t |= 0xF000;
							}
							temp = t;
							temp /= 16.0;
						} else {
							state = s_error;
						}
					}
				} else {
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
			pressure = 9999;
			alt = 9999;
			temp = 9999;
			
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
void MPL3115A2::setMode(uint8_t mode) {
	this->mode = (mode&0x01);
	state = s_change_mode;
}

float MPL3115A2::getPressure() {
	if ((mode != 0) || (pressure == 9999)) {
		return 9999;
	}
	float baro = pressure;
	baro /= 4.0;
	return baro;
}

float MPL3115A2::getAltitude() {
	if ((mode != 1) || (alt == 9999)) {
		return 9999;
	}
	float altitude = alt;
	altitude /= 65536.0;
	return altitude;
}
float MPL3115A2::getTemperature() {
	return temp;
}

#endif