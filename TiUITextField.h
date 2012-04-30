/*
 * TiUITextField.h
 *
 *  Created on: 2012-04-26
 *      Author: hmovsisyan
 */

#ifndef TIUITEXTFIELD_H_
#define TIUITEXTFIELD_H_

#include "TiUIBase.h"

/*
 * TiUITextField
 *
 * Represents a Titanium TextField object
 *
 * This object can be created by:
 * Titanium.UI.createTextField({...});
 */
class TiUITextField : public TiUIBase
{
public:
    static TiUITextField* createTextField(NativeObjectFactory* nativeObjectFactory);

protected:
    virtual ~TiUITextField();
    virtual void initializeTiObject(TiObject* parentContext);

private:
    TiUITextField(NativeObjectFactory* nativeObjectFactory);
};

#endif /* TIUITEXTFIELD_H_ */
