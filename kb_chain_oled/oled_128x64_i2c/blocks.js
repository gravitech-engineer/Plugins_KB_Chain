function oled128x64_init(_this) {
	// oled chipset
	_this.appendDummyInput()
		.appendField(new Blockly.FieldDropdown([
			["SSD1306", "ocs_ssd1306"],
			["SH1106", "ocs_sh1106"]
		]), 'CHIPSET');

	// i2c channel 0 to 64
	var channel_array = [];
	for (var i = 0;i <= 64; i++) {
		channel_array.push([String(i), String(i)]);
	}
	_this.appendDummyInput()
		.appendField(Blockly.Msg.CHANNEL)
		.appendField(new Blockly.FieldDropdown(channel_array), 'CHANNEL');

	// device addess
	_this.appendDummyInput()
		.appendField(Blockly.Msg.ADDRESS)
		.appendField(new Blockly.FieldDropdown([
			["0x3C", "60"],
			["0x3D", "61"]
		]), 'ADDRESS');
}

Blockly.Blocks["oled_128x64_i2c.clear"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.OLED_128X64_I2C_TITLE);

		// init
		oled128x64_init(this);

		this.appendDummyInput()
			.appendField(Blockly.Msg.OLED_128X64_I2C_CLR_TITLE);

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.OLED_128X64_I2C_CLR_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.OLED_128X64_I2C_CLR_HELPURL);
	}
};

Blockly.Blocks["oled_128x64_i2c.putstr"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.OLED_128X64_I2C_TITLE);

		// init
		oled128x64_init(this);

		this.appendValueInput('VALUE')
			.appendField(Blockly.Msg.OLED_128X64_I2C_PRINT_TITLE)
			.appendField('(')
			.appendField(new Blockly.FieldNumber(1, 1, 21, 1), 'COLUMN')
			.appendField(',')
			.appendField(new Blockly.FieldNumber(1, 1, 8, 1), 'ROW')
			.appendField(')');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.OLED_128X64_I2C_PRINT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.OLED_128X64_I2C_PRINT_HELPURL);
	}
};

Blockly.Blocks["oled_128x64_i2c.putstr_prec"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.OLED_128X64_I2C_TITLE);

		// init
		oled128x64_init(this);

		this.appendValueInput('VALUE')
			.setCheck('Number')
			.appendField(Blockly.Msg.OLED_128X64_I2C_PRINT_PREC_TITLE)
			.appendField('(')
			.appendField(new Blockly.FieldNumber(1, 1, 21, 1), 'COLUMN')
			.appendField(',')
			.appendField(new Blockly.FieldNumber(1, 1, 8, 1), 'ROW')
			.appendField(')')
			.appendField(Blockly.Msg.PRECISION_TITLE)
			.appendField(new Blockly.FieldNumber(2, 0, 4, 1), 'PREC');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.OLED_128X64_I2C_PRINT_PREC_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.OLED_128X64_I2C_PRINT_PREC_HELPURL);
	}
};

Blockly.Blocks["oled_128x64_i2c.putstr_big"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.OLED_128X64_I2C_TITLE);

		// init
		oled128x64_init(this);

		this.appendValueInput('VALUE')
			.appendField(Blockly.Msg.OLED_128X64_I2C_PRINT_BIG_TITLE)
			.appendField('(')
			.appendField(new Blockly.FieldNumber(1, 1, 21, 1), 'COLUMN')
			.appendField(',')
			.appendField(new Blockly.FieldNumber(1, 1, 8, 1), 'ROW')
			.appendField(')');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.OLED_128X64_I2C_PRINT_BIG_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.OLED_128X64_I2C_PRINT_BIG_HELPURL);
	}
};

Blockly.Blocks["oled_128x64_i2c.putstr_big_prec"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.OLED_128X64_I2C_TITLE);

		// init
		oled128x64_init(this);

		this.appendValueInput('VALUE')
			.setCheck('Number')
			.appendField(Blockly.Msg.OLED_128X64_I2C_PRINT_BIG_PREC_TITLE)
			.appendField('(')
			.appendField(new Blockly.FieldNumber(1, 1, 21, 1), 'COLUMN')
			.appendField(',')
			.appendField(new Blockly.FieldNumber(1, 1, 8, 1), 'ROW')
			.appendField(')')
			.appendField(Blockly.Msg.PRECISION_TITLE)
			.appendField(new Blockly.FieldNumber(2, 0, 4, 1), 'PREC');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.OLED_128X64_I2C_PRINT_BIG_PREC_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.OLED_128X64_I2C_PRINT_BIG_PREC_HELPURL);
	}
};
