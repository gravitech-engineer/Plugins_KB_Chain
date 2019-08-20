Blockly.JavaScript['oled_128x64_i2c.clear'] = function(block) {
	return 'DEV_I2C1.OLED_128X64_I2C(' + block.getFieldValue('CHIPSET') + ', ' + block.getFieldValue('CHANNEL') + ', ' + block.getFieldValue('ADDRESS') + ').clear();\n';
};

Blockly.JavaScript['oled_128x64_i2c.putstr'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'VALUE', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var column = Blockly.JavaScript.valueToCode(block, 'COLUMN', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var row = Blockly.JavaScript.valueToCode(block, 'ROW', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';

	return 'DEV_I2C1.OLED_128X64_I2C(' + block.getFieldValue('CHIPSET') + ', ' + block.getFieldValue('CHANNEL') + ', ' + block.getFieldValue('ADDRESS') + ').putstr(' + column + ', ' + row + ', ' + argument0 + ');\n';
};

Blockly.JavaScript['oled_128x64_i2c.putstr_prec'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'VALUE', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var column = Blockly.JavaScript.valueToCode(block, 'COLUMN', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var row = Blockly.JavaScript.valueToCode(block, 'ROW', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
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
	var column = Blockly.JavaScript.valueToCode(block, 'COLUMN', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var row = Blockly.JavaScript.valueToCode(block, 'ROW', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';

	return 'DEV_I2C1.OLED_128X64_I2C(' + block.getFieldValue('CHIPSET') + ', ' + block.getFieldValue('CHANNEL') + ', ' + block.getFieldValue('ADDRESS') + ').putstr_big(' + column + ', ' + row + ', ' + argument0 + ');\n';
};

Blockly.JavaScript['oled_128x64_i2c.putstr_big_prec'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'VALUE', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var column = Blockly.JavaScript.valueToCode(block, 'COLUMN', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var row = Blockly.JavaScript.valueToCode(block, 'ROW', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var prec = parseInt(block.getFieldValue('PREC'));

	if (prec < 0) {
		prec = 0;
	}
	if (prec > 4) {
		prec = 4;
	}

	return 'DEV_I2C1.OLED_128X64_I2C(' + block.getFieldValue('CHIPSET') + ', ' + block.getFieldValue('CHANNEL') + ', ' + block.getFieldValue('ADDRESS') + ').putstr_big(' + column + ', ' + row + ', ' + argument0 + ', ' + prec + ');\n';
};

Blockly.JavaScript["oled_128x64_i2c.column_number"] = function(block) {
	// Numeric value.
	var code = parseFloat(block.getFieldValue('VALUE'));
	var order = code >= 0 ? Blockly.JavaScript.ORDER_ATOMIC : Blockly.JavaScript.ORDER_UNARY_NEGATION;
	return [code, order];
};

Blockly.JavaScript["oled_128x64_i2c.row_number"] = function(block) {
	return Blockly.JavaScript["oled_128x64_i2c.column_number"](block);
};

Blockly.JavaScript["oled_128x64_i2c.string_number"] = function(block) {
	return [
		'(char *)"' + block.getFieldValue('VALUE') + '"',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript["oled_128x64_i2c.number"] = function(block) {
	return Blockly.JavaScript["oled_128x64_i2c.column_number"](block);
};
