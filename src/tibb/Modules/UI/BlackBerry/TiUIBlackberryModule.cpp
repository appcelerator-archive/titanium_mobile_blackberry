/**
 * TiUIBlackberry.cpp
 *
 *
 */

#include "TiUIBlackberryModule.h"
#include "ApplicationMenu/ApplicationMenuProxy.h"
#include "NavButton/NavButtonProxy.h"
#include "View/TiUIViewProxy.h"
#include "WebView/TiUIWebViewProxy.h"
#include "Button/TiUIButtonProxy.h"
#include "Window/TiUIWindowProxy.h"
#include "TabGroup/TiUITabGroupProxy.h"
#include "TabGroup/TiUITabProxy.h"
#include "AlertDialog/TiUIAlertDialogProxy.h"
#include "TableView/TiUITableViewProxy.h"
#include "TableView/TiUITableViewRowProxy.h"
#include "TableView/TiUITableViewSectionProxy.h"
#include "ScrollableView/TiUIScrollableViewProxy.h"
#include "ScrollView/TiUIScrollViewProxy.h"
#include "ImageView/TiUIImageViewProxy.h"
#include "Label/TiUILabelProxy.h"
#include "TextWidget/TiUITextWidgetProxy.h"
#include "Switch/TiUISwitchProxy.h"
#include "Slider/TiUISliderProxy.h"

#include <bb/cascades/SupportedDisplayOrientation>
#include <bb/cascades/ActionBarPlacement>
#include <bb/cascades/OverScrollEffectMode>
#include <bb/cascades/TextAlign>
#include <bb/cascades/VerticalAlignment>

using namespace TiUI;

