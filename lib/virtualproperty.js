var VirtualPropertyTemplate = require('./virtualpropertytemplate');

var VirtualProperty = VirtualPropertyTemplate.create();

VirtualProperty.prototype.__get__ = function (idx) {
	return idx;
};

VirtualProperty.prototype.__set__ = function () {
	return false;
};

VirtualProperty.prototype.__enum__ = function () {
	return [];
};

module.exports = VirtualProperty;

