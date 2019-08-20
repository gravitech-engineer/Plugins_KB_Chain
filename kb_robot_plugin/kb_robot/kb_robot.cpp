#ifndef __KB_ROBOT_CPP__
#define __KB_ROBOT_CPP__

#include "KB_Robot.h"

KB_Robot::KB_Robot(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = 40; // Not not use
}

void KB_Robot::init(void) {
	// clear error flag
	error = false;
	// set initialized flag
	initialized = true;
	
	// Set new timeout of i2c
	i2c_set_timeout(I2C_NUM_1, 40000);
	
	// Debug
	esp_log_level_set("*", ESP_LOG_INFO);
}

int KB_Robot::prop_count(void) {
	// not supported
	return 0;
}

bool KB_Robot::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool KB_Robot::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool KB_Robot::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool KB_Robot::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool KB_Robot::prop_write(int index, char *value) {
	// not supported
	return false;
}
// --------------------------------------

void KB_Robot::process(Driver *drv) {
	i2c = (I2CDev *)drv;
	switch (state) {
		case s_detect:
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {
				// clear error flag
				error = false;
				// set initialized flag
				initialized = true;
				
				// Send reset module
				reset();
				
				// Setup
				// Config Servo 1-4
				setFrequency(servo_to_pwm_number[1], 50);
				setFrequency(servo_to_pwm_number[2], 50);
				setFrequency(servo_to_pwm_number[3], 50);
				setFrequency(servo_to_pwm_number[4], 50);
				
				// Config driver
				setFrequency(driver_to_pwm_number[1], 1000);
				setFrequency(driver_to_pwm_number[2], 1000);
				setFrequency(driver_to_pwm_number[3], 1000);
				setFrequency(driver_to_pwm_number[4], 1000);
				
				// Go to main state
				state = s_runing;
			} else {
				state = s_error;
			}
			break;
		
		case s_runing: {
			if (i2c->detect(channel, address) != ESP_OK) {
				state = s_error;
			}
		}
		
		case s_wait:
			if (error) {
				// wait polling_ms timeout
				if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
					state = s_detect;
				}
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

// Method
bool KB_Robot::reset() {
	uint8_t data[] = { SEESAW_STATUS_BASE, SEESAW_STATUS_SWRST, 0xFF };
	return i2c->write(channel, address, data, 3) == ESP_OK;
}

bool KB_Robot::pinMode(uint8_t pin, uint8_t mode) {
	uint32_t mode_port_a, mode_port_b;
	if (pin >= 32) {
		mode_port_a = 0;
		mode_port_b = 1<<(pin-32);
	} else {
		mode_port_a = 1<<pin;
		mode_port_b = 0;
	}
	
	uint8_t data[10] = { 
		SEESAW_GPIO_BASE, 
		mode == 0 ? SEESAW_GPIO_DIRCLR_BULK : SEESAW_GPIO_DIRSET_BULK,
		(uint8_t)(mode_port_a>>24),
		(uint8_t)(mode_port_a>>16),
		(uint8_t)(mode_port_a>>8),
		(uint8_t)(mode_port_a),
		(uint8_t)(mode_port_b>>24),
		(uint8_t)(mode_port_b>>16),
		(uint8_t)(mode_port_b>>8),
		(uint8_t)(mode_port_b)
	};
	
	return i2c->write(channel, address, data, 10) == ESP_OK;
}

int KB_Robot::digital_read(uint8_t ch) {
	uint8_t pin = signal_to_pin[ch];
	
	if (!pinMode(pin, 0)) { // Set pin to INPUT
		ESP_LOGI("KB_Robot", "set gpio mode error!");
		return 0;
	}

	uint8_t data_write[2] = { SEESAW_GPIO_BASE, SEESAW_GPIO_BULK };
	uint8_t buf[8];
	
	if (i2c->read(channel, address, data_write, 2, buf, 8) != ESP_OK) {
		ESP_LOGI("KB_Robot", "Read gpio status error !");
		return 0;
	}

	uint32_t port_a = ((uint32_t)(buf[0])<<24)|((uint32_t)(buf[1])<<16)|((uint32_t)(buf[2])<<8)|(uint32_t)(buf[3]);
	uint32_t port_b = ((uint32_t)(buf[4])<<24)|((uint32_t)(buf[5])<<16)|((uint32_t)(buf[6])<<8)|(uint32_t)(buf[7]);
	if (pin >= 32) {
		return ((uint32_t)(1<<(pin-32)) & port_b) != 0 ? 1 : 0;
	} else {
		return ((uint32_t)(1<<pin) & port_a) != 0 ? 1 : 0;
	}
	return 0;
}

void KB_Robot::digital_write(uint8_t ch, uint8_t value) {
	uint8_t pin = signal_to_pin[ch];
	
	if (!pinMode(pin, 1)) { // Set pin to OUTPUT
		ESP_LOGI("KB_Robot", "set gpio mode error!");
		return;
	}

	uint32_t port_a, port_b;
	if (pin >= 32) {
		port_a = 0;
		port_b = 1<<(pin-32);
	} else {
		port_a = 1<<pin;
		port_b = 0;
	}
	
	uint8_t data[10] = { 
		SEESAW_GPIO_BASE, 
		value == 0 ? SEESAW_GPIO_BULK_CLR : SEESAW_GPIO_BULK_SET,
		(uint8_t)(port_a>>24),
		(uint8_t)(port_a>>16),
		(uint8_t)(port_a>>8),
		(uint8_t)(port_a),
		(uint8_t)(port_b>>24),
		(uint8_t)(port_b>>16),
		(uint8_t)(port_b>>8),
		(uint8_t)(port_b)
	};
	
	if (i2c->write(channel, address, data, 10) != ESP_OK) {
		ESP_LOGI("KB_Robot", "set gpio lavel error!");
	}
}

int KB_Robot::analog_read(uint8_t ch) {
	if (!pinMode(signal_to_pin[ch], 0)) { // Set pin to INPUT
		ESP_LOGI("KB_Robot", "set gpio mode error!");
		return 0;
	}
	
	uint8_t data[2];
	
	data[0] = SEESAW_ADC_BASE;
	data[1] = SEESAW_ADC_CHANNEL_OFFSET + (ch - 1);
	if (i2c->write(channel, address, data, 2) != ESP_OK) {
		ESP_LOGI("KB_Robot", "write to start adc error!");
		return 0;
	}
	
	ets_delay_us(500); // delay 500uS
	
	if (i2c->read(channel, address, NULL, 0, data, 2) != ESP_OK) {
		ESP_LOGI("KB_Robot", "read adc error!");
		return 0;
	}
	
	return ((uint16_t)data[0] << 8) | data[1];
}

void KB_Robot::driver_setDuty(uint8_t ch, uint16_t duty) {
	if (ch < 1 || ch > 4) {
		return;
	}
	
	if (duty > 1023) {
		duty = 1023;
	}
	
	setDuty(driver_to_pwm_number[ch], duty * 65535.0 / 1023.0);
}

void KB_Robot::driver_setFreq(uint8_t ch, uint16_t freq) {
	if (ch < 1 || ch > 4) {
		return;
	}
	
	setFrequency(driver_to_pwm_number[ch], freq);
}

void KB_Robot::driverSetPort(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) {
	driver_setDuty(1, pin1 ? 1023 : 0);
	driver_setDuty(2, pin2 ? 1023 : 0);
	driver_setDuty(3, pin3 ? 1023 : 0);
	driver_setDuty(4, pin4 ? 1023 : 0);
}

void KB_Robot::driver1stepCW() {
	driverSetPort(0, 0, 0, 1);
	driverSetPort(0, 0, 1, 1);
	driverSetPort(0, 0, 1, 0);
	driverSetPort(0, 1, 1, 0);
	driverSetPort(0, 1, 0, 0);
	driverSetPort(1, 1, 0, 0);
	driverSetPort(1, 0, 0, 0);
	driverSetPort(1, 0, 0, 1);
}

void KB_Robot::driver1stepCCW() {
	driverSetPort(1, 0, 0, 0);
	driverSetPort(1, 1, 0, 0);
	driverSetPort(0, 1, 0, 0);
	driverSetPort(0, 1, 1, 0);
	driverSetPort(0, 0, 1, 0);
	driverSetPort(0, 0, 1, 1);
	driverSetPort(0, 0, 0, 1);
	driverSetPort(1, 0, 0, 1);
}

void KB_Robot::driver_stepperMotor(int16_t step) {
	uint16_t u_step = abs(step);
	for (uint16_t i=0;i<u_step;i++) {
		if (step > 0) {
			driver1stepCW();
		} else {
			driver1stepCCW();
		}
	}
	driverSetPort(0, 0, 0, 0);
}

int KB_Robot::touch(uint8_t ch) {
	if (ch < 1 || ch > 4) {
		return 0;
	}
	
	uint8_t data[2];
	
	data[0] = SEESAW_TOUCH_BASE;
	data[1] = SEESAW_TOUCH_CHANNEL_OFFSET + (ch - 1);
	if (i2c->write(channel, address, data, 2) != ESP_OK) {
		ESP_LOGI("KB_Robot", "write to start touch error!");
		return 0;
	}
	
	ets_delay_us(1000); // delay 1000uS
	
	if (i2c->read(channel, address, NULL, 0, data, 2) != ESP_OK) {
		ESP_LOGI("KB_Robot", "read touch error!");
		return 0;
	}
	
	return ((uint16_t)data[0] << 8) | data[1];
}

void KB_Robot::motor(uint8_t ch, int8_t speed) {
	/*
	PWM Pin to CH
		CRICKIT_MOTOR_B1  = 4
		CRICKIT_MOTOR_B2  = 5
		CRICKIT_MOTOR_A1  = 6
		CRICKIT_MOTOR_A2  = 7
	*/
	
	if (ch < 1 || ch > 2) {
		return;
	}
	
	uint16_t duty = abs(speed) * 65535.0 / 100.0;
	// uint16_t duty = abs(speed);
	// uint16_t duty = abs(speed);
	uint8_t ch_a = ch == 1 ? 6 : 4;
	uint8_t ch_b = ch == 1 ? 7 : 5;
	
	if (speed > 0) { // forward
		setDuty(ch_a, 0);
		setDuty(ch_b, duty);
	} else if (speed < 0) { // backward
		setDuty(ch_a, duty);
		setDuty(ch_b, 0);
	} else { // stop
		setDuty(ch_a, 0);
		setDuty(ch_b, 0);
	}
}

void KB_Robot::servo(uint8_t ch, uint8_t angle) {
	if (ch < 1 || ch > 4) {
		return;
	}
	
	// Calc duty
	uint32_t value = (angle * (SERVO_MAX_PULSE - SERVO_MIN_PULSE) / 180) + SERVO_MIN_PULSE;
	
	setDuty(servo_to_pwm_number[ch], value);
}

bool KB_Robot::setDuty(uint8_t ch, uint16_t duty) {
	uint8_t buff[5];
	
	// Config Pulse
	buff[0] = SEESAW_TIMER_BASE; 
	buff[1] = SEESAW_TIMER_PWM;
	buff[2] = ch;
	buff[3] = (uint8_t)(duty >> 8); 
	buff[4] = (uint8_t)duty;
	if (i2c->write(channel, address, buff, 5) != ESP_OK) {
		ESP_LOGI("KB_Robot", "config duty pulse error!");
		return false;
	}
	return true;
}

bool KB_Robot::setFrequency(uint8_t ch, uint16_t freq) {
	uint8_t buff[5];
	
	buff[0] = SEESAW_TIMER_BASE; 
	buff[1] = SEESAW_TIMER_FREQ;
	buff[2] = ch;
	buff[3] = (uint8_t)(freq >> 8); 
	buff[4] = (uint8_t)freq;
	if (i2c->write(channel, address, buff, 5) != ESP_OK) {
		ESP_LOGI("KB_Robot", "config frequency error!");
		return false;
	}
	return true;
}

void KB_Robot::neopixel_init(uint16_t len) {
	uint8_t buff[4];
	
	// Config pin
	buff[0] = SEESAW_NEOPIXEL_BASE;
	buff[1] = SEESAW_NEOPIXEL_PIN;
	buff[2] = 20; // KB Robot connect NeoPixel via PA20
	if (i2c->write(channel, address, buff, 3) != ESP_OK) {
		ESP_LOGI("KB_Robot", "config neopixel pin error !");
		return;
	}
	
	// Config speed
	buff[0] = SEESAW_NEOPIXEL_BASE;
	buff[1] = SEESAW_NEOPIXEL_SPEED;
	buff[2] = 0x01; // 800 kHz
	if (i2c->write(channel, address, buff, 3) != ESP_OK) {
		ESP_LOGI("KB_Robot", "config neopixel speed error !");
		return;
	}
	
	len = len * 3; // 3 bytes per 1 led
	
	// Config length
	buff[0] = SEESAW_NEOPIXEL_BASE;
	buff[1] = SEESAW_NEOPIXEL_BUF_LENGTH;
	buff[2] = (uint8_t)(len>>8);
	buff[3] = (uint8_t)(len);
	if (i2c->write(channel, address, buff, 4) != ESP_OK) {
		ESP_LOGI("KB_Robot", "config neopixel length error !");
		return;
	}
}

void KB_Robot::neopixel_setColor(uint8_t n, uint32_t color) {
	neopixel_setColor(n, (uint8_t)(color>>16), (uint8_t)(color>>8), color);
}

void KB_Robot::neopixel_setColor(uint8_t n, uint8_t r, uint8_t g, uint8_t b) {
	uint8_t buff[7];
	buff[0] = SEESAW_NEOPIXEL_BASE;
	buff[1] = SEESAW_NEOPIXEL_BUF;
	
	// Start address
	uint16_t offset = n * 3;
	buff[2] = (uint8_t)(offset>>8);
	buff[3] = (uint8_t)(offset&0xFF);
	
	// color data
	buff[4] = g;
	buff[5] = r;
	buff[6] = b;
	
	// Write to KB Robot
	if (i2c->write(channel, address, buff, 7) != ESP_OK) {
		ESP_LOGI("KB_Robot", "send neopixel buffer error !");
		return;
	}
}

void KB_Robot::neopixel_show() {
	uint8_t data[2] = {
		SEESAW_NEOPIXEL_BASE, 
		SEESAW_NEOPIXEL_SHOW
	};
	if (i2c->write(channel, address, data, 2) != ESP_OK) {
		ESP_LOGI("KB_Robot", "show neopixel error!");
	}
}

#endif