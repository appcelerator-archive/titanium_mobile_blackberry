/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TIUISLIDERPROXY_H_
#define TI_TIUISLIDERPROXY_H_

#include <TiCore.h>
#include <bb/cascades/Slider>

namespace TiUI {
class TiUISlider;
class TiUISliderProxy : public Ti::TiViewProxy
{
public:
	CREATE_PROXY(TiUISliderProxy)
	TiUISliderProxy(const char*);
	virtual ~TiUISliderProxy();

	void setDisabledLeftTrackImage(Ti::TiValue);
	void setDisabledRightTrackImage(Ti::TiValue);
	void setDisabledThumbImage(Ti::TiValue);
	void setHighlightedLeftTrackImage(Ti::TiValue);
	void setHighlightedRightTrackImage(Ti::TiValue);
	void setHighlightedThumbImage(Ti::TiValue);
	void setLeftTrackImage(Ti::TiValue);
	void setLeftTrackLeftCap(Ti::TiValue);
	void setLeftTrackTopCap(Ti::TiValue);
	void setMax(Ti::TiValue);
	void setMaxRange(Ti::TiValue);
	void setMin(Ti::TiValue);
	void setMinRange(Ti::TiValue);
	void setRightTrackImage(Ti::TiValue);
	void setRightTrackLeftCap(Ti::TiValue);
	void setRightTrackTopCap(Ti::TiValue);
	void setSelectedLeftTrackImage(Ti::TiValue);
	void setSelectedRightTrackImage(Ti::TiValue);
	void setSelectedThumbImage(Ti::TiValue);
	void setThumbImage(Ti::TiValue);
	void setValue(Ti::TiValue);

	Ti::TiValue getDisabledLeftTrackImage();
	Ti::TiValue getDisabledRightTrackImage();
	Ti::TiValue getDisabledThumbImage();
	Ti::TiValue getHighlightedLeftTrackImage();
	Ti::TiValue getHighlightedRightTrackImage();
	Ti::TiValue getHighlightedThumbImage();
	Ti::TiValue getLeftTrackImage();
	Ti::TiValue getLeftTrackLeftCap();
	Ti::TiValue getLeftTrackTopCap();
	Ti::TiValue getMax();
	Ti::TiValue getMaxRange();
	Ti::TiValue getMin();
	Ti::TiValue getMinRange();
	Ti::TiValue getRightTrackImage();
	Ti::TiValue getRightTrackLeftCap();
	Ti::TiValue getRightTrackTopCap();
	Ti::TiValue getSelectedLeftTrackImage();
	Ti::TiValue getSelectedRightTrackImage();
	Ti::TiValue getSelectedThumbImage();
	Ti::TiValue getThumbImage();
	Ti::TiValue getValue();


	EXPOSE_SETTER(TiUISliderProxy, setDisabledLeftTrackImage)
	EXPOSE_SETTER(TiUISliderProxy, setDisabledRightTrackImage)
	EXPOSE_SETTER(TiUISliderProxy, setDisabledThumbImage)
	EXPOSE_SETTER(TiUISliderProxy, setHighlightedLeftTrackImage)
	EXPOSE_SETTER(TiUISliderProxy, setHighlightedRightTrackImage)
	EXPOSE_SETTER(TiUISliderProxy, setHighlightedThumbImage)
	EXPOSE_SETTER(TiUISliderProxy, setLeftTrackImage)
	EXPOSE_SETTER(TiUISliderProxy, setLeftTrackLeftCap)
	EXPOSE_SETTER(TiUISliderProxy, setLeftTrackTopCap)
	EXPOSE_SETTER(TiUISliderProxy, setMax)
	EXPOSE_SETTER(TiUISliderProxy, setMaxRange)
	EXPOSE_SETTER(TiUISliderProxy, setMin)
	EXPOSE_SETTER(TiUISliderProxy, setMinRange)
	EXPOSE_SETTER(TiUISliderProxy, setRightTrackImage)
	EXPOSE_SETTER(TiUISliderProxy, setRightTrackLeftCap)
	EXPOSE_SETTER(TiUISliderProxy, setRightTrackTopCap)
	EXPOSE_SETTER(TiUISliderProxy, setSelectedLeftTrackImage)
	EXPOSE_SETTER(TiUISliderProxy, setSelectedRightTrackImage)
	EXPOSE_SETTER(TiUISliderProxy, setSelectedThumbImage)
	EXPOSE_SETTER(TiUISliderProxy, setThumbImage)
	EXPOSE_SETTER(TiUISliderProxy, setValue)

	EXPOSE_GETTER(TiUISliderProxy, getDisabledLeftTrackImage)
	EXPOSE_GETTER(TiUISliderProxy, getDisabledRightTrackImage)
	EXPOSE_GETTER(TiUISliderProxy, getDisabledThumbImage)
	EXPOSE_GETTER(TiUISliderProxy, getHighlightedLeftTrackImage)
	EXPOSE_GETTER(TiUISliderProxy, getHighlightedRightTrackImage)
	EXPOSE_GETTER(TiUISliderProxy, getHighlightedThumbImage)
	EXPOSE_GETTER(TiUISliderProxy, getLeftTrackImage)
	EXPOSE_GETTER(TiUISliderProxy, getLeftTrackLeftCap)
	EXPOSE_GETTER(TiUISliderProxy, getLeftTrackTopCap)
	EXPOSE_GETTER(TiUISliderProxy, getMax)
	EXPOSE_GETTER(TiUISliderProxy, getMaxRange)
	EXPOSE_GETTER(TiUISliderProxy, getMin)
	EXPOSE_GETTER(TiUISliderProxy, getMinRange)
	EXPOSE_GETTER(TiUISliderProxy, getRightTrackImage)
	EXPOSE_GETTER(TiUISliderProxy, getRightTrackLeftCap)
	EXPOSE_GETTER(TiUISliderProxy, getRightTrackTopCap)
	EXPOSE_GETTER(TiUISliderProxy, getSelectedLeftTrackImage)
	EXPOSE_GETTER(TiUISliderProxy, getSelectedRightTrackImage)
	EXPOSE_GETTER(TiUISliderProxy, getSelectedThumbImage)
	EXPOSE_GETTER(TiUISliderProxy, getThumbImage)
	EXPOSE_GETTER(TiUISliderProxy, getValue)

private:
	TiUISlider *_slider;
	bb::cascades::Slider *_native;

	float _fromRange;
	float _toRange;
};

}
#endif /* TIUISLIDERPROXY_H_ */
