Blockly.JavaScript['veml6075_read_uvi'] = function(block) {
	var code = 'DEV_I2C1.VEML6075(0, 0x10).get_uvi()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['veml6075_read_uva'] = function(block) {
	var code = 'DEV_I2C1.VEML6075(0, 0x10).get_uva()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['veml6075_read_uvb'] = function(block) {
	var code = 'DEV_I2C1.VEML6075(0, 0x10).get_uvb()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

