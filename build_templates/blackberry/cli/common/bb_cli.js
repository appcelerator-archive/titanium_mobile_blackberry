var path = require('path');
var fs = require('fs');
var wrench = require('wrench');
var ti = require('titanium-sdk');
var appc = require('node-appc');
var i18n = appc.i18n(__dirname);
var __ = i18n.__;
var __n = i18n.__n;
var exec = require('child_process').exec;
const MOD_NATIVE = 1;
const MOD_COMMON_JS = 2;

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

function TiModules(projectDir, tiSDK, tiapp, logger, callback) {
	callback = callback || function(){};
	if (!tiapp.modules || !tiapp.modules.length) {
		logger.info(__('No Titanium Modules required, continuing'));
		callback([]);
	}

	var moduleSearchPaths = [projectDir, afs.resolvePath(tiSDK, '..', '..', '..', '..')];
	var deployType = "development"; // TODO: look at g to figure dev or prod
	var projectDependencies = [];

	logger.info(__n('Searching for %s Titanium Module', 'Searching for %s Titanium Modules', tiapp.modules.length));

	var modArray = [];
	appc.timodule.find(tiapp.modules, 'blackberry', deployType, ti.manifest.version, moduleSearchPaths, logger, function (modules) {
		if (modules.missing.length) {
			logger.error(__('Could not find all required Titanium Modules:'));
			modules.missing.forEach(function (m) {
				logger.error('   id: ' + m.id + '\t version: ' + (m.version || 'latest') + '\t platform: ' + m.platform + '\t deploy-type: ' + m.deployType);
			});
			logger.log();
			process.exit(1);
		}

		if (modules.incompatible.length) {
			logger.error(__('Found incompatible Titanium Modules:'));
			modules.incompatible.forEach(function (m) {
				logger.error('   id: ' + m.id + '\t version: ' + (m.version || 'latest') + '\t platform: ' + m.platform + '\t min sdk: ' + m.minsdk);
			});
			logger.log();
			process.exit(1);
		}

		if (modules.conflict.length) {
			logger.error(__('Found conflicting Titanium modules:'));
			modules.conflict.forEach(function (m) {
				logger.error('   ' + __('Titanium module "%s" requested for both Mobile Web and CommonJS platforms, but only one may be used at a time.', m.id));
			});
			logger.log();
			process.exit(1);
		}
		modules.found.forEach(function (module) {
			var moduleDir = module.modulePath;

			logger.info(__('Bundling Titanium Mobile Module %s', module.id.cyan));

			if (module.platform.indexOf('commonjs') != -1) {
					module.native = false;
			} else {
					module.native = true;
			}

			var moduleName = module.manifest.moduleid != module.manifest.name ? module.manifest.moduleid + '/' + module.manifest.name : module.manifest.moduleid;

			modArray.push({
				'name': module.manifest.name,
				'id': module.manifest.moduleid,
				'version': module.manifest.version,
				'location': path.join(moduleDir),
				'type': module.native ? MOD_NATIVE : MOD_COMMON_JS,
				'root': 1
			});
		});
		callback(modArray);
	});
	return modArray;
}

function RenderTemplate(file, props) {
	var template = fs.readFileSync(file).toString().trim();
	template = template.replace(/\$\{([^\:\}]+)(?:\:([^\s\:\}]+))?\}/g, function (match, key, format) {
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
	fs.writeFileSync(file, template);
	return template;
}

function CreateApp(appName, appId, appPath, appVersion, tiSDK) {

	if(!appName || appName.length == 0) {
		log('No name');
		return;
	}
	if(!appId || appId.length == 0) {
		log('No id');
		return;
	}
	if(!appPath || appPath.length == 0) {
		log('No path');
		return;
	}
	if(!appVersion || appVersion.length == 0) {
		log('No version');
		return;
	}
	if(!tiSDK || tiSDK.length == 0) {
		log('No sdk');
		return;
	}

	function copyFilesToDir(_dirFrom, _dirTo) {
		// Get all the files from the app template directory
		var allFiles = fs.readdirSync(_dirFrom);

		for(var i = 0, len = allFiles.length; i < len; i++) {
			
			var oldFilePath = path.join(_dirFrom, allFiles[i]);
			
			var fileInfo = fs.statSync(oldFilePath);
			var fileName = allFiles[i];

			fileName = fileName.replace(/APP_NAME/g, appName.replace(/ /g, '_'));
			fileName = fileName.replace(/APP_ID/g, appId);
			fileName = fileName.replace(/APP_VERSION/g, appVersion);
			fileName = fileName.replace(/SDK_PATH/g, tiSDK);
			fileName = fileName.replace(/APP_PATH/g, appPath);
			var newFilePath = path.join(_dirTo, fileName);

			if(fileInfo.isDirectory()) {
				if(!fs.existsSync(newFilePath))
					fs.mkdirSync(newFilePath);
				copyFilesToDir(oldFilePath, newFilePath);
				continue;
			}

			var fileContent = fs.readFileSync(oldFilePath).toString().trim();
			fileContent = fileContent.replace(/APP_NAME/g, appName.replace(/ /g, '_'));
			fileContent = fileContent.replace(/APP_ID/g, appId);
			fileContent = fileContent.replace(/APP_VERSION/g, appVersion);
			fileContent = fileContent.replace(/SDK_PATH/g, tiSDK);
			fileContent = fileContent.replace(/APP_PATH/g, appPath);

			fs.writeFileSync(newFilePath, fileContent);

		}
	}
	copyFilesToDir(path.join(__dirname, '../../templates/app/default'), path.join(appPath, 'build', 'blackberry'));
}
function BlackBerry(_params) {

	this.projectDir = _params.projectDir;
	this.tiSDK = _params.titaniumBBSdkPath;
	this.tiapp = _params.tiapp;
	this.appName = String(this.tiapp.name);
	this.tiapp.name = this.tiapp.name.replace(/ /g, '_');
	this.ipAddress = _params.ipAddress;
	this.availablePort = _params.availablePort;
	this.modules = TiModules(this.projectDir, this.tiSDK, _params.tiapp, _params.logger);
	this.target = (_params.target || '').toLowerCase();
}

