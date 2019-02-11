Blockly.Blocks["ads1015_read_analog"] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.ADS1015_READ_ANALOG_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "ch",
				"options": [
					[ "ANA0", "4" ],
					[ "ANA1", "5" ],
					[ "ANA2", "6" ],
					[ "ANA3", "7" ],
					[ "(+)ANA0, (-)ANA1", "0" ],
					[ "(+)ANA0, (-)ANA3", "1" ],
					[ "(+)ANA1, (-)ANA3", "2" ],
					[ "(+)ANA2, (-)ANA3", "3" ]
				]
			}],
			"inputsInline": true,
			"output": "Number",
			"colour": 285,
			"tooltip": Blockly.Msg.ADS1015_READ_ANALOG_TOOLTIP,
			"helpUrl": "https://www.kidbright.io/product-page/kb-chain-4-ch-12-bit-adc"
		})
	}
};

Blockly.Blocks["ads1015_set_gain"] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.ADS1015_SET_GAIN_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "gain",
				"options": [
					[ "±6.144V", "0" ],
					[ "±4.096V", "1" ],
					[ "±2.048V", "2" ],
					[ "±1.024V", "3" ],
					[ "±0.512V", "4" ],
					[ "±0.256V", "5" ]
				]
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 285,
			"tooltip": Blockly.Msg.ADS1015_SET_GAIN_TOOLTIP,
			"helpUrl": "https://www.kidbright.io/product-page/kb-chain-4-ch-12-bit-adc"
		})
	}
};

Blockly.Blocks["ads1015_read_voltage"] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.ADS1015_READ_VOLTAGE_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "ch",
				"options": [
					[ "ANA0", "4" ],
					[ "ANA1", "5" ],
					[ "ANA2", "6" ],
					[ "ANA3", "7" ],
					[ "(+)ANA0, (-)ANA1", "0" ],
					[ "(+)ANA0, (-)ANA3", "1" ],
					[ "(+)ANA1, (-)ANA3", "2" ],
					[ "(+)ANA2, (-)ANA3", "3" ]
				]
			}],
			"inputsInline": true,
			"output": "Number",
			"colour": 285,
			"tooltip": Blockly.Msg.ADS1015_READ_VOLTAGE_TOOLTIP,
			"helpUrl": "https://www.kidbright.io/product-page/kb-chain-4-ch-12-bit-adc"
		})
	}
};
