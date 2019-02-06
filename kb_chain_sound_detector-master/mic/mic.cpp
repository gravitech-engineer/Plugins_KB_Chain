#ifndef __MIC_CPP__
#define __MIC_CPP__

#include "MIC.h"

MIC::MIC(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = MIC_POLLING_MS;
}

void MIC::init(void) {
	// esp_log_level_set("*", ESP_LOG_INFO);
	
	// Set new timeout of i2c
	i2c_set_timeout(I2C_NUM_1, 12800);
	
	state = s_detect;
}

int MIC::prop_count(void) {
	return 0;
}

bool MIC::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool MIC::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool MIC::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool MIC::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool MIC::prop_write(int index, char *value) {
	// not supported
	return false;
}

void MIC::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {	
				// set initialized flag
				initialized = true;
					
				// clear error flag
				error = false;
				
				state = s_read;
			} else {
				state = s_error;
			}
			break;
		
		case s_read: {
			uint8_t reg = 0xA1;
			uint8_t dataRead[2];
			esp_err_t err = i2c->read(channel, address, &reg, 1, dataRead, 2);
			if (err == ESP_OK) {
				// ESP_LOGI("MIC", "OK !");
				sound_value = dataRead[0] << 8 | dataRead[1];
			} else {
				// ESP_LOGI("MIC", "Error code: %d", err);
				state = s_error;
			}
			break;
		}

		case s_error:
			// clear value
			sound_value = 0;
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

uint16_t MIC::getRawValue() {
	return sound_value;
}

#endif
