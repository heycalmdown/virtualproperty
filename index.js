var fs = require('fs');
var VirtualProperty = require('./lib/virtualproperty');

exports.prototype = VirtualProperty.prototype;

exports.expose = function () {
  return new VirtualProperty();
};
