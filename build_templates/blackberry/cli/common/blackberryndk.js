
var path = require('path'),
	os = require('os'),
	util = require('util'),
	fs = require('fs'),
	appc = require('node-appc'),
    afs = appc.fs,
    i18n = appc.i18n(__dirname),
	__ = i18n.__,
	__n = i18n.__n,
    wrench = require('wrench'),
    ti = require('titanium-sdk'),
	exec = require('child_process').exec,
	jsExtRegExp = /\.js$/,
	lastLogLength = 0,
	timerID = 0;
	getLog = true;

var findNDK = function() {

	var default_dirs;
	var ndkPath = 'not found';

	if (process.platform === 'win32') {
		default_dirs = ['C:\\bbndk']
	}
	else {
		default_dirs = ['/Applications/bbndk', '/Developer/SDKs/bbndk', '/opt/bbndk', '~/bbndk', '~/opt/bbndk']
	}

	var len = default_dirs.length;

	for (i = 0; i < len; i++) {
		if (fs.existsSync(default_dirs[i])) {
			return default_dirs[i];
	     }
	}
}

var generateTmpName = function(suffix) {

	var now = new Date();
	var name = [	now.getYear(), now.getMonth(), now.getDate(),
				'-',
				process.pid,
				'-',
				(Math.random() * 0x100000000 + 1).toString(36),
				'-',
				suffix
	          ].join('');
	return name;
}

var runCommandFromArray = function(commandArray, showCommand, callback) {

    var len = commandArray.length;
    var command = '';
	for (i = 0; i < len; i++) {
		command += commandArray[i]  + ' ';
	}

    if (showCommand === true) {
		console.log('[Command] :' + command);
	}

	exec(command, function(err, stdout, stderr) {

		callback(err, stdout);
		if (showCommand === true) {
		    if (err != null) {
				util.puts(err);
			}
			if (stderr != null) {
				util.puts(stderr);
			}
			if (stdout != null) {
				util.puts(stdout.trim());
		    }
		}
	});	
}

var renderTemplate = function(template, props) {
	return template.replace(/\$\{([^\:\}]+)(?:\:([^\s\:\}]+))?\}/g, function (match, key, format) {
		var parts = key.trim().split('|').map(function (s) { return s.trim(); });
		key = parts[0];
		var value = '' + (props.hasOwnProperty(key) ? props[key] : 'null');
		if (parts.length > 1) {
			parts[1].split(',').forEach(function (cmd) {
				if (cmd == 'h') {
					value = value.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
				} else if (cmd == 'trim') {
					value = value.trim();
				} else if (cmd == 'jsQuoteEscapeFilter') {
					value = value.replace(/"/g, '\\"').replace(/\n/g, '\\n');
				}
			});
		}
		return value;
	});
}

var collapsePath = function (p) {
	var result = [], segment, lastSegment;
	p = p.replace(/\\/g, '/').split('/');
	while (p.length) {
		segment = p.shift();
		if (segment == '..' && result.length && lastSegment != '..') {
			result.pop();
			lastSegment = result[result.length - 1];
		} else if (segment != '.') {
			result.push(lastSegment = segment);
		}
	}
	return result.join('/');
}

