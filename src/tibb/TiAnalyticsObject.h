/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIANALYTICSOBJECT_H_
#define TIANALYTICSOBJECT_H_

#include "TiProxy.h"
#include <QtCore/QObject>
#include <QNetworkReply>
#include <QTimer>
#include <string>
#include <sqlite3.h>

using namespace std;

class TiAnalyticsHandler;

/*
 * TiAnalyticsObject
 *
 * Object that represents name space: Titanium.Analytics
 */

class TiAnalyticsObject : public TiProxy
{
public:
	static void addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory);
	bool createAnalyticsDatabase();
	void addAnalyticsEvent(std::string const& name, std::string const& data = "");
	void sendPendingAnalyticsEvents();
	sqlite3* db_;

protected:
    virtual ~TiAnalyticsObject();
    virtual void onCreateStaticMembers();

private:
    TiAnalyticsObject();
    explicit TiAnalyticsObject(NativeObjectFactory* objectFactory);
    TiAnalyticsObject(const TiAnalyticsObject&);
    TiAnalyticsObject& operator=(const TiAnalyticsObject&);

    static Handle<Value> _featureEvent(void* userContext, TiObject*, const Arguments& args);

    NativeObjectFactory* objectFactory_;
    QTimer* timer_;
    QNetworkRequest request_;
    QNetworkReply* reply_;
    QNetworkAccessManager networkAccessManager_;
    TiAnalyticsHandler* eventHandler_;
	long sequence_;
	QByteArray mid_;
	QByteArray sid_;
	QByteArray aguid_;
	QByteArray deployType_;
	QByteArray appVersion_;
};

//Event handler for TiAnalytics object
class TiAnalyticsHandler : public QObject
{
    Q_OBJECT

public:
    explicit TiAnalyticsHandler(TiAnalyticsObject* tiAnalyticsObject);
    virtual ~TiAnalyticsHandler();

public slots:
    void finished(QNetworkReply* reply);
    void errors(QNetworkReply* reply);
    void sendPendingRequests();
    void thumbnail();
    void fullscreen();
    void manualExit();

private:
    TiAnalyticsObject* tiAnalyticsObject_;
    // Disable copy ctor & assignment operator
    TiAnalyticsHandler(const TiAnalyticsHandler& eHandler);
    TiAnalyticsHandler& operator=(const TiAnalyticsHandler& eHandler);
};

#endif /* TIANALYTICSOBJECT_H_ */
