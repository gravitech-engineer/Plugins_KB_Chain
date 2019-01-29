Blockly.Blocks['max30101_get_heart_rate'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.MAX30101_HEART_RATE);
		this.setOutput(true, "Number");
		this.setColour(285);
		this.setTooltip("");
		this.setHelpUrl("https://www.gravitechthai.com/");
	}
};

Blockly.Blocks['max30101_get_raw_data'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.MAX30101_RAW_DATA)
			.appendField(new Blockly.FieldDropdown([[Blockly.Msg.MAX30101_RED,"1"], [Blockly.Msg.MAX30101_IR,"2"]]), "led");
		this.setOutput(true, "Number");
		this.setColour(285);
		this.setTooltip("");
		this.setHelpUrl("https://www.gravitechthai.com/");
	}
};