const ipcRenderer = require('electron').ipcRenderer;
var $ = require('jquery');

$(function() {
  var input = $('.input');
  input.focus();
  input.focusout(function() {
    input.focus();
  });
  $('.number').click(function() {
    input.val(input.val() + this.value);
  });
  $('.operation').click(function() {
    var value = input.val().toString();
    if (!check.operation(value) || this.value == "\u221A")    //for sqrt
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
    input.val(value.slice(0, -1));
  });
  $('.equal').click(function() {
    if (check.brackets(input.val())){
      var expression = input.val().toString();
      ipcRenderer.send('asynchronous-message', expression);
      ipcRenderer.on('asynchronous-reply', function(event, result) {
        input.val(result);
      });
    } else {
      input.val("error");
    }
  });
}); 

var check = {
  "number": /\d/,
  "oper": /\bsqrt\b|[-/^*+]{1,2}/,
  operation: function(expression) {
    if (this.oper.test(expression.slice(-1)))
      return true
    return false
  },
  priviousCharacter: function(expression) {
    if (this.number.test(expression.slice(-1))) 
      return true;
    return false;
  },
  brackets: function(expression) {
    var nr = 0;
    for (var i = 0; i < expression.length; i++) {
      if (expression[i] == "(")
        nr++
      if (expression[i] == ")")
        nr-- 
    }
    if (nr >= 0) 
      return true;
    return false;
  }
}


