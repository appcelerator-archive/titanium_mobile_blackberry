/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIScrollView.h"
#include "TiGenericFunctionObject.h"
#include "NativeScrollViewObject.h"
#include "NativeException.h"
#include "TiMessageStrings.h"
#include "V8Utils.h"

using namespace titanium;

TiUIScrollView::TiUIScrollView()
    : TiUIBase("ScrollView")
{
}

TiUIScrollView::~TiUIScrollView()
{
}

TiUIScrollView* TiUIScrollView::createScrollView(NativeObjectFactory* nativeObjectFactory)
{
    TiUIScrollView* obj = new TiUIScrollView;
    obj->setNativeObjectFactory(nativeObjectFactory);
    obj->initializeTiObject(NULL);
    return obj;
}

void TiUIScrollView::initializeTiObject(TiObject* parentContext)
{
    if (!isInitialized())
    {
        TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(N_TYPE_SCROLL_VIEW, this);
        setNativeObject(obj);
        obj->release();
    }
}

void TiUIScrollView::onCreateStaticMembers()
{
    TiUIBase::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setContentOffset", this, _setContentOffset);
}

Handle<Value> TiUIScrollView::_setContentOffset(void* userContext, TiObject* /*caller*/, const Arguments& args)
{
    if (args.Length() < 2) {
        return ThrowException(String::New(Ti::Msg::Missing_argument));
    }
    HandleScope handleScope;
    TiUIScrollView* obj = (TiUIScrollView*) userContext;
    NativeScrollViewObject* nScrollView = (NativeScrollViewObject*) obj->getNativeObject();
    try
    {

    	Ti::TiValue position = Ti::TiValue(args[0]);

    	if(position.isMap()){

    		QMap<QString, Ti::TiValue> positionMap = position.toMap();
    		Ti::TiValue xPos = positionMap.value(QString("x"));
    		Ti::TiValue yPos = positionMap.value(QString("y"));
    		float x = xPos.toNumber();
    		float y = yPos.toNumber();
    		bool isAnimated = true;

    		if(!args[1].IsEmpty()){

    			Ti::TiValue animated = Ti::TiValue(args[1]);

    			if(animated.isMap()){

    				QMap<QString, Ti::TiValue> animatedMap = animated.toMap();
        			Ti::TiValue animatedValue = animatedMap.value(QString("animated"));

        			//if(animatedValue.isString()){

        			//}else{
        				isAnimated = animatedValue.toBool();
        			//}

        		}
    		}

    		nScrollView->scrollTo(x,y,isAnimated);

    	}

    }
    catch (NativeException& ne)
    {
        return ThrowException(String::New(ne.what()));
    }
    return Undefined();
}


