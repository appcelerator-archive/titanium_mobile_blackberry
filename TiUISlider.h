/*
 * TiUISlider.h
 *
 *  Created on: 2012-04-17
 *      Author: dcampbell
 */

#ifndef TIUISLIDER_H_
#define TIUISLIDER_H_

#include "TiUIBase.h"

class TiUISlider : public TiUIBase
{
public:
    static TiUISlider* createSlider(NativeObjectFactory* nativeObjectFactory);
protected:
    virtual ~TiUISlider();
    virtual void initializeTiObject(TiObject* parentContext);
private:
    TiUISlider(NativeObjectFactory* nativeObjectFactory);
};

#endif /* TIUISLIDER_H_ */
