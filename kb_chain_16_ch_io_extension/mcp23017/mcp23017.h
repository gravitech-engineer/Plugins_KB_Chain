#ifndef __MCP23017_H__
#define __MCP23017_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/event_groups.h"
#include "kidbright32.h"

#define MCP23017_POLLING_MS 100

// registers
#define MCP23017_IODIRA   0x00
#define MCP23017_IODIRB   0x01

#define MCP23017_GPIOA    0x12
#define MCP23017_GPIOB    0x13

#define MCP23017_OLATA    0x14
#define MCP23017_OLATB    0x15


class MCP23017 : public Device {
	private:
		enum {
			s_detect, 
			s_running, 
			s_error, 
			s_wait
		} state;
		TickType_t tickcnt;
		
		// flag group
		EventGroupHandle_t readFlag = NULL, writeFlag = NULL;
		uint16_t port_mode, port_data;

	public:
		// constructor
		MCP23017(int bus_ch, int dev_addr);
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		
		// method
		void digitalWrite(uint8_t pin, uint8_t value) ;
		int digitalRead(uint8_t pin) ;
		
};

#endif
