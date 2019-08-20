Blockly.Blocks['rgb.set_color'] = {
	init: function() {
		this.jsonInit({
			"message0": "%1 %2 set color to RGB( %3 , %4 , %5 )",
			"args0": [{
				"type": "field_dropdown",
				"name": "n",
				"options": [
					[ "LED1", "1" ],
					[ "LED2", "2" ],
					[ "LED3", "3" ],
					[ "LED4", "4" ]
				]
			}, {
				"type": "input_dummy"
			}, {
				"type": "input_value",
				"name": "red",
				"check": "Number"
			}, {
				"type": "input_value",
				"name": "green",
				"check": "Number"
			}, {
				"type": "input_value",
				"name": "blue",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 300,
			"tooltip": "",
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['rgb.set_color2'] = {
	init: function() {
		this.jsonInit({
			"message0": "%1 set color to %2",
			"args0": [{
				"type": "field_dropdown",
				"name": "n",
				"options": [
					[ "LED1", "1" ],
					[ "LED2", "2" ],
					[ "LED3", "3" ],
					[ "LED4", "4" ]
				]
			}, {
				"type": "field_colour",
				"name": "color",
				"colour": "#ff0000"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 300,
			"tooltip": "",
			"helpUrl": ""
		});
	}
};
