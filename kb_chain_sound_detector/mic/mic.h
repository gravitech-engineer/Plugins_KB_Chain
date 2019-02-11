#ifndef __MIC_H__
#define __MIC_H__

#include "math.h"
#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "esp_log.h"

#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"

#define MIC_POLLING_MS 500

class MIC : public Device {
	private:
		enum {
			s_detect, 
			s_read, 
			s_error, 
			s_wait
		} state;
		TickType_t tickcnt;
		
		uint16_t sound_value = 0;

	public:
		// constructor
		MIC(int bus_ch, int dev_addr);
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
		uint16_t getRawValue() ;
		
};

#endif
