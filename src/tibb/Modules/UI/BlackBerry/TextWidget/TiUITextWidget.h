/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUITEXTWIDGETS_H_
#define TI_TIUITEXTWIDGETS_H_

#include "TiCore.h"
#include <bb/cascades/AbstractTextControl>

namespace TiUI {

class TiUITextWidget : public Ti::TiView
{
	Q_OBJECT;
public:
	TiUITextWidget(Ti::TiViewProxy*);
	virtual ~TiUITextWidget();
	virtual void setTextControl(bb::cascades::AbstractTextControl*);
	virtual bb::cascades::AbstractTextControl* getTextControl();
private:
	bb::cascades::AbstractTextControl* _textControl;

public slots:
	virtual void onChanging(const QString);
	virtual void onChange(QString);
	virtual void onFocusChange(bool);
	virtual void onSubmitted(bb::cascades::AbstractTextControl *);
};

} /* namespace TiUI */
#endif /* TIUITEXTWIDGETS_H_ */
