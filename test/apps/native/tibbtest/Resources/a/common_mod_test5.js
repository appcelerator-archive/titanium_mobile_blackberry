

function fn_inner() {
	console.log('module inner function called (common_mod_test5)');
};

function fn_test() {
	var self =  { x : fn_inner };
	console.log('module function called (common_mod_test5)');
	return self;
};

module.exports = fn_test;

