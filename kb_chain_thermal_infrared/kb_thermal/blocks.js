Blockly.Blocks['thermal'] = {
  init: function() {
    this.appendDummyInput()
        .setAlign(Blockly.ALIGN_RIGHT)
        .appendField(Blockly.Msg.kb_thermal_TEXT_TITLE)
        .appendField(new Blockly.FieldDropdown([["Ambient","0x06"], 
        ["Object","0x07"]]), "Sel");
    this.setOutput(true, null);
    this.setColour(230);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};