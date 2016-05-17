var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  var girl = {
    name: "Vallery",
    age: 20
  }
  res.render('index', girl);
});

module.exports = router;
