/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiAnalyticsObject.h"
#include "NativeMapViewObject.h"
#include <QSettings>
#include <bb/cascades/Application>
#include <bb/device/HardwareInfo>
#include "TiGenericFunctionObject.h"
#include <QUuid>
#include <bps/bps.h>
#include <bps/netstatus.h>


/**
 A BlackBerry analytics event payload has the follow values
     seq - increment counter for each even sent during the app life cycle
	 ver - used by server must be > 2
	 id - a uuid that is unique to each event
	 sid - a unique value that identifies the entire life-cycle of the app
	 mid - mobile device id, every BlackBerry device has a unique id
	 aguid - the id of the application, generated when the application is first created
	 event - the name of the event, ti.enroll (app first runs), ti.start, ti.end, ti.foreground, ti.background, featureEvent
	 type - the name of the event, ti.enroll (app first runs), ti.start, ti.end, ti.foreground, ti.background, featureEvent
	 ts - UTC time stamp of event
	 platform - always blackberry
	 deploytype - development or production
	 app_version - the version of the application as it appears in the tiapp.xml file
	 feature_data - when users call Ti.Analytics.featureEvent(name, data) feature_data holds the json data
*/

// Application properties defined at compile in tiapp.xml
// can be read using this settings instance. It is read only.
static QSettings defaultSettings("app/native/assets/app_properties.ini",
                                 QSettings::IniFormat);

// Singleton
TiAnalyticsObject::TiAnalyticsObject()
    : TiProxy("Analytics"), appStart(true), sequence_(1)
{
    objectFactory_ = NULL;
}

// Singleton
TiAnalyticsObject::TiAnalyticsObject(NativeObjectFactory* objectFactory)
    : TiProxy("Analytics"), appStart(true), sequence_(1)
{
    objectFactory_ = objectFactory;

    // if analytics is false just return
    bool analytics = defaultSettings.value("analytics").toBool();
    if (analytics == true) {
		// get unique application id
		QString aguid = defaultSettings.value("aguid").toString();
		aguid_ = aguid.toLocal8Bit();

		// get unique mobile device id
		bb::device::HardwareInfo hdi;
		QString mid = hdi.pin();
		mid_ = mid.toLocal8Bit();

		// generate the session id
		QString sid = QUuid::createUuid().toString();
		sid.replace("{", "");
		sid.replace("}", "");
		sid_ = sid.toLocal8Bit();

		// get deploy type if development or production
		QString deployType = defaultSettings.value("deploytype").toString();
		deployType_ = deployType.toLocal8Bit();

		// application version
		QString appVersion = defaultSettings.value("version").toString();
		appVersion_ = appVersion.toLocal8Bit();

		QUrl analyticsSite("https://api.appcelerator.net/p/v3/mobile-track/" + aguid);
		request_.setUrl(analyticsSite);

		// hook the manualExit Cascades app  callback
		bb::cascades::Application::instance()->setAutoExit(false);

		// async callbacks to notify application of HTTP events
		eventHandler_ = new TiAnalyticsHandler(this, "");
		QObject::connect(&networkAccessManager_, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), eventHandler_, SLOT(errors(QNetworkReply*)));

		// Hook application life cycle events
		QObject::connect(bb::cascades::Application::instance(), SIGNAL(thumbnail()), eventHandler_, SLOT(thumbnail()));
		QObject::connect(bb::cascades::Application::instance(), SIGNAL(fullscreen()), eventHandler_, SLOT(fullscreen()));
		QObject::connect(bb::cascades::Application::instance(), SIGNAL(manualExit()), eventHandler_, SLOT(manualExit()));

		if (createAnalyticsDatabase()) {
			addAnalyticsEvent("ti.enroll");
		}

		// set up timer and every 30 seconds send out analytics events if any are pending
		// usually because of unavailable network access
		TiAnalyticsHandler* eventHandler = new TiAnalyticsHandler(this, "");
		timer_ = new QTimer(eventHandler);
		QObject::connect(timer_, SIGNAL(timeout()), eventHandler,  SLOT(sendPendingRequests()));
		timer_->start(30000);
    }
}

TiAnalyticsObject::~TiAnalyticsObject()
{
}

void TiAnalyticsObject::addObjectToParent(TiObject* parent, NativeObjectFactory* objectFactory)
{
    TiAnalyticsObject* obj = new TiAnalyticsObject(objectFactory);
    parent->addMember(obj);
    obj->release();
}

