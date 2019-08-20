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

		this.appendDummyInput()
			.appendField(Blockly.Msg.OLED_128X64_I2C_PRINT_TITLE + ' (');
		this.appendValueInput("COLUMN")
			.setCheck("Number");
		this.appendDummyInput()
			.appendField(',');
		this.appendValueInput("ROW")
			.setCheck("Number");
		this.appendDummyInput()
			.appendField(')');
		this.appendValueInput('VALUE');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.OLED_128X64_I2C_PRINT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.OLED_128X64_I2C_PRINT_HELPURL);
	},
	// custom xmlToolbox
	xmlToolbox: function() {
		return $(document.createElement('block')).attr({
			type: 'oled_128x64_i2c.putstr'
		}).append('\
		   <value name="COLUMN">\
			   <shadow type="oled_128x64_i2c.column_number">\
			   </shadow>\
		   </value>\
		   <value name="ROW">\
			   <shadow type="oled_128x64_i2c.row_number">\
			   </shadow>\
		   </value>\
		   <value name="VALUE">\
			  <shadow type="oled_128x64_i2c.string_number">\
			  </shadow>\
		  </value>'
	   );
   }
};

Blockly.Blocks["oled_128x64_i2c.putstr_prec"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.OLED_128X64_I2C_TITLE);

		// init
		oled128x64_init(this);

		this.appendDummyInput()
			.appendField(Blockly.Msg.OLED_128X64_I2C_PRINT_PREC_TITLE + ' (');
		this.appendValueInput("COLUMN")
			.setCheck("Number");
		this.appendDummyInput()
			.appendField(',');
		this.appendValueInput("ROW")
			.setCheck("Number");
		this.appendDummyInput()
			.appendField(')')
			.appendField(Blockly.Msg.PRECISION_TITLE)
			.appendField(new Blockly.FieldNumber(2, 0, 4, 1), 'PREC')
			.appendField(' ');
		this.appendValueInput('VALUE')
			.setCheck('Number');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.OLED_128X64_I2C_PRINT_PREC_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.OLED_128X64_I2C_PRINT_PREC_HELPURL);
	},
	// custom xmlToolbox
	xmlToolbox: function() {
		return $(document.createElement('block')).attr({
			type: 'oled_128x64_i2c.putstr_prec'
		}).append('\
		   <value name="COLUMN">\
			   <shadow type="oled_128x64_i2c.column_number">\
			   </shadow>\
		   </value>\
		   <value name="ROW">\
			   <shadow type="oled_128x64_i2c.row_number">\
			   </shadow>\
		   </value>\
		   <value name="VALUE">\
			  <shadow type="oled_128x64_i2c.number">\
			  </shadow>\
		  </value>'
	   );
   }
};

Blockly.Blocks["oled_128x64_i2c.putstr_big"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.OLED_128X64_I2C_TITLE);

		// init
		oled128x64_init(this);

		this.appendDummyInput()
			.appendField(Blockly.Msg.OLED_128X64_I2C_PRINT_BIG_TITLE + ' (');
		this.appendValueInput("COLUMN")
			.setCheck("Number");
		this.appendDummyInput()
			.appendField(',');
		this.appendValueInput("ROW")
			.setCheck("Number");
		this.appendDummyInput()
			.appendField(')');
		this.appendValueInput('VALUE');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.OLED_128X64_I2C_PRINT_BIG_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.OLED_128X64_I2C_PRINT_BIG_HELPURL);
	},
	// custom xmlToolbox
	xmlToolbox: function() {
		return $(document.createElement('block')).attr({
			type: 'oled_128x64_i2c.putstr_big'
		}).append('\
		   <value name="COLUMN">\
			   <shadow type="oled_128x64_i2c.column_number">\
			   </shadow>\
		   </value>\
		   <value name="ROW">\
			   <shadow type="oled_128x64_i2c.row_number">\
			   </shadow>\
		   </value>\
		   <value name="VALUE">\
			  <shadow type="oled_128x64_i2c.string_number">\
			  </shadow>\
		  </value>'
	   );
   }
};

