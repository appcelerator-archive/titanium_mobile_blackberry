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

exports.run = function (logger, config, cli, projectConfig) {
	var templatePath = afs.resolvePath(path.dirname(module.filename), '..', '..', 'templates', cli.argv.type, cli.argv.template),
		projectDir = afs.resolvePath(cli.argv['workspace-dir'], cli.argv.name);

	if (afs.exists(templatePath)) {
		if (cli.argv.type == 'app') {
			var resPath = path.join(projectDir, 'Resources', 'blackberry');
			templatePath = path.join(templatePath, 'Resources', 'blackberry');
			afs.copyDirSyncRecursive(templatePath, resPath, { preserve: true, logger: logger.debug });
		} else if (cli.argv.type == 'module') {
			afs.copyDirSyncRecursive(templatePath, projectDir, { preserve: true, logger: logger.debug });

			// now fixup the template files	
			var cpp_file_path = path.join(projectDir, 'ReplaceWithModuleName.cpp');
			var cpp_template = fs.readFileSync(cpp_file_path).toString().trim();
			cpp_template = cpp_template.replace(/ReplaceWithModuleName/g, cli.argv.name);	
			fs.writeFileSync(path.join(projectDir, cli.argv.name + '.cpp'), cpp_template);
			fs.unlinkSync(cpp_file_path);

			var header_file_path = path.join(projectDir, 'ReplaceWithModuleName.h');
			var header_template = fs.readFileSync(header_file_path).toString().trim();
			header_template = header_template.replace(/ReplaceWithModuleName/g, cli.argv.name);	
			header_template = header_template.replace(/REPLACEWITHMODULENAME/g, cli.argv.name.toUpperCase());				
			fs.writeFileSync(path.join(projectDir, cli.argv.name + '.h'), header_template);
			fs.unlinkSync(header_file_path);	

			var qt_project_file_path = path.join(projectDir, 'ReplaceWithModuleName.pro');
			var qt_project_template = fs.readFileSync(qt_project_file_path).toString().trim();
			fs.writeFileSync(path.join(projectDir, cli.argv.name + '.pro'), qt_project_template);
			fs.unlinkSync(qt_project_file_path);	

			fs.unlinkSync(path.join(projectDir, 'timodule.xml'));	

			var app_sample_file_path = path.join(projectDir, 'example', 'app.js');
			var app_sample_template = fs.readFileSync(app_sample_file_path).toString().trim();
			app_sample_template = app_sample_template.replace(/___PROJECTNAME___/g, cli.argv.name);	
			app_sample_template = app_sample_template.replace(/__MODULE_ID__/g, cli.argv.name);	
			fs.writeFileSync(app_sample_file_path, app_sample_template);	


			var assets_read_file_path = path.join(projectDir, 'assets', 'README');
			var assets_read_template = 'Place your assets like PNG files in this directory and they will be packaged with your module.'
			fs.writeFileSync(assets_read_file_path, assets_read_template);	

			var doc_index_file_path = path.join(projectDir, 'documentation', 'index.md');
			var doc_index_template = fs.readFileSync(doc_index_file_path).toString().trim();
			doc_index_template = doc_index_template.replace(/___PROJECTNAME___/g, cli.argv.name);	
			doc_index_template = doc_index_template.replace(/__MODULE_ID__/g, cli.argv.name);
			doc_index_template = doc_index_template.replace(/___PROJECTNAMEASIDENTIFIER__/g, 'MyModule');
			fs.writeFileSync(doc_index_file_path, doc_index_template);

			var cproject_file_path = path.join(projectDir, '.cproject');
			var cproject_template = fs.readFileSync(cproject_file_path).toString().trim();
			cproject_template = cproject_template.replace(/ReplaceWithModuleName/g, cli.argv.name);		
			fs.writeFileSync(cproject_file_path, cproject_template);

			var project_file_path = path.join(projectDir, '.project');
			var project_template = fs.readFileSync(project_file_path).toString().trim();
			project_template = project_template.replace(/ReplaceWithModuleName/g, cli.argv.name);		
			fs.writeFileSync(project_file_path, project_template);

			var makefile_file_path = path.join(projectDir, 'Makefile');
			var makefile_template = fs.readFileSync(makefile_file_path).toString().trim();
			makefile_template = makefile_template.replace(/ReplaceWithModuleName/g, cli.argv.name);		
			fs.writeFileSync(makefile_file_path, makefile_template);
		}
	}
};
