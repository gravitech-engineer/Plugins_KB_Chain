Blockly.Blocks['write_led'] = {
  init: function() {
  
    this.appendDummyInput()
    .appendField(Blockly.Msg.write_led_TEXT_TITLE)
        .appendField(Blockly.Msg.write_led_TEXT_1)
        .appendField(new Blockly.FieldDropdown([["BT","17"], ["WIFI","2"], ["NTP","15"], ["IOT","12"]]), "pin")
        .appendField(Blockly.Msg.write_led_TEXT_2)
        .appendField(new Blockly.FieldDropdown([["ON","0"], ["OFF","1"]]), "state");
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(120);
 this.setTooltip(Blockly.Msg.write_led_TEXT_TOOLTIP);
 this.setHelpUrl(Blockly.Msg.write_led_TEXT_HELPURL);
  }
};