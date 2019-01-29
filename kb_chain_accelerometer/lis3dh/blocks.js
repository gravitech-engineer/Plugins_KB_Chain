Blockly.Blocks['lis3dh_get_acceleration'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.LIS3DH_ACCELERATION)
			.appendField(new Blockly.FieldDropdown([["x","1"], ["y","2"], ["z","3"], ["strength","4"]]), "axis");
		this.setOutput(true, "Number");
		this.setColour(285);
		this.setTooltip("");
		this.setHelpUrl("https://www.gravitechthai.com/");
	}
};

Blockly.Blocks['lis3dh_get_acceleration2'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.LIS3DH_ACCELEROMETER_ADDRESS)
			.appendField(new Blockly.FieldDropdown([["0x18","0x18"], ["0x19","0x19"]]), "address")
			.appendField(Blockly.Msg.LIS3DH_READ_ACCELERATION)
			.appendField(new Blockly.FieldDropdown([["x","1"], ["y","2"], ["z","3"], ["strength","4"]]), "axis");
		this.setOutput(true, "Number");
		this.setColour(285);
		this.setTooltip("");
		this.setHelpUrl("https://www.gravitechthai.com/");
	}
};

Blockly.Blocks['lis3dh_get_adc'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.LIS3DH_ACCELEROMETER_ADDRESS)
			.appendField(new Blockly.FieldDropdown([["0x18","0x18"], ["0x19","0x19"]]), "address")
			.appendField(Blockly.Msg.LIS3DH_READ_ADC)
			.appendField(new Blockly.FieldDropdown([["1","1"], ["2","2"], ["3","3"]]), "ch");
		this.setOutput(true, "Number");
		this.setColour(285);
		this.setTooltip("");
		this.setHelpUrl("https://www.gravitechthai.com/");
	}
};

/*
Blockly.Blocks['lis3dh_get_temperature'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Accelerometer address")
			.appendField(new Blockly.FieldDropdown([["0x18","0x18"], ["0x19","0x19"]]), "address")
			.appendField("read temperature");
		this.setOutput(true, "Number");
		this.setColour(285);
		this.setTooltip("");
		this.setHelpUrl("https://www.gravitechthai.com/");
	}
};
*/

