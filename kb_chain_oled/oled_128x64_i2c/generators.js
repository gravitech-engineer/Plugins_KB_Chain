Blockly.JavaScript['oled_128x64_i2c.clear'] = function(block) {
	return 'DEV_I2C1.OLED_128X64_I2C(' + block.getFieldValue('CHIPSET') + ', ' + block.getFieldValue('CHANNEL') + ', ' + block.getFieldValue('ADDRESS') + ').clear();\n';
};

Blockly.JavaScript['oled_128x64_i2c.putstr'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'VALUE', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';

	var column = parseInt(block.getFieldValue('COLUMN')) - 1;
	var row = parseInt(block.getFieldValue('ROW')) - 1;

	return 'DEV_I2C1.OLED_128X64_I2C(' + block.getFieldValue('CHIPSET') + ', ' + block.getFieldValue('CHANNEL') + ', ' + block.getFieldValue('ADDRESS') + ').putstr(' + column + ', ' + row + ', ' + argument0 + ');\n';
};

Blockly.JavaScript['oled_128x64_i2c.putstr_prec'] = function(block) {
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

	return 'DEV_I2C1.OLED_128X64_I2C(' + block.getFieldValue('CHIPSET') + ', ' + block.getFieldValue('CHANNEL') + ', ' + block.getFieldValue('ADDRESS') + ').putstr(' + column + ', ' + row + ', ' + argument0 + ', ' + prec + ');\n';
};

Blockly.JavaScript['oled_128x64_i2c.putstr_big'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'VALUE', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';

	var column = parseInt(block.getFieldValue('COLUMN')) - 1;
	var row = parseInt(block.getFieldValue('ROW')) - 1;

	return 'DEV_I2C1.OLED_128X64_I2C(' + block.getFieldValue('CHIPSET') + ', ' + block.getFieldValue('CHANNEL') + ', ' + block.getFieldValue('ADDRESS') + ').putstr_big(' + column + ', ' + row + ', ' + argument0 + ');\n';
};

Blockly.JavaScript['oled_128x64_i2c.putstr_big_prec'] = function(block) {
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

	return 'DEV_I2C1.OLED_128X64_I2C(' + block.getFieldValue('CHIPSET') + ', ' + block.getFieldValue('CHANNEL') + ', ' + block.getFieldValue('ADDRESS') + ').putstr_big(' + column + ', ' + row + ', ' + argument0 + ', ' + prec + ');\n';
};
