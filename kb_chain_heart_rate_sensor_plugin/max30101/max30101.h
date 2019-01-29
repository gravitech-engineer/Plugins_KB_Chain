#ifndef __MAX30101_H__
#define __MAX30101_H__

#include "math.h"
#include "driver/uart.h"
#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "heartRate.h"

#define MAX30101_POLLING_MS 500

// #define MAX30101_DEBUG

/*
#define MAX30101_REG_MODE_CONFIG 0x09
#define MAX30101_REG_FIFO_CONFIG 0x08
#define MAX30101_REG_SPO2_CONFIG 0x0A
#define MAX30101_REG_LED1_PULSE_AMPLITUDE 0x0C
#define MAX30101_REG_LED2_PULSE_AMPLITUDE 0x0D
#define MAX30101_REG_LED3_PULSE_AMPLITUDE 0x0E
#define MAX30101_REG_LED4_PULSE_AMPLITUDE 0x0F
*/

#define MAX30101_RATE_SIZE 4

class MAX30101 : public Device {
	private:
		enum {
			s_detect, 
			s_reset,
			s_wait_reset,
			s_config,
			s_read, 
			s_error, 
			s_wait
		} state;
		TickType_t tickcnt, polling_tickcnt, waiting_reset;
		
		typedef union {
			uint8_t block[2];
			struct {
				uint8_t reg;
				uint8_t data;
			};
		} Reg; 
		
		uint16_t _heart_rate;
		uint32_t _raw_data_ir, _raw_data_red;
		
		// ----------- Example5_HeartRate -------
		uint8_t rates[MAX30101_RATE_SIZE]; //Array of heart rates
		uint8_t rateSpot = 0;
		uint64_t lastBeat;
		
		float beatsPerMinute;
		int beatAvg;
		// -----------
		
		bool writeConfigData(I2CDev *i2c) ;
		uint16_t check(I2CDev *i2c) ;


	public:
		// constructor
		MAX30101(int bus_ch, int dev_addr);
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
		int get_heart_rate() ;
		uint16_t get_raw_data(uint8_t led) ;
		
};

#endif
