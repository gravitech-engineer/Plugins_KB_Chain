/*Blockly.Blocks['set_gpio'] = {
  init: function() {
    this.appendDummyInput()
        .appendField(Blockly.Msg.set_gpio_TEXT_TITLE)
        .appendField(Blockly.Msg.set_gpio_TEXT_1)
        .appendField(new Blockly.FieldDropdown([["18","18"], ["19","19"], ["23","23"]]), "pin")
        .appendField(Blockly.Msg.set_gpio_TEXT_2)
        .appendField(new Blockly.FieldDropdown([["High","1"], ["Low","0"]]), "state");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
 this.setTooltip(Blockly.Msg.set_gpio_TEXT_TOOLTIP);
 this.setHelpUrl("");
  }
};*/


Blockly.Blocks['get_gpio'] = {
  init: function() {
    this.appendDummyInput()
        .appendField(Blockly.Msg.get_gpio_TEXT_TITLE)
        .appendField(Blockly.Msg.get_gpio_TEXT_1)
        .appendField(new Blockly.FieldDropdown([["18","18"], ["19","19"], ["23","23"]]), "gpin");
    this.setOutput(true, null);
    this.setColour(230);
 this.setTooltip(Blockly.Msg.get_gpio_TEXT_TOOLTIP);
 this.setHelpUrl("");
  }
};