#ifndef __BH1745NUC_H__
#define __BH1745NUC_H__

#include "math.h"
#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define BH1745NUC_POLLING_MS 500

class BH1745NUC : public Device {
	private:
		enum {
			s_detect, 
			s_read, 
			s_error, 
			s_wait
		} state;
		TickType_t tickcnt, polling_tickcnt;
		
		uint16_t _raw_red, _raw_green, _raw_blue, _raw_clear;
		
		bool write_reg(I2CDev *i2c, uint8_t reg, uint8_t data) ;
		bool validID(I2CDev *i2c) ;
		bool config(I2CDev *i2c) ;
		bool readRawData(I2CDev *i2c) ;

	public:
		// constructor
		BH1745NUC(int bus_ch, int dev_addr);
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
		uint16_t getRawColor(uint8_t color) ;
		
};

#endif
