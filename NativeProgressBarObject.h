/*
 * NativeProgressBarObject.h
 *
 *  Created on: 2012-04-20
 *      Author: dcampbell
 */

#ifndef NATIVEPROGRESSBAROBJECT_H_
#define NATIVEPROGRESSBAROBJECT_H_

#include "NativeControlObject.h"
#include <bb/cascades/ProgressIndicator>

/*
 * NativeProgressBarObject
 *
 * UI: Progress bar control
 */

class NativeProgressBarObject : public NativeControlObject
{
public:
    NativeProgressBarObject();
    virtual ~NativeProgressBarObject();
    virtual int getObjectType() const;
    virtual int initialize(TiEventContainerFactory* containerFactory);
    virtual NAHANDLE getNativeHandle() const;

private:
    bb::cascades::ProgressIndicator* progressIndicator_;
};

#endif /* NATIVEPROGRESSBAROBJECT_H_ */
