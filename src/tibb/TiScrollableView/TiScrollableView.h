/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TISCROLLABLEVIEW_H_
#define TISCROLLABLEVIEW_H_

#include <QtCore/QObject>
#include <bb/cascades/ScrollView>
#include <bb/cascades/Container>

class TiScrollableViewPage;

class TiScrollableView: public bb::cascades::ScrollView {
    Q_OBJECT;
public:
    TiScrollableView();
    virtual ~TiScrollableView();
    void addView(bb::cascades::Container* view);
    void scrollToIndex(int index, bool animated);
    int currentIndex;
    int indexCount;
    void startAt(int index);
public slots:
    void handleLayoutFrameUpdated(QRectF rect);
    void onScroll(const QRectF & rect, float);
    void onScrolling(const QRectF & rect, float);
private:
    QList<TiScrollableViewPage*> views;
    bb::cascades::Container* contentView;
    void arrangeViews();
    float width;
    float contentOffsetX;
    int startIndex;
};

#endif /* TISCROLLABLEVIEW_H_ */
