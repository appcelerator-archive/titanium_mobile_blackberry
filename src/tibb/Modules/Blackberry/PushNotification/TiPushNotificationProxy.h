/*
 * TiPushNotificationProxy.h
 *
 *  Created on: Dec 3, 2013
 *      Author: penrique
 */

#ifndef TIPUSHNOTIFICATIONPROXY_H_
#define TIPUSHNOTIFICATIONPROXY_H_

#include "TiCore.h"
#include "service/PushNotificationService.hpp"
#include "service/ConfigurationService.hpp"
#include <bb/system/InvokeManager>
#include <bb/system/InvokeRequest>
#include <bb/system/SystemCredentialsPrompt>

namespace TiBlackberry
{
class TiPushNotificationEventHandler;
class TiPushNotificationProxy : public Ti::TiProxy
{
public:
	CREATE_PROXY(TiPushNotificationProxy)
	TiPushNotificationProxy(const char*);
	virtual ~TiPushNotificationProxy();

	virtual void initEnd();

	bool validateConfiguration();
	// void initializePushSession();
	void loadConfiguration();
	void saveConfiguration();

	void sessionCreated(const bb::network::PushStatus &);
	void channelCreated(const bb::network::PushStatus &, const QString &);
	void pushRecieved(const bb::system::InvokeRequest &);

	void setAppId(Ti::TiValue);
	void setPpgUrl(Ti::TiValue);
	void setPushInitiatorUrl(Ti::TiValue);
	void setUsePublicPpg(Ti::TiValue);
	void setUseSDK(Ti::TiValue);
	void setLaunchApplicationOnPush(Ti::TiValue);
	void setUser(Ti::TiValue);

	Ti::TiValue getAppId();
	Ti::TiValue getPpgUrl();
	Ti::TiValue getPushInitiatorUrl();
	Ti::TiValue getUsePublicPpg();
	Ti::TiValue getUseSDK();
	Ti::TiValue getLaunchApplicationOnPush();
	Ti::TiValue getUser();

//	Ti::TiValue createChannel(Ti::TiValue);
	void createChannel();

	EXPOSE_SETTER(TiPushNotificationProxy, setAppId)
	EXPOSE_SETTER(TiPushNotificationProxy, setPpgUrl)
	EXPOSE_SETTER(TiPushNotificationProxy, setPushInitiatorUrl)
	EXPOSE_SETTER(TiPushNotificationProxy, setUsePublicPpg)
	EXPOSE_SETTER(TiPushNotificationProxy, setUseSDK)
	EXPOSE_SETTER(TiPushNotificationProxy, setLaunchApplicationOnPush)
	EXPOSE_SETTER(TiPushNotificationProxy, setUser)

	EXPOSE_GETTER(TiPushNotificationProxy, getAppId)
	EXPOSE_GETTER(TiPushNotificationProxy, getPpgUrl)
	EXPOSE_GETTER(TiPushNotificationProxy, getPushInitiatorUrl)
	EXPOSE_GETTER(TiPushNotificationProxy, getUsePublicPpg)
	EXPOSE_GETTER(TiPushNotificationProxy, getUseSDK)
	EXPOSE_GETTER(TiPushNotificationProxy, getLaunchApplicationOnPush)
	EXPOSE_GETTER(TiPushNotificationProxy, getUser)

private:
	bool _shouldRegisterToLaunch;
	bool _shouldUnregisterFromLaunch;
	bool _launchApplicationOnPush;
	bool _configSaveAction;
	TiPushNotificationEventHandler* _eventHandler;
    PushNotificationService* _pushNotificationService;
    ConfigurationService* _configurationService;
    Configuration* _configuration;
    User *_user;

    QString _appId;
    QString _ppgUrl;
    QString _pushInitiatorUrl;

    bool _usePublicPpg;
    bool _useSdk;
    // The manager object to react to invocations
    bb::system::InvokeManager *_invokeManager;

};


class TiPushNotificationEventHandler : public QObject
{
	Q_OBJECT
public:
	TiPushNotificationEventHandler(TiPushNotificationProxy*);
	virtual ~TiPushNotificationEventHandler();
private:
	TiPushNotificationProxy *_proxy;
public Q_SLOTS:
	void onCreateSessionCompleted(const bb::network::PushStatus &status);
	void onCreateChannelCompleted(const bb::network::PushStatus &status, const QString &token);
	void onDestroyChannelCompleted(const bb::network::PushStatus &status);
	void onRegisterToLaunchCompleted(const bb::network::PushStatus &status);
	void onUnregisterFromLaunchCompleted(const bb::network::PushStatus &status);
	void onRegisterPromptFinished(bb::system::SystemUiResult::Type value);
	void onUnregisterPromptFinished(bb::system::SystemUiResult::Type value);
	void onPIRegistrationCompleted(int code, const QString &description);
	void onPIDeregistrationCompleted(int code, const QString &description);
	void onInvoked(const bb::system::InvokeRequest &request);
	void onSimChanged();
	void onPushTransportReady(bb::network::PushCommand::Type command);
	void onNoPushServiceConnection();
	void onAllPushesRemoved();
};



} /* namespace TiBlackberry */
#endif /* TIPUSHNOTIFICATIONPROXY_H_ */
