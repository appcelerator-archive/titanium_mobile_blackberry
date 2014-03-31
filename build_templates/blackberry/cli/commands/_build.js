
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
    __n = i18n.__n,
    ti = require('titanium-sdk'),
    BlackBerry = require('../common/bb_cli'),
    path = require('path'),
    net = require('net'),
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
        var self = this;
        var ipFound = false;
        appc.net.interfaces(function(a){
            for(var key in a) {
                var obj = a[key];
                if(!obj.gateway) continue;
                obj.ipAddresses.forEach(function (ip) {
                    if(ip.family == 'IPv4') {
                        self.ipAddress = ip.address;
                        ipFound = true;
                        return;
                    }
                });
                if(ipFound) break;
            }
            getAvailablePort(function(port){
                self.availablePort = port;
                var bbndk = new BlackBerry(self);
                bbndk.build(finished);
            });

        });

    }.bind(this));
}

function getAvailablePort(_callback) {
    var port = Math.floor(Math.random() * (9999 - 8001 + 1)) + 8001;
    var server = net.createServer(function(socket) {
        socket.on('connection',function(socket){
            console.info('socket connection...');
        });
        socket.on('data',function(message){
            var parts = (message + '').split('\n');
            parts.forEach(function(msg){
                console.info('' + msg.replace(/\n\net/g, '\n'));
            });
        });
        socket.on('error',function(error){
            console.info('error on socket message:'+error);
        });
    });
    server.on('error', function(a,b){
        getAvailablePort(_callback);
    });
    server.on('listening', function() {
        console.info('[INFO] Listening to port ' + port);
        _callback(port);
    });
    server.listen(port);
}
