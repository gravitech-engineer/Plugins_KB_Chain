// var ADDONS_kb_chain_batt_CLASS_BEGIN = 'DEV_I2C1.kb_chain_battery(0, 0x4E)';

Blockly.JavaScript['kb_chain_battery'] = function(block) {
  var code = 'DEV_I2C1.kb_chain_battery(0, 0x4E).get_cal_volt()\n';
  // console.log( code);
  return [code, Blockly.JavaScript.ORDER_ATOMIC];
  // return code;
  
};

