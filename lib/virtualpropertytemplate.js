var virtualpropertytemplate;

try {
	virtualpropertytemplate = require('../build/Release/virtualpropertytemplate.node');
} catch(err) {
	try {
		virtualpropertytemplate = require('../build/Debug/virtualpropertytemplate.node');
	} catch(err) {
		virtualpropertytemplate = require('../virtualpropertytemplate.node');
	}
}
module.exports = new virtualpropertytemplate.VirtualPropertyTemplate();
