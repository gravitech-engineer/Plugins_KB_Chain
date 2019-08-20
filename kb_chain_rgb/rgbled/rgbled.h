#ifndef __RGBLED_H__
#define __RGBLED_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "kidbright32.h"

class RGBLED : public Device {
	private:		
		enum {
			s_detect,
			s_read,
			s_wait,
			s_error
		} state;
		TickType_t tickcnt, polling_tickcnt;
		I2CDev *i2c;
		
		uint32_t colors[4];

	public:
		// constructor
		RGBLED(int bus_ch, int dev_addr) ;
		
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
		void setColor(uint8_t i, uint32_t c) ;
		void setColor(uint8_t i, uint8_t r, uint8_t g, uint8_t b) ;
		void updataColor();
		
};

#endif