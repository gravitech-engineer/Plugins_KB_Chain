#ifndef __VCNL4200_CPP__
#define __VCNL4200_CPP__

#include "vcnl4200.h"

VCNL4200::VCNL4200(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = 100;
}

void VCNL4200::init(void) {
	// clear error flag
	error = false;
	// set initialized flag
	initialized = true;
}

int VCNL4200::prop_count(void) {
	// not supported
	return 0;
}

bool VCNL4200::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool VCNL4200::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool VCNL4200::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool VCNL4200::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool VCNL4200::prop_write(int index, char *value) {
	// not supported
	return false;
}
// --------------------------------------

void VCNL4200::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				uint8_t dataBuff[3];
				
				//Write to PS_CONF1 and PS_CONF2 to set Proximity Sensor (PS) settings.
				dataBuff[0] = 0x03;
				dataBuff[1] = 0b00011010;
				dataBuff[2] = 0b00001000;
				i2c->write(channel, address, dataBuff, 3);
				
				//Write to ALS_CONF to turn Ambient Light Sensor (ALS) off.
				dataBuff[0] = 0x01;
				dataBuff[1] = 0b01000001;
				dataBuff[2] = 0b00000000;
				i2c->write(channel, address, dataBuff, 3);
				
				//Write to PS_THDL_L and PS_THDL_H to set Proxmitt Sensor (PS) Threshhold.
				dataBuff[0] = 0x6;
				dataBuff[1] = 0b00010000;
				dataBuff[2] = 0b00000000;
				i2c->write(channel, address, dataBuff, 3);
				
				//Write to PS_CONF3 and PS_MS to set Proximity Sensor (PS) settings.
				dataBuff[0] = 0x4;
				dataBuff[1] = 0b01110000;
				dataBuff[2] = 0b00000111;
				i2c->write(channel, address, dataBuff, 3);
				
				// clear error flag
				error = false;
				// set initialized flag
				initialized = true;

				// Go to main state
				state = s_read;
			} else {
				state = s_error;
			}
			break;
		
		case s_read: {
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				tickcnt = get_tickcnt();
				
				uint8_t reg = 0x08;
				uint8_t dataBuff[2];
				if (i2c->read(channel, address, &reg, 1, dataBuff, 2) == ESP_OK) {
					proximity = (dataBuff[1]<<8)|dataBuff[0];
				} else {
					proximity = 0;
					state = s_error;
				}
				/*
				reg = 0x09;
				if (i2c->read(channel, address, &reg, 1, dataBuff, 2) == ESP_OK) {
					ambient = (dataBuff[1]<<8)|dataBuff[0];
				} else {
					ambient = 0;
					state = s_error;
				}*/
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
int VCNL4200::getProximity() {
	return proximity;
}

int VCNL4200::getAmbient() {
	return ambient;
}

#endif