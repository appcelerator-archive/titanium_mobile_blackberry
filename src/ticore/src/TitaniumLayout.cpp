/*
 * TitaniumLayout.cpp
 *
 *  Created on: Sep 19, 2013
 *      Author: penrique
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
        
        Ti::Layout::TiNode::nodeInitialize(&layoutNode_);
        layoutNode_.onLayout = onPostLayout;
        layoutNode_.data = this;
        
        // ================================
        if(_tiView->defaultHeight() == Ti::TiConstants::SizeSIZE)
        {
            layoutNode_.properties.defaultHeightType = Ti::Layout::Size;
            deferHeight_ = true;
            if(ignoreHeight_)
                layoutNode_.properties.height.valueType = Ti::Layout::Size;
        }
        else
            if(_tiView->defaultHeight() == Ti::TiConstants::SizeFILL)
            {
                layoutNode_.properties.defaultHeightType = Ti::Layout::Fill;
                if(ignoreHeight_)
                    layoutNode_.properties.height.valueType = Ti::Layout::Fill;
                
            }
        // ================================
        if(_tiView->defaultWidth() == Ti::TiConstants::SizeSIZE)
        {
            deferWidth_ = true;
            layoutNode_.properties.defaultWidthType = Ti::Layout::Size;
            if(ignoreWidth_)
                layoutNode_.properties.width.valueType = Ti::Layout::Size;
        }
        else
            if(_tiView->defaultWidth() == Ti::TiConstants::SizeFILL)
            {
                layoutNode_.properties.defaultWidthType = Ti::Layout::Fill;
                if(ignoreWidth_)
                    layoutNode_.properties.width.valueType = Ti::Layout::Fill;
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
            if (deferWidth_ && (layoutNode_.properties.left.valueType == Ti::Layout::Fixed || layoutNode_.properties.left.valueType == Ti::Layout::Percent) &&
                (layoutNode_.properties.right.valueType == Ti::Layout::Fixed || layoutNode_.properties.right.valueType == Ti::Layout::Percent) &&
                deferWidthType_ != Ti::Layout::Size) {
            }
            else {
                layoutNode_.properties.width.value = rect.width();
                layoutNode_.properties.width.valueType = Ti::Layout::Fixed;
                
                if (lastWidth_ == rect.width()) {
                    requestLayout = false;
                }
                else {
                    requestLayout = true;
                };
            }
        }
        
        if (deferHeight_ == true && rect.height() != 0) {
            if (deferHeight_ && (layoutNode_.properties.top.valueType == Ti::Layout::Fixed || layoutNode_.properties.top.valueType == Ti::Layout::Percent) &&
                (layoutNode_.properties.bottom.valueType == Ti::Layout::Fixed || layoutNode_.properties.bottom.valueType == Ti::Layout::Percent) &&
                deferHeightType_ != Ti::Layout::Size) {
            }
            else {
                layoutNode_.properties.height.value = rect.height();
                layoutNode_.properties.height.valueType = Ti::Layout::Fixed;
                
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
            layoutNode_.element._measuredWidth = rect.width();
            layoutNode_.element._measuredHeight = rect.height();
            requestLayout = true;
        }
        
        if (requestLayout) {
            struct Ti::Layout::Node* root = Ti::Layout::TiNode::nodeRequestLayout(&layoutNode_);
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
        Ti::Layout::TiNode::nodeAddChild(&layoutNode_, &newView->viewLayout->layoutNode_);
        struct Ti::Layout::Node* root = Ti::Layout::TiNode::nodeRequestLayout(&layoutNode_);
        if (root) {
            Ti::Layout::TiNode::nodeLayout(root);
        }
    }
    
    void TitaniumLayout::removeChild(TiView *oldView)
    {
        Ti::Layout::TiNode::nodeRemoveChild(&layoutNode_, &oldView->viewLayout->layoutNode_);
        struct Ti::Layout::Node* root = Ti::Layout::TiNode::nodeRequestLayout(&layoutNode_);
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
        
        if (deferWidth_ && (layoutNode_.properties.left.valueType == Ti::Layout::Fixed || layoutNode_.properties.left.valueType == Ti::Layout::Percent) &&
            (layoutNode_.properties.right.valueType == Ti::Layout::Fixed || layoutNode_.properties.right.valueType == Ti::Layout::Percent) &&
            deferWidthType_ != Ti::Layout::Size) {
            control->setMinWidth(width);
            control->setMaxWidth(width);
            resized = true;
        }
        
        if (deferHeight_ && (layoutNode_.properties.top.valueType == Ti::Layout::Fixed || layoutNode_.properties.top.valueType == Ti::Layout::Percent) &&
            (layoutNode_.properties.bottom.valueType == Ti::Layout::Fixed || layoutNode_.properties.bottom.valueType == Ti::Layout::Percent) &&
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
        
        Ti::Layout::ParseProperty::populateLayoutPoperties(property, &layoutNode_.properties, (double)Ti::TiHelper::PPI());
        
        struct Ti::Layout::Node* root = Ti::Layout::TiNode::nodeRequestLayout(&layoutNode_);
        if (root) {
            Ti::Layout::TiNode::nodeLayout(root);
        }
    }
    
    
    void TitaniumLayout::_setLayout(QString val)
    {
        Ti::Layout::TiNode::nodeSetLayoutType(&layoutNode_, val.toLocal8Bit());
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
