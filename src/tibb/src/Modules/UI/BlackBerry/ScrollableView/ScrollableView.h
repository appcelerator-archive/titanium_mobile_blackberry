/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_SCROLLABLEVIEW_H_
#define TI_SCROLLABLEVIEW_H_

#include <QObject>
#include <TiCore.h>
#include <bb/cascades/CustomControl>
#include <bb/cascades/ListView>
#include "ScrollableViewPage.h"
#include "TiUIScrollableView.h"

namespace TiUI
{

class ScrollableItemProvider :	public bb::cascades::ListItemProvider
{
	Q_OBJECT;
public:
	ScrollableItemProvider();
private:
	bb::cascades::VisualNode * createItem(bb::cascades::ListView*, const QString &);
	void updateItem(	bb::cascades::ListView*,
						bb::cascades::VisualNode *,
						const QString &,
						const QVariantList &,
						const QVariant &);

};
class ScrollableView : public bb::cascades::CustomControl

{
	Q_OBJECT;
public:
	ScrollableView();
	virtual ~ScrollableView();
	void addView(Ti::TiView*);
	void removeView(Ti::TiView*);
	void setTiView(TiUIScrollableView*);
	void scrollToIndexAnimated(int, bool);
	void scrollToViewAnimated(Ti::TiView*, bool);
	int getCurrentIndex();
	int getIndexCount();
	bb::cascades::ListView* _listView;
public slots:
	void onItemChanged(QVariantList);
private:
	TiUIScrollableView* _tiView;
	int _currentIndex;
	int _indexCount;
};
}
#endif /* SCROLLABLEVIEW_H_ */
