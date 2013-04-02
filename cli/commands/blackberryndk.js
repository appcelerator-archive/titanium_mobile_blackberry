var path = require('path'),
	os = require('os'),
	util = require('util'),
	fs = require('fs');
	exec = require('child_process').exec;

var findNDK = function() {
	var default_dirs;
	var ndkPath = 'not found';

	if (process.platform === 'win32') {
		default_dirs = ['C:\\bbndk']
	}
	else {
		default_dirs = ['/Applications/bbndk', '/Developer/SDKs/bbndk', '/opt/bbndk', '~/bbndk', '~/opt/bbndk']
	}

	default_dirs.forEach(function(value) {
		if (fs.existsSync(value)) {
			return value;
	     }
	 });
}

// runs the source command to setup the BlacBerry build environment
var sourceEnvironment = function(blackBerryNDK) {
	var envFile;
	var command;

	if (process.platform === 'win32') {
		envFile = path.join(blackBerryNDK, 'bbndk-env.bat');
		command = envFile + ' && set';
	} else {
		envFile = path.join(blackBerryNDK, 'bbndk-env.sh');
		command = ['bash', '-c', 'source ' + envFile + ' && env'];
	}

	exec(command, function(err, stdout) {
		util.puts(stdout.trim());
	});		
}

var generateTmpDirName = function(suffix) {
  var now = new Date();
  var name = [	now.getYear(), now.getMonth(), now.getDate(),
				'-',
				process.pid,
				'-',
				(Math.random() * 0x100000000 + 1).toString(36),
				'-',
				suffix
              ].join('');
  return path.join(os.tmpDir(), name);
}

function BlackberryNDK(builder) {
	
	var self =  { 

        builder: builder,
        logger: builder.logger,
		
		build: function () {


			// build 
		    // 3) locate the bb ndk environment
		    // 4) run the source command to setup the bb build environment
		    // 5) create temp dir
		    // 6) copy libs - tiapp and v8
		    // 5) copy project to temp dir 
		    // 6) run make command 
		    // 7) copy back bar file back to project

			
            //ndk = findNDK();
            //this.logger.log('\n' + ' ndk ' + ndk.cyan);


           // xyz = generateTmpDirName(this.builder.projectName);
           // console.log(xyz); 


//process.chdir(dirPath);

/*
            assert os.path.exists(project)
		templateDir = os.path.abspath(os.path.dirname(sys._getframe(0).f_code.co_filename))

		# BB NDK makefiles do not allow spaces in path names and cause build problem.
		# The solution is to use python temporary directories without spaces to do builds.

		tmpPathSDK = tempfile.mkdtemp()

		self._copy_file(os.path.join(templateDir, "tibb"), os.path.join(tmpPathSDK, "tibb"))
		self._copy_file(os.path.join(templateDir, "libv8"), os.path.join(tmpPathSDK, "libv8"))

		tiappName = 'TIAPP_NAME=' + name
		cpuList = 'CPULIST=' + cpu
		bbRoot = 'BB_ROOT=' + tmpPathSDK
		variant = 'VARIANTLIST=' + ('g' if variant.endswith('-g') else '')

		oldPath = os.getcwd()	
		os.chdir(project)
		tmpPathProj = tempfile.mkdtemp()
		self._copy_file(os.getcwd(), tmpPathProj)
		projPath = os.getcwd()	
		os.chdir(tmpPathProj)

		command = ['make', tiappName, cpuList, bbRoot, variant]
		retCode = self._run(command)

		self._copy_file(tmpPathProj, projPath)

		try:
			shutil.rmtree(tmpPathSDK)
			shutil.rmtree(tmpPathProj)
		except:
			print "Error removing temporary file"

		os.chdir(oldPath)

		return retCode
*/
/*

            afs.copyFileSync(
			path.join(this.titaniumIosSdkPath, this.platformName, 'Titanium_Prefix.pch'),
			path.join(this.buildDir, this.tiapp.name + '_Prefix.pch'),
			{
				logger: this.logger.debug
			}
		);
*/
        }


	};


	return self;
};

module.exports = BlackberryNDK;

