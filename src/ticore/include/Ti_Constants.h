/*
 * TiConstants.h
 *
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TICONSTANTS_H_
#define TI_TICONSTANTS_H_
#include <QString>
namespace Ti
{
class TiConstants {
public:

	static const QString EventType;

	// Touch events:
	static const QString EventClick;
	static const QString EventDoubleClick;
	static const QString EventSingleTap;
	static const QString EventDoubleTap;
	static const QString EventLongPress;
	static const QString EventLongClick;
	static const QString EventPinch;

	static const QString EventReturn;
	static const QString EventFocus;
	static const QString EventBlur;
	static const QString EventChange;

	static const QString EventClose;
	static const QString EventOpen;

	static const QString SizeSIZE;
	static const QString SizeFILL;

	static const QString LayoutHorizontal;
	static const QString LayoutVertical;
	static const QString NotSupported;

	static const QString ResourcesDir;
};
}
#endif /* TICONSTANTS_H_ */
