Blockly.Blocks["control_relay"] = {
  init: function() {
    this.appendDummyInput()
      .appendField(Blockly.Msg.kb_chain_TEXT_TITLE)
      .appendField(Blockly.Msg.kb_chain_TEXT_CHANNEL)
      .appendField(new Blockly.FieldDropdown([["0", "0"], ["1", "1"]]), "ch")
      .appendField(Blockly.Msg.kb_chain_TEXT_STATE)
      .appendField(
        new Blockly.FieldDropdown([["ON", "0"], ["OFF", "1"]]),
        "state"
      );
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(240);
    this.setTooltip(Blockly.Msg.kb_chain_TEXT_TOOLTIP);
    this.setHelpUrl(Blockly.Msg.kb_chain_TEXT_HELPURL);
  }
};