Blockly.Blocks["oled_128x64_i2c.putstr_big_prec"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.OLED_128X64_I2C_TITLE);

		// init
		oled128x64_init(this);

		this.appendDummyInput()
			.appendField(Blockly.Msg.OLED_128X64_I2C_PRINT_BIG_PREC_TITLE + ' (');
		this.appendValueInput("COLUMN")
			.setCheck("Number");
		this.appendDummyInput()
			.appendField(',');
		this.appendValueInput("ROW")
			.setCheck("Number");
		this.appendDummyInput()
			.appendField(')')
			.appendField(Blockly.Msg.PRECISION_TITLE)
			.appendField(new Blockly.FieldNumber(2, 0, 4, 1), 'PREC')
			.appendField(' ');
		this.appendValueInput('VALUE')
			.setCheck('Number');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.OLED_128X64_I2C_PRINT_BIG_PREC_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.OLED_128X64_I2C_PRINT_BIG_PREC_HELPURL);
	},
	// custom xmlToolbox
	xmlToolbox: function() {
		return $(document.createElement('block')).attr({
			type: 'oled_128x64_i2c.putstr_big_prec'
		}).append('\
		   <value name="COLUMN">\
			   <shadow type="oled_128x64_i2c.column_number">\
			   </shadow>\
		   </value>\
		   <value name="ROW">\
			   <shadow type="oled_128x64_i2c.row_number">\
			   </shadow>\
		   </value>\
		   <value name="VALUE">\
			  <shadow type="oled_128x64_i2c.number">\
			  </shadow>\
		  </value>'
	   );
   }
};

// hidden block (no generator defined), temporary used for shadow block
Blockly.Blocks["oled_128x64_i2c.column_number"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldNumber(1, 1, 21, 1), 'VALUE');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(math_colour);
		this.setTooltip(Blockly.Msg.OLED_128X64_I2C_COLUMN_NUMBER_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.OLED_128X64_I2C_COLUMN_NUMBER_HELPURL);
	},
	// custom xmlToolboxcolumn
	xmlToolbox: function() {
		return null; // hidden block
	}
};

Blockly.Blocks["oled_128x64_i2c.row_number"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldNumber(1, 1, 8, 1), 'VALUE');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(math_colour);
		this.setTooltip(Blockly.Msg.OLED_128X64_I2C_ROW_NUMBER_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.OLED_128X64_I2C_ROW_NUMBER_HELPURL);
	},
	// custom xmlToolbox
	xmlToolbox: function() {
		return null; // hidden block
	}
};

Blockly.Blocks["oled_128x64_i2c.string_number"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldImage('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAwAAAAKCAQAAAAqJXdxAAAAn0lEQVQI1z3OMa5BURSF4f/cQhAKjUQhuQmFNwGJEUi0RKN5rU7FHKhpjEH3TEMtkdBSCY1EIv8r7nFX9e29V7EBAOvu7RPjwmWGH/VuF8CyN9/OAdvqIXYLvtRaNjx9mMTDyo+NjAN1HNcl9ZQ5oQMM3dgDUqDo1l8DzvwmtZN7mnD+PkmLa+4mhrxVA9fRowBWmVBhFy5gYEjKMfz9AylsaRRgGzvZAAAAAElFTkSuQmCC', 12, 12, '*'))
			.appendField(new Blockly.FieldTextInput('Hello World!'), 'VALUE')
			.appendField(new Blockly.FieldImage('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAwAAAAKCAQAAAAqJXdxAAAAqUlEQVQI1z3KvUpCcRiA8ef9E4JNHhI0aFEacm1o0BsI0Slx8wa8gLauoDnoBhq7DcfWhggONDmJJgqCPA7neJ7p934EOOKOnM8Q7PDElo/4x4lFb2DmuUjcUzS3URnGib9qaPNbuXvBO3sGPHJDRG6fGVdMSeWDP2q99FQdFrz26Gu5Tq7dFMzUvbXy8KXeAj57cOklgA+u1B5AoslLtGIHQMaCVnwDnADZIFIrXsoXrgAAAABJRU5ErkJggg==', 12, 12, '*'));
		this.setOutput(true, 'String');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(basic_colour);
		this.setTooltip(Blockly.Msg.OLED_128X64_I2C_STRING_NUMBER_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.OLED_128X64_I2C_STRING_NUMBER_TOOLTIP);
	},
	// custom xmlToolbox
	xmlToolbox: function() {
		return null; // hidden block
	}
};

Blockly.Blocks["oled_128x64_i2c.number"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldNumber(0, -9999999, 9999999, 0.01), 'VALUE');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(math_colour);
		this.setTooltip(Blockly.Msg.OLED_128X64_I2C_NUMBER_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.OLED_128X64_I2C_NUMBER_HELPURL);
	},
	// custom xmlToolbox
	xmlToolbox: function() {
		return null; // hidden block
	}
};
