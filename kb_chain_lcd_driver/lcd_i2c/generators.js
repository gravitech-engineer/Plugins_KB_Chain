Blockly.JavaScript['kb_chain_lcd_driver.clear'] = function(block) {
	return 'DEV_I2C1.LCD_I2C(0, 0x22).clear();\n';
};

Blockly.JavaScript['kb_chain_lcd_driver.backlight'] = function(block) {
	return 'DEV_I2C1.LCD_I2C(0, 0x22).backlight(' + block.getFieldValue('STATUS') + ');\n';
}

Blockly.JavaScript['kb_chain_lcd_driver.print'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'VALUE', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';

	var column = parseInt(block.getFieldValue('COLUMN')) - 1;
	var row = parseInt(block.getFieldValue('ROW')) - 1;

	return 'DEV_I2C1.LCD_I2C(0, 0x22).print(' + column + ', ' + row + ', ' + argument0 + ');\n';
};

Blockly.JavaScript['kb_chain_lcd_driver.print_prec'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'VALUE', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';

	var column = parseInt(block.getFieldValue('COLUMN')) - 1;
	var row = parseInt(block.getFieldValue('ROW')) - 1;
	var prec = parseInt(block.getFieldValue('PREC'));
	if (prec < 0) {
		prec = 0;
	}
	if (prec > 4) {
		prec = 4;
	}

	return 'DEV_I2C1.LCD_I2C(0, 0x22).print(' + column + ', ' + row + ', ' + argument0 + ', ' + prec + ');\n';
};
