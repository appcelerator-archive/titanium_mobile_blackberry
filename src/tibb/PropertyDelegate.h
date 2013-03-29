/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_PROPERTY_DELEGATE_H_
#define TI_PROPERTY_DELEGATE_H_

#include <vector>

class TiObject;

namespace titanium {

// A delegate that provides access for setting and getting property values.
// Usually a NativeObject implements this interface to provide property
// logic for accessing native platform APIs. The TiObject will delegate
// to the attached NativeObject whenever the property is accessed
// from JavaScript.
class PropertyDelegate {
public:
    virtual int getProperty(int propertyId, TiObject* value) = 0;
    virtual int setProperty(int propertyId, TiObject* value) = 0;
};

// A base implemention which is usually extended from when implementing
// a property delegate that uses C++ getter and setter methods.
template <class T>
class PropertyDelegateBase : public PropertyDelegate {
public:
    typedef int(T::*PropertyCallback)(TiObject* value);

    struct PropertyInfo {
        int propertyId;
        PropertyCallback getter;
        PropertyCallback setter;
    };

    PropertyDelegateBase(T* object, PropertyInfo properties[], int propertyCount)
      : object_(object)
      , properties_(propertyCount) {
        for (int i = 0; i < propertyCount; i++) {
            PropertyInfo& p = properties[i];
            properties_[p.propertyId] = p;
        }
    }

    virtual int getProperty(int propertyId, TiObject* val) {
        return (object_->*properties_[propertyId].getter)(val);
    }

    virtual int setProperty(int propertyId, TiObject* val) {
        return (object_->*properties_[propertyId].setter)(val);
    }

private:
    T* object_;
    std::vector<PropertyInfo> properties_;
};

} // namespace titanium

#endif
