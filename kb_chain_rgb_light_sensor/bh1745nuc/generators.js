
Blockly.JavaScript['bh1745nuc_get_color'] = function(block) {
	var dropdown_color = block.getFieldValue('color');
	var code = 'DEV_I2C1.BH1745NUC(0, 0x38).getRawColor(' + dropdown_color + ')';
	return [code, Blockly.JavaScript.ORDER_NONE];
};
