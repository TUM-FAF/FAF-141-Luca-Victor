var $ = require('jquery');
var _ = require('underscore');
var operations = ["-", "+", "/", "*", "^"];
var core = require('./core/index.js');


$(function() {
  var input = $('.input');
  $('.number').click(function() {
    input.val(input.val() + this.value);
  });
  $('.operation').click(function() {
    var value = input.val().toString();
    if (check.firstCharacter(value)) {
      return;
    }
    if (!check.operation(value))
      input.val(input.val() + this.value);
  });
  $('.bracket').click(function() {
    input.val(input.val() + this.value);
  });
  $('.dot').click(function() {
    if (check.priviousCharacter(input.val())) 
      input.val(input.val() + this.value);
  });
  $('.clear').click(function() {
    input.val("");
  });
  $('.undo').click(function() {
    var value = input.val().toString();
    value = value.slice(0, -1);
    input.val(value);
  });
  $('.equal').click(function() {
    input.val(core.calculate(input.val().toString()));
  });
}); 

var check = {
  "number": /\d/,
  "oper": /[-/^*+]{1,2}/,
  operation: function(expression) {
    if (this.oper.test(expression.slice(-1)))
      return true
    return false
  },
  firstCharacter: function(expression) {
    if (expression == "")
      return true;
    return false;
  },
  priviousCharacter: function(expression) {
    if (this.number.test(expression.slice(-1))) 
      return true;
    return false;
  }
}