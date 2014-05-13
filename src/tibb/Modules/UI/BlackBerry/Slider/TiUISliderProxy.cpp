/*
 * TiUISliderProxy.cpp
 *
 *  Created on: Wednesday, September 25, 2013
 *      Author: penrique
 */

#include "TiUISliderProxy.h"
#include "TiUISlider.h"

namespace TiUI {

TiUISliderProxy::TiUISliderProxy(const char* name) :
		Ti::TiViewProxy(name),
		_fromRange(-1),
		_toRange(-1)
{

	createPropertySetterGetter("disabledLeftTrackImage", _setDisabledLeftTrackImage,  _getDisabledLeftTrackImage);
	createPropertySetterGetter("disabledRightTrackImage", _setDisabledRightTrackImage,  _getDisabledRightTrackImage);
	createPropertySetterGetter("disabledThumbImage", _setDisabledThumbImage,  _getDisabledThumbImage);
	createPropertySetterGetter("enabled", _setEnabled,  _getEnabled);
	createPropertySetterGetter("highlightedLeftTrackImage", _setHighlightedLeftTrackImage,  _getHighlightedLeftTrackImage);
	createPropertySetterGetter("highlightedRightTrackImage", _setHighlightedRightTrackImage,  _getHighlightedRightTrackImage);
	createPropertySetterGetter("highlightedThumbImage", _setHighlightedThumbImage,  _getHighlightedThumbImage);
	createPropertySetterGetter("leftTrackImage", _setLeftTrackImage,  _getLeftTrackImage);
	createPropertySetterGetter("leftTrackLeftCap", _setLeftTrackLeftCap,  _getLeftTrackLeftCap);
	createPropertySetterGetter("leftTrackTopCap", _setLeftTrackTopCap,  _getLeftTrackTopCap);
	createPropertySetterGetter("max", _setMax,  _getMax);
	createPropertySetterGetter("maxRange", _setMaxRange,  _getMaxRange);
	createPropertySetterGetter("min", _setMin,  _getMin);
	createPropertySetterGetter("minRange", _setMinRange,  _getMinRange);
	createPropertySetterGetter("rightTrackImage", _setRightTrackImage,  _getRightTrackImage);
	createPropertySetterGetter("rightTrackLeftCap", _setRightTrackLeftCap,  _getRightTrackLeftCap);
	createPropertySetterGetter("rightTrackTopCap", _setRightTrackTopCap,  _getRightTrackTopCap);
	createPropertySetterGetter("selectedLeftTrackImage", _setSelectedLeftTrackImage,  _getSelectedLeftTrackImage);
	createPropertySetterGetter("selectedRightTrackImage", _setSelectedRightTrackImage,  _getSelectedRightTrackImage);
	createPropertySetterGetter("selectedThumbImage", _setSelectedThumbImage,  _getSelectedThumbImage);
	createPropertySetterGetter("thumbImage", _setThumbImage,  _getThumbImage);
	createPropertySetterGetter("value", _setValue,  _getValue);

	createPropertyFunction("add", _add);
	createPropertyFunction("remove", _remove);

	_slider = new TiUISlider(this);
	_native = _slider->getNative();
	setView(_slider);
}

TiUISliderProxy::~TiUISliderProxy()
{
}

void TiUISliderProxy::setDisabledLeftTrackImage(Ti::TiValue)
{
}
void TiUISliderProxy::setDisabledRightTrackImage(Ti::TiValue)
{
}
void TiUISliderProxy::setDisabledThumbImage(Ti::TiValue)
{
}
void TiUISliderProxy::setHighlightedLeftTrackImage(Ti::TiValue)
{
}
void TiUISliderProxy::setHighlightedRightTrackImage(Ti::TiValue)
{
}
void TiUISliderProxy::setHighlightedThumbImage(Ti::TiValue)
{
}
void TiUISliderProxy::setLeftTrackImage(Ti::TiValue)
{
}
void TiUISliderProxy::setLeftTrackLeftCap(Ti::TiValue)
{
}
void TiUISliderProxy::setLeftTrackTopCap(Ti::TiValue)
{
}
void TiUISliderProxy::setMax(Ti::TiValue val)
{
	_native->setToValue(val.toNumber());
}
void TiUISliderProxy::setMaxRange(Ti::TiValue val)
{
	_toRange = val.toNumber();
	_native->setRange(_fromRange, _toRange);
}
void TiUISliderProxy::setMin(Ti::TiValue val)
{
	_native->setFromValue(val.toNumber());
}
void TiUISliderProxy::setMinRange(Ti::TiValue val)
{
	_fromRange = val.toNumber();
	_native->setRange(_fromRange, _toRange);
}
void TiUISliderProxy::setRightTrackImage(Ti::TiValue)
{
}
void TiUISliderProxy::setRightTrackLeftCap(Ti::TiValue)
{
}
void TiUISliderProxy::setRightTrackTopCap(Ti::TiValue)
{
}
void TiUISliderProxy::setSelectedLeftTrackImage(Ti::TiValue)
{
}
void TiUISliderProxy::setSelectedRightTrackImage(Ti::TiValue)
{
}
void TiUISliderProxy::setSelectedThumbImage(Ti::TiValue)
{
}
void TiUISliderProxy::setThumbImage(Ti::TiValue)
{
}
void TiUISliderProxy::setValue(Ti::TiValue val)
{
	_native->setValue(val.toNumber());
}

Ti::TiValue TiUISliderProxy::getDisabledLeftTrackImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getDisabledRightTrackImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getDisabledThumbImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getHighlightedLeftTrackImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getHighlightedRightTrackImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getHighlightedThumbImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getLeftTrackImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getLeftTrackLeftCap()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getLeftTrackTopCap()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getMax()
{
	Ti::TiValue val;
	val.setNumber(_native->toValue());
	return val;
}
Ti::TiValue TiUISliderProxy::getMaxRange()
{
	Ti::TiValue val;
	val.setNumber(_toRange);
	return val;
}
Ti::TiValue TiUISliderProxy::getMin()
{
	Ti::TiValue val;
	val.setNumber(_native->fromValue());
	return val;
}
Ti::TiValue TiUISliderProxy::getMinRange()
{
	Ti::TiValue val;
	val.setNumber(_fromRange);
	return val;
}
Ti::TiValue TiUISliderProxy::getRightTrackImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getRightTrackLeftCap()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getRightTrackTopCap()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getSelectedLeftTrackImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getSelectedRightTrackImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getSelectedThumbImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getThumbImage()
{
	Ti::TiValue val;
	val.setUndefined();
	return val;
}
Ti::TiValue TiUISliderProxy::getValue()
{
	Ti::TiValue val;
	val.setNumber(_native->value());
	return val;
}

}
