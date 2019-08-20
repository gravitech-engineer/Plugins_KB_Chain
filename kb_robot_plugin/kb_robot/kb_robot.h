#ifndef __KB_ROBOT_H__
#define __KB_ROBOT_H__

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver.h"
#include "device.h"
#include "i2c-dev.h"
#include "driver/uart.h"
#include "kidbright32.h"

enum {
	SEESAW_STATUS_BASE = 0x00,
	SEESAW_GPIO_BASE = 0x01,
	SEESAW_SERCOM0_BASE = 0x02,

	SEESAW_TIMER_BASE = 0x08,
	SEESAW_ADC_BASE = 0x09,
	SEESAW_DAC_BASE = 0x0A,
	SEESAW_INTERRUPT_BASE = 0x0B,
	SEESAW_DAP_BASE = 0x0C,
	SEESAW_EEPROM_BASE = 0x0D,
	SEESAW_NEOPIXEL_BASE = 0x0E,
	SEESAW_TOUCH_BASE = 0x0F,
	SEESAW_KEYPAD_BASE = 0x10,
	SEESAW_ENCODER_BASE = 0x11,
};

enum {
	SEESAW_GPIO_DIRSET_BULK = 0x02,
	SEESAW_GPIO_DIRCLR_BULK = 0x03,
	SEESAW_GPIO_BULK = 0x04,
	SEESAW_GPIO_BULK_SET = 0x05,
	SEESAW_GPIO_BULK_CLR = 0x06,
	SEESAW_GPIO_BULK_TOGGLE = 0x07,
	SEESAW_GPIO_INTENSET = 0x08,
	SEESAW_GPIO_INTENCLR = 0x09,
	SEESAW_GPIO_INTFLAG = 0x0A,
	SEESAW_GPIO_PULLENSET = 0x0B,
	SEESAW_GPIO_PULLENCLR = 0x0C,
};

enum {
	SEESAW_STATUS_HW_ID = 0x01,
	SEESAW_STATUS_VERSION = 0x02,
	SEESAW_STATUS_OPTIONS = 0x03,
	SEESAW_STATUS_TEMP = 0x04,
	SEESAW_STATUS_SWRST = 0x7F,
};

enum {
	SEESAW_TIMER_STATUS = 0x00,
	SEESAW_TIMER_PWM = 0x01,
	SEESAW_TIMER_FREQ = 0x02,
};

enum {
	SEESAW_ADC_STATUS = 0x00,
	SEESAW_ADC_INTEN = 0x02,
	SEESAW_ADC_INTENCLR = 0x03,
	SEESAW_ADC_WINMODE = 0x04,
	SEESAW_ADC_WINTHRESH = 0x05,
	SEESAW_ADC_CHANNEL_OFFSET = 0x07,
};

enum {
	SEESAW_NEOPIXEL_STATUS = 0x00,
	SEESAW_NEOPIXEL_PIN = 0x01,
	SEESAW_NEOPIXEL_SPEED = 0x02,
	SEESAW_NEOPIXEL_BUF_LENGTH = 0x03,
	SEESAW_NEOPIXEL_BUF = 0x04,
	SEESAW_NEOPIXEL_SHOW = 0x05,
};

enum {
	SEESAW_TOUCH_CHANNEL_OFFSET = 0x10,
};

#define CRICKIT_SIGNAL1 2
#define CRICKIT_SIGNAL2 3
#define CRICKIT_SIGNAL3 40
#define CRICKIT_SIGNAL4 41
#define CRICKIT_SIGNAL5 11
#define CRICKIT_SIGNAL6 10
#define CRICKIT_SIGNAL7 9
#define CRICKIT_SIGNAL8 8

#define CRICKIT_SERVO4 14
#define CRICKIT_SERVO3 15
#define CRICKIT_SERVO2 16
#define CRICKIT_SERVO1 17

#define CRICKIT_MOTOR_A1 22
#define CRICKIT_MOTOR_A2 23
#define CRICKIT_MOTOR_B1 19
#define CRICKIT_MOTOR_B2 18
#define CRICKIT_DRIVE1 13
#define CRICKIT_DRIVE2 12
#define CRICKIT_DRIVE3 43
#define CRICKIT_DRIVE4 42

#define CRICKIT_TOUCH1 0
#define CRICKIT_TOUCH2 1
#define CRICKIT_TOUCH3 2
#define CRICKIT_TOUCH4 3

#define CRICKIT_DUTY_CYCLE_OFF 0
#define CRICKIT_DUTY_CYCLE_MAX 65535

#define SERVO_MIN_PULSE 3277
#define SERVO_MAX_PULSE 6554

static uint8_t signal_to_pin[] = { 
	0, 
	CRICKIT_SIGNAL1, 
	CRICKIT_SIGNAL2, 
	CRICKIT_SIGNAL3, 
	CRICKIT_SIGNAL4, 
	CRICKIT_SIGNAL5, 
	CRICKIT_SIGNAL6, 
	CRICKIT_SIGNAL7,
	CRICKIT_SIGNAL8
};

/*
PWM Pin to CH
	CRICKIT_SERVO4    = 0
	CRICKIT_SERVO3    = 1
	CRICKIT_SERVO2    = 2
	CRICKIT_SERVO1    = 3
	CRICKIT_MOTOR_B1  = 4
	CRICKIT_MOTOR_B2  = 5
	CRICKIT_MOTOR_A1  = 6
	CRICKIT_MOTOR_A2  = 7
	CRICKIT_DRIVE4    = 8
	CRICKIT_DRIVE3    = 9
	CRICKIT_DRIVE2    = 10
	CRICKIT_DRIVE1    = 11
*/

static uint8_t servo_to_pwm_number[] = {
	0,
	3, // CH1
	2, // CH2
	4, // CH3
	0  // CH4
};

static uint8_t driver_to_pwm_number[] = {
	0,
	11, // CH1
	10, // CH2
	9,  // CH3
	8   // CH4
};

class KB_Robot : public Device {
	private:		
		enum {
			s_detect,
			s_runing,
			s_wait,
			s_error
		} state;
		TickType_t tickcnt, polling_tickcnt;
		
		I2CDev *i2c;
		
        bool reset() ;
		bool pinMode(uint8_t pin, uint8_t mode) ;
		bool setDuty(uint8_t ch, uint16_t duty) ;
		bool setFrequency(uint8_t ch, uint16_t freq) ;
		
		void driverSetPort(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) ;
		void driver1stepCW() ;
		void driver1stepCCW() ;

	public:
		// constructor
		KB_Robot(int bus_ch, int dev_addr) ;
		
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
		
		// Signal I/O
		int digital_read(uint8_t ch) ;
		void digital_write(uint8_t ch, uint8_t value) ;
		int analog_read(uint8_t ch) ;
        // void analog_write(uint8_t ch, uint8_t value) ;
		
		// Driver
		void driver_setDuty(uint8_t ch, uint16_t duty) ;
		void driver_setFreq(uint8_t ch, uint16_t freq) ;
		void driver_stepperMotor(int16_t step) ;
		
		// Touch
        int touch(uint8_t ch) ;
		
		// Motor
		void motor(uint8_t ch, int8_t speed) ;
		
		// Servo
		void servo(uint8_t ch, uint8_t angle) ;
		
		// NeoPixel
		void neopixel_init(uint16_t len) ;
        void neopixel_setColor(uint8_t n, uint32_t color) ;
        void neopixel_setColor(uint8_t n, uint8_t r, uint8_t g, uint8_t b) ;
		void neopixel_show() ;

		
};

#endif