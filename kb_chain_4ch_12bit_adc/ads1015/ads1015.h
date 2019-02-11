#ifndef __ADS1015_H__
#define __ADS1015_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define ADS1015_POLLING_MS 1000

class ADS1015 : public Device {
	private:
		enum {
			 s_detect, 
			 s_read, 
			 s_error, 
			 s_wait
		} state;
		TickType_t tickcnt, polling_tickcnt;
		
		int16_t read_value = 0;
		uint8_t mux_ch = 0;
		uint8_t gain = 0;
		
		bool reConfig = true;

	public:
		// constructor
		ADS1015(int bus_ch, int dev_addr);
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
		int16_t getRawValue(uint8_t ch) ;
		void setGain(uint8_t gain) ;
		
		double readVoltage(uint8_t ch) ;
		
};

#endif
