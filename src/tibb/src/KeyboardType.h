/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

namespace titanium {

class KeyboardType {
public:
    enum Type {
        DEFAULT,
        ASCII,
        EMAIL,
        NAMEPHONE_PAD,
        NUMBERS_PUNCTUATION,
        PHONE_PAD,
        URL
    };

private:
    KeyboardType();
};

} // namespace titanium

