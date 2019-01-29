#ifndef __VEML6075_H__
#define __VEML6075_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"

#define VEML6075_POLLING_MS 500

// VEML6075 Register
#define VEML6075_REG_UV_CONF      0x00
#define VEML6075_REG_UVA_Data     0x07
#define VEML6075_REG_UVB_Data     0x09
#define VEML6075_REG_UVCOMP1_Data 0x0A
#define VEML6075_REG_UVCOMP2_Data 0x0B


#define VEML6075_DEFAULT_UVA_A_COEFF 2.22     ///< Default for no coverglass
#define VEML6075_DEFAULT_UVA_B_COEFF 1.33     ///< Default for no coverglass
#define VEML6075_DEFAULT_UVB_C_COEFF 2.95     ///< Default for no coverglass
#define VEML6075_DEFAULT_UVB_D_COEFF 1.74     ///< Default for no coverglass
#define VEML6075_DEFAULT_UVA_RESPONSE 0.001461     ///< Default for no coverglass
#define VEML6075_DEFAULT_UVB_RESPONSE 0.002591     ///< Default for no coverglass

class VEML6075 : public Device {
	private:
		enum {
			s_detect, 
			s_write,
			s_read, 
			s_wait_next_time,
			
			s_error, 
			s_wait
		} state;
		TickType_t tickcnt, polling_tickcnt;
		
		float _uva_a, _uva_b, _uvb_c, _uvb_d, _uva_resp, _uvb_resp;
		float _uva_calc, _uvb_calc;
		
		union {
			uint8_t block[3];
			struct {
				uint8_t reg;
				uint16_t data;
			};
		} uv_conf_data; 


	public:
		// constructor
		VEML6075(int bus_ch, int dev_addr);
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
		double get_uva();
		double get_uvb();
		double get_uvi();

};

#endif
