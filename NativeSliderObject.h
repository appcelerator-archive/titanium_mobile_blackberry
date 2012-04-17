/*
 * NativeSliderObject.h
 *
 *  Created on: 2012-04-17
 *      Author: dcampbell
 */

#ifndef NATIVESLIDEROBJECT_H_
#define NATIVESLIDEROBJECT_H_

#include "NativeControlObject.h"
#include <bb/cascades/Slider>

class NativeSliderObject : public NativeControlObject
{
public:
    NativeSliderObject();
    virtual ~NativeSliderObject();
    virtual int getObjectType() const;
    virtual int initialize();
    virtual NAHANDLE getNativeHandle() const;
    virtual int setMax(float max);
    virtual int setMin(float min);
    virtual int setValue(float value);
private:
    bb::cascades::Slider* slider_;
};

#endif /* NATIVESLIDEROBJECT_H_ */
