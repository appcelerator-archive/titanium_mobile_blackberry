/*
 * TiUIView.cpp
 *
 *  Created on: Jul 14, 2013
 *      Author: penrique
 */

#include "TiUIView.h"

namespace TiUI {

TiUIView::TiUIView(Ti::TiViewProxy* _proxy) : Ti::TiView(_proxy)
{
}

TiUIView::~TiUIView()
{

}
bool TiUIView::ingoreWidth()
{
	return false;
}
bool TiUIView::ingoreHeight()
{
	return false;
}
QString TiUIView::defaultWidth()
{
	return Ti::TiConstants::SizeFILL;
}
QString TiUIView::defaultHeight()
{
	return Ti::TiConstants::SizeFILL;
}

}
