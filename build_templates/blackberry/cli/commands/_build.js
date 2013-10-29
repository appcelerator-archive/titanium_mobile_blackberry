
/*
 * build.js: Titanium CLI build command stub. Called when a project is built.
 *
 * Copyright (c) 2013, Appcelerator, Inc.  All Rights Reserved.
 * See the LICENSE file for more information.
 */
 
var appc = require('node-appc'),
    afs = appc.fs,
    i18n = appc.i18n(__dirname),
    __ = i18n.__,
    ti = require('titanium-sdk'),
    BlackBerryNDK = require('../common/blackberryndk'),
    path = require('path'),

    targets = ['simulator', 'device', 'distribute'];
 
exports.config = function (logger, config, cli) {

    return {
        options: {
            'ip-address': {
                abbr: 'A',
                //default: '192.168.137.159',
                desc: __('the internet address of the simulator or device'),
                hint: __('address')
            },
            'target': {
                abbr: 'T',
                desc: __('the target to build for,'),
                hint: __('value'),
                values: ['simulator', 'device', 'distribute']
            },
            'debug-token': {
                abbr: 'D',
                desc: __('the path to the debug token bar file'),
                hint: __('path')
            },
            'ndk': {
                abbr: 'N',
                desc: __('the path to the BlackBerry Native Development SDK'),
                hint: __('path')
            },
            'password': {
                abbr: 'P',
                desc: __('the password used on the simulator or device'),
                hint: __('value')
            },
            'keystore-password': {
                abbr: 'K',
                desc: __('the password given while registering the application signing keys'),
                hint: __('value')
            },
            'output-dir': {
                abbr: 'O',
                desc: __('the path containing the signed bar file'),
                hint: __('path')
            }
        }
    };
};
 
exports.validate = function (logger, config, cli) {
	
	ti.validateProjectDir(logger, cli, cli.argv, 'project-dir'); 
};
 

exports.run = function (logger, config, cli, finished) {
     cli.fireHook('build.pre.construct', function () {
        new build(logger, config, cli, function (err) {
            cli.fireHook('build.post.compile', this, function (postHookErr) {
                sendAnalytics(cli);
                if (postHookErr && postHookErr.type == 'AppcException') {
                    logger.error(postHookErr.message);
                    postHookErr.details.forEach(function (line) {
                        line && logger.error(line);
                    });
                    logger.error();
                }
            }.bind(this));
        });
    });
};
 
function sendAnalytics(cli) {
    var eventName = cli.argv['device-family'] + '.' + cli.argv.target;
    if (cli.argv.target == 'distribute') {
        eventName = cli.argv['device-family'] + '.distribute.' + cli.argv.target.replace('dist-', '');
    } else if (cli.argv['debug-host']) {
        eventName += '.debug';
    } else if (cli.argv['profiler-host']) {
        eventName += '.profile';
    } else {
        eventName += '.run';
    }
    cli.addAnalyticsEvent(eventName, {
        dir: cli.argv['project-dir'],
        name: cli.tiapp.name,
        publisher: cli.tiapp.publisher,
        url: cli.tiapp.url,
        image: cli.tiapp.icon,
        appid: cli.tiapp.id,
        description: cli.tiapp.description,
        type: cli.argv.type,
        guid: cli.tiapp.guid,
        version: cli.tiapp.version,
        copyright: cli.tiapp.copyright,
        date: (new Date()).toDateString()
    });
}
 
function build(logger, config, cli, finished) {
    this.logger = logger;
    this.projectDir = cli.argv['project-dir'];
    this.titaniumBBSdkPath = afs.resolvePath(__dirname, '..', '..');
    this.projectName = cli.tiapp['name'];
    this.deviceInternetAddress = cli.argv['ip-address'];
    this.tiapp = cli.tiapp;
    this.target = cli.argv.target;
    this.type2variantCpu = {'simulator': ['o-g', 'x86', 'a-g'],
                     'device': ['o.le-v7', 'arm', 'a.le-v7'],
                     'distribute': ['o.le-v7', 'arm', 'a.le-v7']};
    this.ndk = cli.argv['ndk'];

    cli.fireHook('build.pre.compile', this, function (e) {
        // Make sure we have an app.js. This used to be validated in validate(), but since plugins like
        // Alloy generate an app.js, it may not have existed during validate(), but should exist now
        // that build.pre.compile was fired.
        ti.validateAppJsExists(this.projectDir, this.logger, 'blackberry');


        var bbndk = new BlackBerryNDK(this);

        var projectBuildPath = path.join(this.projectDir, 'build', 'blackberry');
        // permission errors can be thrown here if the projectDir folder is private
        afs.copyDirSyncRecursive(path.join(this.titaniumBBSdkPath, 'tibbapp'), projectBuildPath, { preserve: true, logger: logger.debug });

        bbndk.build(finished);
    }.bind(this));
}
