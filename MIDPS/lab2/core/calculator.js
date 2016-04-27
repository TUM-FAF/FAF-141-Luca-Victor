var parse = require('./ShuntingYardAlgorithm');
var RPNcalculate = require('./RPN_Calculator');

module.exports = {
  calculate: function(exp) {
    var parsed_data = parse(exp);
    return RPNcalculate(parsed_data);
  }
};

