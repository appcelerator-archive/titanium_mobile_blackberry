/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "Ti_WindowProxy.h"

#include <bb/cascades/AbstractPane>
#include <bb/cascades/OrientationSupport>

namespace Ti {


TiWindowProxy::TiWindowProxy(const char* name)
	: Ti::TiViewProxy(name), _pane(NULL),  _isFocused(false)
{
	createPropertyFunction("open", _open);
	createPropertyFunction("close", _close);
	createPropertySetterGetter("orientationModes", _setOrientationModes, _getOrientationModes);
}


TiWindowProxy::~TiWindowProxy()
{
	if(_pane != NULL) delete _pane;
}

void TiWindowProxy::setPane(bb::cascades::AbstractPane* pane)
{
	_pane = pane;
}

bb::cascades::AbstractPane *TiWindowProxy::getPane()
{
	return _pane;
}

void TiWindowProxy::updateOrientation()
{
    bb::cascades::OrientationSupport* support = bb::cascades::OrientationSupport::instance();

    bool landscape = false;
    bool portrait = false;
    foreach(bb::cascades::SupportedDisplayOrientation::Type type, _orientationModes)
    {
    	if(type == bb::cascades::SupportedDisplayOrientation::DisplayLandscape)
    	{
    		landscape = true;
    	} else if(type == bb::cascades::SupportedDisplayOrientation::DisplayPortrait)
    	{
    		portrait = true;
    	}
    }

    if(landscape == true && portrait == true)
    {
    	support->setSupportedDisplayOrientation(bb::cascades::SupportedDisplayOrientation::All);
    }
    else if(landscape == true && portrait == false)
    {
    	support->setSupportedDisplayOrientation(bb::cascades::SupportedDisplayOrientation::DisplayLandscape);
    }
    else if(landscape == false && portrait == true)
    {
    	support->setSupportedDisplayOrientation(bb::cascades::SupportedDisplayOrientation::DisplayPortrait);
    }
    else
    {
    	support->setSupportedDisplayOrientation(support->supportedDisplayOrientation());
    }
}

bool TiWindowProxy::isFocused()
{
	return _isFocused;
}
void TiWindowProxy::fireEvent(QString name, Ti::TiEventParameters params)
{
	if(name == Ti::TiConstants::EventFocus)
	{
		if(_isFocused) return;
		_isFocused = true;
		updateOrientation();
	}
	if(name == Ti::TiConstants::EventBlur)
	{
		if(!_isFocused) return;
		_isFocused = false;
	}
	Ti::TiViewProxy::fireEvent(name, params);
}

TI_GETTER_DEFER(TiWindowProxy, getOrientationModes);
void TiWindowProxy::setOrientationModes(Ti::TiValue val)
{
	if(val.isNumber())
	{
		_orientationModes.append((bb::cascades::SupportedDisplayOrientation::Type)val.toNumber());
		return;
	}
	if(val.isList())
	{
		QList<Ti::TiValue> array = val.toList();
		foreach(Ti::TiValue v, array)
		{
			_orientationModes.append((bb::cascades::SupportedDisplayOrientation::Type)v.toNumber());
		}
	}
}

Ti::TiValue TiWindowProxy::open(Ti::TiValue value)
{
	Ti::TiSceneManager::Open(this);
	clearWeak();
	Ti::TiValue val;
	val.setUndefined();

	return val;
}

Ti::TiValue TiWindowProxy::close(Ti::TiValue value)
{
	Ti::TiSceneManager::Close(this);
	makeWeak();
	Ti::TiValue val;
	val.setUndefined();
	return val;
}


}
