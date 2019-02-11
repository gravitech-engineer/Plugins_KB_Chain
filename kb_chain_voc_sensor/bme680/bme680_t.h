#ifndef __BME680_H__
#define __BME680_H__

#include "math.h"
#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "esp_log.h"

#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"

#include "bme680.h"

#define BME680_POLLING_MS 500

static int8_t bme680_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) ;
static int8_t bme680_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) ;
static void bme680_delay_ms(uint32_t period) ;

class BME680 : public Device {
	private:
		enum {
			s_detect, 
			s_trigger, 
			s_read, 
			s_error, 
			s_wait
		} state;
		TickType_t tickcnt;
		
		struct bme680_dev gas_sensor;
		uint8_t set_required_settings;
		uint16_t meas_period;
		struct bme680_field_data bme680_data;

	public:
		// constructor
		BME680(int bus_ch, int dev_addr);
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
		double getTemperature() ;
		double getPressure() ;
		double getHumidity() ;
		double getGasResistance() ;
		double getAltitude() ;
		
};

#endif
