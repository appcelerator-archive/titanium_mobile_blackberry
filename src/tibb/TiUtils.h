/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include <QObject>

class TiUtils
{
public:
	TiUtils();
	~TiUtils();
	static TiUtils* getInstance();
	float getCalculatedDimension(QString);
	float getPPI();
private:

	float ppi_;
};
