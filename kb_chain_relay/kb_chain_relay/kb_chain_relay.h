#ifndef __kb_chain_H__
#define __kb_chain_H__

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "driver/uart.h"
#include "kidbright32.h"

#define kb_chain_POLLING_MS         100

class kb_chain_relay : public Device {
    private:
        enum {
			s_detect,
			s_write
		} state;
        TickType_t tickcnt, polling_tickcnt;
        uint8_t value;
        int _ch_sel;
        int _logic;
        uint8_t _address;   
    public:
        // constructor
        kb_chain_relay(int bus_ch,int dev_addr);
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
        // void begin(uint8_t address);
        void set_ch(int ch_sel, int logic);
        
};

#endif
