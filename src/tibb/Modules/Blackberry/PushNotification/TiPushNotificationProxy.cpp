/*
 * TiPushNotificationProxy.cpp
 *
 *  Created on: Dec 3, 2013
 *      Author: penrique
 */

#include "TiPushNotificationProxy.h"
#include <bb/network/PushErrorCode>
#include <bb/platform/Notification>

#define BB_OPEN_INVOCATION_ACTION "bb.action.OPEN"
#define NOTIFICATION_PREFIX "com.example.pushCollector_"

namespace TiBlackberry {

TiPushNotificationProxy::TiPushNotificationProxy(const char* name) :
		Ti::TiProxy(name),
		_shouldRegisterToLaunch(false),
		_shouldUnregisterFromLaunch(false),
		_launchApplicationOnPush(false),
		_configSaveAction(false),
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
//	createPropertyFunction("createChannel", _createChannel);

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
    QObject::connect(_pushNotificationService, SIGNAL(destroyChannelCompleted(const bb::network::PushStatus&)),
            _eventHandler, SLOT(onDestroyChannelCompleted(const bb::network::PushStatus&)));
    QObject::connect(_pushNotificationService, SIGNAL(registerToLaunchCompleted(const bb::network::PushStatus&)),
            _eventHandler, SLOT(onRegisterToLaunchCompleted(const bb::network::PushStatus&)));
    QObject::connect(_pushNotificationService, SIGNAL(unregisterFromLaunchCompleted(const bb::network::PushStatus&)),
            _eventHandler, SLOT(onUnregisterFromLaunchCompleted(const bb::network::PushStatus&)));
    QObject::connect(_pushNotificationService, SIGNAL(piRegistrationCompleted(int, const QString)),
            _eventHandler, SLOT(onPIRegistrationCompleted(int, const QString)));
    QObject::connect(_pushNotificationService, SIGNAL(piDeregistrationCompleted(int, const QString)),
            _eventHandler, SLOT(onPIDeregistrationCompleted(int, const QString)));
    QObject::connect(_pushNotificationService, SIGNAL(simChanged()),
            _eventHandler, SLOT(onSimChanged()));
    QObject::connect(_pushNotificationService, SIGNAL(pushTransportReady(bb::network::PushCommand::Type)),
                _eventHandler, SLOT(onPushTransportReady(bb::network::PushCommand::Type)));
    QObject::connect(_pushNotificationService, SIGNAL(noPushServiceConnection()),
            _eventHandler, SLOT(onNoPushServiceConnection()));
    QObject::connect(_pushNotificationService, SIGNAL(allPushesRemoved()),
            _eventHandler, SLOT(onAllPushesRemoved()));
    QObject::connect(_invokeManager, SIGNAL(invoked(const bb::system::InvokeRequest&)),
    		_eventHandler, SLOT(onInvoked(const bb::system::InvokeRequest&)));

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
	qDebug() << "initEnd";
	if(!validateConfiguration())
	{
		qDebug() << "!validateConfiguration";
		return;
	}
	saveConfiguration();
}

