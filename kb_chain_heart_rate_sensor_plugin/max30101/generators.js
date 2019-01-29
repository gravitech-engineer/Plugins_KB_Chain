
Blockly.JavaScript['max30101_get_heart_rate'] = function(block) {
	var code = 'DEV_I2C1.MAX30101(0, 0x57).get_heart_rate()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['max30101_get_raw_data'] = function(block) {
	var dropdown_led = block.getFieldValue('led');
	var code = 'DEV_I2C1.MAX30101(0, 0x57).get_raw_data(' + dropdown_led + ')';
	return [code, Blockly.JavaScript.ORDER_NONE];
};
