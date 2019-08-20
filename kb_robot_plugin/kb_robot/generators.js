Blockly.JavaScript['kb_robot_motor_forward'] = function(block) {
  var number_speed = block.getFieldValue('speed');
  var number_time = block.getFieldValue('time');
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).motor(1, ' + number_speed + ');\tDEV_I2C1.KB_Robot(0, 0x49).motor(2, -' + number_speed + ');\tvTaskDelay(' + (number_time * 1000) + ' / portTICK_RATE_MS);\n';
  return code;
};

Blockly.JavaScript['kb_robot_motor_backward'] = function(block) {
  var number_speed = block.getFieldValue('speed');
  var number_time = block.getFieldValue('time');
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).motor(1, -' + number_speed + ');\tDEV_I2C1.KB_Robot(0, 0x49).motor(2, ' + number_speed + ');\tvTaskDelay(' + (number_time * 1000) + ' / portTICK_RATE_MS);\n';
  return code;
};

Blockly.JavaScript['kb_robot_motor_trun_left'] = function(block) {
  var number_speed = block.getFieldValue('speed');
  var number_time = block.getFieldValue('time');
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).motor(1, 0);\tDEV_I2C1.KB_Robot(0, 0x49).motor(2, -' + number_speed + ');\tvTaskDelay(' + (number_time * 1000) + ' / portTICK_RATE_MS);\n';
  return code;
};

Blockly.JavaScript['kb_robot_motor_trun_right'] = function(block) {
  var number_speed = block.getFieldValue('speed');
  var number_time = block.getFieldValue('time');
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).motor(1, ' + number_speed + ');\tDEV_I2C1.KB_Robot(0, 0x49).motor(2, 0);\tvTaskDelay(' + (number_time * 1000) + ' / portTICK_RATE_MS);\n';
  return code;
};

Blockly.JavaScript['kb_robot_motor_move'] = function(block) {
  var dropdown_move = block.getFieldValue('move');
  var number_speed = block.getFieldValue('speed');
  var code = '';;
  if (dropdown_move == 1) {
    code = 'DEV_I2C1.KB_Robot(0, 0x49).motor(1, ' + number_speed + ');\tDEV_I2C1.KB_Robot(0, 0x49).motor(2, -' + number_speed + ');\n';
  } else if (dropdown_move == 2) {
    code = 'DEV_I2C1.KB_Robot(0, 0x49).motor(1, -' + number_speed + ');\tDEV_I2C1.KB_Robot(0, 0x49).motor(2, ' + number_speed + ');\n';
  } else if (dropdown_move == 3) {
    code = 'DEV_I2C1.KB_Robot(0, 0x49).motor(1, 0);\tDEV_I2C1.KB_Robot(0, 0x49).motor(2, -' + number_speed + ');\n';
  } else if (dropdown_move == 4) {
    code = 'DEV_I2C1.KB_Robot(0, 0x49).motor(1, ' + number_speed + ');\tDEV_I2C1.KB_Robot(0, 0x49).motor(2, 0);\n';
  }
  return code;
};

Blockly.JavaScript['kb_robot_motor_wheel'] = function(block) {
  var number_speed1 = block.getFieldValue('speed1');
  var number_speed2 = block.getFieldValue('speed2');
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).motor(1, ' + number_speed1 + ');\tDEV_I2C1.KB_Robot(0, 0x49).motor(2, ' + number_speed2 + ' * -1);\n';
  return code;
};

Blockly.JavaScript['kb_robot_motor_stop'] = function(block) {
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).motor(1, 0);\tDEV_I2C1.KB_Robot(0, 0x49).motor(2, 0);\n';
  return code;
};

Blockly.JavaScript['kb_robot_servo'] = function(block) {
  var dropdown_n = block.getFieldValue('n');
  var value_angle = Blockly.JavaScript.valueToCode(block, 'angle', Blockly.JavaScript.ORDER_ATOMIC) || 0;
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).servo(' + dropdown_n + ', ' + value_angle + ');\n';
  return code;
};

Blockly.JavaScript['kb_robot_gpio_read'] = function(block) {
  var dropdown_n = block.getFieldValue('n');
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).digital_read(' + dropdown_n + ')';
  return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['kb_robot_gpio_write'] = function(block) {
  var dropdown_n = block.getFieldValue('n');
  var value_value = Blockly.JavaScript.valueToCode(block, 'value', Blockly.JavaScript.ORDER_ATOMIC) || 0;
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).digital_write(' + dropdown_n + ', ' + value_value + ');\n';
  return code;
};

Blockly.JavaScript['kb_robot_analog_read'] = function(block) {
  var dropdown_n = block.getFieldValue('n');
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).analog_read(' + dropdown_n + ')';
  return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['kb_robot_driver_analog_write'] = function(block) {
  var dropdown_n = block.getFieldValue('n');
  var value_value = Blockly.JavaScript.valueToCode(block, 'value', Blockly.JavaScript.ORDER_ATOMIC) || 0;
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).driver_setDuty(' + dropdown_n + ', ' + value_value + ');\n';
  return code;
};

Blockly.JavaScript['kb_robot_driver_frequency'] = function(block) {
  var dropdown_n = block.getFieldValue('n');
  var number_freq = block.getFieldValue('freq');
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).driver_setFreq(' + dropdown_n + ', ' + number_freq + ');\n';
  return code;
};

Blockly.JavaScript['kb_robot_driver_stepper'] = function(block) {
  var value_step = Blockly.JavaScript.valueToCode(block, 'step', Blockly.JavaScript.ORDER_ATOMIC) || 0;
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).driver_stepperMotor(' + value_step + ');\n';
  return code;
};

Blockly.JavaScript['kb_robot_touch'] = function(block) {
  var dropdown_n = block.getFieldValue('n');
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).touch(' + dropdown_n + ')';
  return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['kb_robot_neopixel_init'] = function(block) {
  var number_n = block.getFieldValue('n');
  // TODO: Assemble JavaScript into code variable.
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).neopixel_init(' + number_n + ');\n';
  return code;
};

Blockly.JavaScript['kb_robot_neopixel_setcolor'] = function(block) {
  var number_n = block.getFieldValue('n');
  var colour_color = block.getFieldValue('color').replace('#', '0x');;
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).neopixel_setColor(' + number_n + ', ' + colour_color + ');\n';
  return code;
};

Blockly.JavaScript['kb_robot_neopixel_setcolor2'] = function(block) {
  var number_n = block.getFieldValue('n');
  var value_r = Blockly.JavaScript.valueToCode(block, 'r', Blockly.JavaScript.ORDER_ATOMIC) || 0;
  var value_g = Blockly.JavaScript.valueToCode(block, 'g', Blockly.JavaScript.ORDER_ATOMIC) || 0;
  var value_b = Blockly.JavaScript.valueToCode(block, 'b', Blockly.JavaScript.ORDER_ATOMIC) || 0;
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).neopixel_setColor(' + number_n + ', ' + value_r + ', ' + value_g + ', ' + value_b + ');\n';
  return code;
};

Blockly.JavaScript['kb_robot_neopixel_show'] = function(block) {
  var code = 'DEV_I2C1.KB_Robot(0, 0x49).neopixel_show();\n';
  return code;
};