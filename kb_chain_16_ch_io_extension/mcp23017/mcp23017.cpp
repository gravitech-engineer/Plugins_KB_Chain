#ifndef __MCP23017_CPP__
#define __MCP23017_CPP__

#include "MCP23017.h"

MCP23017::MCP23017(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = MCP23017_POLLING_MS;
}

void MCP23017::init(void) {
	// esp_log_level_set("*", ESP_LOG_INFO);
	
	readFlag = xEventGroupCreate();
	writeFlag = xEventGroupCreate();
	
	state = s_detect;
}

int MCP23017::prop_count(void) {
	return 0;
}

bool MCP23017::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool MCP23017::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool MCP23017::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool MCP23017::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool MCP23017::prop_write(int index, char *value) {
	// not supported
	return false;
}

void MCP23017::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {	
				// set initialized flag
				initialized = true;
					
				// clear error flag
				error = false;
				
				// Set all port to input
				port_mode = 0xFFFF;
				
				// set all bits in flag
				xEventGroupSetBits(writeFlag, 0xFFFF);
				
				// clear all bits in flag
				xEventGroupClearBits(readFlag, 0xFFFF);
				
				state = s_running;
			} else {
				state = s_error;
			}
			break;
		
		case s_running: {
			uint8_t data[3];
			
			uint16_t writeBits = xEventGroupGetBits(writeFlag);
			uint16_t readBits = xEventGroupGetBits(readFlag);
			
			if ((writeBits < 0xFFFF) || (readBits < 0xFFFF)) {
				data[0] = MCP23017_IODIRA;
				data[1] = port_mode & 0xFF;
				data[2] = port_mode >> 8;
				if (i2c->write(channel, address, data, 3) != ESP_OK) {
					state = s_error;
					break;
				}
			}
			
			
			if (writeBits < 0xFFFF) {
				data[0] = MCP23017_OLATA;
				data[1] = port_data & 0xFF;
				data[2] = port_data >> 8;
				if (i2c->write(channel, address, data, 3) == ESP_OK) {
					// set all bits in flag
					xEventGroupSetBits(writeFlag, 0xFFFF);
				} else {
					state = s_error;
					break;
				}
			}

			if (readBits < 0xFFFF) {
				uint8_t reg = MCP23017_GPIOA;
				if (i2c->read(channel, address, &reg, 1, data, 2) == ESP_OK) {
					port_data |= (data[1] << 8) | data[0];

					// set all bits in flag
					xEventGroupSetBits(readFlag, 0xFFFF);
				} else {
					state = s_error;
					break;
				}
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

void MCP23017::digitalWrite(uint8_t pin, uint8_t value) {
	port_mode &= ~(1<<pin); // Set to OUTPUT (0)
	if (value) {
		port_data |= (1<<pin);
	} else {
		port_data &= ~(1<<pin);
	}
	
	// Clear write flag to start write
	xEventGroupClearBits(writeFlag, 1<<pin);
	
	// Wait write flag set
	xEventGroupWaitBits(writeFlag, 1<<pin, false, true, 100 / portTICK_PERIOD_MS);
}

int MCP23017::digitalRead(uint8_t pin) {
	port_mode |= (1<<pin); // Set to INPUT (1)
	port_data &= ~(1<<pin);
	
	// Clear read flag to start read
	xEventGroupClearBits(readFlag, 1<<pin);
	
	// Wait read flag set
	xEventGroupWaitBits(readFlag, 1<<pin, false, true, 100 / portTICK_PERIOD_MS);
	
	return (port_data >> pin) & 0x01;
}

#endif
