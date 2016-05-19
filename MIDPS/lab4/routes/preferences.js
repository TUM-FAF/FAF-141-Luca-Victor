var express = require('express');
var router = express.Router();
var mongoose = require('mongoose');
var Preferences = require('../models/preference');
/* GET home page. */
router.get('/preferences', function(req, res, next) {
  console.log("++++++++++++ GET REQUEST /preferences");
  Preferences.find(function(err, preferences) {
    res.json(preferences);
  });
});

router.post('/preferences', function(req, res, next) {
  console.log("+++++++++++++++ POST REQUEST /preferences");
  console.log(req.body);
  var preference = new Preferences(req.body);
  preference.save(function(error, preference) {
    if(error) {
      console.log(error);
      return res.status(500).send("Fail to add preference");
    }
    console.log(preference);
    res.json({success: true, preference: preference});
  });
});

router.delete('/preferences/:id', function(req, res, next) {
  console.log("+++++++++++++++ DELETE REQUEST /preferences");
  console.log(req.body);
  Preferences.remove({_id: req.params.id}, function(error, preference) {
    if(error) {
      return res.status(500).send("Error finding preference by id");
    }
    res.send({succes: true});
  });
});

module.exports = router;
