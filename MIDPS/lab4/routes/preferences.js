var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  console.log("++++++++++++ GET REQUEST /preferences");
  var data = [
    {
      nr: 1,
      name: "Anlina",
      fruit: "apple"
    },
    {
      nr: 2,
      name: "Danny",
      fruit: "orange"
    },
    {
      nr: 3,
      name: "Ionii",
      fruit: "pineapple"
    }
  ];
  res.json(data);
});

router.post('/', function(req, res, next) {
  console.log("+++++++++++++++ POST REQUEST /preferences");
  console.log(req.body);
  var new_preference = req.body;
  res.json(new_preference);
});

module.exports = router;
