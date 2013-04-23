/*
 * TiScrollableView.h
 *
 *  Created on: Apr 23, 2013
 *      Author: penrique
 */

#ifndef TISCROLLABLEVIEW_H_
#define TISCROLLABLEVIEW_H_

#include <QtCore/QObject>
#include <bb/cascades/ScrollView>


namespace bb{
namespace cascades{
class Container;
}
}
class TiScrollableViewPage;

class TiScrollableView: public bb::cascades::ScrollView {
	Q_OBJECT;
public:
	TiScrollableView();
	virtual ~TiScrollableView();
	void addView(bb::cascades::Container* view);
	void scrollToIndex(int index, bool animated);
private:
	QList<TiScrollableViewPage*> views;
	bb::cascades::Container* contentView;
	void arrangeViews();
	float width;
	float contentOffsetX;
public slots:
    void handleLayoutFrameUpdated(QRectF rect);
    void onScroll(const QRectF & rect, float);
    void onScrolling(const QRectF & rect, float);
};

#endif /* TISCROLLABLEVIEW_H_ */
