Blockly.JavaScript['thermal'] = function(block) {
  var dropdown_sel = block.getFieldValue('Sel');
  // TODO: Assemble JavaScript into code variable.
  var code = 'DEV_I2C1.kb_thermal(0, 0x5A).Readtemp(' + dropdown_sel + ')';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.JavaScript.ORDER_NONE];
};

