#ifndef __kb_thermal_H__
#define __kb_thermal_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"


#define kb_thermal_POLLING_MS         1000
#define IR_Themometer_I2CADDR 0x5A            
#define IR_Themometer_TA 0x06
#define IR_Themometer_TOBJ1 0x07



class kb_thermal : public Device {
    private:
        enum { s_detect, 
			 s_read, 
			 s_error, 
			 s_wait} state;
        TickType_t tickcnt, polling_tickcnt;
        I2CDev *i2c;

        float RawData;
        float ConVData = 0;
        uint8_t reg;

    public:
        // constructor
        kb_thermal(int bus_ch, int dev_addr);
        // override
        void init(void);
        void process(Driver *drv);
        int  prop_count(void);
        bool prop_name(int index, char *name);
        bool prop_unit(int index, char *unit);
        bool prop_attr(int index, char *attr);
        bool prop_read(int index, char *value);
        bool prop_write(int index, char *value);
        // method
        float Readtemp(uint8_t sel);

};

#endif
