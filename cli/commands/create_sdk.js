var fs = require('fs'),
    wrench = require('wrench');

var currDir = process.cwd();

// blackberry folder will contain the backerry sdk and can be dropped into a current titanium sdk
wrench.mkdirSyncRecursive('../../build/sdk/blackberry', 0777);

process.chdir('../../build_templates/');
wrench.copyDirSyncRecursive('blackberry', '../build/sdk/blackberry');

// repo root
process.chdir('../');

var copyFileSync = function(srcFile, destFile, encoding) {
  var content = fs.readFileSync(srcFile, encoding);
  fs.writeFileSync(destFile, content, encoding);
}

// copy over the contents over the blackberry sdk to the build folder 
copyFileSync('src/tibb/arm/a.le-v7/libtibb.a', 'build/sdk/blackberry/tibb/arm/a.le-v7/libtibb.a');
copyFileSync('src/tibb/arm/a.le-v7-g/libtibb.a', 'build/sdk/blackberry/tibb/arm/a.le-v7-g/libtibb.a');
copyFileSync('src/tibb/x86/a/libtibb.a', 'build/sdk/blackberry/tibb/x86/a/libtibb.a');
copyFileSync('src/tibb/x86/a-g/libtibb.a',  'build/sdk/blackberry/tibb/x86/a-g/libtibb.a');

copyFileSync('runtime/v8/libv8-arm.a', 'build/sdk/blackberry/libv8/lib/arm/libv8.a');
copyFileSync('runtime/v8/libv8-ia32.a', 'build/sdk/blackberry/libv8/lib/x86/libv8.a');

// bump version before publishing release notes, this way a platform can be have a version and release cycle 
// separate from titanium sdk
copyFileSync('sdk_version.json', 'build/sdk/blackberry/sdk_version.json');

process.chdir(currDir);


 

