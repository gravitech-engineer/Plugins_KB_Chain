Blockly.JavaScript['bme680_get_temperature'] = function(block) {
	var code = 'DEV_I2C1.BME680(0, 0x76).getTemperature()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['bme680_get_humidity'] = function(block) {
	var code = 'DEV_I2C1.BME680(0, 0x76).getHumidity()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['bme680_get_pressure'] = function(block) {
	var code = 'DEV_I2C1.BME680(0, 0x76).getPressure()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['bme680_get_gas_resistance'] = function(block) {
	var code = 'DEV_I2C1.BME680(0, 0x76).getGasResistance()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['bme680_get_altitude'] = function(block) {
	var code = 'DEV_I2C1.BME680(0, 0x76).getAltitude()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};
