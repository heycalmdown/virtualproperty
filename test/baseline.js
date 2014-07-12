var assert = require('assert');
var util = require('util');
var VirtualProperty = require('../index').VirtualProperty;

describe('Test', function () {
	it('dead simple', function () {
		var aa = new VirtualProperty;
		assert(aa.a === 'a');
		assert(aa.b === 'b');
	});
	it('override', function () {
		VirtualProperty.prototype.__get__ = function (idx) {
			return 'a';
		};
		var aa = new VirtualProperty;
		assert(aa.a === 'a');
		assert(aa.b === 'a');
	});
});
