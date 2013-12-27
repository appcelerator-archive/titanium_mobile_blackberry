var win = Ti.UI.createWindow({
  backgroundColor: 'green'
});

win.open();

var label = Ti.UI.createLabel({
    text: 'Token:',
    left: 20, right: 20
});

win.add(label);
Ti.BlackBerry.createPushService({
    appId: '4427-7h6l37627mrr0I3956a74om7643M17l7921',
    ppgUrl: 'http://cp4427.pushapi.eval.blackberry.com',
    usePublicPpg: true,
    launchApplicationOnPush: true,
    onSessionCreated: function(e) {
        Ti.API.info('------------------');
        Ti.API.info('Session Created');
        Ti.API.info('------------------');
    },
    onChannelCreated: function(e) {
        Ti.API.info('------------------');
        Ti.API.info('Channel Created');
        Ti.API.info('Message: ' + e.message);
        Ti.API.info('Token: ' + e.token);
        Ti.API.info('------------------');
        label.text = 'Token: ' + e.token;
    },
    onPushRecieved: function(e) {
        Ti.API.info('------------------');
        Ti.API.info('Push Recieved');
        Ti.API.info('Id: ' + e.pushId);
        Ti.API.info('PayloadId: ' + e.payloadId);
        Ti.API.info('Data: ' + e.data);
        Ti.API.info('------------------');
        e.source.removePush(e.pushId);
    },
    onConfigError: function(e) {
        Ti.API.info('------------------');
        Ti.API.info('CONFIG ERROR');
        Ti.API.info('Title: ' + e.errorTitle);
        Ti.API.info('Msg: ' + e.errorMessage);
        Ti.API.info('------------------');
        Ti.UI.createAlertDialog({
            title: e.errorTitle,
            message: e.errorMessage
        }).show();
    },
    onError: function(e) {
        Ti.API.info('------------------');
        Ti.API.info('ERROR');
        Ti.API.info('Title: ' + e.errorTitle);
        Ti.API.info('Msg: ' + e.errorMessage);
        Ti.API.info('------------------');
        Ti.UI.createAlertDialog({
            title: e.errorTitle,
            message: e.errorMessage
        }).show();
    },
    onAppOpened: function(e) {
        Ti.API.info('------------------');
        Ti.API.info('App Opened Recieved');
        Ti.API.info('PushId: ' + e.pushId);
        Ti.API.info('PayloadId: ' + e.payloadId);
        Ti.API.info('Data: ' + e.data);
        Ti.API.info('------------------');
        
        e.source.removePush(e.pushId);
    }
});

