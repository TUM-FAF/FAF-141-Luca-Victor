var _ = require('underscore');

var parse = function(data) {
  var StackOperators = [];
  var OutputQueue = [];
  var TokenArray = [];
  var number = /^[+-]?\d+(\.\d+)?$/;
  var operator = /[-/^*+]{1}/;
  var precedence = {
    "+": 0, 
    "-": 0, 
    "*": 1, 
    "/": 1,
    "^": 2
  };

  function splitString(string) {
    string = string.replace(/\+/g, ",+,")
      .replace(/\-/g, ",-,")
      .replace(/\*/g, ",*,")
      .replace(/\//g, ",/,")
      .replace(/\^/g, ",^,")
      .replace(/\(/g, "(,")
      .replace(/\)/g, ",)")
      .split(',');
    return string;
  }
  function ShuntingYardAlgorithm(data) {
    data = splitString(data);
    while (data.length != 0) {
      var current_token = data.shift();
      if (number.test(current_token))   // if it's a number push to OutputQueue
        OutputQueue.push(current_token);
      if (operator.test(current_token)) { // if it's an operator
        while(StackOperators.length > 0 && precedence[_.last(StackOperators)] >= precedence[current_token]) {
          if (operator.test(_.last(StackOperators)))
            OutputQueue.push(StackOperators.pop());
        } 
        StackOperators.push(current_token);
      }
      if (current_token == "(")           // if it's left bracket
        StackOperators.push(current_token);
      if (current_token == ")") {         // if it's right bracket
        while (_.last(StackOperators) != "(") {
          if (operator.test(_.last(StackOperators))) // make sure it's an operator not bracket
            OutputQueue.push(StackOperators.pop());
        }
        StackOperators.pop();
      }
    }
    while (StackOperators.length != 0)
      OutputQueue.push(StackOperators.pop());
    return OutputQueue;
  }
  return ShuntingYardAlgorithm(data);
}

module.exports = parse;