void TiAnalyticsObject::onCreateStaticMembers()
{
    TiProxy::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "featureEvent", this, _featureEvent);
}

bool TiAnalyticsObject::createAnalyticsDatabase()
{
	sqlite3_stmt* stmt;
	int rc;
	bool dbCreate = false;

	rc = sqlite3_open_v2("data/analytics.db", &db, SQLITE_OPEN_READWRITE, NULL);
	if(rc){
		//TiLogger::getInstance().log(sqlite3_errmsg(db));
		sqlite3_close(db);

		// TODO check errmsg and make sure that it's caused by no db, create if that is the error
		dbCreate = true;
		rc = sqlite3_open_v2("data/analytics.db", &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
		if(rc){
			TiLogger::getInstance().log(sqlite3_errmsg(db));
			sqlite3_close(db);
			return(false);
		}

		// create the events table
		string cmd = "CREATE TABLE IF NOT EXISTS events (uid TEXT, event TEXT)";
		rc = sqlite3_prepare_v2(db, cmd.c_str(), strlen(cmd.c_str()) + 1, &stmt, NULL);
		if( rc ) {
			TiLogger::getInstance().log(sqlite3_errmsg(db));
			sqlite3_close(db);
			return(false);
		}

		if (sqlite3_step(stmt) != SQLITE_DONE) {
			TiLogger::getInstance().log("\nCould not step (execute) stmt.\n");
			return (false);
		}

		sqlite3_reset(stmt);
	}

	return dbCreate ;
}

void TiAnalyticsObject::addAnalyticsEvent(std::string const& name, std::string const& data, std::string const& typeArg)
{
	sqlite3_stmt* stmt;
	int rc;
	string type;

	string cmd = "INSERT INTO events VALUES (?, ?)";
	rc = sqlite3_prepare_v2(db, cmd.c_str(), strlen(cmd.c_str()) + 1, &stmt, NULL);
	if( rc ) {
		TiLogger::getInstance().log(sqlite3_errmsg(db));
		sqlite3_close(db);
	}

	// generate the event time stamp
	QDateTime utc = QDateTime::currentDateTimeUtc();
	QString displayDate = utc.toString("yyyy-MM-ddTHH:mm:ss.zzz+0000");
	QByteArray ts = displayDate.toLocal8Bit();

	// generate the uid
	QString uid = QUuid::createUuid().toString();
	uid.replace("{", "");
	uid.replace("}", "");
	QByteArray id = uid.toLocal8Bit();

	if (name.find("app.feature") == std::string::npos) {
		type = name;
	} else {
		type = typeArg;
	}

	// TODO guard against 1024 overrun
	char json[1024];
	sprintf(json, "[{\"seq\":%d,\"ver\":\"2\",\"id\":\"%s\",\"sid\":\"%s\",\"mid\":\"%s\",\"aguid\":\"%s\",\"type\":\"%s\",\"event\":\"%s\",\"ts\":\"%s\",\"data\":{\"platform\":\"blackberry\",\"deploytype\":\"%s\",\"app_version\":\"%s\",\"feature_data\":\"%s\"}}]",
				sequence_, id.data(), sid_.data(), mid_.data(), aguid_.data(), name.c_str(), type.c_str(), ts.data(),
				deployType_.data(), appVersion_.data(), data.c_str());

	sqlite3_bind_text(stmt, 1, id.data(), strlen(id.data()), 0);
	sqlite3_bind_text(stmt, 2, json, strlen(json), 0);

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		TiLogger::getInstance().log("\nCould not step (execute) stmt.\n");
	}

	sequence_++;

	sqlite3_reset(stmt);
	sqlite3_clear_bindings(stmt);

	if (name == "ti.end" ) {
		bb::cascades::Application::instance()->exit(0);
	}
	else {
		sendPendingAnalyticsEvents();
	}
}

