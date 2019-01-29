var ADDONS_kb_chain_CLASS_BEGIN = 'DEV_I2C1.kb_chain_relay(0, 0x1A)';

Blockly.JavaScript['control_relay'] = function(block) {
  var dropdown_ch = block.getFieldValue('ch');
  var dropdown_state = block.getFieldValue('state');
  // TODO: Assemble JavaScript into code variable.
  var code = ADDONS_kb_chain_CLASS_BEGIN + '.set_ch('+dropdown_ch+','+dropdown_state+');\n';
  return code;
};