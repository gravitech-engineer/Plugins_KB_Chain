Blockly.Blocks['mcp23017_digital_read'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.MCP23017_DIGITAL_READ_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "PA0", "0" ],
					[ "PA1", "1" ],
					[ "PA2", "2" ],
					[ "PA3", "3" ],
					[ "PA4", "4" ],
					[ "PA5", "5" ],
					[ "PA6", "6" ],
					[ "PA7", "7" ],
					[ "PB0", "8" ],
					[ "PB1", "9" ],
					[ "PB2", "10" ], 
					[ "PB3", "11" ],
					[ "PB4", "12" ],
					[ "PB5", "13" ],
					[ "PB6", "14" ],
					[ "PB7", "15"]
				]
			}],
			"inputsInline": true,
			"output": "Number",
			"colour": 285,
			"tooltip": Blockly.Msg.MCP23017_DIGITAL_READ_TOOLTIP,
			"helpUrl": "https://www.kidbright.io/product-page/kb-chain-16-ch-io-extension"
		});
	}
};

Blockly.Blocks['mcp23017_digital_write'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.MCP23017_DIGITAL_WRITE_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "PA0", "0" ],
					[ "PA1", "1" ],
					[ "PA2", "2" ],
					[ "PA3", "3" ],
					[ "PA4", "4" ],
					[ "PA5", "5" ],
					[ "PA6", "6" ],
					[ "PA7", "7" ],
					[ "PB0", "8" ],
					[ "PB1", "9" ],
					[ "PB2", "10" ], 
					[ "PB3", "11" ],
					[ "PB4", "12" ],
					[ "PB5", "13" ],
					[ "PB6", "14" ],
					[ "PB7", "15"]
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
			"colour": 285,
			"tooltip": Blockly.Msg.MCP23017_DIGITAL_WRITE_TOOLTIP,
			"helpUrl": "https://www.kidbright.io/product-page/kb-chain-16-ch-io-extension"
		});
	}
};

