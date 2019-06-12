#include <stdio.h>
#include <string.h>
#include <math.h>
#include "esp_system.h"
#include "kidbright32.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include "c_gpio.h"


c_gpio::c_gpio() {
  polling_ms = c_gpio_POLLING_MS;
}

void c_gpio::init(void) {
  state = s_detect;
  initialized = true;
}

int c_gpio::prop_count(void) {
  // not supported
  return 0;
}

bool c_gpio::prop_name(int index, char *name) {
  // not supported
  return false;
}

bool c_gpio::prop_unit(int index, char *unit) {
  // not supported
  return false;
}

bool c_gpio::prop_attr(int index, char *attr) {
  // not supported
  return false;
}

bool c_gpio::prop_read(int index, char *value) {
  // not supported
  return false;
}

bool c_gpio::prop_write(int index, char *value) {
  // not supported
  return false;
}

void c_gpio::process(Driver *drv) {
//  char buffer[64];
//  sprintf(buffer, "%lldms\n", (esp_timer_get_time() / 1000));
//  uart_write_bytes(UART_NUM_0, (const char*)buffer, strlen(buffer));
}

/* 
void c_gpio::set_gpio(int pin,int state)
{
  if (pin == 18)
  {
    gpio_set_level(GPIO_NUM_18,state);

  }else if (pin == 19)
  {
    gpio_set_level(GPIO_NUM_19,state);
  }else if (pin == 23)
  {
    gpio_set_level(GPIO_NUM_23,state);
  }
  
}*/

double c_gpio::get_gpio(int gpin)
{
  
  if (gpin == 18)
  {
    return (gpio_get_level(GPIO_NUM_18));
    // return = 10;
  }
  else if (gpin == 19)
  {
    return (gpio_get_level(GPIO_NUM_19));
  }
  else if (gpin == 23)
  {
    return (gpio_get_level(GPIO_NUM_23));
  }
  
return 0;
}

