#ifndef __LIS3DH_H__
#define __LIS3DH_H__

#include "math.h"
#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define LIS3DH_POLLING_MS 500

class LIS3DH : public Device {
	private:
		enum {
			s_detect, 
			s_read, 
			s_error, 
			s_wait
		} state;
		TickType_t tickcnt, polling_tickcnt;
		
		int16_t _raw_x, _raw_y, _raw_z;
		float _axis_x, _axis_y, _axis_z;
		
		typedef union {
			uint8_t block[2];
			struct {
				uint8_t reg;
				uint8_t data;
			};
		} Reg; 
		
		Reg config[5];
		int configSize = 0;
		
		bool _read_adc_flag;
		uint16_t _adc1, _adc2, _adc3;
		
		void getConfigData() ;
		bool readRawData(I2CDev *i2c) ;


	public:
		// constructor
		LIS3DH(int bus_ch, int dev_addr);
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
		float get_acceleration(uint8_t axis) ;
		uint16_t get_adc(uint8_t ch) ;
		
};

#endif
