Blockly.Blocks['bh1745nuc_get_color'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.BH1745NUC_GET_COLOR_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "color",
				"options": [
					[ Blockly.Msg.BH1745NUC_GET_COLOR_OPTION_RED, "1" ],
					[ Blockly.Msg.BH1745NUC_GET_COLOR_OPTION_GREEN, "2" ],
					[ Blockly.Msg.BH1745NUC_GET_COLOR_OPTION_BLUE, "3" ]
				]
			}],
			"output": "Number",
			"colour": 285,
			"tooltip": Blockly.Msg.BH1745NUC_GET_COLOR_TOOLTIP,
			"helpUrl": "https://www.kidbright.io/product-page/kb-chain-rgb-light-sensor"
		})
	}
};