void TiPushNotificationProxy::setAppId(Ti::TiValue value)
{
	_appId = value.toString();
	qDebug() << "setAppId" << _appId;
}
void TiPushNotificationProxy::setPpgUrl(Ti::TiValue value)
{
	_ppgUrl = value.toString();
	qDebug() << "_ppgUrl" << _ppgUrl;
}
void TiPushNotificationProxy::setPushInitiatorUrl(Ti::TiValue value)
{
	_pushInitiatorUrl = value.toString();
	qDebug() << "setPushInitiatorUrl" << _pushInitiatorUrl;
}
void TiPushNotificationProxy::setUsePublicPpg(Ti::TiValue value)
{
	_usePublicPpg = value.toBool();
	qDebug() << "setUsePublicPpg" << _usePublicPpg;
}
void TiPushNotificationProxy::setUseSDK(Ti::TiValue value)
{
	_useSdk = value.toBool();
	qDebug() << "setUseSDK" << _useSdk;
}
void TiPushNotificationProxy::setLaunchApplicationOnPush(Ti::TiValue value)
{
	_launchApplicationOnPush = value.toBool();
	qDebug() << "setLaunchApplicationOnPush" << _launchApplicationOnPush;
}
void TiPushNotificationProxy::setUser(Ti::TiValue value)
{
	QMap<QString, Ti::TiValue> _object = value.toMap();

	Ti::TiValue userId = _object["id"];
	Ti::TiValue userPassword = _object["password"];
	_user->setPassword(userPassword.toString());
	_user->setUserId(userId.toString());

	qDebug() << "setUser id" << _user->userId() << "password" << _user->password();

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
        	errorMessage = "Configuration was saved, but was unable to create push session. (Error code: " + QString::number(status.code())+ ")";
        } else {
        	errorTitle = "Push Collector";
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
    qDebug()<< "creatChannelComplete status: " << status.code();
    qDebug()<< "createChannelComplete token: " << token;

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
            qDebug()<< "_pushNotificationService->subscribeToPushInitiator(_user, token);";

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

void TiPushNotificationProxy::pushRecieved(const bb::system::InvokeRequest &request)
{
    qDebug() << "pushRecieved";
	/*
	 * 	Ti::TiEventParameters _params;
	_params.addParam("target", request.target());
	_params.addParam("action", request.action());
	_params.addParam("mimeType", request.mimeType());
	_params.addParam("uri", request.uri().toString());
	_params.addParam("data", QString(request.data()));
	_proxy->fireCallback("callback", _params);
	 *
	 */
    if (_configurationService->hasConfiguration()) {
        // The underlying PushService instance might not have been
        // initialized when an invoke first comes in
        // Make sure that we initialize it here if it hasn't been already
        // It requires an application ID (for consumer applications) so we have to check
        // that configuration settings have already been stored
        _pushNotificationService->initializePushService();

        if (request.action().compare(BB_PUSH_INVOCATION_ACTION) == 0) {
            qDebug() << "Received push action";
            // Received an incoming push
            // Extract it from the invoke request and then process it
            bb::network::PushPayload payload(request);
            if (payload.isValid()) {
            	/*
                pushNotificationHandler(payload);
                */
           	 	Ti::TiEventParameters _params;
 //				_params.addParam("headers", payload.headers());
				_params.addParam("id", payload.id());
				_params.addParam("data", QString(payload.data()));
				fireCallback("onPushRecieved", _params);

			    Push push(payload);

				bb::platform::Notification *notification = new bb::platform::Notification(NOTIFICATION_PREFIX + QString::number(push.seqNum()), _eventHandler);
			    notification->setTitle("Push Collector");
			    notification->setBody(QString("New %0 push received").arg(push.fileExtension()));

			    // Add an invoke request to the notification
			    // This invoke will contain the seqnum of the push.
			    // When the notification in the BlackBerry Hub is selected, this seqnum will be used to lookup the push in
			    // the database and display it
			    bb::system::InvokeRequest invokeRequest;
			    invokeRequest.setTarget(INVOKE_TARGET_KEY_OPEN);
			    invokeRequest.setAction(BB_OPEN_INVOCATION_ACTION);
			    invokeRequest.setMimeType("text/plain");
			    invokeRequest.setData(QByteArray::number(push.seqNum()));
			    notification->setInvokeRequest(invokeRequest);

			    // Add the notification for the push to the BlackBerry Hub
			    // Calling this method will add a "splat" to the application icon, indicating that a new push has been received
			    notification->notify();
            }
            else
            {
            	qDebug() << "something failed";
            }
        } else if (request.action().compare(BB_OPEN_INVOCATION_ACTION) == 0){
            qDebug() << "Received open action";
            // Received an invoke request to open an existing push (ie. from a notification in the BlackBerry Hub)
            // The payload from the open invoke is the seqnum for the push in the database
            // openPush(request.data().toInt());
        }
        else
        {
        	qDebug() << "What?" << request.action();
        }

    }
}

//Ti::TiValue TiPushNotificationProxy::createChannel(Ti::TiValue)
void TiPushNotificationProxy::createChannel()
{
	//	TODO: Remove this next line:
	//	initializePushSession();

    if (!_configurationService->hasConfiguration())
    {
		qDebug() << "!_configurationService->hasConfiguration";
		Ti::TiEventParameters _params;
		_params.addParam("errorTitle", "Push Collector");
		_params.addParam("errorMessage", "Please fill in the config before attempting to register.");
		fireCallback("configError", _params);
		return;
    }

    // The Push Service SDK will be used on the server-side so prompt for a username and password
    if(!_configuration->pushInitiatorUrl().isEmpty()) {
		qDebug() << "!_configuration->pushInitiatorUrl().isEmpty";
    	if(!_user->password().isEmpty() && !_user->userId().isEmpty())
    	{
    		qDebug() << "_user->password().length() > 0 && _user->userId().isEmpty()";
            _pushNotificationService->createChannel();
            return;
    	}
    	else
    	{
    		Ti::TiEventParameters _params;
    		_params.addParam("errorTitle", "Need User");
    		_params.addParam("errorMessage", "Please add user by calling .setUser({ id: __, password: __ }).");
    		fireCallback("configError", _params);
    		return;
    	}
    }
	qDebug() << "_pushNotificationService->createChannel";
    _pushNotificationService->createChannel();
}

void TiPushNotificationProxy::loadConfiguration()
{
	qDebug() << "TiPushNotificationProxy::loadConfiguration";

    *_configuration = _configurationService->configuration();
    _appId = _configuration->providerApplicationId();
    _ppgUrl = _configuration->ppgUrl();
    _pushInitiatorUrl = _configuration->pushInitiatorUrl();
    _useSdk = !_pushInitiatorUrl.isEmpty();
    _launchApplicationOnPush = _configuration->launchApplicationOnPush();
    _usePublicPpg = _configuration->usingPublicPushProxyGateway();
}

bool TiPushNotificationProxy::validateConfiguration()
{
	qDebug() << "TiPushNotificationProxy::validateConfiguration";
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
    	qDebug() << "!isValid";
		Ti::TiEventParameters _params;
		_params.addParam("errorTitle", errorTitle);
		_params.addParam("errorMessage", errorMessage);
		fireCallback("configError", _params);
    }
    return isValid;
}

