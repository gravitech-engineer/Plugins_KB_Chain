Blockly.Blocks['kb_robot_motor_forward'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_motor_forward",
			"message0": Blockly.Msg.KB_ROBOT_MOTOR_FORWARD_MESSAGE,
			"args0": [{
				"type": "field_number",
				"name": "speed",
				"value": 50,
				"min": 0,
				"max": 100
			}, {
				"type": "field_number",
				"name": "time",
				"value": 1,
				"min": 0
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_MOTOR_FORWARD_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_motor_backward'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_motor_backward",
			"message0": Blockly.Msg.KB_ROBOT_MOTOR_BACKWARD_MESSAGE,
			"args0": [{
				"type": "field_number",
				"name": "speed",
				"value": 50,
				"min": 0,
				"max": 100
			}, {
				"type": "field_number",
				"name": "time",
				"value": 1,
				"min": 0
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_MOTOR_BACKWARD_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_motor_trun_left'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_motor_trun_left",
			"message0": Blockly.Msg.KB_ROBOT_MOTOR_TRUN_LEFT_MESSAGE,
			"args0": [{
				"type": "field_number",
				"name": "speed",
				"value": 50,
				"min": 0,
				"max": 100
			}, {
				"type": "field_number",
				"name": "time",
				"value": 1,
				"min": 0
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_MOTOR_TRUN_LEFT_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_motor_trun_right'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_motor_trun_right",
			"message0": Blockly.Msg.KB_ROBOT_MOTOR_TRUN_RIGHT_MESSAGE,
			"args0": [{
				"type": "field_number",
				"name": "speed",
				"value": 50,
				"min": 0,
				"max": 100
			}, {
				"type": "field_number",
				"name": "time",
				"value": 1,
				"min": 0
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_MOTOR_TRUN_RIGHT_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_motor_move'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_motor_move",
			"message0": Blockly.Msg.KB_ROBOT_MOTOR_MOVE_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "move",
				"options": [
					[ Blockly.Msg.KB_ROBOT_MOTOR_MOVE_FORWARD_MESSAGE, "1" ],
					[ Blockly.Msg.KB_ROBOT_MOTOR_MOVE_BACKWARD_MESSAGE, "2" ],
					[ Blockly.Msg.KB_ROBOT_MOTOR_MOVE_TRUN_LEFT_MESSAGE, "3" ],
					[ Blockly.Msg.KB_ROBOT_MOTOR_MOVE_TRUN_RIGHT_MESSAGE, "4" ]
				]
			}, {
				"type": "field_number",
				"name": "speed",
				"value": 50,
				"min": 0,
				"max": 100
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_MOTOR_MOVE_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_motor_wheel'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_motor_wheel",
			"message0": Blockly.Msg.KB_ROBOT_MOTOR_WHEEL_MESSAGE,
			"args0": [{
				"type": "field_number",
				"name": "speed1",
				"value": 50,
				"min": -100,
				"max": 100
			}, {
				"type": "field_number",
				"name": "speed2",
				"value": 50,
				"min": -100,
				"max": 100
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_MOTOR_WHEEL_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_motor_stop'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_motor_stop",
			"message0": Blockly.Msg.KB_ROBOT_MOTOR_STOP_MESSAGE,
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_MOTOR_STOP_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_servo'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_servo",
			"message0": Blockly.Msg.KB_ROBOT_SERVO_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "n",
				"options": [
					[ "1", "1" ],
					[ "2", "2" ],
					[ "3", "3" ],
					[ "4", "4" ],
				]
			}, {
			  "type": "input_value",
			  "name": "angle"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_SERVO_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_gpio_read'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_gpio_read",
			"message0": Blockly.Msg.KB_ROBOT_DIGITAL_READ_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "n",
				"options": [
					[ "1", "1" ],
					[ "2", "2" ],
					[ "3", "3" ],
					[ "4", "4" ],
					[ "5", "5" ],
					[ "6", "6" ],
					[ "7", "7" ],
					[ "8", "8" ]
			  ]
			}],
			"inputsInline": true,
			"output": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_DIGITAL_READ_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_gpio_write'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_gpio_write",
			"message0": Blockly.Msg.KB_ROBOT_DIGITAL_WRITE_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "n",
				"options": [
					[ "1", "1" ],
					[ "2", "2" ],
					[ "3", "3" ],
					[ "4", "4" ],
					[ "5", "5" ],
					[ "6", "6" ],
					[ "7", "7" ],
					[ "8", "8" ]
			  ]
			}, {
				"type": "input_value",
				"name": "value",
				"check": [
					"Number",
					"Boolean"
				]
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_DIGITAL_WRITE_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_analog_read'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_analog_read",
			"message0": Blockly.Msg.KB_ROBOT_ANALOG_READ_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "n",
				"options": [
					[ "1", "1" ],
					[ "2", "2" ],
					[ "3", "3" ],
					[ "4", "4" ],
					[ "5", "5" ],
					[ "6", "6" ],
					[ "7", "7" ],
					[ "8", "8" ]
				]
			}],
			"inputsInline": true,
			"output": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_ANALOG_READ_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_driver_analog_write'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_driver_analog_write",
			"message0": Blockly.Msg.KB_ROBOT_DRIVER_ANALOG_WRITE_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "n",
				"options": [
					[ "1", "1" ],
					[ "2", "2" ],
					[ "3", "3" ],
					[ "4", "4" ]
				]
			}, {
				"type": "input_value",
				"name": "value",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_DRIVER_ANALOG_WRITE_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_driver_frequency'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_driver_frequency",
			"message0": Blockly.Msg.KB_ROBOT_DRIVER_FREQ_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "n",
				"options": [
					[ "1", "1" ],
					[ "2", "2" ],
					[ "3", "3" ],
					[ "4", "4" ]
				]
			}, {
				"type": "field_number",
				"name": "freq",
				"value": 1000,
				"min": 1,
				"max": 65535
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_DRIVER_FREQ_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_driver_stepper'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_driver_stepper",
			"message0": Blockly.Msg.KB_ROBOT_DRIVER_STEPPER_MESSAGE,
			"args0": [{
				"type": "input_value",
				"name": "step",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_DRIVER_STEPPER_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_touch'] = {
	init: function() {
		this.jsonInit({
		  "type": "kb_robot_touch",
		  "message0": Blockly.Msg.KB_ROBOT_TOUCH_READ_MESSAGE,
		  "args0": [
			{
			  "type": "field_dropdown",
			  "name": "n",
			  "options": [
				[ "1", "1" ],
				[ "2", "2" ],
				[ "3", "3" ],
				[ "4", "4" ]
			  ]
			}
		  ],
		  "inputsInline": true,
		  "output": "Number",
		  "colour": 270,
		  "tooltip": Blockly.Msg.KB_ROBOT_TOUCH_READ_TOOLTIP,
		  "helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_neopixel_init'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_neopixel_init",
			"message0": Blockly.Msg.KB_ROBOT_NEOPIXEL_INIT_MESSAGE,
			"args0": [{
				"type": "field_number",
				"name": "n",
				"value": 1,
				"min": 1,
				"max": 340
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_NEOPIXEL_INIT_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_neopixel_setcolor'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_neopixel_setcolor",
			"message0": Blockly.Msg.KB_ROBOT_NEOPIXEL_SET_COLOR_MESSAGE,
			"args0": [{
				"type": "field_number",
				"name": "n",
				"value": 0,
				"min": 0
			}, {
				"type": "field_colour",
				"name": "color",
				"colour": "#ff0000"
			}],
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_NEOPIXEL_SET_COLOR_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_neopixel_setcolor2'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_neopixel_setcolor2",
			"message0": Blockly.Msg.KB_ROBOT_NEOPIXEL_SET_COLOR_2_MESSAGE,
			"args0": [{
				"type": "field_number",
				"name": "n",
				"value": 0,
				"min": 0
			}, {
				"type": "input_value",
				"name": "r",
				"check": "Number"
			}, {
				"type": "input_value",
				"name": "g",
				"check": "Number"
			}, {
				"type": "input_value",
				"name": "b",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_NEOPIXEL_SET_COLOR_2_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['kb_robot_neopixel_show'] = {
	init: function() {
		this.jsonInit({
			"type": "kb_robot_neopixel_show",
			"message0": Blockly.Msg.KB_ROBOT_NEOPIXEL_SHOW_MESSAGE,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 270,
			"tooltip": Blockly.Msg.KB_ROBOT_NEOPIXEL_SHOW_TOOLTIP,
			"helpUrl": ""
		});
	}
};


