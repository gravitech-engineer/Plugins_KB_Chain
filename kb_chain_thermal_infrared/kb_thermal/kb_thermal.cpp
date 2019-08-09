#include <stdio.h>
#include <string.h>
#include <math.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include "kb_thermal.h"

kb_thermal::kb_thermal(int bus_ch, int dev_addr)
{
	channel = bus_ch;
	address = dev_addr;
	polling_ms = kb_thermal_POLLING_MS;
}

void kb_thermal::init(void)
{
	i2c_config_t conf;

    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = GPIO_NUM_4;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = GPIO_NUM_5;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 100000;

	i2c_param_config(I2C_NUM_1,&conf);


	state = s_detect;
}

int kb_thermal::prop_count(void)
{
	// not supported
	return 0;
}

bool kb_thermal::prop_name(int index, char *name)
{
	// not supported
	return false;
}

bool kb_thermal::prop_unit(int index, char *unit)
{
	// not supported
	return false;
}

bool kb_thermal::prop_attr(int index, char *attr)
{
	// not supported
	return false;
}

bool kb_thermal::prop_read(int index, char *value)
{
	// not supported
	return false;
}

bool kb_thermal::prop_write(int index, char *value)
{
	// not supported
	return false;
}

void kb_thermal::process(Driver *drv)
{
	//  char buffer[64];
	//  sprintf(buffer, "%lldms\n", (esp_timer_get_time() / 1000));
	//  uart_write_bytes(UART_NUM_0, (const char*)buffer, strlen(buffer));

	i2c = (I2CDev *)drv;
	uint8_t data[3];
	uint16_t temp;
	double tempC;

	switch (state)
	{
	case s_detect:
		// detect i2c device
		if (i2c->detect(channel, address) == ESP_OK)
		{
			uint8_t tempdata[3];
			// set initialized flag
			// if (i2c->read(0, 0x5A, &reg, 1, tempdata, 3) == ESP_OK){
			initialized = true;

			// clear error flag
			error = false;
			state = s_read;
			// }
		}
		else
		{
			state = s_error;
		}
		break;

	case s_read:
		//uint8_t reg = 0x07;
		// get current tickcnt
		tickcnt = get_tickcnt();
		// wait polling_ms timeout
		//  if (is_tickcnt_elapsed(tickcnt, 300))
		// {
			// get current tickcnt
			tickcnt = get_tickcnt();
			// printf("REG is %d\n",reg);
			if (i2c->read(0, 0x5A, &reg, 1, data, 3) == ESP_OK)
			{
				
				// printf("temp %d\n",data[2]);
				temp = data[0];
				temp |= data[1] << 8;
				tempC = temp * 0.02;
				RawData = (float)tempC - 273.15;
				ConVData = roundf(RawData * 100)/ 100;
				
			}
			else
			{
				state = s_error;
			}
			// }
		break;
	
	

	case s_wait:
		// wait polling_ms timeout
		if (is_tickcnt_elapsed(tickcnt, polling_ms))
		{
			initialized = false;
			state = s_detect;
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
	}
}

float kb_thermal::Readtemp(uint8_t sel)
{
	reg = sel;
	
	if(ConVData < -30)
	{
		return 0;
	}
	return ConVData;
}
