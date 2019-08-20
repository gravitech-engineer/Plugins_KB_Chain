Blockly.Blocks['read_proximity'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.PROXIMITY_READ_MESSAGE,
			"output": "Number",
			"colour": 300,
			"tooltip": Blockly.Msg.PROXIMITY_READ_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['read_ambient'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.PROXIMITY_READ_AMBIEANT_MESSAGE,
			"output": "Number",
			"colour": 300,
			"tooltip": Blockly.Msg.PROXIMITY_READ_AMBIEANT_TOOLTIP,
			"helpUrl": ""
		});
	}
};
