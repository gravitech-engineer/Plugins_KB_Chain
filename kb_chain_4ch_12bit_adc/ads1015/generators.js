Blockly.JavaScript['ads1015_read_analog'] = function(block) {
	var dropdown_ch = block.getFieldValue('ch');
	var code = 'DEV_I2C1.ADS1015(0, 0x48).getRawValue(' + dropdown_ch + ')';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['ads1015_set_gain'] = function(block) {
	var dropdown_gain = block.getFieldValue('gain');
	var code = 'DEV_I2C1.ADS1015(0, 0x48).setGain(' + dropdown_gain + ');\n';
	return code;
};

Blockly.JavaScript['ads1015_read_voltage'] = function(block) {
	var dropdown_ch = block.getFieldValue('ch');
	var code = 'DEV_I2C1.ADS1015(0, 0x48).readVoltage(' + dropdown_ch + ')';
	return [code, Blockly.JavaScript.ORDER_NONE];
};
