#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "MAX30101.h"

MAX30101::MAX30101(int bus_ch, int dev_addr) {
	channel = bus_ch;
	address = dev_addr;
	polling_ms = MAX30101_POLLING_MS;
}

void MAX30101::init(void) {
	state = s_detect;
}

int MAX30101::prop_count(void) {
	return 0;
}

bool MAX30101::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool MAX30101::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool MAX30101::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool MAX30101::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool MAX30101::prop_write(int index, char *value) {
	// not supported
	return false;
}

void MAX30101::process(Driver *drv) {
	I2CDev *i2c = (I2CDev *)drv;
	
	switch (state) {
		case s_detect:
			// stamp polling tickcnt
			polling_tickcnt = get_tickcnt();
			
			// detect i2c device
			if (i2c->detect(channel, address) == ESP_OK) {	
				
				
				// set initialized flag
				initialized = true;
				
				// clear error flag
				error = false;
				
				state = s_reset;
			} else {
				state = s_error;
			}
			break;
		case s_reset: {
			Reg softReset;
			
			/* ----> Mode Configuration (0x09) <----
			 * [7 SHDN]:     0 -> normal mode
			 * [6 RESET]:    1 -> Reset
			 * [3-5]:      000 -> reverse
			 * [0-2 MODE]: 000 -> Do not use
			 */
			softReset.reg = 0x09;
			softReset.data = 0b01000000;
			if (i2c->write(channel, address, softReset.block, 2) == ESP_OK) {
				// stamp waiting_reset tickcnt
				waiting_reset = get_tickcnt();
				
				state = s_wait_reset;
			} else {
				state = s_error;
			}
			break;
		}
		
		case s_wait_reset: 
			// if wait reset timeout
			if (is_tickcnt_elapsed(waiting_reset, 300)) { // 300mS
				state = s_error;
			} else { // if in time 300mS
				uint8_t reg[1], dataBuffer[1];
				reg[0] = 0x09; // Mode Configuration
				if (i2c->read(channel, address, reg, 1, dataBuffer, 1) == ESP_OK) {
					if ((dataBuffer[0]&(1<<6)) == 0) { // Check RESET bit is 0 ?
						state = s_config;
					}
				} else {
					state = s_error;
				}
			}
			break;
		
		case s_config:
			if (writeConfigData(i2c)) {
				state = s_read;
			} else {
				state = s_error;
			}
			break;
			
		case s_read:
			// Do this forever
			if (!check(i2c)) {
				state = s_error;
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

		case s_wait:
			// wait polling_ms timeout
			if (is_tickcnt_elapsed(tickcnt, polling_ms)) {
				state = s_detect;
			}
			break;
	}
}

bool MAX30101::writeConfigData(I2CDev *i2c) {
	int configSize = 11;
	Reg config[configSize];
	
	/* ----> FIFO Configuration (0x08) <----
	 * [7-5 SMP_AVE]:        010 ->  Sample Averaging is 4
	 * [4 FIFO_ROLLOVER_EN]:   1 ->  FIFO Rolls on Full
	 * [3-0 FIFO_A_FULL]:   0000 ->  interrupt is issued when 32 FIFO words have unread data
	 */
	config[0].reg = 0x08;
	config[0].data = 0b01010000;
	
	/* ----> Mode Configuration (0x09) <----
	 * [7 SHDN]:     0 -> normal mode
	 * [6 RESET]:    0 -> Not reset
	 * [5-3]:      000 -> reverse
	 * [2-0 MODE]: 011 -> Active Red and IR
	 */
	config[1].reg = 0x09;
	config[1].data = 0b00000011;
	
	/* ----> SpO2 Configuration (0x0A) <----
	 * [7]:                   0 -> reverse
	 * [6-5 SPO2_ADC_RGE]:   01 -> Full scale = 4096
	 * [4-2 SPO2_SR]:       011 -> 400 sample per sec
	 * [1-0 LED_PW]:         11 -> 411 pwm, ADC 18 bits
	 */
	config[2].reg = 0x0A;
	config[2].data = 0b00101111;
	
	/* ----> LED1 Pulse Amplitude (0x0C) <----
	 * [7-0 LED1_PA]:         0x0A <- RED LED
	 */
	config[3].reg = 0x0C;
	config[3].data = 0x0A;
	
	/* ----> LED2 Pulse Amplitude (0x0D) <----
	 * [7-0 LED2_PA]:         0x0A <- IR LED
	 */
	config[4].reg = 0x0D;
	config[4].data = 0x0A;
	
	/* ----> LED3 Pulse Amplitude (0x0E) <----
	 * [7-0 LED3_PA]:         0x00 <- GREEN LED
	 */
	config[5].reg = 0x0E;
	config[5].data = 0x00;
	
	/* ----> LED4 Pulse Amplitude (0x0F) <----
	 * [7-0 LED4_PA]:         0x0A <- Proximity LED
	 */
	config[6].reg = 0x0F;
	config[6].data = 0x0A;
	
	/* ----> Multi-LED (1) Mode Control Registers (0x11) <----
	 * [7]:            0 <- reverse
	 * [6-4 SLOT2]:  010 <- LED2 (IR) 
	 * [3]:            0 <- reverse
	 * [2-0 SLOT1]:  001 <- LED1 (RED) 
	 */
	config[7].reg = 0x11;
	config[7].data = 0b00100001;
	
	/* ----> FIFO Write Pointer (0x04) <----
	 * [7-5]:              0 <- reverse
	 * [4-0 FIFO_WR_PTR]:  0 <- clear
	 */
	config[8].reg = 0x04;
	config[8].data = 0;
	
	/* ----> FIFO Overflow Counter (0x05) <----
	 * [7-5]:              0 <- reverse
	 * [4-0 OVF_COUNTER]:  0 <- clear
	 */
	config[9].reg = 0x05;
	config[9].data = 0;
	
	/* ----> FIFO Read Pointer (0x06) <----
	 * [7-5]:              0 <- reverse
	 * [4-0 FIFO_RD_PTR]:  0 <- clear
	 */
	config[10].reg = 0x06;
	config[10].data = 0;
	
	// Write via I2C
	for (int inx=0;inx<configSize;inx++) {
		if (i2c->write(channel, address, config[inx].block, 2) != ESP_OK) {
			return false;
		}
	}
	
	return true;
}

uint16_t MAX30101::check(I2CDev *i2c) {
	/* Step --------------
	 *   - Read FIFO_RD_PTR
	 *   - Read FIFO_WR_PTR
	 *   - NUM_AVAILABLE_SAMPLES = FIFO_WR_PTR – FIFO_RD_PTR // FIFO_RD_PTR ?
	 *   - Loop count is NUM_AVAILABLE_SAMPLE
	 *       - Read FIFO_DATA - 2 * 3 byte
	 *    
	 */ 
	
	
	uint8_t reg[1];
	uint8_t data[1];
	
	// Read FIFO_RD_PTR
	reg[0] = 0x06;
	if (i2c->read(channel, address, reg, 1, data, 1) != ESP_OK) {
		return false;
	}
	uint8_t readPointer = data[0];
	
	// Read FIFO_WR_PTR
	reg[0] = 0x04;
	if (i2c->read(channel, address, reg, 1, data, 1) != ESP_OK) {
		return false;
	}
	uint8_t writePointer = data[0];
	
	int numberOfSamples = 0;

	//Do we have new data?
	if (readPointer != writePointer) {
		//Calculate the number of readings we need to get from sensor
		numberOfSamples = writePointer - readPointer;
		if (numberOfSamples < 0) numberOfSamples += 32; //Wrap condition

		// int bytesLeftToRead = numberOfSamples * 2 * 3; // 2 LED (RED + IR) * 3 bytes

		//Get ready to read a burst of data from the FIFO register
		reg[0] = 0x07; // FIFO_DATA
		if (i2c->write(channel, address, reg, 1) != ESP_OK) {
			return false;
		}
		
		// Read Sample
		while (numberOfSamples--) {
			int bytePerSamples = 2 * 3;  // 2 LED (RED + IR) * 3 bytes
			
			uint8_t OneSampleBuffer[bytePerSamples];
			if (i2c->read(channel, address, NULL, 0, OneSampleBuffer, bytePerSamples) != ESP_OK) {
				return false;
			}
			
			_raw_data_red = uint32_t(OneSampleBuffer[0]<<16)|uint32_t(OneSampleBuffer[1]<<8)|(uint32_t)OneSampleBuffer[2];
			_raw_data_ir = uint32_t(OneSampleBuffer[3]<<16)|uint32_t(OneSampleBuffer[4]<<8)|(uint32_t)OneSampleBuffer[5];
			
			#ifdef MAX30101_DEBUG
			if (numberOfSamples == 0) {
				char str[20];
				sprintf(str, "%d\n", _raw_data_ir);
				uart_write_bytes(UART_NUM_0, str, strlen(str));
			}
			#endif
			
			
			if (checkForBeat(_raw_data_ir)) {
				//We sensed a beat!
				uint64_t delta = esp_timer_get_time() - lastBeat;
				lastBeat = esp_timer_get_time();

				beatsPerMinute = 60 / (delta / 1000.0 / 1000.0);

				if (beatsPerMinute < 255 && beatsPerMinute > 20) {
					rates[rateSpot++] = (uint8_t)beatsPerMinute; //Store this reading in the array
					rateSpot %= MAX30101_RATE_SIZE; //Wrap variable

					//Take average of readings
					beatAvg = 0;
					for (uint8_t x = 0 ; x < MAX30101_RATE_SIZE ; x++)
						beatAvg += rates[x];
					beatAvg /= MAX30101_RATE_SIZE;
				}
			}
			
			if (_raw_data_ir < 20000) beatAvg = 0;
		}
	}

	return true;
}

int MAX30101::get_heart_rate() {
	if (error) return -1;
	
	return beatAvg;
}

uint16_t MAX30101::get_raw_data(uint8_t led) {
	if (led == 1) return _raw_data_red;
	if (led == 2) return _raw_data_ir;
	
	return 0;
}
