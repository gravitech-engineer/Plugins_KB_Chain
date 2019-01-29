#include "kb_chain_relay.h"


kb_chain_relay::kb_chain_relay(int bus_ch,int dev_addr) {
  channel = bus_ch;
	address = dev_addr;
	polling_ms = kb_chain_POLLING_MS;
}

void kb_chain_relay::init(void) {
  state = s_detect;
  initialized = true;

  i2c_config_t conf;

    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = CHAIN_SDA_GPIO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = CHAIN_SCL_GPIO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 100E3; // Set speed to 100kHz

	i2c_param_config(I2C_NUM_1, &conf);
}

int kb_chain_relay::prop_count(void) {
  // not supported
  return 0;
}

bool kb_chain_relay::prop_name(int index, char *name) {
  // not supported
  return false;
}

bool kb_chain_relay::prop_unit(int index, char *unit) {
  // not supported
  return false;
}

bool kb_chain_relay::prop_attr(int index, char *attr) {
  // not supported
  return false;
}

bool kb_chain_relay::prop_read(int index, char *value) {
  // not supported
  return false;
}

bool kb_chain_relay::prop_write(int index, char *value) {
  // not supported
  return false;
}

void kb_chain_relay::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	
	switch (this->state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(this->channel, this->address) == ESP_OK) {
				// clear error flag
				this->error = false;
				// set initialized flag
				this->initialized = true;
				
				// Reset module
        
				// this->syncData[CH_A] = true;
				// this->syncData[CH_B] = true;
				this->state = s_write;
			} else {
			}
			break;

		case s_write:

			if (this->value > 0) {
				uint8_t data[] = {((uint8_t)this->value)};
				if (i2c->write(this->channel, this->address, data, sizeof data) == ESP_OK) {
          this->value = 0;

				} else {

				}
			}
			break;
	}
}



//Method

void kb_chain_relay::set_ch(int ch_sel, int logic) {
  /* Start communication */
  
  _ch_sel = ch_sel;
  _logic = logic;

  if (_ch_sel == 0) {
    switch (_logic)
    {
      case 0:
        this->value = 0xA0;
        break;
      case 1:
        this->value = 0xA1;
        break;
      default:
        break;
    }
  }
  else if (_ch_sel == 1)
  {
    switch (_logic)
    {
      case 0:
        this->value = 0xB0;
        break;
      case 1:
        this->value = 0xB1;
        break;
      default:
        break;
    }
  }
   
}




