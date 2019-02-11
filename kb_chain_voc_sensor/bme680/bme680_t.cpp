#ifndef __BME680_CPP__
#define __BME680_CPP__

#include "BME680_t.h"

static I2CDev *BME680_i2c = NULL;

int8_t bme680_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

    /*
     * The parameter dev_id can be used as a variable to store the I2C address of the device
     */

    /*
     * Data on the bus should be like
     * |------------+---------------------|
     * | I2C action | Data                |
     * |------------+---------------------|
     * | Start      | -                   |
     * | Write      | (reg_addr)          |
     * | Stop       | -                   |
     * | Start      | -                   |
     * | Read       | (reg_data[0])       |
     * | Read       | (....)              |
     * | Read       | (reg_data[len - 1]) |
     * | Stop       | -                   |
     * |------------+---------------------|
     */
	 
	if (BME680_i2c) {
		rslt = BME680_i2c->read(0, dev_id, &reg_addr, 1, reg_data, len);
	}

    return rslt;
}

int8_t bme680_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

    /*
     * The parameter dev_id can be used as a variable to store the I2C address of the device
     */

    /*
     * Data on the bus should be like
     * |------------+---------------------|
     * | I2C action | Data                |
     * |------------+---------------------|
     * | Start      | -                   |
     * | Write      | (reg_addr)          |
     * | Write      | (reg_data[0])       |
     * | Write      | (....)              |
     * | Write      | (reg_data[len - 1]) |
     * | Stop       | -                   |
     * |------------+---------------------|
     */
	 
	if (BME680_i2c) {
		uint8_t buff[1 + len];
		buff[0] = reg_addr;
		memcpy(&buff[1], reg_data, len);
		rslt = BME680_i2c->write(0, dev_id, buff, sizeof buff);
	}

    return rslt;
}

void bme680_delay_ms(uint32_t period) {
    /*
     * Return control or wait,
     * for a period amount of milliseconds
     */
	 
	vTaskDelay(period / portTICK_RATE_MS);
}

BME680::BME680(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = BME680_POLLING_MS;
}

void BME680::init(void) {
	// esp_log_level_set("*", ESP_LOG_INFO);
	
	/* Setting I2C */
	gas_sensor.dev_id = address;
	gas_sensor.intf = BME680_I2C_INTF;
	gas_sensor.read = bme680_i2c_read;
	gas_sensor.write = bme680_i2c_write;
	gas_sensor.delay_ms = bme680_delay_ms;
	
	/* Set the temperature, pressure and humidity settings */
	gas_sensor.tph_sett.os_hum = BME680_OS_2X;
	gas_sensor.tph_sett.os_pres = BME680_OS_4X;
	gas_sensor.tph_sett.os_temp = BME680_OS_8X;
	gas_sensor.tph_sett.filter = BME680_FILTER_SIZE_3;

	/* Set the remaining gas sensor settings and link the heating profile */
	gas_sensor.gas_sett.run_gas = BME680_ENABLE_GAS_MEAS;
	/* Create a ramp heat waveform in 3 steps */
	gas_sensor.gas_sett.heatr_temp = 320; /* degree Celsius */
	gas_sensor.gas_sett.heatr_dur = 150; /* milliseconds */

	/* Select the power mode */
	/* Must be set before writing the sensor configuration */
	gas_sensor.power_mode = BME680_FORCED_MODE; 

	/* Set the required sensor settings needed */
	set_required_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL 
        | BME680_GAS_SENSOR_SEL;
	
	state = s_detect;
}

int BME680::prop_count(void) {
	return 0;
}

bool BME680::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool BME680::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool BME680::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool BME680::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool BME680::prop_write(int index, char *value) {
	// not supported
	return false;
}

void BME680::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	BME680_i2c = i2c;
	
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {	
				if (bme680_init(&gas_sensor) == BME680_OK) {
					if (bme680_set_sensor_settings(set_required_settings,&gas_sensor) == BME680_OK) {
						// set initialized flag
						initialized = true;	
						// clear error flag
						error = false;
						
						state = s_trigger;
					} else {
						state = s_error;
					}
				} else {
					state = s_error;
				}
			} else {
				state = s_error;
			}
			break;
		
		case s_trigger: 
			if (bme680_set_sensor_mode(&gas_sensor) == BME680_OK) {
				bme680_get_profile_dur(&meas_period, &gas_sensor);
				
				// get current tickcnt
				tickcnt = get_tickcnt();
				
				state = s_read;
			} else {
				state = s_error;
			}
			break;
			
		case s_read:
			if (is_tickcnt_elapsed(tickcnt, meas_period)) {
				if (bme680_get_sensor_data(&bme680_data, &gas_sensor) == BME680_OK) {
					// ESP_LOGI("BME680", "OK !");
					
					// ESP_LOGI("BME680", "T: %.2f degC, P: %.2f hPa, H %.2f %%rH, G: %d ohms", bme680_data.temperature / 100.0f, bme680_data.pressure / 100.0f, bme680_data.humidity / 1000.0f, bme680_data.gas_resistance);
					
					state = s_trigger;
				} else {
					// ESP_LOGI("BME680", "Error code: %d", err);
					state = s_error;
				}
			}
			break;

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

double BME680::getTemperature() {
	return bme680_data.temperature / 100.0f;
}

double BME680::getPressure() {
	return bme680_data.pressure / 100.0f;
}

double BME680::getHumidity() {
	return bme680_data.humidity / 1000.0f;
}

double BME680::getGasResistance() {
	return bme680_data.gas_resistance;
}

double BME680::getAltitude() {
    // Equation taken from BMP180 datasheet (page 16):
    //  http://www.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf

    // Note that using the equation from wikipedia can give bad results
    // at high altitude. See this thread for more information:
    //  http://forums.adafruit.com/viewtopic.php?f=22&t=58064
	
	double seaLevel = 1013.25;
	double atmospheric = bme680_data.pressure / 100.0f;
	return 44330.0 * (1.0 - pow(atmospheric / seaLevel, 0.1903));
}

#endif
