Blockly.JavaScript['lis3dh_get_acceleration'] = function(block) {
	var dropdown_axis = block.getFieldValue('axis');
	var code = 'DEV_I2C1.LIS3DH(0, 0x18).get_acceleration(' + dropdown_axis + ')';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['lis3dh_get_acceleration2'] = function(block) {
	var dropdown_address = block.getFieldValue('address');
	var dropdown_axis = block.getFieldValue('axis');
	var code = 'DEV_I2C1.LIS3DH(0, ' + dropdown_address + ').get_acceleration(' + dropdown_axis + ')';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['lis3dh_get_adc'] = function(block) {
	var dropdown_address = block.getFieldValue('address');
	var dropdown_ch = block.getFieldValue('ch');
	var code = 'DEV_I2C1.LIS3DH(0, ' + dropdown_address + ').get_adc(' + dropdown_ch + ')';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

/*
Blockly.JavaScript['lis3dh_get_temperature'] = function(block) {
	var dropdown_address = block.getFieldValue('address');
	var code = 'DEV_I2C1.LIS3DH(0, ' + dropdown_address + ').get_adc(3)';
	return [code, Blockly.JavaScript.ORDER_NONE];
};
*/