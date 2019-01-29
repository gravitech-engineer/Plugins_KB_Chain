#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "VEML6075.h"

VEML6075::VEML6075(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = VEML6075_POLLING_MS;
}

void VEML6075::init(void) {
	/* Config
		[6-4 UV_IT]: 001 -> 100mS
		[3 HD]: ->   0   -> normal dynamic setting
		[2 UV_TRIG]: 1   -> trigger one measurement
		[1 UV_AF]:   0   -> active force mode disable (normal mode)
		[0 SD]:      0   -> power on
	*/
	uv_conf_data.reg = VEML6075_REG_UV_CONF;
	uv_conf_data.block[1] = (0b0010100);
	uv_conf_data.block[2] = 0;
	
	_uva_a = VEML6075_DEFAULT_UVA_A_COEFF;
	_uva_b = VEML6075_DEFAULT_UVA_B_COEFF;
	_uvb_c = VEML6075_DEFAULT_UVB_C_COEFF;
	_uvb_d = VEML6075_DEFAULT_UVB_D_COEFF;
	_uva_resp = VEML6075_DEFAULT_UVA_RESPONSE;
	_uvb_resp = VEML6075_DEFAULT_UVB_RESPONSE;

	state = s_detect;
}

int VEML6075::prop_count(void) {
	return 0;
}

bool VEML6075::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool VEML6075::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool VEML6075::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool VEML6075::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool VEML6075::prop_write(int index, char *value) {
	// not supported
	return false;
}

void VEML6075::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	
	switch (state) {
		case s_detect:
			// stamp polling tickcnt
			polling_tickcnt = get_tickcnt();
			
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				state = s_write;
			} else {
				state = s_error;
			}
			break;
		
		case s_write:
			if (i2c->write(channel, address, uv_conf_data.block, sizeof uv_conf_data.block) == ESP_OK) {
				// clear error flag
				error = false;
				
				// get current tickcnt
				tickcnt = get_tickcnt();
				
				state = s_read;
			} else {
				state = s_error;
			}
			break;
			
		case s_read:
			// read delay for 110ms
			if (is_tickcnt_elapsed(tickcnt, 110)) {
				uint8_t reg[1];
				uint8_t data[2];
				
				// Read  UVA Data
				reg[0] = VEML6075_REG_UVA_Data;
				if (i2c->read(channel, address, reg, sizeof reg, data, 2) != ESP_OK) {
					state = s_error;
					break;
				}
				float uva = (uint16_t)(data[0]|(((uint16_t)data[1])<<8));
				
				// Read  UVB Data
				reg[0] = VEML6075_REG_UVB_Data;
				if (i2c->read(channel, address, reg, sizeof reg, data, 2) != ESP_OK) {
					state = s_error;
					break;
				}
				float uvb = (uint16_t)(data[0]|(((uint16_t)data[1])<<8));
				
				// Read UVCOMP1 Data
				reg[0] = VEML6075_REG_UVCOMP1_Data;
				if (i2c->read(channel, address, reg, sizeof reg, data, 2) != ESP_OK) {
					state = s_error;
					break;
				}
				float uvcomp1 = (uint16_t)(data[0]|(((uint16_t)data[1])<<8));
				
				// Read UVCOMP2 Data
				reg[0] = VEML6075_REG_UVCOMP2_Data;
				if (i2c->read(channel, address, reg, sizeof reg, data, 2) != ESP_OK) {
					state = s_error;
					break;
				}
				float uvcomp2 = (uint16_t)(data[0]|(((uint16_t)data[1])<<8));
				
				// Data process
				_uva_calc = uva - (_uva_a * uvcomp1) - (_uva_b * uvcomp2);
				_uvb_calc = uvb - (_uvb_c * uvcomp1) - (_uvb_d * uvcomp2);
				
				// set initialized flag
				initialized = true;

				// load polling tickcnt
				tickcnt = polling_tickcnt;
				
				// goto wait and retry with detect state
				state = s_wait_next_time;
			}
			break;
			
		case s_wait_next_time: {
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_write;
			}
			break;
		}

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

double VEML6075::get_uva() {
	return _uva_calc;
}

double VEML6075::get_uvb() {
	return _uvb_calc;
}

double VEML6075::get_uvi() {
	return ((_uva_calc * _uva_resp) + (_uvb_calc * _uvb_resp)) / 2;
}
