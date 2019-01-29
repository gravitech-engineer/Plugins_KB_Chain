Blockly.Blocks['kb_chain_battery'] = {
  init: function() {
    this.appendDummyInput()
        .appendField(Blockly.Msg.kb_chain_battery_TEXT_TITLE);
    this.setOutput(true, null);
    this.setColour(240);
 this.setTooltip(Blockly.Msg.kb_chain_battery_TEXT_TOOLTIP);
 this.setHelpUrl(Blockly.Msg.kb_chain_battery_TEXT_HELPURL);
  }
};