Blockly.JavaScript['read_proximity'] = function(block) {
	var code = 'DEV_I2C1.VCNL4200(0, 0x51).getProximity()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['read_ambient'] = function(block) {
	var code = 'DEV_I2C1.VCNL4200(0, 0x51).getAmbient()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};



