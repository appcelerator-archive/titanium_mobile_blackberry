/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiPushNotificationProxy.h"
#include <bb/network/PushErrorCode>
#include <bb/platform/Notification>

#define BB_OPEN_INVOCATION_ACTION "bb.action.OPEN"

namespace TiBlackberry {

TiPushNotificationProxy::TiPushNotificationProxy(const char* name) :
		Ti::TiProxy(name),
		_shouldRegisterToLaunch(false),
		_shouldUnregisterFromLaunch(false),
		_launchApplicationOnPush(false),
		_configSaveAction(false),
		_hasBeenInForeground(false),
	    _appId(""),
	    _ppgUrl(""),
	    _pushInitiatorUrl(""),
	    _usePublicPpg(true),
	    _useSdk(false)
{

	createPropertySetterGetter("appId", _setAppId, _getAppId);
	createPropertySetterGetter("ppgUrl", _setPpgUrl, _getPpgUrl);
	createPropertySetterGetter("pushInitiatorUrl", _setPushInitiatorUrl, _getPushInitiatorUrl);
	createPropertySetterGetter("usePublicPpg", _setUsePublicPpg, _getUsePublicPpg);
	createPropertySetterGetter("useSDK", _setUseSDK, _getUseSDK);
	createPropertySetterGetter("launchApplicationOnPush", _setLaunchApplicationOnPush, _getLaunchApplicationOnPush);
	createPropertySetterGetter("user", _setUser, _getUser);

	createPropertyFunction("removePush", _removePush);
	createPropertyFunction("markPushAsRead", _markPushAsRead);
	createPropertyFunction("removeAllPushes", _removeAllPushes);
	createPropertyFunction("markAllPushesAsRead", _markAllPushesAsRead);

	_eventHandler = new TiPushNotificationEventHandler(this);
    _invokeManager = new bb::system::InvokeManager();
	_pushNotificationService = new PushNotificationService();
	_configurationService = new ConfigurationService();
    _configuration = new Configuration();
    _user = new User();

    // connect the push notification service signals and slots
    QObject::connect(_pushNotificationService, SIGNAL(createSessionCompleted(const bb::network::PushStatus&)),
            _eventHandler, SLOT(onCreateSessionCompleted(const bb::network::PushStatus&)));
    QObject::connect(_pushNotificationService, SIGNAL(createChannelCompleted(const bb::network::PushStatus&, const QString)),
            _eventHandler, SLOT(onCreateChannelCompleted(const bb::network::PushStatus&, const QString)));
    QObject::connect(_pushNotificationService, SIGNAL(noPushServiceConnection()),
            _eventHandler, SLOT(onNoPushServiceConnection()));
    QObject::connect(_invokeManager, SIGNAL(invoked(const bb::system::InvokeRequest&)),
    		_eventHandler, SLOT(onInvoked(const bb::system::InvokeRequest&)));
    QObject::connect(bb::cascades::Application::instance(), SIGNAL(fullscreen()), _eventHandler, SLOT(onFullScreen()));

    _tiAppId = Ti::TiHelper::getAppSetting("app_id").toString();
    _tiAppPushTitle = Ti::TiHelper::getAppSetting("push_title").toString();
    _tiAppKeyOpen = Ti::TiHelper::getAppSetting("ti.bb.invoke.target.key.push").toString();
}

TiPushNotificationProxy::~TiPushNotificationProxy() {
	_eventHandler->deleteLater();
    _invokeManager->deleteLater();
	_pushNotificationService->deleteLater();
	delete _configurationService;
    delete _configuration;
    delete _user;
}

void TiPushNotificationProxy::initEnd()
{
	clearWeak();
	if(!validateConfiguration())
	{
		return;
	}
	saveConfiguration();
}

void TiPushNotificationProxy::setFullScreen(bool flag) {
	_hasBeenInForeground = flag;
}

Ti::TiValue TiPushNotificationProxy::removePush(Ti::TiValue value)
{
	_pushNotificationService->removePush((int)value.toNumber());
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiPushNotificationProxy::markPushAsRead(Ti::TiValue value)
{
	_pushNotificationService->markPushAsRead((int)value.toNumber());
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiPushNotificationProxy::removeAllPushes(Ti::TiValue)
{
	_pushNotificationService->removeAllPushes();
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiPushNotificationProxy::markAllPushesAsRead(Ti::TiValue)
{
	_pushNotificationService->markAllPushesAsRead();
	Ti::TiValue val;
	val.setUndefined();
	return val;

}

void TiPushNotificationProxy::setAppId(Ti::TiValue value)
{
	_appId = value.toString();
}
void TiPushNotificationProxy::setPpgUrl(Ti::TiValue value)
{
	_ppgUrl = value.toString();
}
void TiPushNotificationProxy::setPushInitiatorUrl(Ti::TiValue value)
{
	_pushInitiatorUrl = value.toString();
}
void TiPushNotificationProxy::setUsePublicPpg(Ti::TiValue value)
{
	_usePublicPpg = value.toBool();
}
void TiPushNotificationProxy::setUseSDK(Ti::TiValue value)
{
	_useSdk = value.toBool();
}
void TiPushNotificationProxy::setLaunchApplicationOnPush(Ti::TiValue value)
{
	_launchApplicationOnPush = value.toBool();
}
void TiPushNotificationProxy::setUser(Ti::TiValue value)
{
	QMap<QString, Ti::TiValue> _object = value.toMap();

	Ti::TiValue userId = _object["id"];
	Ti::TiValue userPassword = _object["password"];
	_user->setPassword(userPassword.toString());
	_user->setUserId(userId.toString());
}

Ti::TiValue TiPushNotificationProxy::getAppId()
{
	Ti::TiValue value;
	value.setString(_appId);
	return value;
}
Ti::TiValue TiPushNotificationProxy::getPpgUrl()
{
	Ti::TiValue value;
	value.setString(_ppgUrl);
	return value;
}
Ti::TiValue TiPushNotificationProxy::getPushInitiatorUrl()
{
	Ti::TiValue value;
	value.setString(_pushInitiatorUrl);
	return value;
}
Ti::TiValue TiPushNotificationProxy::getUsePublicPpg()
{
	Ti::TiValue value;
	value.setBool(_usePublicPpg);
	return value;
}
Ti::TiValue TiPushNotificationProxy::getUseSDK()
{
	Ti::TiValue value;
	value.setBool(_useSdk);
	return value;
}
Ti::TiValue TiPushNotificationProxy::getLaunchApplicationOnPush()
{
	Ti::TiValue value;
	value.setBool(_launchApplicationOnPush);
	return value;
}
Ti::TiValue TiPushNotificationProxy::getUser()
{
	QMap<QString, Ti::TiValue> _object;

	Ti::TiValue userId;
	userId.setString(_user->userId());
	_object["id"] = userId;

	Ti::TiValue userPassword;
	userPassword.setString(_user->password());
	_object["password"] = userPassword;

	Ti::TiValue returnedValue;
	returnedValue.setMap(_object);
	return returnedValue;
}

void TiPushNotificationProxy::sessionCreated(const bb::network::PushStatus &status)
{
    if (status.code() == bb::network::PushErrorCode::NoError) {
        if (_shouldRegisterToLaunch) {
            _pushNotificationService->registerToLaunch();
        } else if (_shouldUnregisterFromLaunch) {
            _pushNotificationService->unregisterFromLaunch();
        }

        if (_configSaveAction){
        	Ti::TiEventParameters _params;
            fireCallback("onSessionCreated", _params);
        	createChannel();
        }
    } else{
    	Ti::TiEventParameters _params;
    	QString errorTitle;
    	QString errorMessage;
        if (_configSaveAction) {
        	errorTitle = "Configuration";
        	errorMessage = "Configuration was saved, but was unable to create push session. (Error code: " + QString::number(status.code()) + " " + status.errorDescription() +" )";
        } else {
        	errorTitle = _tiAppPushTitle;
        	errorMessage = "Error: unable to create push session. (Error code: " + QString::number(status.code())+ ")";
        }
        _params.addParam("errorTitle", errorTitle);
        _params.addParam("errorMessage", errorMessage);
        fireCallback("onError", _params);

    }

    _configSaveAction = false;
}

void TiPushNotificationProxy::channelCreated(const bb::network::PushStatus &status, const QString &token)
{
    // Typically in your own application you wouldn't want to display this error to your users
    QString message = QString("Create channel failed with error code: %0").arg(status.code());
    QString errorTitle;
    bool isError = false;
    switch(status.code()){
    case  bb::network::PushErrorCode::NoError:
         if (!_configuration->pushInitiatorUrl().isEmpty()) {
            // Now, attempt to subscribe to the Push Initiator

            // This is very important: the token returned in the create channel success event is what
            // the Push Initiator should use when initiating a push to the BlackBerry Push Service.
            // This token must be communicated back to the Push Initiator's server-side application.
            _pushNotificationService->subscribeToPushInitiator(*_user, token);
            return;
        } else {
            message = "Register succeeded.";
        }
        break;
    case  bb::network::PushErrorCode::TransportFailure:
    	isError = true;
        message = "Create channel failed as the push transport is unavailable. "
                  "Verify your mobile network and/or Wi-Fi are turned on. "
                  "If they are on, you will be notified when the push transport is available again.";
        errorTitle = "Transport failure";
        break;
    case bb::network::PushErrorCode::SubscriptionContentNotAvailable:
    	isError = true;
        message = "Create channel failed as the PPG is currently returning a server error. "
                  "You will be notified when the PPG is available again.";
        errorTitle = "Subscription content not available";

        break;
    }
    Ti::TiEventParameters _params;
    _params.addParam("statusCode", status.code());
    if(isError)
    {
        _params.addParam("errorTitle", errorTitle);
        _params.addParam("errorMessage", message);
    	fireCallback("onError", _params);
    }
    else
    {
        _params.addParam("token", token);
        _params.addParam("message", message);
    	fireCallback("onChannelCreated", _params);
    }

}

void TiPushNotificationProxy::pushReceived(const bb::system::InvokeRequest &request)
{
    if (_configurationService->hasConfiguration())
    {
        // The underlying PushService instance might not have been
        // initialized when an invoke first comes in
        // Make sure that we initialize it here if it hasn't been already
        // It requires an application ID (for consumer applications) so we have to check
        // that configuration settings have already been stored
        _pushNotificationService->initializePushService();

        if (request.action().compare(BB_PUSH_INVOCATION_ACTION) == 0)
        {
            // Received an incoming push
            // Extract it from the invoke request and then process it
            bb::network::PushPayload payload(request);
            if (payload.isValid())
            {

			    Push push(payload);
			    push.setSeqNum(_pushNotificationService->savePush(push));
				bb::platform::Notification *notification = new bb::platform::Notification(_tiAppId + "_" + QString::number(push.seqNum()), _eventHandler);
			    notification->setTitle(_tiAppPushTitle);
			    notification->setBody(QString(payload.data()));

			    // Add an invoke request to the notification
			    // This invoke will contain the seqnum of the push.
			    // When the notification in the BlackBerry Hub is selected, this seqnum will be used to lookup the push in
			    // the database and display it
			    bb::system::InvokeRequest invokeRequest;
			    invokeRequest.setTarget(_tiAppKeyOpen);
			    invokeRequest.setAction(BB_OPEN_INVOCATION_ACTION);
			    invokeRequest.setMimeType("text/plain");
			    invokeRequest.setData(QByteArray::number(push.seqNum()));
			    notification->setInvokeRequest(invokeRequest);

           	 	Ti::TiEventParameters _params;
				_params.addParam("pushId", push.seqNum());
				_params.addParam("payloadId", payload.id());
				_params.addParam("data", QString(payload.data()));
				fireCallback("onPushReceived", _params);

				// Add the notification for the push to the BlackBerry Hub
			    // Calling this method will add a "splat" to the application icon, indicating that a new push has been received
                _pushNotificationService->acceptPush(payload.id());
                notification->notify();
                if (!_hasBeenInForeground) {
                    bb::cascades::Application::instance()->requestExit();
                }
            }
            else
            {
            	Ti::TiHelper::Log("[ERROR] something failed on \"pushReceived\"");
            }
        } else if (request.action().compare(BB_OPEN_INVOCATION_ACTION) == 0){
            // Received an invoke request to open an existing push (ie. from a notification in the BlackBerry Hub)
            // The payload from the open invoke is the seqnum for the push in the database
            // openPush(request.data().toInt());

            bb::network::PushPayload payload(request);
       	 	Ti::TiEventParameters _params;

			_params.addParam("pushId", request.data().toInt(NULL));
			_params.addParam("payloadId", payload.id());
			_params.addParam("id", payload.id());
			_params.addParam("data", QString(payload.data()));
			fireCallback("onAppOpened", _params);
        }
        else
        {
            Ti::TiHelper::Log("[DEBUG] something PushNotificationProxy - failed on \"pushReceived\"");
        }

    }
}

void TiPushNotificationProxy::createChannel()
{
    if (!_configurationService->hasConfiguration())
    {
		Ti::TiEventParameters _params;
		_params.addParam("errorTitle", _tiAppPushTitle);
		_params.addParam("errorMessage", "Please fill in the config before attempting to register.");
		fireCallback("onConfigError", _params);
		return;
    }

    // The Push Service SDK will be used on the server-side so prompt for a username and password
    if(!_configuration->pushInitiatorUrl().isEmpty()) {
    	if(!_user->password().isEmpty() && !_user->userId().isEmpty())
    	{
            _pushNotificationService->createChannel();
            return;
    	}
    	else
    	{
    		Ti::TiEventParameters _params;
    		_params.addParam("errorTitle", "Need User");
    		_params.addParam("errorMessage", "Please add user by calling .setUser({ id: __, password: __ }).");
    		fireCallback("onConfigError", _params);
    		return;
    	}
    }
    _pushNotificationService->createChannel();
}

bool TiPushNotificationProxy::validateConfiguration()
{
    bool isValid = false;

    // Trim the values
    _appId = _appId.trimmed();
    _ppgUrl = _ppgUrl.trimmed();
    _pushInitiatorUrl = _pushInitiatorUrl.trimmed();

    QString errorTitle = "Configuration";
    QString errorMessage;
    if ((_usePublicPpg || _useSdk) && _appId.isEmpty()) {
    	errorMessage = "Error: No provider application ID was specified.";
    } else if ((_usePublicPpg || _useSdk) && _appId.indexOf("||") != -1) {
    	errorMessage = "Error: A provider application ID is not allowed to contain '||'.";
    } else if (_usePublicPpg && _ppgUrl.isEmpty()) {
    	errorMessage = "Error: No PPG URL was specified.";
    } else if (_usePublicPpg && !_ppgUrl.startsWith("http://")) {
    	errorMessage = "Error: The PPG URL must start with http://.";
    } else if (_usePublicPpg && !QUrl(_ppgUrl).isValid()) {
    	errorMessage = "Error: The PPG URL is invalid.";
    } else if (_usePublicPpg && _ppgUrl.endsWith("/")) {
    	errorMessage = "Error: The PPG URL should not end with a /. One will be automatically added to the end.";
    } else if (_useSdk && _pushInitiatorUrl.isEmpty()) {
    	errorMessage = "Error: No Push Initiator URL was specified.";
    } else if (_useSdk && !_pushInitiatorUrl.startsWith("http://") && !_pushInitiatorUrl.startsWith("https://")) {
    	errorMessage = "Error: The Push Initiator URL must start with http:// or https://.";
    } else if (_useSdk && !QUrl(_pushInitiatorUrl).isValid()) {
    	errorMessage = "Error: The Push Initiator URL is invalid.";
    } else if (_useSdk && _pushInitiatorUrl.endsWith("/")) {
    	errorMessage = "Error: The Push Initiator URL should not end with a /. One will be automatically added to the end.";
    } else {
        isValid = true;
    }
    if(!isValid)
    {
		Ti::TiEventParameters _params;
		_params.addParam("errorTitle", errorTitle);
		_params.addParam("errorMessage", errorMessage);
		fireCallback("onConfigError", _params);
    }
    return isValid;
}

void TiPushNotificationProxy::saveConfiguration()
{
    // First, load the previous configuration so we can determine whether or not to register to launch
    // or unregister from launch
    if (_configurationService->hasConfiguration()) {

        Configuration storedConfig = _configurationService->configuration();

        if (!storedConfig.launchApplicationOnPush() && _configuration->launchApplicationOnPush()) {
            _shouldRegisterToLaunch = true;
            _shouldUnregisterFromLaunch = false;
        } else if (storedConfig.launchApplicationOnPush() && !_configuration->launchApplicationOnPush()) {
            _shouldRegisterToLaunch = false;
            _shouldUnregisterFromLaunch = true;
        } else {
            _shouldRegisterToLaunch = true;
            _shouldUnregisterFromLaunch = false;
        }

    } else {
        _shouldRegisterToLaunch = _configuration->launchApplicationOnPush();

        // There is no configuration currently stored, so register to launch was never previously called
        // so we wouldn't need to call unregister
        _shouldUnregisterFromLaunch = false;
    }

    if (_usePublicPpg || _useSdk)
        _configuration->setProviderApplicationId(_appId);
    else
        _configuration->setProviderApplicationId(QString());

    if (_usePublicPpg)
        _configuration->setPpgUrl(_ppgUrl);
    else
        _configuration->setPpgUrl(QString());

    if (_useSdk)
        _configuration->setPushInitiatorUrl(_pushInitiatorUrl);
    else
        _configuration->setPushInitiatorUrl(QString());

    _configuration->setLaunchApplicationOnPush(_launchApplicationOnPush);
    _configuration->setUsingPublicPushProxyGateway(_usePublicPpg);

    _configurationService->save(*_configuration);
    _configSaveAction = true;
    _pushNotificationService->createSession();
}

TiPushNotificationEventHandler::TiPushNotificationEventHandler(TiPushNotificationProxy* proxy) :
		_proxy(proxy)
{

}
TiPushNotificationEventHandler::~TiPushNotificationEventHandler()
{

}

void TiPushNotificationEventHandler::onCreateSessionCompleted(const bb::network::PushStatus &status)
{
	_proxy->sessionCreated(status);

}
void TiPushNotificationEventHandler::onCreateChannelCompleted(const bb::network::PushStatus &status, const QString &token)
{
	_proxy->channelCreated(status, token);
}
void TiPushNotificationEventHandler::onInvoked(const bb::system::InvokeRequest &request)
{
	_proxy->pushReceived(request);
}
void TiPushNotificationEventHandler::onNoPushServiceConnection()
{
	Ti::TiEventParameters eventParams;
	eventParams.addParam("errorTitle", "No Push Service");
	eventParams.addParam("errorMessage", 	"Could not stablish connection with server. "
											"This can occur if the application doesn't have sufficient permissions to use push, "
											"there is no network connection, or you're running on the simulator"
						);
	_proxy->fireCallback("onError", eventParams);
}
void TiPushNotificationEventHandler::onFullScreen()
{
	_proxy->setFullScreen(true);
}


} /* namespace TiBlackberry */
