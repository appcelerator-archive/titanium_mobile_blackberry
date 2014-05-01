/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumLayout.h"
#include "Layout/Headers.h"
#include "Ti_Constants.h"
#include "Ti_Helper.h"
#include <bb/cascades/AbsoluteLayoutProperties>
#include <bb/device/DeviceInfo>
#include <bb/device/DisplayInfo>
namespace Ti {
    
    
    TitaniumLayout::TitaniumLayout(TiView* tiView) :
    QObject(tiView),
    _layout(""),
    _left(""), _right(""), _top(""), _bottom(""),
    _width(""), _height(""),
    _nLayout(-1),
    _nLeft(-1), _nRight(-1), _nTop(-1), _nBottom(-1),
    _nWidth(-1), _nHeight(-1),
    lastWidth_(0),
    lastHeight_(0),
    displayWidth_(0),
    displayHeight_(0),
    
    ignoreHeight_(false),
    ignoreWidth_(false),
    deferWidth_(false), deferHeight_(false),
    deferWidthType_((enum Ti::Layout::ValueType)-1),
    deferHeightType_((enum Ti::Layout::ValueType)-1),
    
    _tiView(tiView),
    _control(NULL)
    {
        
        ignoreHeight_ = _tiView->ingoreHeight();
        ignoreWidth_ = _tiView->ingoreWidth();
        
        Ti::Layout::TiNode::nodeInitialize(&_layoutNode);
        _layoutNode.onLayout = onPostLayout;
        _layoutNode.data = this;
        
        // ================================
        if(_tiView->defaultHeight() == Ti::TiConstants::SizeSIZE)
        {
            _layoutNode.properties.defaultHeightType = Ti::Layout::Size;
            deferHeight_ = true;
            if(ignoreHeight_)
                _layoutNode.properties.height.valueType = Ti::Layout::Size;
        }
        else
            if(_tiView->defaultHeight() == Ti::TiConstants::SizeFILL)
            {
                _layoutNode.properties.defaultHeightType = Ti::Layout::Fill;
                if(ignoreHeight_)
                    _layoutNode.properties.height.valueType = Ti::Layout::Fill;
                
            }
        // ================================
        if(_tiView->defaultWidth() == Ti::TiConstants::SizeSIZE)
        {
            deferWidth_ = true;
            _layoutNode.properties.defaultWidthType = Ti::Layout::Size;
            if(ignoreWidth_)
                _layoutNode.properties.width.valueType = Ti::Layout::Size;
        }
        else
            if(_tiView->defaultWidth() == Ti::TiConstants::SizeFILL)
            {
                _layoutNode.properties.defaultWidthType = Ti::Layout::Fill;
                if(ignoreWidth_)
                    _layoutNode.properties.width.valueType = Ti::Layout::Fill;
            }
        
        _control = _tiView->childControl != NULL ? _tiView->childControl : _tiView;
        bb::cascades::LayoutUpdateHandler::create(_control).onLayoutFrameChanged(this,SLOT(onLayout(QRectF)));
    }
    
    TitaniumLayout::~TitaniumLayout() {
        // TODO Auto-generated destructor stub
    }
    
    void TitaniumLayout::_setChildControl(bb::cascades::Control* control)
    {
        return;
    }
    
    bb::cascades::Control * TitaniumLayout::_getChildControl()
    {
        return _control;
    }
    
    TiView* TitaniumLayout::getView()
    {
        return _tiView;
    }
    
    void TitaniumLayout::onPostLayout(struct Ti::Layout::Node* node)
    {
        TitaniumLayout* layout = static_cast<TitaniumLayout*>(node->data);
        
        float width = node->element._measuredWidth,
        height = node->element._measuredHeight,
        left = node->element._measuredLeft,
        top = node->element._measuredTop;
        
        // do not allow a control to go to 0 or the OS will not render control and will stop call back os deferred sizes
        if (width == 0 || height == 0) {
            return;
        }
        
        bool resized = layout->resize(width, height);
        
        bb::cascades::AbsoluteLayoutProperties* layoutProperties =
        static_cast<bb::cascades::AbsoluteLayoutProperties*>(layout->_tiView->layoutProperties());
        
        if (layoutProperties != NULL) {
            layoutProperties->setPositionX(node->element._measuredLeft);
            layoutProperties->setPositionY(node->element._measuredTop);
            //    	control->setOpacity(native->opacity_);
        }
        if(resized)
            layout->_tiView->onRelayout(QRectF(left, top, width, height));
    }
    
    void TitaniumLayout::onLayout(QRectF rect)
    {
        bool requestLayout = false;
        rect_ = rect;
        
        if (deferWidth_ == true && rect.width() != 0) {
            if (deferWidth_ && (_layoutNode.properties.left.valueType == Ti::Layout::Fixed || _layoutNode.properties.left.valueType == Ti::Layout::Percent) &&
                (_layoutNode.properties.right.valueType == Ti::Layout::Fixed || _layoutNode.properties.right.valueType == Ti::Layout::Percent) &&
                deferWidthType_ != Ti::Layout::Size) {
            }
            else {
                _layoutNode.properties.width.value = rect.width();
                _layoutNode.properties.width.valueType = Ti::Layout::Fixed;
                
                if (lastWidth_ == rect.width()) {
                    requestLayout = false;
                }
                else {
                    requestLayout = true;
                };
            }
        }
        
        if (deferHeight_ == true && rect.height() != 0) {
            if (deferHeight_ && (_layoutNode.properties.top.valueType == Ti::Layout::Fixed || _layoutNode.properties.top.valueType == Ti::Layout::Percent) &&
                (_layoutNode.properties.bottom.valueType == Ti::Layout::Fixed || _layoutNode.properties.bottom.valueType == Ti::Layout::Percent) &&
                deferHeightType_ != Ti::Layout::Size) {
            }
            else {
                _layoutNode.properties.height.value = rect.height();
                _layoutNode.properties.height.valueType = Ti::Layout::Fixed;
                
                if (lastHeight_ == rect.height()) {
                    requestLayout = false;
                }
                else {
                    requestLayout = true;
                };
            }
        }
        // is window
        if(_tiView->parentView == NULL)
        {
            _layoutNode.element._measuredWidth = rect.width();
            _layoutNode.element._measuredHeight = rect.height();
            requestLayout = true;
        }
        
        if (requestLayout) {
            struct Ti::Layout::Node* root = Ti::Layout::TiNode::nodeRequestLayout(&_layoutNode);
            if(root) {
                Ti::Layout::TiNode::nodeLayout(root);
            }
        }
        
        lastWidth_ = rect.width();
        lastHeight_ = rect.height();
    }
    
