Blockly.JavaScript['rgb_set_color'] = function(block) {
	var dropdown_n = block.getFieldValue('n');
	var value_red = Blockly.JavaScript.valueToCode(block, 'red', Blockly.JavaScript.ORDER_ATOMIC) || 0;
	var value_green = Blockly.JavaScript.valueToCode(block, 'green', Blockly.JavaScript.ORDER_ATOMIC) || 0;
	var value_blue = Blockly.JavaScript.valueToCode(block, 'blue', Blockly.JavaScript.ORDER_ATOMIC) || 0;
	var code = 'DEV_I2C1.RGBLED(0, 0x3A).setColor();\n';
	return code;
};

Blockly.JavaScript['rgb.set_color2'] = function(block) {
	var dropdown_n = block.getFieldValue('n');
	var colour_color = block.getFieldValue('color');
	colour_color = colour_color.replace('#', '0x');
	var code = 'DEV_I2C1.RGBLED(0, 0x3A).setColor(' + dropdown_n + ', ' + colour_color + ');\n';
	return code;
};
