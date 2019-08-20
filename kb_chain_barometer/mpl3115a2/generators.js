Blockly.JavaScript['mpl3115a2.read_pressure'] = function(block) {
	var code = 'DEV_I2C1.MPL3115A2(0, 0x60).getPressure()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['mpl3115a2.read_altitude'] = function(block) {
	var code = 'DEV_I2C1.MPL3115A2(0, 0x60).getAltitude()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['mpl3115a2.read_temperature'] = function(block) {
	var code = 'DEV_I2C1.MPL3115A2(0, 0x60).getTemperature()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['mpl3115a2.set_mode'] = function(block) {
	var dropdown_mode = block.getFieldValue('mode');
	var code = 'DEV_I2C1.MPL3115A2(0, 0x60).setMode(' + dropdown_mode + ');\n';
	return code;
};
