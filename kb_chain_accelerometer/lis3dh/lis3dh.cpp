#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "LIS3DH.h"

LIS3DH::LIS3DH(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = LIS3DH_POLLING_MS;
}

void LIS3DH::init(void) {
	getConfigData(); // gen data config
	_read_adc_flag = false; // Not use ADC
	
	state = s_detect;
}

int LIS3DH::prop_count(void) {
	return 0;
}

bool LIS3DH::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool LIS3DH::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool LIS3DH::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool LIS3DH::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool LIS3DH::prop_write(int index, char *value) {
	// not supported
	return false;
}

void LIS3DH::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	
	switch (state) {
		case s_detect:
			// stamp polling tickcnt
			polling_tickcnt = get_tickcnt();
			
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {	
				for (int inx=0;inx<configSize;inx++) {
					if (i2c->write(channel, address, config[inx].block, 2) != ESP_OK) {
						state = s_error;
						break;
					}
					configSize--;
				}
				if (state == s_error) {
					break;
				}
				
				// set initialized flag
				initialized = true;
				
				// clear error flag
				error = false;
				
				state = s_read;
			} else {
				state = s_error;
			}
			break;
		
		case s_read:
			if (!readRawData(i2c)) {
				state = s_error;
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
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_detect;
			}
			break;
	}
}

void LIS3DH::getConfigData() {
	/* ----> TEMP_CFG_REG <----
	 * [7 ADC_EN]:    1 -> ADC enabled
	 * [6 TEMP_EN]:   0 -> T disabled
	 * [0-5 reverse]: 0
	 */
	config[0].reg = 0x1F;
	config[0].data = 0b10000000; 
	
	/* ----> CTRL_REG1 <----
	 * [4-7 ODR]:  0100 -> HR / Normal / Low-power mode (50 Hz)
	 * [3 LPen]:      0 -> high-resolution mode / normal mode
	 * [2 Zen]:       1 -> Z-axis enabled
	 * [1 Yen]:       1 -> Y-axis enabled
	 * [0 Xen]:       1 -> X-axis enabled
	 */
	config[1].reg = 0x20;
	config[1].data = 0b01000111;

	/* ----> CTRL_REG4 <----
	 * [7 BDU]:     0 -> continuous update
	 * [6 BLE]:     0 -> Data LSB @ lower address
	 * [4-5 FS]:   00 -> +-2 g
	 * [3 HR]:      1 -> high-resolution enabled
	 * [1-2 ST]:    1 -> Y-axis enabled
	 * [0 SIM]:     0 -> 4-wire interface (Not use)
	 */
	config[2].reg = 0x23;
	config[2].data = 0b0000110;
	
	// OK, now ready to read data
	
	configSize = 3;
}

bool LIS3DH::readRawData(I2CDev *i2c) {
	uint8_t reg[1] = { 0x28 | 0x80 }; // OUT_X_L | auto-increment bit
	uint8_t dataBuffer[6];
	memset(dataBuffer, 0, sizeof dataBuffer);
	
	if (i2c->read(channel, address, reg, sizeof reg, dataBuffer, 6) != ESP_OK) {
		return false;
	}
	
	_raw_x = int16_t(dataBuffer[1] << 8)|(int16_t)dataBuffer[0];
	_raw_y = int16_t(dataBuffer[3] << 8)|(int16_t)dataBuffer[2];
	_raw_z = int16_t(dataBuffer[5] << 8)|(int16_t)dataBuffer[4];
	
	// cal
	_axis_x = (float)_raw_x / 15987.0 * 1000.0; // to milli-g
	_axis_y = (float)_raw_y / 15987.0 * 1000.0; // to milli-g
	_axis_z = (float)_raw_z / 15987.0 * 1000.0; // to milli-g
	
	if (_read_adc_flag) {
		reg[0] = 0x08 | 0x80; // OUT_ADC1_L | auto-increment bit
		if (i2c->read(channel, address, reg, sizeof reg, dataBuffer, 6) != ESP_OK) {
			return false;
		}
		
		int16_t adc1 = int16_t(dataBuffer[1] << 8)|(int16_t)dataBuffer[0];
		int16_t adc2 = int16_t(dataBuffer[3] << 8)|(int16_t)dataBuffer[2];
		int16_t adc3 = int16_t(dataBuffer[5] << 8)|(int16_t)dataBuffer[4];
		
		adc1 = 0 - adc1;
		adc2 = 0 - adc2;
		adc3 = 0 - adc3;
		
		_adc1 = (adc1 + 32768)>>6;
		_adc2 = (adc2 + 32768)>>6;
		_adc3 = (adc3 + 32768)>>6;
	}
	
	return true;
}

float LIS3DH::get_acceleration(uint8_t axis) {
	if (axis == 1) return _axis_x;
	if (axis == 2) return _axis_y;
	if (axis == 3) return _axis_z;
	if (axis == 4) {
		float strength3D = 0;
		strength3D = sqrt((_axis_x * _axis_x) + (_axis_y * _axis_y) + (_axis_z * _axis_z));
		return strength3D;
	}
	
	return 0;
}

uint16_t LIS3DH::get_adc(uint8_t ch) {
	_read_adc_flag = true;
	
	if (ch == 1) return _adc1;
	if (ch == 2) return _adc2;
	if (ch == 3) return _adc3;
	
	return 0;
}