var findTiModules = function (builder, callback) {
	if (!builder.tiapp.modules || !builder.tiapp.modules.length) {
		builder.logger.info(__('No Titanium Modules required, continuing'));
		callback();
		return;
	}

    var moduleSearchPaths = [builder.projectDir, afs.resolvePath(builder.titaniumBBSdkPath, '..', '..', '..', '..')];
    var deployType = "development"; // TODO: look at g to figure dev or prod
	var projectDependencies = [];

	builder.logger.info(__n('Searching for %s Titanium Module', 'Searching for %s Titanium Modules', builder.tiapp.modules.length));
	appc.timodule.find(builder.tiapp.modules, 'blackberry', deployType, ti.manifest.version, moduleSearchPaths, builder.logger, function (modules) {
		if (modules.missing.length) {
			builder.logger.error(__('Could not find all required Titanium Modules:'));
			modules.missing.forEach(function (m) {
				builder.logger.error('   id: ' + m.id + '\t version: ' + (m.version || 'latest') + '\t platform: ' + m.platform + '\t deploy-type: ' + m.deployType);
			}, builder);
			builder.logger.log();
			process.exit(1);
		}

		if (modules.incompatible.length) {
			builder.logger.error(__('Found incompatible Titanium Modules:'));
			modules.incompatible.forEach(function (m) {
				builder.logger.error('   id: ' + m.id + '\t version: ' + (m.version || 'latest') + '\t platform: ' + m.platform + '\t min sdk: ' + m.minsdk);
			}, builder);
			builder.logger.log();
			process.exit(1);
		}

		if (modules.conflict.length) {
			builder.logger.error(__('Found conflicting Titanium modules:'));
			modules.conflict.forEach(function (m) {
				builder.logger.error('   ' + __('Titanium module "%s" requested for both Mobile Web and CommonJS platforms, but only one may be used at a time.', m.id));
			}, builder);
			builder.logger.log();
			process.exit(1);
		}

		modules.found.forEach(function (module) {
			var moduleDir = module.modulePath,
				pkgJson,
				pkgJsonFile = path.join(moduleDir, 'package.json');
			if (!afs.exists(pkgJsonFile)) {
				builder.logger.error(__('Invalid Titanium Mobile Module "%s": missing package.json', module.id) + '\n');
				process.exit(1);
			}

			try {
				pkgJson = JSON.parse(fs.readFileSync(pkgJsonFile));
			} catch (e) {
				builder.logger.error(__('Invalid Titanium Mobile Module "%s": unable to parse package.json', module.id) + '\n');
				process.exit(1);
			}

			var libDir = ((pkgJson.directories && pkgJson.directories.lib) || '').replace(/^\//, '');	


			builder.logger.info(__('Bundling Titanium Mobile Module %s', module.id.cyan));

			builder.projectDependencies.push(pkgJson.main);

			var moduleName = module.id != pkgJson.main ? module.id + '/' + pkgJson.main : module.id;

			if (/\/commonjs/.test(moduleDir)) {
				builder.modulesToCache.push((/\/commonjs/.test(moduleDir) ? 'commonjs:' : '') + moduleName);
			} else {
				builder.modulesToCache.push(moduleName);
				builder.tiModulesToLoad.push(module.id);
			}

			builder.packages.push({
				'name': module.id,
				'location': path.join(moduleDir, libDir),
				'main': pkgJson.main,
				'type': pkgJson.type,
				'root': 1
			});
		}, builder);

		callback();
	}.bind(builder));
}

var package = function(builder) {

    var projectDir = builder.projectDir;
	var buildDir = path.join(projectDir, 'build', 'blackberry');
    var titaniumBBSdkPath = builder.titaniumBBSdkPath;

    // copy over bootstrap files
	afs.copyDirSyncRecursive(path.join(titaniumBBSdkPath, 'tibb', 'titanium', 'javascript'),
	 									path.join(buildDir, 'framework'), { preserve: true, logger: logger.debug });

    // copy localization and resources into assets folder
    var i18nDir = path.join(projectDir, 'i18n');
    var assetsDir = path.join(buildDir, 'assets');   
	var resourcesDir = path.join(projectDir, 'Resources');
	
	if (fs.existsSync(i18nDir)) {
		afs.copyDirSyncRecursive(i18nDir, path.join(assetsDir, 'i18n'), { preserve: true, logger: logger.debug });
	}

	afs.copyDirSyncRecursive(resourcesDir, assetsDir, { preserve: true, logger: logger.debug });

    var iphoneRes = path.join(assetsDir, 'iphone');
    var mobilewebRes = path.join(assetsDir, 'mobileweb');
    var androidRes = path.join(assetsDir, 'android');
    var blackberryRes = path.join(assetsDir, 'blackberry');
	if (fs.existsSync(iphoneRes)) { wrench.rmdirSyncRecursive(iphoneRes); }
	if (fs.existsSync(mobilewebRes)) { wrench.rmdirSyncRecursive(mobilewebRes); }
	if (fs.existsSync(androidRes)) { wrench.rmdirSyncRecursive(androidRes); }
    // blackberry resources start at assets
	if (fs.existsSync(blackberryRes)) { wrench.rmdirSyncRecursive(blackberryRes); }

	// Copy BlackBerry resources from SDK (templates).
	afs.copyDirSyncRecursive(
		path.join(titaniumBBSdkPath, 'templates', 'app', 'default', 'Resources', 'blackberry'),
		assetsDir,
		{ preserve: true, logger: logger.debug }
	);

	// Copy any BlackBerry resources from the project.
	var blackberryProjectRes = path.join(resourcesDir, 'blackberry');
	if (fs.existsSync(blackberryProjectRes)) {
		afs.copyDirSyncRecursive(
			blackberryProjectRes,
			assetsDir,
			{ preserve: true, logger: logger.debug }
		);
	}

	var appPropsFile = path.join(buildDir, 'assets', 'app_properties.ini');
    fs.writeFileSync(appPropsFile, builder.appProps);

    builder.projectDependencies = [];
	builder.modulesToCache = [];
	builder.tiModulesToLoad = [];
    builder.packages = [];


    findTiModules(builder, function(){
    	builder.packages.forEach(function (p) {

    		if (typeof p.type === 'undefined') {	
				var lib = path.join(p.location, p.main + '.js');
    			fs.createReadStream(lib).pipe(fs.createWriteStream(path.join(assetsDir, p.main + '.js')));	
			}

			// copy module assets to blackberry assets folder
			var moduleAssetsDir = path.join(p.location, 'assets');
			if (fs.existsSync(moduleAssetsDir)) {
				afs.copyDirSyncRecursive(moduleAssetsDir, assetsDir, { preserve: true, logger: logger.debug });
			}
		});
    });
}

var getAppLog = function(ndk, deviceIP, barFile, password, callback) {

	// setup the build environment and then run the ndk command
    var srccmd;
    var ndkcmd;
    if (process.platform === 'win32') {
    	srccmd = path.join(ndk, 'bbndk-env.bat');
		ndkcmd = 'blackberry-deploy.bat';
	} else {
		srccmd = 'source ' + path.join(ndk, 'bbndk-env.sh');
		ndkcmd = 'blackberry-deploy';
	}

	var command = [srccmd, '&&', ndkcmd, '-isAppRunning', '-device', deviceIP, '-package', barFile];

	if (typeof password !== 'undefined') {
		command = command.concat(['-password', password])
	}

    if (getLog == true) {
	    getLog = false;
		runCommandFromArray(command, showCmd = false, function(err, stdout) { 

			if (stdout.indexOf('result::true') != -1) {

				var hostFile = "-";
				var deviceFile = "logs/log";
				command = [srccmd, '&&', ndkcmd, '-getFile', deviceFile, hostFile, '-device', deviceIP, '-package', barFile];

				if (typeof password !== 'undefined') {
					command = command.concat(['-password', password])
				}

				runCommandFromArray(command, showCmd = false, function(err, stdout) {  

					if (lastLogLength != stdout.length)
					{
						console.log(stdout);
						lastLogLength = stdout.length;
					}

			        getLog = true;   	
				});
			} else {
				clearInterval(timerID);
				callback(/* finished */);

			}
		});
	}
}

function BlackberryNDK(builder) {
	
	var self =  { 

        builder: builder,

		build: function (finished) {

            var builder = this.builder;
            var logger = builder.logger;
			var ndk = builder.ndk;
			// so BlackBerry NDK can build  projects with spaces do a space replace
			var projectName = builder.projectName.replace(/ /g, '_');

			if (typeof ndk === 'undefined') {
		        ndk = findNDK();
		        if (typeof ndk === 'undefined') {
		        	return  1;
		        }
	    	}
	        logger.log('\n' + 'Path to BlackBerry NDK is: ' + ndk.cyan);

	        if (typeof builder.target === 'undefined') {
		        logger.log('\n' + 'Build Failed: You must specify a target with -T flag. Valid values are device, simulator, distribute');
		        return  1;

	    	}	        

	        // BB NDK makefiles do not allow spaces in path names and cause build problem.
			// The solution is to use temporary directories without spaces to do builds. Also
			// the project name needs to have spaces removed.
			var tmpPathSDK = path.join(os.tmpDir(), generateTmpName(projectName)); 
			afs.copyDirSyncRecursive(path.join(builder.titaniumBBSdkPath, 'tibb'),
								path.join(tmpPathSDK, 'tibb'), {logger: logger.debug});
			afs.copyDirSyncRecursive(path.join(builder.titaniumBBSdkPath, 'libv8'),
								path.join(tmpPathSDK, 'libv8'), {logger: logger.debug});

            // Copy over any module header file and make the static library location available to build
			builder.projectDependencies = [];
			builder.modulesToCache = [];
			builder.tiModulesToLoad = [];
		    builder.packages = [];
		    var extra_lib_paths = '';
		    var lib_names = '';
		    var headers = '';
		    var register_modules = '';
		    var header_paths = [];

            findTiModules(builder, function(){
		    	builder.packages.forEach(function (p) {

		    		if (typeof p.type !== 'undefined' && p.type === "native") {	
		    			var cpu = builder.type2variantCpu[builder.target][1];
		    			var header_path =  path.join(p.location, p.main + '.h');
		    			var lib_path = path.join(p.location, cpu, builder.type2variantCpu[builder.target][2]); 
		    			var lib_name = 'lib' + p.main + '.a';

                        // copy header to build directory
                        header_paths.push({'path': header_path, 'name': p.main + '.h'});
		    			
		    			// add lib name to common.mk, for convience copy lib to tibb lib location which is already on library search 
		    			// path and does not contain spaces in path
                        fs.createReadStream(path.join(lib_path, lib_name)).pipe(fs.createWriteStream(path.join(tmpPathSDK, 'tibb', cpu, builder.type2variantCpu[builder.target][2], lib_name)));
		    			lib_names += 'LIBS+=' + p.main + ' ';

		    			// add header and register calls to main.cpp	
		    			headers += '#include "' + p.main + '.h"\n'; 
		    			register_modules += '\ttiRegisterModule("' + p.main + '", (TiModule*) new ' + p.main + '());\n';
					}
				});
		    });			

			var variant = builder.type2variantCpu[this.builder.target][0];
			var cpu = builder.type2variantCpu[this.builder.target][1];
            
			var tiappName = 'TIAPP_NAME=' + projectName;
			var cpuList = 'CPULIST=' + cpu;
			var bbRoot = 'BB_ROOT=' + tmpPathSDK;
			var debug = 'VARIANTLIST=';
			if (variant.indexOf('-g', variant.length - 2) !== -1) {
				debug += 'g';
			} 

			var oldPath = process.cwd()	
			var tmpPathProj = path.join(os.tmpDir(), generateTmpName(projectName)); 
			var projectDir = this.builder.projectDir;
			afs.copyDirSyncRecursive(projectDir, tmpPathProj, {logger: logger.debug});
			process.chdir(path.join(tmpPathProj, 'build', 'blackberry'));

			header_paths.forEach(function(entry) {
			    fs.createReadStream(entry.path).pipe(fs.createWriteStream(path.join(tmpPathProj, 'build', 'blackberry', entry.name)));
			 });

			var common_make_file_path = path.join(tmpPathProj, 'build', 'blackberry', 'common.mk');
			fs.writeFileSync(common_make_file_path, renderTemplate(fs.readFileSync(common_make_file_path).toString().trim(), {
				libs: lib_names
			}));

			var main_file_path = path.join(tmpPathProj, 'build', 'blackberry', 'main.cpp');
			fs.writeFileSync(main_file_path, renderTemplate(fs.readFileSync(main_file_path).toString().trim(), {
				module_headers: headers,
				module_registration: register_modules
			}));


			// setup the build environment and then build the app executable using make
			var srccmd;
			if (process.platform === 'win32') {
				srccmd = path.join(ndk, 'bbndk-env.bat');
			} else {
				srccmd = 'source ' + path.join(ndk, 'bbndk-env.sh');
			}

			runCommandFromArray([srccmd, '&&', 'make', tiappName, cpuList, bbRoot, debug], showCmd = true, function() {
				afs.copyDirSyncRecursive(tmpPathProj, projectDir, {logger: logger.debug});

				try {
					wrench.rmdirSyncRecursive(tmpPathSDK);
					wrench.rmdirSyncRecursive(tmpPathProj);
				}
				catch(e) {
					logger.log('\nUnable to remove temporary folders: ' + e);
				}
                
				process.chdir(oldPath);
				finished(/* if there was an error, pass it to finished */);
			});		
        },

        run: function (finished) {

        	var builder = this.builder;
            var logger = builder.logger;
			var ndk = builder.ndk;
			var deviceIP = builder.deviceIP;
			var projectName = builder.projectName.replace(/ /g, '_');

        	if (typeof ndk === 'undefined') {
		        ndk = findNDK();
		        if (typeof ndk === 'undefined') {
		        	return  1;
		        }
	    	}

	        logger.log('\n' + 'Path to BlackBerry NDK is: ' + ndk.cyan);

			// write the bar-descriptor file
            var permissions = '';
            var tiapp = builder.tiapp;
            if (typeof tiapp.blackberry !== 'undefined' && typeof tiapp.blackberry.permissions !== 'undefined') {
	            for (key in tiapp.blackberry.permissions) {
	            	permissions += '<permission>' + key + '</permission>\n\t';
	        	}
	        }

	        if (tiapp['analytics'] === true) {
	        	permissions += '<permission>read_device_identifying_information</permission>\n\t';
	        }
            
        	var autoOrient = false;
        	var orientation = '';
        	if (typeof tiapp.blackberry !== 'undefined' && typeof tiapp.blackberry.orientation !== 'undefined') {
	        	orientation = builder.tiapp.blackberry['orientation'];
	        	if (orientation === 'auto') {
	        		autoOrient = true;
	        	}
	        }

            var projectDir = builder.projectDir;
            var buildDir = path.join(projectDir, 'build', 'blackberry');
			var barDescriptor = path.join(buildDir, 'bar-descriptor.xml');
			var barDescriptorTmpl = path.join(builder.titaniumBBSdkPath, 'templates', 'bar-descriptor2.xml');
			fs.writeFileSync(barDescriptor, renderTemplate(fs.readFileSync(barDescriptorTmpl).toString().trim(), {
				id: tiapp['id'] || '',
				appname: builder.projectName || '',
				binname: projectName || '',
				description: tiapp.description || 'not specified',
				version: tiapp.version || '1.0',
				author: tiapp.publisher || 'not specified',
				autoOrient: autoOrient,
				orientation: orientation, 
				category: 'core.games',
				permissions: permissions || '',
				icon: 'assets/' + tiapp.icon || 'assets/appicon.png'
			}));

			// write app_properties.ini file 
			appProps = builder.appProps;
			appProps = '[General]\n';
			for (key in tiapp.properties) {
	            for (key2 in tiapp.properties[key]) {
	                if (key2 == 'value') {
	                    appProps += key + ' = ' + tiapp.properties[key][key2] + '\n';
	                }
	            }
	        }
	        appProps += 'analytics = ' + tiapp['analytics'] + '\n';
	        appProps += 'aguid = ' + tiapp['guid'] + '\n';
	        appProps += 'version = ' + tiapp['version'] + '\n';
	        if (builder.target === 'distribute') {
				appProps += 'deploytype = production\n';
			}
			else {
				appProps += 'deploytype = development\n';
			}
		
            // create the bar package
            package(builder);

            // setup the build environment and then run the ndk command
            var srccmd;
            var ndkcmd;
            if (process.platform === 'win32') {
            	srccmd = path.join(ndk, 'bbndk-env.bat');
				ndkcmd = 'blackberry-nativepackager.bat';
			} else {
				srccmd = 'source ' + path.join(ndk, 'bbndk-env.sh');
				ndkcmd = 'blackberry-nativepackager';
			}

			var variant = builder.type2variantCpu[builder.target][0];
        	var cpu = builder.type2variantCpu[builder.target][1];
        	var barFile = '"' + path.join(buildDir, cpu, variant, projectName + '.bar') + '"';
        	var appBinaryFile = '"' + path.join(buildDir, cpu, variant, projectName) + '"';
        	var type = builder.target;
        	var password = builder.password;
        	var debugToken = builder.debugToken;
			
			// BuildID is is a 0-65535 value that identifies this package it must be incremented before bar signing 
			var buildID = 1;
        	if (typeof tiapp.blackberry !== 'undefined' && typeof builder.tiapp.blackberry['build-id'] !== 'undefined') {
	        	buildID = builder.tiapp.blackberry['build-id'];
	        }

            var command = [srccmd, '&&', ndkcmd, '-package', barFile, 'bar-descriptor.xml', '-e', appBinaryFile , 
            					'"' + projectName + '"', '-buildID', buildID, 'assets', 'framework'];

            if (type !== 'distribute') {
				command.push('-devMode');
			}

			if (typeof debugToken !== 'undefined') {
				debugToken = '"' + debugToken + '"';
				command = command.concat(['-debugToken', debugToken])
			}
           
            var oldPath = process.cwd();
            process.chdir(buildDir);	
            runCommandFromArray(command, showCmd = true, function() {  

            	if (type !== 'distribute') {                      

		            if (process.platform === 'win32') {
						ndkcmd = 'blackberry-deploy.bat';
					} else {
						ndkcmd = 'blackberry-deploy';
					}

					command = [srccmd, '&&', ndkcmd, '-installApp', '-launchApp', '-device', deviceIP, '-package', barFile];

					if (typeof password !== 'undefined') {
						command = command.concat(['-password', password]);
					}

					runCommandFromArray(command, showCmd = true, function() {  
						timerID = setInterval(getAppLog, 2000, ndk, deviceIP, barFile, password, finished);                     
					});

	            } else {

	            	if (process.platform === 'win32') {
						ndkcmd = 'blackberry-signer.bat';
					} else {
						ndkcmd = 'blackberry-signer';
					}

					command = [srccmd, '&&', ndkcmd, '-storepass', builder.keystorePassword, barFile];

					runCommandFromArray(command, showCmd = true, function() { 

						if (typeof builder.outputDir !== 'undefined') {
                        	fs.mkdir(builder.outputDir); 
                        	barFile = path.join(buildDir, cpu, variant, projectName + '.bar'); 
                        	fs.createReadStream(barFile).pipe(fs.createWriteStream(path.join(builder.outputDir, projectName + '.bar')));						
						}      

						process.chdir(oldPath);
						finished(/* if there was an error, pass it to finished */);
					});
	            }
			});		
        } // end of run function
	};

	return self;
};

module.exports = BlackberryNDK;

