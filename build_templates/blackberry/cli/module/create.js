var Replace = require('./replace');
var Wrench = require('./wrench');


function slipArguments(_arg) {
	if(_arg.indexOf('--') != 0) return false;
	_arg = _arg.replace('--', '');
	var parts = _arg.split('=');
	if(!parts[1]) return false;

	var obj = [];
	obj.push(parts[0]);
	obj.push(parts[1]);
	return obj;
}

function failBuild(_name) {
	console.log('[ERROR] Needs ' + _name);
	process.kill();
}

function capitaliseFirstLetter(str)
{
    return str.charAt(0).toUpperCase() + str.slice(1);
}


function createModule (_params) {
	var moduleName = _params.name;
	var moduleVersion = _params.version;
	var moduleId = _params.id;
	var moduleFolder = _params.folder;
	var tiSDK = _params.tiSDK || null;

	console.log(moduleName);
	console.log(moduleVersion);
	console.log(moduleId);
	console.log(moduleFolder);
	console.log(tiSDK);


	// cd to the folder specified
	// create a new folder with the module name
	// cd to module template in Ti SDK `tiSDK` or min sdk (3.1.3)
	// copy the folder over to the new created folder
	// Go over the files and replace the names according to the name
	//		NameModuleStartup.h
	//		NameModuleStartup.cpp
	//		NameModule.h
	//		NameModule.cpp
	//		name.pro <---- set the path to the Ti SDK
	// 		Find and replace all
	//				__MODULE_NAME__
	//				__MODULE_ID__
	//				__MODULE_VERSION__


	var newFolder = moduleFolder + '/' + moduleName;
	Wrench.copyDirSyncRecursive(__dirname + '/../../templates/module', newFolder, {
		forceDelete: true,
	});

	Replace({
		regex: '__MODULE_NAME__',
		replacement: moduleName,
		excludeList: '',
		paths: [newFolder],
		recursive: true,
		silent: true,
	});

	Replace({
		regex: '__MODULE_ID__',
		replacement: moduleId,
		excludeList: '',
		paths: [newFolder],
		recursive: true,
		silent: true,
	});

	Replace({
		regex: '__MODULE_VERSION__',
		replacement: moduleVersion,
		paths: [newFolder],
		excludeList: '',
		recursive: true,
		silent: true,
	});


}
(function(){
	var args = process.argv;
	var parts = {};
	for(var key in args) {
		var obj = slipArguments(args[key]);
		if(!obj) continue;
		parts[obj[0]] = obj[1];
	}

	if(!parts.name) failBuild('name');
	if(!parts.id) failBuild('id');
	if(!parts.folder) failBuild('folder');
	if(!parts.version) failBuild('version');

	createModule(parts);

})();

