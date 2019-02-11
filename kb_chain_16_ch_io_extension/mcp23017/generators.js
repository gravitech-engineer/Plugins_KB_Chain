Blockly.JavaScript['mcp23017_digital_read'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var code = 'DEV_I2C1.MCP23017(0, 0x20).digitalRead(' + dropdown_pin + ')';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['mcp23017_digital_write'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var value_value = Blockly.JavaScript.valueToCode(block, 'value', Blockly.JavaScript.ORDER_ATOMIC);
	var code = 'DEV_I2C1.MCP23017(0, 0x20).digitalWrite(' + dropdown_pin + ', ' + value_value + ');\n';
	return code;
};