void TiAnalyticsObject::sendPendingAnalyticsEvents()
{
	sqlite3_stmt* stmt;
	int rc;

	string cmd = "SELECT * FROM events";
	rc = sqlite3_prepare_v2(db, cmd.c_str(), strlen(cmd.c_str()) + 1, &stmt, NULL);
	if( rc ) {
		TiLogger::getInstance().log(sqlite3_errmsg(db));
		sqlite3_close(db);
	}

	while (true) {
		int s;

		s = sqlite3_step (stmt);
		if (s == SQLITE_ROW) {
			const unsigned char* uid;
			const unsigned char* json;
			uid = sqlite3_column_text (stmt, 0);
			json = sqlite3_column_text (stmt, 1);

			bool is_available = true;
			netstatus_get_availability(&is_available);

			if (is_available) {
				// do not send an http post if a reply is pending
				std::string id = std::string((const char*)uid, strlen((const char*)uid));
				if (pendingHttpReplies.find(id) == pendingHttpReplies.end())
				{
					TiAnalyticsHandler* requestHandler = new TiAnalyticsHandler(this, (const char*)uid);
					pendingHttpReplies[id] = requestHandler;

					bool log = defaultSettings.value("analytics-log").toBool();
					if (log) {
						TiLogger::getInstance().log("Sending Analytic Event: ");
						TiLogger::getInstance().log((const char*)json);
					}


					// send HTTP POST Asynchronously
					QByteArray postDataSize = QByteArray::number(strlen((const char*)json));
					request_.setRawHeader("Content-Length", postDataSize);
					QNetworkReply* reply = networkAccessManager_.post(request_, (const char*)json);
					QObject::connect(reply, SIGNAL(finished()), requestHandler, SLOT(finished()));
				}
			}
		}
		else if (s == SQLITE_DONE) {
			break;
		}
		else {
			break;
		}
	}

	sqlite3_reset(stmt);
	sqlite3_clear_bindings(stmt);
}

Handle<Value> TiAnalyticsObject::_featureEvent(void* userContext, TiObject*, const Arguments& args)
{
	TiAnalyticsObject* obj = (TiAnalyticsObject*) userContext;
	string type = TiObject::getSTDStringFromValue(args[0]);
	string data = TiObject::getSTDStringFromValue(args[1]);

	obj->addAnalyticsEvent("app.feature", data, type);

	return Undefined();
}

TiAnalyticsHandler::TiAnalyticsHandler(TiAnalyticsObject* tiAnalyticsObject, string  uid)
{
    tiAnalyticsObject_ = tiAnalyticsObject;
    uid_ = uid;
}

TiAnalyticsHandler::~TiAnalyticsHandler()
{
}

void TiAnalyticsHandler::finished()
{
	sqlite3_stmt* stmt;
	int rc;

	string cmd = "DELETE FROM events WHERE uid=?";
	rc = sqlite3_prepare_v2(tiAnalyticsObject_->db, cmd.c_str(), strlen(cmd.c_str()) + 1, &stmt, NULL);
	if( rc ) {
		TiLogger::getInstance().log(sqlite3_errmsg(tiAnalyticsObject_->db));
		sqlite3_close(tiAnalyticsObject_->db);
	}

	sqlite3_bind_text(stmt, 1, uid_.c_str(), strlen(uid_.c_str()), 0);

	int stepResult = sqlite3_step(stmt);

	if (stepResult == SQLITE_DONE) {
		bool log = defaultSettings.value("analytics-log").toBool();
		if (log) {
			TiLogger::getInstance().log("Clearing Analytic Event from DB for ID: ");
			TiLogger::getInstance().log(uid_.c_str());
		}
	}

    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);

    // remove the pending http reply
    tiAnalyticsObject_->pendingHttpReplies.erase(uid_);
    this->deleteLater();

}

void TiAnalyticsHandler::errors(QNetworkReply* reply)
{
	TiLogger::getInstance().log("\nHTTP error while sending analytic event.\n");
	this->deleteLater();
}

void TiAnalyticsHandler::sendPendingRequests()
{
	tiAnalyticsObject_->sendPendingAnalyticsEvents();
}

void TiAnalyticsHandler::thumbnail()
{
	tiAnalyticsObject_->addAnalyticsEvent("ti.background");
}

void TiAnalyticsHandler::fullscreen()
{
	if (tiAnalyticsObject_->appStart == true) {
		tiAnalyticsObject_->addAnalyticsEvent("ti.start");
		tiAnalyticsObject_->appStart = false;
	} else {
		tiAnalyticsObject_->addAnalyticsEvent("ti.foreground");
	}
}

void TiAnalyticsHandler::manualExit()
{
	tiAnalyticsObject_->addAnalyticsEvent("ti.end");
}
