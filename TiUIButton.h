/*
 * TiUIButton.h
 *
 *  Created on: 2012-04-17
 *      Author: dcampbell
 */

#ifndef TIUIBUTTON_H_
#define TIUIBUTTON_H_

#include "TiUIBase.h"

class TiUIButton : public TiUIBase
{
public:
    static TiUIButton* createButton(NativeObjectFactory* nativeObjectFactory);
protected:
    virtual ~TiUIButton();
    virtual void initializeTiObject(TiObject* parentContext);
private:
    TiUIButton(NativeObjectFactory* nativeObjectFactory);
};

#endif /* TIUIBUTTON_H_ */
