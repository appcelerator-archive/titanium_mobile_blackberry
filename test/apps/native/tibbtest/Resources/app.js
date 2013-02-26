
var mod_test = require('a/common_mod_test2')('paramABC');
var mod_test2 = require('/a/common_mod_test2')('paramXYZ');

if (require('a/common_mod_test2') === require('/a/common_mod_test2')) {
	console.log('object cache working')
}

mod_test.x();
mod_test2.x();
