#ifndef __ADS1015_CPP__
#define __ADS1015_CPP__

#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "ADS1015.h"
#include "esp_log.h"

ADS1015::ADS1015(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = ADS1015_POLLING_MS;
}

void ADS1015::init(void) {
	mux_ch = 4; // ANA0
	gain = 0; // ±6.144V
	
	// esp_log_level_set("*", ESP_LOG_INFO);
	
	state = s_detect;
}

int ADS1015::prop_count(void) {
	return 0;
}

bool ADS1015::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool ADS1015::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool ADS1015::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool ADS1015::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool ADS1015::prop_write(int index, char *value) {
	// not supported
	return false;
}

void ADS1015::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				// set initialized flag
				initialized = true;
				
				// clear error flag
				error = false;
				
				// set reConfig flag
				reConfig = true;
				
				state = s_read;
			} else {
				state = s_error;
			}
			break;

		case s_read: {
			if (reConfig) {
				uint8_t data[3] = { 0x01, 0, 0};
				
				// MSB
				data[1] |= 0b0    << 7; // Operational status or single-shot conversion start
				data[1] |= mux_ch << 4; // Input multiplexer configuration
				data[1] |= gain   << 1; // Programmable gain amplifier configuration
				data[1] |= 0b0    << 0; // Continuous-conversion mode
				
				data[2] |= 0b100 << 5; // Data rate = 1600 SPS
				data[2] |= 0b0   << 4; // Comparator mode
				data[2] |= 0b0   << 3; // Comparator polarity
				data[2] |= 0b0   << 2; // Latching comparator
				data[2] |= 0b11  << 0; // Comparator queue and disable
				// LSB
				
				if (i2c->write(channel, address, data, 3) != ESP_OK) {
					state = s_error;
				}
				
				// get current tickcnt
				tickcnt = get_tickcnt();
				
				// clear reConfig flag
				reConfig = false;
				break;
			}
			
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, 10)) {
				// get current tickcnt
				tickcnt = get_tickcnt();
			
				uint8_t reg = 0x00; // Conversion Register
				uint8_t buff[2];
				if (i2c->read(channel, address, &reg, 1, buff, 2) == ESP_OK) {
					uint16_t res = (buff[0]<<8) | buff[1];
					res = res >> 4;
					if ((mux_ch >= 0) && (mux_ch <= 3)) {
						if (res > 0x07FF) { // negative number - extend the sign to 16th bit
							res |= 0xF000;
						}
						read_value = (int16_t)res;
					} else {
						read_value = (uint16_t)res;
					}
				} else{
					state = s_error;
				}
			}

			break;
		}
		
		case s_wait:
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_detect;
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

int16_t ADS1015::getRawValue(uint8_t ch) {
	if (mux_ch != ch) {
		mux_ch = ch;
		
		reConfig = true;
		return 0;
	}
	
	return read_value;
}

void ADS1015::setGain(uint8_t gain) {
	this->gain = gain;
	reConfig = true;
}

double ADS1015::readVoltage(uint8_t ch) {
	float gainToVolt = 6.144;
	switch (this->gain) {
		case 0:
			gainToVolt = 6.144;
			break;
		
		case 1:
			gainToVolt = 4.096;
			break;
		
		case 2:
			gainToVolt = 2.048;
			break;
		
		case 3:
			gainToVolt = 1.024;
			break;
		
		case 4:
			gainToVolt = 0.512;
			break;
		
		case 5:
			gainToVolt = 0.256;
			break;
		
	}

	return getRawValue(ch) * gainToVolt / 2047;
}

#endif
