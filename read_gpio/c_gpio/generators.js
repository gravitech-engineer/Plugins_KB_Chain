/*Blockly.JavaScript['set_gpio'] = function(block) {
  var dropdown_pin = block.getFieldValue('pin');
  var dropdown_state = block.getFieldValue('state');
  // TODO: Assemble JavaScript into code variable.
  var code = 'DEV_IO.c_gpio()' + '.set_gpio(' + dropdown_pin + ',' + dropdown_state + ');\n';
  return code;
};*/



Blockly.JavaScript['get_gpio'] = function(block) {
  var dropdown_gpin = block.getFieldValue('gpin');
  // TODO: Assemble JavaScript into code variable.
  var code = 'DEV_IO.c_gpio().get_gpio(' + dropdown_gpin + ')\n';
  // TODO: Change ORDER_NONE to the correct strength.
  return [code, Blockly.JavaScript.ORDER_ATOMIC];
};