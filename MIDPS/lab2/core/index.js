var parse = require('./ShuntingYardAlgorithm');
var calculate = require('./RPN_Calculator');

module.exports = {
  calculate: function(exp) {
    var data = exp;
    var parsed_data = parse(data);
    return calculate(parsed_data);
  }
};
