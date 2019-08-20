#ifndef __MPL3115A2_H__
#define __MPL3115A2_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "kidbright32.h"

class MPL3115A2 : public Device {
	private:		
		enum {
			s_detect,
			s_change_mode,
			s_read,
			s_wait,
			s_error
		} state;
		TickType_t tickcnt, polling_tickcnt;
		
		uint8_t mode = 1; // 0: barometer mode, 1: altimeter mode
		uint32_t pressure = 0, alt = 0;
		float temp = 0;

	public:
		// constructor
		MPL3115A2(int bus_ch, int dev_addr) ;
		
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
		void setMode(uint8_t mode) ;
		float getPressure() ;
		float getAltitude() ;
		float getTemperature() ;
		
		
		
};

#endif