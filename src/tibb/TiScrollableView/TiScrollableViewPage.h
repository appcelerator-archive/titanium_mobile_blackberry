/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TISCROLLABLEVIEWPAGE_H_
#define TISCROLLABLEVIEWPAGE_H_

#include <bb/cascades/Container>

class TiScrollableViewPage: public bb::cascades::Container {
public:
    TiScrollableViewPage();
    virtual ~TiScrollableViewPage();
    void setIndex(int index);
    int getIndex();
    void setLeft(float left);
    float getLeft();
    void setIsCurrentItem(bool isCurrent);
    bool getIsCurrentItem();
    void setSize(float width, float height);
    void addView(bb::cascades::Control *control);
private:
    int _index;
    float _left;
    bool _isCurrentItem;
};

#endif /* TISCROLLABLEVIEWPAGE_H_ */
