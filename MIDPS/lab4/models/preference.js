var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var preferenceSchema = new Schema({
  name: String,
  food: String
}, {
  collection: 'preferencelist'
});

module.exports = mongoose.model('preference', preferenceSchema);
