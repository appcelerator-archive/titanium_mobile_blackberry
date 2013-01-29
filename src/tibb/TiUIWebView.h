/*
 * TiUIWebView.h
 *
 *  Created on: Jan 25, 2013
 *      Author: penrique
 */

#ifndef TIUIWEBVIEW_H_
#define TIUIWEBVIEW_H_

#include "TiUIBase.h"

/*
 * TiUIWebView
 *
 * Represents a Titanium WebView object
 *
 */

class TiUIWebView: public TiUIBase
{
public:
    static TiUIWebView* createWebView(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUIWebView();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onCreateStaticMembers();

private:
	TiUIWebView();
	TiUIWebView(const char* name);
	static Handle<Value> _evalJS(void* userContext, TiObject* caller, const Arguments& args);
};

#endif /* TIUIWEBVIEW_H_ */
