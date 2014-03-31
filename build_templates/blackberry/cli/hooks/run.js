/*
 * run.js: Titanium iOS CLI run hook
 *
 * Copyright (c) 2012, Appcelerator, Inc.  All Rights Reserved.
 * See the LICENSE file for more information.
 */

var appc = require('node-appc');
    afs = appc.fs,
    BlackBerry = require('../common/bb_cli'),
    

exports.init = function (logger, config, cli, appc) {
    cli.addHook('build.post.compile', function (build, finished) {
    	this.logger = logger;
    	this.projectDir = cli.argv['project-dir'];
    	this.titaniumBBSdkPath = afs.resolvePath(__dirname, '..', '..');
    	this.projectName = cli.tiapp['name'];
    	this.deviceIP = cli.argv['ip-address'];
    	this.tiapp = cli.tiapp;
    	this.target = cli.argv.target;
        this.type2variantCpu = {'simulator': ['o-g', 'x86'],
                     'device': ['o.le-v7', 'arm'],
                     'distribute': ['o.le-v7', 'arm']};
        this.ndk = cli.argv['ndk'];
        this.debugToken = cli.argv['debug-token'];   
        this.password = cli.argv['password'];  
        this.keystorePassword = cli.argv['keystore-password'];
        this.outputDir = cli.argv['output-dir'];      

        var bbndk = new BlackBerry(this);
        cli.argv.logger = logger;
        bbndk.run(cli.argv, finished);
    });
};
