/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeLoggerWorker.h"

#include <QString>

using namespace std;

void NativeLoggerWorker::log(const QString& t)
{
    fprintf(stderr, "%s", (t + "\n").toStdString().c_str());
}