void TiPushNotificationProxy::saveConfiguration()
{
	qDebug() << "TiPushNotificationProxy::saveConfiguration";
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
            _shouldRegisterToLaunch = false;
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

/*
// TODO: remove dead code:
void TiPushNotificationProxy::initializePushSession()
{
	qDebug() << "TiPushNotificationProxy::initializePushSession";
    // If the app already has config info saved then create the session
    if (_configurationService->hasConfiguration()) {
        _shouldRegisterToLaunch = _configuration->launchApplicationOnPush();
        _shouldUnregisterFromLaunch = !_configuration->launchApplicationOnPush();
        _pushNotificationService->createSession();

    } else {

        Sheet* configSheet = Application::instance()->findChild<Sheet*>("configurationSheet");
        if (configSheet) {
            configSheet->open();

            _hasBeenInForeground = true;
        }

        showDialog(tr("Push Collector"), tr("No configuration settings were found. Please fill them in."));
    }
}
*/

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
	qDebug() << "onCreateSessionCompleted";

}
void TiPushNotificationEventHandler::onCreateChannelCompleted(const bb::network::PushStatus &status, const QString &token)
{
	qDebug() << "onCreateChannelCompleted";
	_proxy->channelCreated(status, token);

}
void TiPushNotificationEventHandler::onDestroyChannelCompleted(const bb::network::PushStatus &status)
{
	qDebug() << "onDestroyChannelCompleted";

}
void TiPushNotificationEventHandler::onRegisterToLaunchCompleted(const bb::network::PushStatus &status)
{
	qDebug() << "onRegisterToLaunchCompleted";
}
void TiPushNotificationEventHandler::onUnregisterFromLaunchCompleted(const bb::network::PushStatus &status)
{
	qDebug() << "onUnregisterFromLaunchCompleted";

}
void TiPushNotificationEventHandler::onRegisterPromptFinished(bb::system::SystemUiResult::Type value)
{
	qDebug() << "onRegisterPromptFinished";

}
void TiPushNotificationEventHandler::onUnregisterPromptFinished(bb::system::SystemUiResult::Type value)
{
	qDebug() << "onUnregisterPromptFinished";
}
void TiPushNotificationEventHandler::onPIRegistrationCompleted(int code, const QString &description)
{
	qDebug() << "onPIRegistrationCompleted";

}
void TiPushNotificationEventHandler::onPIDeregistrationCompleted(int code, const QString &description)
{
	qDebug() << "onPIDeregistrationCompleted";
}
void TiPushNotificationEventHandler::onInvoked(const bb::system::InvokeRequest &request)
{
	qDebug() << "onInvoked";
	_proxy->pushRecieved(request);
}
void TiPushNotificationEventHandler::onSimChanged()
{
	qDebug() << "onSimChanged";
}
void TiPushNotificationEventHandler::onPushTransportReady(bb::network::PushCommand::Type command)
{
	qDebug() << "onPushTransportReady";
}
void TiPushNotificationEventHandler::onNoPushServiceConnection()
{
	qDebug() << "onNoPushServiceConnection";
	Ti::TiEventParameters eventParams;
	eventParams.addParam("errorTitle", "No Push Service");
	eventParams.addParam("errorMessage", 	"Could not stablish connection with server. "
											"This can occur if the application doesn't have sufficient permissions to use Push, "
											"There is no network connection, or you're running on the simulator"
						);
	_proxy->fireCallback("onError", eventParams);
}
void TiPushNotificationEventHandler::onAllPushesRemoved()
{
	qDebug() << "onAllPushesRemoved";
}


} /* namespace TiBlackberry */