TiUIBlackberryModule::TiUIBlackberryModule(const char* name) : Ti::TiModule(name)
{
	addFunction("createApplicationMenu", ApplicationMenuProxy::CreateProxy);
	addFunction("createNavButton", NavButtonProxy::CreateProxy);
	addFunction("createView", TiUIViewProxy::CreateProxy);
	addFunction("createWebView", TiUIWebViewProxy::CreateProxy);
	addFunction("createButton", TiUIButtonProxy::CreateProxy);
	addFunction("createWindow", TiUIWindowProxy::CreateProxy);
	addFunction("createTabGroup", TiUITabGroupProxy::CreateProxy);
	addFunction("createTab", TiUITabProxy::CreateProxy);
	addFunction("createAlertDialog", TiUIAlertDialogProxy::CreateProxy);
	addFunction("createTableView", TiUITableViewProxy::CreateProxy);
	addFunction("createTableViewRow", TiUITableViewRowProxy::CreateProxy);
	addFunction("createTableViewSection", TiUITableViewSectionProxy::CreateProxy);
	addFunction("createScrollableView", TiUIScrollableViewProxy::CreateProxy);
	addFunction("createScrollView", TiUIScrollViewProxy::CreateProxy);
	addFunction("createImageView", TiUIImageViewProxy::CreateProxy);
	addFunction("createLabel", TiUILabelProxy::CreateProxy);
	addFunction("createTextField", TiUITextWidgetProxy::CreateTextField);
	addFunction("createTextArea", TiUITextWidgetProxy::CreateTextArea);
	addFunction("createSwitch", TiUISwitchProxy::CreateProxy);
	addFunction("createSlider", TiUISliderProxy::CreateProxy);

	addNumber("WEBVIEW_NAVIGATION_TYPE_LINK_CLICKED", bb::cascades::WebNavigationType::LinkClicked);
	addNumber("WEBVIEW_NAVIGATION_TYPE_FORM_SUBMIT", bb::cascades::WebNavigationType::FormSubmitted);
	addNumber("WEBVIEW_NAVIGATION_TYPE_BACK_FORWARD", bb::cascades::WebNavigationType::BackForward);
	addNumber("WEBVIEW_NAVIGATION_TYPE_RELOAD", bb::cascades::WebNavigationType::Reload);
	addNumber("WEBVIEW_NAVIGATION_TYPE_FORM_RESUBMIT", bb::cascades::WebNavigationType::FormResubmitted);
	addNumber("WEBVIEW_NAVIGATION_TYPE_OTHER", bb::cascades::WebNavigationType::Other);
	addNumber("WEBVIEW_NAVIGATION_TYPE_OPEN_WINDOW", bb::cascades::WebNavigationType::OpenWindow);

	addNumber("LANDSCAPE_LEFT", bb::cascades::SupportedDisplayOrientation::DisplayLandscape);
	addNumber("LANDSCAPE_RIGHT", bb::cascades::SupportedDisplayOrientation::DisplayLandscape);
	addNumber("PORTRAIT", bb::cascades::SupportedDisplayOrientation::DisplayPortrait);
	addNumber("UPSIDE_PORTRAIT", bb::cascades::SupportedDisplayOrientation::DisplayPortrait);

    addNumber("ACTION_BAR_PLACEMENT_ON_BAR", bb::cascades::ActionBarPlacement::OnBar);
    addNumber("ACTION_BAR_PLACEMENT_IN_OVERFLOW", bb::cascades::ActionBarPlacement::InOverflow);
    addNumber("ACTION_ABR_PLACEMENT_DEFAULT", bb::cascades::ActionBarPlacement::Default);

    addNumber("OVER_SCROLL_ALWAYS", bb::cascades::OverScrollEffectMode::Default);
    addNumber("OVER_SCROLL_IF_CONTENT_SCROLLS", bb::cascades::OverScrollEffectMode::OnScroll);
    addNumber("OVER_SCROLL_NEVER", bb::cascades::OverScrollEffectMode::None);

    addNumber("TEXT_ALIGNMENT_LEFT", bb::cascades::TextAlign::Left);
    addNumber("TEXT_ALIGNMENT_CENTER", bb::cascades::TextAlign::Center);
    addNumber("TEXT_ALIGNMENT_RIGHT", bb::cascades::TextAlign::Right);
    addNumber("TEXT_ALIGNMENT_DEFAULT", bb::cascades::TextAlign::Default);

    addNumber("KEYBOARD_DEFAULT", TiUI::KEYBOARD_TYPE_DEFAULT);
    addNumber("KEYBOARD_ASCII", TiUI::KEYBOARD_TYPE_ASCII);
    addNumber("KEYBOARD_EMAIL", TiUI::KEYBOARD_TYPE_EMAIL);
    addNumber("KEYBOARD_NAMEPHONE_PAD", TiUI::KEYBOARD_TYPE_NAMEPHONE_PAD);
    addNumber("KEYBOARD_NUMBERS_PUNCTUATION", TiUI::KEYBOARD_TYPE_NUMBERS_PUNCTUATION);
    addNumber("KEYBOARD_PHONE_PAD", TiUI::KEYBOARD_TYPE_PHONE_PAD);
    addNumber("KEYBOARD_URL", TiUI::KEYBOARD_TYPE_URL);
    addNumber("KEYBOARD_CHAT", TiUI::KEYBOARD_TYPE_CHAT);

    addNumber("TEXT_VERTICAL_ALIGNMENT_BOTTOM", bb::cascades::VerticalAlignment::Top);
    addNumber("TEXT_VERTICAL_ALIGNMENT_CENTER", bb::cascades::VerticalAlignment::Bottom);
    addNumber("TEXT_VERTICAL_ALIGNMENT_TOP", bb::cascades::VerticalAlignment::Center);
}

TiUIBlackberryModule::~TiUIBlackberryModule()
{

}

Ti::TiValue TiUIBlackberryModule::getModuleId()
{
	Ti::TiValue val;
	val.setString("ti.ui.blackberry");
	return val;
}
Ti::TiValue TiUIBlackberryModule::getModuleVersion()
{
	Ti::TiValue val;
	val.setString("1.0");
	return val;
}
Ti::TiValue TiUIBlackberryModule::getModuleName()
{
	Ti::TiValue val;
	val.setString("TiUIBlackberry");
	return val;
}
