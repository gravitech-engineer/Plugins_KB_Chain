#ifndef __c_gpio_H__
#define __c_gpio_H__

#include "driver.h"
#include "device.h"

#define c_gpio_POLLING_MS         1000

class c_gpio : public Device {
    private:
        enum { s_detect } state;
        TickType_t tickcnt, polling_tickcnt;

    public:
    double temp_c;
        // constructor
        c_gpio();
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
        void set_gpio(int pin,int state);
        double get_gpio(int gpin);
};

#endif