function RunCommand(_cmd, _logger, _callback) {
	_logger.info('Running: ' + _cmd);
	var ndkPath = findNDK();
	var envFile = findEnvFile(ndkPath);
	var bashFile = path.join(ndkPath, envFile);
	_cmd = 'source ' + bashFile + ';' + _cmd;
	exec(_cmd, function (err, stdout, stderr) {
		if(err)
			_logger.error('' + err);
		if(stdout)
			_logger.info('' + stdout);
		if(stderr)
			_logger.debug('' + stderr);
		_callback();
	});
}

BlackBerry.prototype.run = function(argv, _onFinish) {

	var buildBlackberry = path.join(this.projectDir, 'build', 'blackberry');
	var pwd = process.cwd();
	process.chdir(buildBlackberry);
	var isDevice = this.target == 'device' || this.target == 'distribute';
	var isRelease = this.target == 'distribute';

	var cmd = [
		'make -j3 ' + (isDevice ? 'Device' : 'Simulator') + (isRelease ? '-Release' : '-Debug'),
		'blackberry-nativepackager -package build/' + this.tiapp.name + '.bar bar-descriptor.xml -configuration ' + (isDevice ? 'Device' : 'Simulator') + (isRelease ? '-Release' : '-Debug')
	];

	if(!isRelease) {
		if(isDevice) {
			cmd[1] += ' -debugToken "' + argv['debug-token'] + '" -devMode';
		}
		cmd.push('blackberry-deploy -installApp -launchApp -device ' + (argv['ip-address'] || '""') + ' -password "' + (argv.password || '')+ '" build/'+this.tiapp.name+'.bar')
	} else {
		cmd.push('blackberry-signer -storepass "' + (argv['keystore-password'] || '') + '" build/' + this.tiapp.name + '.bar')
	}
	var self = this;
	RunCommand(cmd[0], argv.logger, function(){
		RunCommand(cmd[1], argv.logger, function(){
			RunCommand(cmd[2], argv.logger, function(){
				if(isRelease) {
					var outputDir = argv['output-dir'];
					wrench.mkdirSyncRecursive(outputDir); 
					var barFile = path.join('build', self.tiapp.name + '.bar'); 
					fs.createReadStream(barFile).pipe(fs.createWriteStream(path.join(outputDir, self.tiapp.name + '.bar')));						
				}
				process.chdir(pwd);
				_onFinish();
			});
		});
	});
}

