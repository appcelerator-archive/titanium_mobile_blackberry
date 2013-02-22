
var mod_test = require('./a/common_mod_test2')('paramABC');
var mod_test2 = require('a/common_mod_test2')('paramXYZ');

// test the global object
console.log('The global object says ' + global.x);
console.log(xyz);

mod_test.x();
mod_test2.x();


