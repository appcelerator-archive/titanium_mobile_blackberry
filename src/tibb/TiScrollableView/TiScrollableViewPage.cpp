/*
 * TiScrollableViewPage.cpp
 *
 *  Created on: Apr 23, 2013
 *      Author: penrique
 */

#include "TiScrollableViewPage.h"

#include <bb/cascades/DockLayout>
#include <bb/cascades/AbsoluteLayoutProperties>

TiScrollableViewPage::TiScrollableViewPage() {
	bb::cascades::AbsoluteLayoutProperties *layoutProps = new bb::cascades::AbsoluteLayoutProperties();
	this->setLayoutProperties(layoutProps);
	this->setLayout(new bb::cascades::DockLayout());
	this->_isCurrentItem = false;
	this->_left = 0;
	this->_index = 0;
}
TiScrollableViewPage::~TiScrollableViewPage() { }

void TiScrollableViewPage::setIndex(int index) {
	this->_index = index;
}
int TiScrollableViewPage::getIndex() {
	return  this->_index;
}
void TiScrollableViewPage::setLeft(float left) {
	this->_left = left;
	bb::cascades::AbsoluteLayoutProperties* props = (bb::cascades::AbsoluteLayoutProperties*)this->layoutProperties();
	props->setPositionX(left);
}

float TiScrollableViewPage::getLeft() {
	return this->_left;
}

void TiScrollableViewPage::setIsCurrentItem(bool isCurrent) {
	this->_isCurrentItem = isCurrent;
}

bool TiScrollableViewPage::getIsCurrentItem() {
	return this->_isCurrentItem;
}

void TiScrollableViewPage::setSize(float width, float height) {
	this->setPreferredSize(width, height);
	this->setMinHeight(height);
	this->setMaxHeight(height);
	this->setMinWidth(width);
	this->setMaxWidth(width);
}

void TiScrollableViewPage::addView(bb::cascades::Control *control) {
	control->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Fill);
	control->setVerticalAlignment(bb::cascades::VerticalAlignment::Fill);
	this->add(control);
}
