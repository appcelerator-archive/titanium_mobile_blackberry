/*
 * create.js: Titanium iOS CLI create command
 *
 * Copyright (c) 2012, Appcelerator, Inc.  All Rights Reserved.
 * See the LICENSE file for more information.
 */

var appc = require('node-appc'),
	afs = appc.fs,
	fs = require('fs'),
	path = require('path');


exports.config = function (logger, config, cli) {
	return {
		//
	};
};



function copyFilesToDir(_dirFrom, _dirTo, _config) {
	// Get all the files from the module template directory
	var allFiles = fs.readdirSync(_dirFrom);

	for(var i = 0, len = allFiles.length; i < len; i++) {
		
		var oldFilePath = path.join(_dirFrom, allFiles[i]);
		
		var fileInfo = fs.statSync(oldFilePath);
		var fileName = allFiles[i];

		fileName = fileName.replace(/__MODULE_NAME__/g, _config.__PROJECT_SHORT_NAME__);
		fileName = fileName.replace(/__MODULE_ID__/g, _config.__MODULE_ID__);
		fileName = fileName.replace(/__MODULE_VERSION__/g, '1.0');

		var newFilePath = path.join(_dirTo, fileName);

		if(fileInfo.isDirectory()) {
			fs.mkdirSync(newFilePath);
			copyFilesToDir(oldFilePath, newFilePath, _config);
			continue;
		}

		var fileContent = fs.readFileSync(oldFilePath).toString().trim();
		fileContent = fileContent.replace(/__MODULE_NAME__/g, _config.__PROJECT_SHORT_NAME__);
		fileContent = fileContent.replace(/__MODULE_ID__/g, _config.__MODULE_ID__);
		fileContent = fileContent.replace(/__MODULE_VERSION__/g, '1.0');
		fileContent = fileContent.replace(/__SDK_ROOT__/g, _config.__SDK_ROOT__);


		fs.writeFileSync(newFilePath, fileContent);

	}
}

exports.run = function (logger, config, cli, projectConfig) {
	console.log(projectConfig);
	var templatePath = afs.resolvePath(path.dirname(module.filename), '..', '..', 'templates', cli.argv.type, cli.argv.template),
		projectDir = afs.resolvePath(cli.argv['workspace-dir'], cli.argv.name);

	if (afs.exists(templatePath)) {
		if (cli.argv.type == 'app') {
			var resPath = path.join(projectDir, 'Resources', 'blackberry');
			templatePath = path.join(templatePath, 'Resources', 'blackberry');
			afs.copyDirSyncRecursive(templatePath, resPath, { preserve: true, logger: logger.debug });
		} else if (cli.argv.type == 'module') {
			projectDir = path.join(projectDir, 'module');
			fs.mkdirSync(projectDir);
			copyFilesToDir(templatePath, projectDir, projectConfig);
		}
	}
};
