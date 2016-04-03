var _ = require('underscore');

// RPN calculator
var calculate = function(data) {
  var Stack = data;
  var number = /^[+-]?\d+(\.\d+)?$/;
  var operator = /[-/^*+]{1}/;
  var operand_1, operand_2;
  var top_stack;
  var math_it = {
    "+": function(a, b) { return a + b; },
    "-": function(a, b) { return a - b; },
    "/": function(a, b) { return a / b; },
    "*": function(a, b) { return a * b; },
    "^": function(a, b) { return Math.pow(a, b); },
    "sqrt": function(x) { return Math.sqrt(x); }
  }
  while (Stack.length != 1) {
    var current_token = Stack.shift();
    if (number.test(current_token)) {
      Stack.push(current_token);
    }
    if (operator.test(current_token)) {
      operand_1 = Stack.pop();
      operand_2 = Stack.pop();
      Stack.push(math_it[current_token](Number(operand_2), Number(operand_1)));
    }
  }
  return _.first(Stack);
};

module.exports = calculate;
