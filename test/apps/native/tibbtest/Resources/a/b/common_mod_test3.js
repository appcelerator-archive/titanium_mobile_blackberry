
var mod_test = require('../common_mod_test4')(); 

function fn_inner() {
	console.log('module inner function of called (common_mod_test3)');
	mod_test.x();
};

function fn_test() {
	var self =  { x : fn_inner };
	console.log('module function called (common_mod_test3)');
	return self;
};

module.exports = fn_test;