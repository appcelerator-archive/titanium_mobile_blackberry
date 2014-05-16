var archiver;
try {
    archiver = require("archiver");
} catch(e) {
    console.error(e.message);
    console.error("archiver is not found. Try running `npm install`.");
    process.exit(e.code);
}
var wrench = require('wrench');
var fs = require('fs');
var path = require('path');
var exec = require('child_process').exec;
var manifest = {};
var manifestContent = '';

(function(){
	manifestContent = fs.readFileSync('manifest', {encoding: 'utf8'});
	var manifestFile = manifestContent.trim().split('\n');

	manifestFile.forEach(function(line, index) {
		if(line.indexOf('#') == 0) return;
		var parts = line.split(':');
		manifest[parts[0]] = (parts[1] || '').trim()
	});
})();

function findEnvFile(dir) {

	var envFiles = fs.readdirSync(dir);
	var envFile = 'not found';

	for (var i = 0; i < envFiles.length; i++) {
		var name = envFiles[i];
		if (name.indexOf('bbndk-env') == 0) {
			if (process.platform === 'win32') {
				if (name.indexOf('.bat', name.length - 4) != -1) {
					envFile = name;
				}
			}
			else {
				envFile = name;
			}
		}
	}

	return envFile;
}

function findNDK() {

	var default_dirs;
	var ndkPath = 'not found';

	if (process.platform === 'win32') {
		default_dirs = ['C:\\bbndk']
	}
	else {
		default_dirs = ['/Applications/Momentics.app',  '/Applications/bbndk', '/Developer/SDKs/bbndk', '/opt/bbndk', '~/bbndk', '~/opt/bbndk']
	}

	var len = default_dirs.length;

	for (i = 0; i < len; i++) {
		if (fs.existsSync(default_dirs[i])) {
			return default_dirs[i];
		 }
	}
}

function makeZip() {
	var buildDir = path.join(__dirname, 'build');
	if(fs.existsSync(buildDir)) {
		wrench.rmdirSyncRecursive(buildDir);
	}
	var moduleBuildPath = path.join(buildDir, manifest['moduleid'], manifest['version']);
	wrench.mkdirSyncRecursive(moduleBuildPath);

	wrench.copyDirSyncRecursive(path.join(__dirname, 'arm'), path.join(moduleBuildPath, 'arm'));
	wrench.copyDirSyncRecursive(path.join(__dirname, 'x86'), path.join(moduleBuildPath, 'x86'));
	wrench.copyDirSyncRecursive(path.join(__dirname, 'include'), path.join(moduleBuildPath, 'header'));
	fs.writeFileSync(path.join(moduleBuildPath, 'manifest'), manifestContent, 'utf8');

	var output = fs.createWriteStream(manifest['moduleid'] + '-blackberry-' + manifest['version'] + '.zip');
	var archive = archiver('zip');

	output.on('close', function() {
		// done
	});

	archive.on('error', function(err) {
		throw err;
	});

	archive.pipe(output);
	archive.bulk([
		{ expand: true, cwd: 'build', src: ['**'], dest: 'modules/blackberry' }
	]);
	archive.finalize();
}

(function(){
	var ndkPath = findNDK();
	var envFile = findEnvFile(ndkPath);
	var bashFile = path.join(ndkPath, envFile);

	var command = 'source "' + bashFile + '"; make clean; make all;';
	console.log(command);
	exec( command , function(err, stdout, stderr) {

			if (err != null) {
				console.log(err);
			}
			if (stderr != null) {
				console.log(stderr);
			}
			if (stdout != null) {
				console.log(stdout.trim());
			}
			makeZip();
		}
	);
})();
