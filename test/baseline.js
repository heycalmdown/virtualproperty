var assert = require('assert');
var util = require('util');
var VirtualProperty = require('../index');

describe('Accessor Test', function () {
	it('dead simple', function () {
		var aa = VirtualProperty.expose();
		assert(aa.a === 'a');
		assert(aa.b === 'b');
	});
	it('override __get__', function () {
		VirtualProperty.prototype.__get__ = function (idx) {
			return 'a';
		};
		var aa = VirtualProperty.expose();
		assert(aa.a === 'a');
		assert(aa.b === 'a');
	});
	it('overlap accessor', function () {
		VirtualProperty.prototype.__get__ = function (idx) {
			return 'a';
		};
		var aa = VirtualProperty.expose();
		aa.c = 'c';
		assert(aa.a === 'a');
		assert(aa.b === 'a');
		assert(aa.c === 'c');
	});
});

//describe('Setter Test', function () {
// 	it('native behavior', function () {
// 		var aa = VirtualProperty.expose();
// 		aa.a = 'z';
// 		assert(aa.a === 'z');
// 	});
// 	it('native behavior', function () {
// 		var aa = VirtualProperty.expose();
// 		VirtualProperty.prototype.__set__ = function (key, value) {
// 			return false;
// 		};
// 		aa.a = 'z';
// 		assert(aa.a === undefined);
// 	});
// });
