#ifndef __kb_chain_battery_H__
#define __kb_chain_battery_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "driver/uart.h"
#include "kidbright32.h"


#define kb_chain_battery_POLLING_MS 100

class kb_chain_battery : public Device
{
private:
  enum
  {
    s_detect,
    s_read
  } state;
  TickType_t tickcnt, polling_tickcnt;
  double cal_volt;
  int _adcVRef = 4948;
  uint8_t data[2];
  uint16_t result;

public:
  // constructor
  kb_chain_battery(int batt_ch, int batt_addr);
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
  double get_cal_volt(void);
};

#endif
