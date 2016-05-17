var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  var newgirl = {
    name: "Diana",
    age: 20
  }
  res.render('index', newgirl);
});

module.exports = router;
