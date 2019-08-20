Blockly.Blocks["kb_chain_lcd_driver.clear"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.kb_chain_lcd_driver_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.kb_chain_lcd_driver_CLR_TITLE);

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(300);
		this.setTooltip(Blockly.Msg.kb_chain_lcd_driver_CLR_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.kb_chain_lcd_driver_CLR_HELPURL);
	}
};

Blockly.Blocks["kb_chain_lcd_driver.backlight"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.kb_chain_lcd_driver_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.kb_chain_lcd_driver_BACKLIGHT_TITLE)
			.appendField(new Blockly.FieldDropdown([
				[Blockly.Msg.STATUS_OFF, "0"],
				[Blockly.Msg.STATUS_ON, "1"]
			]), 'STATUS');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(300);
		this.setTooltip(Blockly.Msg.kb_chain_lcd_driver_BACKLIGHT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.kb_chain_lcd_driver_BACKLIGHT_HELPURL);
	}
};

Blockly.Blocks["kb_chain_lcd_driver.print"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.kb_chain_lcd_driver_TITLE);

		this.appendValueInput('VALUE')
			.appendField(Blockly.Msg.kb_chain_lcd_driver_PRINT_TITLE)
			.appendField('(')
			.appendField(new Blockly.FieldNumber(1, 1, 20, 1), 'COLUMN')
			.appendField(',')
			.appendField(new Blockly.FieldNumber(1, 1, 4, 1), 'ROW')
			.appendField(')');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(300);
		this.setTooltip(Blockly.Msg.kb_chain_lcd_driver_PRINT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.kb_chain_lcd_driver_PRINT_HELPURL);
	}
};

Blockly.Blocks["kb_chain_lcd_driver.print_prec"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.kb_chain_lcd_driver_TITLE);

		this.appendValueInput('VALUE')
			.setCheck('Number')
			.appendField(Blockly.Msg.kb_chain_lcd_driver_PRINT_PREC_TITLE)
			.appendField('(')
			.appendField(new Blockly.FieldNumber(1, 1, 20, 1), 'COLUMN')
			.appendField(',')
			.appendField(new Blockly.FieldNumber(1, 1, 4, 1), 'ROW')
			.appendField(')')
			.appendField(Blockly.Msg.PRECISION_TITLE)
			.appendField(new Blockly.FieldNumber(2, 0, 4, 1), 'PREC');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(300);
		this.setTooltip(Blockly.Msg.kb_chain_lcd_driver_PRINT_PREC_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.kb_chain_lcd_driver_PRINT_PREC_HELPURL);
	}
};
