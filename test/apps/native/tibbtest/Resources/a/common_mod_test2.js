
global.x = 'hey';

xyz = 'hoist me';

var mod_test2 = require('./b/common_mod_test3')(); 

function fn_inner() {
	console.log('module inner function called (common_mod_test2)');
	mod_test2.x();
};

function fn_test(param) {
	var self =  { x : fn_inner };
	console.log('module function called (common_mod_test2) with param: ' + param);
	return self;
};

module.exports = fn_test;

