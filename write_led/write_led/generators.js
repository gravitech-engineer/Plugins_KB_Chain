Blockly.JavaScript['write_led'] = function(block) {
  var dropdown_pin = block.getFieldValue('pin');
  var dropdown_state = block.getFieldValue('state');
  // TODO: Assemble JavaScript into code variable.
  console.log(dropdown_state);
  var code ="DEV_IO.write_led().writeled(" +dropdown_pin+ "," + dropdown_state +");\n";
  return code;
};