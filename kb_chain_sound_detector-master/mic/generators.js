
Blockly.JavaScript['mic_get_data'] = function(block) {
	var code = 'DEV_I2C1.MIC(0, 0x48).getRawValue()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};