    void TitaniumLayout::addChild(TiView* newView)
    {
        if(newView->parentView == NULL)
        {
            newView->setParentView(_tiView);
        }
        Ti::Layout::TiNode::nodeAddChild(&_layoutNode, &newView->viewLayout->_layoutNode);
        struct Ti::Layout::Node* root = Ti::Layout::TiNode::nodeRequestLayout(&_layoutNode);
        if (root) {
            Ti::Layout::TiNode::nodeLayout(root);
        }
    }
    
    void TitaniumLayout::removeChild(TiView *oldView)
    {
        Ti::Layout::TiNode::nodeRemoveChild(&_layoutNode, &oldView->viewLayout->_layoutNode);
        struct Ti::Layout::Node* root = Ti::Layout::TiNode::nodeRequestLayout(&_layoutNode);
        if (root) {
            Ti::Layout::TiNode::nodeLayout(root);
        }
        
    }
    bool TitaniumLayout::resize(float width, float height)
    {
        // if window
        if(_tiView->parentView == NULL) return true; // fire event for the window
        
        bb::cascades::Control* control;
        if(_control != NULL)
        {
            control = _control;
        }
        else
        {
            control = _tiView;
        }
        bool resized = false;
        if (!deferWidth_) {
            control->setMinWidth(width);
            control->setMaxWidth(width);
            resized = true;
        }
        
        if (!deferHeight_) {
            control->setMinHeight(height);
            control->setMaxHeight(height);
            resized = true;
        }
        
        if (deferWidth_ && (_layoutNode.properties.left.valueType == Ti::Layout::Fixed || _layoutNode.properties.left.valueType == Ti::Layout::Percent) &&
            (_layoutNode.properties.right.valueType == Ti::Layout::Fixed || _layoutNode.properties.right.valueType == Ti::Layout::Percent) &&
            deferWidthType_ != Ti::Layout::Size) {
            control->setMinWidth(width);
            control->setMaxWidth(width);
            resized = true;
        }
        
        if (deferHeight_ && (_layoutNode.properties.top.valueType == Ti::Layout::Fixed || _layoutNode.properties.top.valueType == Ti::Layout::Percent) &&
            (_layoutNode.properties.bottom.valueType == Ti::Layout::Fixed || _layoutNode.properties.bottom.valueType == Ti::Layout::Percent) &&
            deferHeightType_ != Ti::Layout::Size) {
            control->setMinHeight(height);
            control->setMaxHeight(height);
            resized = true;
        }
        return resized;
    }
    
    void TitaniumLayout::updateLayoutProperty(Ti::Layout::ValueName name, QString val)
    {
        struct Ti::Layout::InputProperty property;
        property.name = name;
        property.value = val.toStdString();
        
        Ti::Layout::ParseProperty::populateLayoutPoperties(property, &_layoutNode.properties, (double)Ti::TiHelper::PPI());
        
        struct Ti::Layout::Node* root = Ti::Layout::TiNode::nodeRequestLayout(&_layoutNode);
        if (root) {
            Ti::Layout::TiNode::nodeLayout(root);
        }
    }
    void TitaniumLayout::_setLayout(QString val)
    {
        Ti::Layout::TiNode::nodeSetLayoutType(&_layoutNode, val.toLocal8Bit());
    }
    void TitaniumLayout::_setLeft(QString val)
    {
        updateLayoutProperty(Ti::Layout::Left , val);
    }
    void TitaniumLayout::_setRight(QString val)
    {
        updateLayoutProperty(Ti::Layout::Right , val);
    }
    void TitaniumLayout::_setTop(QString val)
    {
        updateLayoutProperty(Ti::Layout::Top , val);
    }
    void TitaniumLayout::_setBottom(QString val)
    {
        updateLayoutProperty(Ti::Layout::Bottom, val);
    }
    void TitaniumLayout::_setWidth(QString val)
    {
        if(ignoreWidth_) return;
        if(val == "auto") val = _tiView->defaultWidth();
        if (deferWidth_ && val == Ti::TiConstants::SizeSIZE) {
            deferWidthType_ = Ti::Layout::Size;
            return;
        }
        deferWidth_ = false;
        updateLayoutProperty(Ti::Layout::Width, val);
    }
    void TitaniumLayout::_setHeight(QString val)
    {
        if(ignoreHeight_) return;
        if(val == "auto") val = _tiView->defaultHeight();
        if (deferHeight_ && val == Ti::TiConstants::SizeSIZE) {
            deferHeightType_ = Ti::Layout::Size;
            return;
        }
        deferHeight_ = false;
        updateLayoutProperty(Ti::Layout::Height , val);
    }
    
    
} /* namespace Ti */