BlackBerry.prototype.build = function(_onFinish) {

	var build = path.join(this.projectDir, 'build');
	if(!fs.existsSync(build)) {
		fs.mkdirSync(build);
	}

	var buildBlackberry = path.join(build, 'blackberry');

	if (!fs.existsSync(buildBlackberry)) {
		fs.mkdirSync(buildBlackberry);
	} else {
		// TODO: skip rebuilding?
	}
	CreateApp(this.tiapp.name, this.tiapp.id, this.projectDir, this.tiapp.version, this.tiSDK);

	var nativeModuleHeaders = '';
	var nativeModuleResgister = '';
	var modulesArmA = '';
	var modulesArmAG = '';
	var modulesX86A = '';
	var modulesX86AG = '';
	this.modules.forEach(function(p){
		if (p.type === MOD_COMMON_JS) {  
			var oldLibPath = path.join(p.location, p.name + '.js');
			var newLibPath = path.join(buildBlackberry, '_private_assets_' , p.name + '.js');
			afs.copyFileSync(oldLibPath, newLibPath);
		} else if (p.type == MOD_NATIVE) {

			var oldArmPath = path.join(p.location, 'arm', 'a.le-v7', 'lib' + p.name + '.a');
			var newArmPath = path.join(buildBlackberry, 'libs', 'arm', 'a', 'lib' + p.name + '.a');
			afs.copyFileSync(oldArmPath, newArmPath);

			oldArmPath = path.join(p.location, 'arm', 'a.le-v7-g', 'lib' + p.name + '.a');
			newArmPath = path.join(buildBlackberry, 'libs', 'arm', 'a-g', 'lib' + p.name + '.a');
			afs.copyFileSync(oldArmPath, newArmPath);

			var oldX86Path = path.join(p.location, 'x86', 'a', 'lib' + p.name + '.a');
			var newX86Path = path.join(buildBlackberry, 'libs', 'x86', 'a', 'lib' + p.name + '.a');
			afs.copyFileSync(oldX86Path, newX86Path);

			oldX86Path = path.join(p.location, 'x86', 'a-g', 'lib' + p.name + '.a');
			newX86Path = path.join(buildBlackberry, 'libs', 'x86', 'a-g', 'lib' + p.name + '.a');
			afs.copyFileSync(oldX86Path, newX86Path);

			var oldHeaderPath = path.join(p.location, 'header', p.name + 'ModuleStartup.h');
			var newHeaderPath = path.join(buildBlackberry,'libs', 'headers', p.name + 'ModuleStartup.h');
			afs.copyFileSync(oldHeaderPath, newHeaderPath);

			nativeModuleHeaders += '#include "' + p.name + 'ModuleStartup.h"\n';
			nativeModuleResgister += 'tiRegisterModule("' + p.id + '", ' + p.name + 'ModuleStartup::CreateModule);\n';

			modulesArmA += 'LIBS += "$$BASEDIR/libs/arm/a/lib' + p.name + '.a"\n';
			modulesArmAG += 'LIBS += "$$BASEDIR/libs/arm/a-g/lib' + p.name + '.a"\n';
			modulesX86A += 'LIBS += "$$BASEDIR/libs/x86/a/lib' + p.name + '.a"\n';
			modulesX86AG += 'LIBS += "$$BASEDIR/libs/x86/a-g/lib' + p.name + '.a"\n';
		}
	});

	RenderTemplate(buildBlackberry + '/src/main.cpp', {
		module_headers: nativeModuleHeaders,
		module_includes: nativeModuleResgister
	});

	RenderTemplate(buildBlackberry + '/' + this.tiapp.name + '.pro', {
		modules_arm_a: modulesArmA,
		modules_arm_a_g: modulesArmAG,
		modules_x86_a: modulesX86A,
		modules_x86_a_g: modulesX86AG
	});

	var autoOrient = false;
	var orientation = '';
	var permissions = '';
	if (this.tiapp.blackberry && this.tiapp.blackberry.permissions) {
		for (key in this.tiapp.blackberry.permissions) {
			permissions += '<permission>' + key + '</permission>\n\t';
		}
	}

	if (this.tiapp.analytics && this.tiapp.analytics == true) {
		permissions += '<permission>read_device_identifying_information</permission>\n\t';
	}
	if (this.tiapp.blackberry && this.tiapp.blackberry.orientation) {
		orientation = this.tiapp.blackberry['orientation'];
		if (orientation === 'auto') {
			autoOrient = true;
		}
	}

	var iconPath = '';
	var possibleIcons = [
		path.join(this.projectDir, 'Resources', 'appicon.png'),
		path.join(this.projectDir, 'Resources', 'blackberry', 'appicon.png'),
		// maybe more?
	];

	possibleIcons.forEach(function(icon) {
		if(fs.existsSync(icon)) {
			iconPath = icon;
			return false;
		};
	});
	RenderTemplate(buildBlackberry + '/bar-descriptor.xml', {
		binname: this.tiapp.name,
		description: this.tiapp.description || 'not specified',
		author: this.tiapp.publisher || 'not specified',
		autoOrient: autoOrient,
		orientation: orientation, 
		category: 'core.games',
		permissions: permissions || '',
		icon: iconPath,
		icon_name: 'appicon.png',
		appname: this.appName
	});


	// write app_properties.ini file 
	var appProps = '[General]\n';
	for (key in this.tiapp.properties) {
		for (key2 in this.tiapp.properties[key]) {
			if (key2 == 'value') {
				appProps += key + ' = "' + this.tiapp.properties[key][key2] + '"\n';
			}
		}
	}
	appProps += 'analytics = ' + this.tiapp['analytics'] + '\n';
	appProps += 'aguid = ' + this.tiapp['guid'] + '\n';
	appProps += 'version = ' + this.tiapp['version'] + '\n';
	if (this.target == 'distribute') {
		appProps += 'deploytype = production\n';
	} else {
		appProps += 'deploytype = development\n';
	}
	appProps += 'current_ip = ' + this.ipAddress + '\n';
	appProps += 'current_port = ' + this.availablePort + '\n';
	var appPropsFile = path.join(buildBlackberry, '_private_assets_' , 'app_properties.ini');
	fs.writeFileSync(appPropsFile, appProps);
	_onFinish();
};


module.exports = BlackBerry;
