#include "kb_chain_battery.h"

kb_chain_battery::kb_chain_battery(int batt_ch, int batt_addr)
{
  channel = 0;
  address = batt_addr;
  polling_ms = kb_chain_battery_POLLING_MS;
}

void kb_chain_battery::init(void)
{
  state = s_detect;
  initialized = false;

  i2c_config_t conf;

  conf.mode = I2C_MODE_MASTER;
  conf.sda_io_num = CHAIN_SDA_GPIO;
  conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
  conf.scl_io_num = CHAIN_SCL_GPIO;
  conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
  conf.master.clk_speed = 100E3; // Set speed to 100kHz

  i2c_param_config(I2C_NUM_1, &conf);
}

int kb_chain_battery::prop_count(void)
{
  // not supported
  return 0;
}

bool kb_chain_battery::prop_name(int index, char *name)
{
  // not supported
  return false;
}

bool kb_chain_battery::prop_unit(int index, char *unit)
{
  // not supported
  return false;
}

bool kb_chain_battery::prop_attr(int index, char *attr)
{
  // not supported
  return false;
}

bool kb_chain_battery::prop_read(int index, char *value)
{
  // not supported
  return false;
}

bool kb_chain_battery::prop_write(int index, char *value)
{
  // not supported
  return false;
}

void kb_chain_battery::process(Driver *drv)
{
  I2CDev *i2c = (I2CDev *)drv;
  float voltage;
  switch (this->state)
  {
  case s_detect:
    // cal_volt = 01;
    // detect i2c device
    if (i2c->detect(channel, address) == ESP_OK)
    // if (1)
    {
      // cal_volt = 02;
      // clear error flag
      this->error = false;
      // set initialized flag
      this->initialized = false;
      // Reset module
      this->state = s_read;
    }
    else
    {
    }
    break;

  case s_read:
    // cal_volt = 03;
    if (i2c->read(channel, address, NULL, 0, data, 1) == ESP_OK)
    {
      // cal_volt = 03;
      result = data[0];
      // cal_volt = result;
      result = result << 8;
      result += data[1];
      float mV = (float)result;
      mV = ((mV / 4095) * _adcVRef);
      voltage = mV / 1000;

      // 100.00%	4.2
      // 90	4.13
      // 80	4.06
      // 70	3.99
      // 60	3.92
      // 50	3.85
      // 40	3.78
      // 30	3.71
      // 20	3.64
      // 10	3.57
      // 0.00% 3.5

      if (voltage > 4.13)
      {
        cal_volt = 100;
      }
      else if (voltage <= 4.13 && voltage > 4.06)
      {
        cal_volt = 90;
      }
      else if (voltage <= 4.06 && voltage > 3.99)
      {
        cal_volt = 80;
      }
      else if (voltage <= 3.99 && voltage > 3.92)
      {
        cal_volt = 70;
      }
      else if (voltage <= 3.92 && voltage > 3.85)
      {
        cal_volt = 60;
      }
      else if (voltage <= 3.85 && voltage > 3.78)
      {
        cal_volt = 50;
      }
      else if (voltage <= 3.78 && voltage > 3.71)
      {
        cal_volt = 40;
      }
      else if (voltage <= 3.71 && voltage > 3.64)
      {
        cal_volt = 30;
      }
      else if (voltage <= 3.64 && voltage > 3.57)
      {
        cal_volt = 20;
      }
      else if (voltage <= 3.57 && voltage > 3.5)
      {
        cal_volt = 10;
      }
      else if (voltage <= 3.5 && voltage < 3.5)
      {
        cal_volt = 0;
      }
      this->initialized = true;
    }
    else
    {
    }
    break;
  }
}

//Method

double kb_chain_battery::get_cal_volt()
{

  // cal_volt = 10;

  return cal_volt;
}
