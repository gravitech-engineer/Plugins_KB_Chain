#ifndef __write_led_H__
#define __write_led_H__

#include "driver.h"
#include "device.h"

#define write_led_POLLING_MS 1000

class write_led : public Device
{
  private:
    enum
    {
        s_detect
    } state;
    TickType_t tickcnt, polling_tickcnt;

  public:
    // constructor
    write_led();
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
    void writeled(int pin, int state);
};

#endif
