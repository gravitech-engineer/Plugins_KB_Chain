#include <stdio.h>
#include <string.h>
#include <math.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "soc/uart_struct.h"
#include "write_led.h"

write_led::write_led()
{
  polling_ms = write_led_POLLING_MS;
}

void write_led::init(void)
{
  state = s_detect;
  initialized = true;
}

int write_led::prop_count(void)
{
  // not supported
  return 0;
}

bool write_led::prop_name(int index, char *name)
{
  // not supported
  return false;
}

bool write_led::prop_unit(int index, char *unit)
{
  // not supported
  return false;
}

bool write_led::prop_attr(int index, char *attr)
{
  // not supported
  return false;
}

bool write_led::prop_read(int index, char *value)
{
  // not supported
  return false;
}

bool write_led::prop_write(int index, char *value)
{
  // not supported
  return false;
}

void write_led::process(Driver *drv)
{
  //  char buffer[64];
  //  sprintf(buffer, "%lldms\n", (esp_timer_get_time() / 1000));
  //  uart_write_bytes(UART_NUM_0, (const char*)buffer, strlen(buffer));
}

void write_led::writeled(int pin, int state)
{
  if (pin == 17)
  {
    gpio_set_level(BT_LED_GPIO, state);
  }
  else if (pin == 2)
  {
    gpio_set_level(WIFI_LED_GPIO, state);
  }else if (pin == 15)
  {
    gpio_set_level(NTP_LED_GPIO, state);
  }else if (pin == 12)
  {
    gpio_set_level(IOT_LED_GPIO, state);
  }
}


