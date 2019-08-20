Blockly.Blocks['mpl3115a2.read_pressure'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.MPL3115A2_READ_PRESSURE_MESSAGE,
			"output": "Number",
			"colour": 300,
			"tooltip": Blockly.Msg.MPL3115A2_READ_PRESSURE_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['mpl3115a2.read_altitude'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.MPL3115A2_READ_ALTITUDE_MESSAGE,
			"output": "Number",
			"colour": 300,
			"tooltip": Blockly.Msg.MPL3115A2_READ_ALTITUDE_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['mpl3115a2.read_temperature'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.MPL3115A2_READ_TEMPERATURE_MESSAGE,
			"output": "Number",
			"colour": 300,
			"tooltip": Blockly.Msg.MPL3115A2_READ_TEMPERATURE_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['mpl3115a2.set_mode'] = {
	init: function() {
		this.jsonInit({
			"message0": "Set mode to %1",
			"args0": [{
				"type": "field_dropdown",
				"name": "mode",
				"options": [
					[ "Barometer", "0" ],
					[ "Altimeter", "1" ]
				]
			}],
			"previousStatement": null,
			"nextStatement": null,
			"colour": 300,
			"tooltip": "",
			"helpUrl": ""
		});
	}
};
