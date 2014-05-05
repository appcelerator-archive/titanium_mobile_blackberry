/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_WINDOWPROXY_H_
#define TI_WINDOWPROXY_H_

#include <TiCore.h>
#include <bb/cascades/SupportedDisplayOrientation>

namespace bb{
namespace cascades{
class AbstractPane;
}
}
namespace Ti {
class TiWindowProxy: public Ti::TiViewProxy {
public:
	CREATE_PROXY(TiWindowProxy)
	TiWindowProxy(const char*);
	virtual ~TiWindowProxy();

	virtual Ti::TiValue open(Ti::TiValue);
	virtual Ti::TiValue close(Ti::TiValue);
	virtual void fireEvent(QString, Ti::TiEventParameters);

	EXPOSE_METHOD(TiWindowProxy, open)
	EXPOSE_METHOD(TiWindowProxy, close)

	TI_CREATE_SETTER_GETTER(TiWindowProxy, setOrientationModes, getOrientationModes)
	bool isFocused();
	bb::cascades::AbstractPane *getPane();
protected:
	virtual void setPane(bb::cascades::AbstractPane*);
private:
	bb::cascades::AbstractPane *_pane;
	QList<bb::cascades::SupportedDisplayOrientation::Type> _orientationModes;
	bool _isFocused;
	void updateOrientation();
};

}
#endif /* TIUIWINDOWPROXY_H_ */
