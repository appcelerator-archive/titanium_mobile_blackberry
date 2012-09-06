/*
 * build.js: Titanium <PLATFORM> CLI build command
 *
 * Copyright (c) 2012, Appcelerator, Inc.  All Rights Reserved.
 * See the LICENSE file for more information.
 */

function build(logger, config, cli, sdkVersion, lib, finished) {
	logger.info(__('Compiling "%s" build', cli.argv['build-type']));
}

module.exports = build;