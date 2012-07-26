/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef PERSISTENTV8VALUE_H_
#define PERSISTENTV8VALUE_H_

class PersistentV8Value
{
public:
    explicit PersistentV8Value(v8::Handle<v8::Value> value)
    {
        value_ = v8::Persistent<v8::Value>::New(value);
    }
    PersistentV8Value(const PersistentV8Value& obj)
    {
        value_ = v8::Persistent<v8::Value>::New(obj.getValue());
    }
    PersistentV8Value()
    {}
    ~PersistentV8Value()
    {
        value_.Dispose();
    }
    const v8::Persistent<v8::Value> getValue() const
    {
        return value_;
    }
private:
    v8::Persistent<v8::Value> value_;
};

Q_DECLARE_METATYPE(PersistentV8Value);

#endif /* PERSISTENTV8VALUE_H_ */
