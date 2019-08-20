#ifndef __VCNL4200_H__
#define __VCNL4200_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "kidbright32.h"

class VCNL4200 : public Device {
	private:		
		enum {
			s_detect,
			s_read,
			s_wait,
			s_error
		} state;
		TickType_t tickcnt, polling_tickcnt;
		
		uint16_t proximity = 0, ambient = 0;

	public:
		// constructor
		VCNL4200(int bus_ch, int dev_addr) ;
		
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
		int getProximity() ;
		int getAmbient() ;
		
		
};

#endif