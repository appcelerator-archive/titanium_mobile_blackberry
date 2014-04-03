/**
 *
 *
 *
 *
 *
 */
#include "Ti_ErrorScreen.h"
#include <bb/cascades/Page>
#include <bb/cascades/Container>
#include <bb/cascades/DockLayout>
#include <bb/cascades/Label>
#include <bb/cascades/Button>
#include <bb/cascades/Color>
#include <bb/cascades/TextStyleDefinition>
#include <bb/cascades/FontSize>
#include <bb/cascades/FontWeight>
#include <bb/cascades/FontStyle>
#include <bb/cascades/TextAlign>
#include <bb/cascades/VerticalAlignment>
#include <bb/cascades/HorizontalAlignment>
#include <bb/cascades/SystemDefaults>
#include <bb/cascades/Application>

namespace Ti {

TiErrorScreen::TiErrorScreen() : QObject(), _lineNumber(-1), _colNumber(-1), _errorSheet(NULL)
{

}

TiErrorScreen::~TiErrorScreen()
{

}

void TiErrorScreen::buildAndShow() {

	QString log = "";
	if(_lineNumber > -1) {
		log.append("line = " + QString::number(_lineNumber) + "\n");
	}
	if(!_exceptionMessage.isEmpty()) {
		log.append("message = " + _exceptionMessage + "\n");
	}
	if(!_exceptionName.isEmpty()) {
		log.append("name = " + _exceptionName + "\n");
	}
	if(!_sourceLine.isEmpty()) {
		log.append("source = " + _sourceLine + "\n");
	}
	if(!_fileName.isEmpty()) {
		log.append("file = " + _fileName + "\n");
	}
	if(!_stackTrace.isEmpty()) {
		log.append("trace = " + _stackTrace);
	}
	QStringList parts = log.split('\n');
	foreach(QString p, parts) {
		Ti::TiHelper::Log("[ERROR]", p);
	}

	QString msg = "";
	if(!_stackTrace.isEmpty()) {
		msg.append(_stackTrace + "\n");
	}
	if(!_exceptionName.isEmpty()) {
		msg.append(_exceptionName + ": ");
	}
	if(!_exceptionMessage.isEmpty()) {
		msg.append(_exceptionMessage + "\n");
	}

	bb::cascades::Page* page = new bb::cascades::Page();
	_errorSheet = new bb::cascades::Sheet();
	_errorSheet->setParent(this);
    {
		_errorSheet->setPeekEnabled(false);
		QObject::connect(_errorSheet, SIGNAL(closed()), this, SLOT(onClosed()));
    }
	bb::cascades::Container *pageContainer = new bb::cascades::Container();
	{
		pageContainer->setLayout(new bb::cascades::DockLayout());
		pageContainer->setBackground(bb::cascades::Color::Red);
		pageContainer->setTopPadding(50);
		pageContainer->setBottomPadding(50);
		pageContainer->setLeftPadding(20);
		pageContainer->setRightPadding(20);
	}
	bb::cascades::Label *title = new bb::cascades::Label();
	{
		bb::cascades::TextStyleDefinition* textStyle = title->textStyle();
		title->setText("Application Error");
		title->setVerticalAlignment(bb::cascades::VerticalAlignment::Top);
		title->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Center);
		textStyle->setFontSize(bb::cascades::FontSize::XXLarge);
		textStyle->setFontWeight(bb::cascades::FontWeight::Bold);
		textStyle->setFontStyle(bb::cascades::FontStyle::Normal);
		textStyle->setFontSizeValue(0.0);
		textStyle->setTextAlign(bb::cascades::TextAlign::Center);
		textStyle->setColor(bb::cascades::Color::Green);
	}
    bb::cascades::Container *messageContainer = new bb::cascades::Container();
    {
		messageContainer->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Center);
		messageContainer->setVerticalAlignment(bb::cascades::VerticalAlignment::Center);
    }
	bb::cascades::Label *messageLabel = new bb::cascades::Label();
	{
		bb::cascades::TextStyleDefinition* textStyle = messageLabel->textStyle();
		messageLabel->setMultiline(true);
		messageLabel->setText(msg);
		messageLabel->setVerticalAlignment(bb::cascades::VerticalAlignment::Top);
		messageLabel->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Center);
		messageLabel->setBottomMargin(20);
		textStyle->setColor(bb::cascades::Color::White);
		textStyle->setFontSize(bb::cascades::FontSize::Medium);
		textStyle->setFontWeight(bb::cascades::FontWeight::Bold);
		textStyle->setTextAlign(bb::cascades::TextAlign::Center);
	}
	bb::cascades::Button *dismissButton = new bb::cascades::Button();
	{
		dismissButton->setText("Dismiss");
		dismissButton->setVerticalAlignment(bb::cascades::VerticalAlignment::Top);
		dismissButton->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Center);
		dismissButton->setTopMargin(20);
		QObject::connect(dismissButton, SIGNAL(clicked()), this, SLOT(onClicked()));
	}
    bb::cascades::Label *warningLabel = new bb::cascades::Label();
    {
		bb::cascades::TextStyleDefinition* textStyle = warningLabel->textStyle();
		warningLabel->setText("Error messages will only be displayed during development. When your app is packaged for final distribution, no error screen will appear. Test your code!");
		warningLabel->setMultiline(true);
		warningLabel->setVerticalAlignment(bb::cascades::VerticalAlignment::Bottom);
		warningLabel->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Center);
		textStyle->setFontSize(bb::cascades::FontSize::Small);
		textStyle->setFontWeight(bb::cascades::FontWeight::Bold);
		textStyle->setTextAlign(bb::cascades::TextAlign::Center);
    }

	messageContainer->add(messageLabel);
	messageContainer->add(dismissButton);

	pageContainer->add(title);
    pageContainer->add(messageContainer);
    pageContainer->add(warningLabel);

    page->setContent(pageContainer);
	_errorSheet->setContent(page);

    bb::cascades::Application* app = bb::cascades::Application::instance();
    if(app->scene() == NULL) {
    	app->setScene(new bb::cascades::Page());
    }
    _errorSheet->open();
}

void TiErrorScreen::onClicked()
{
	_errorSheet->close();
}
void TiErrorScreen::onClosed()
{
	delete this;
}
void TiErrorScreen::ShowWithTryCatch(TryCatch tryCatch)
{
	TiErrorScreen *errorScreen = new TiErrorScreen();
	errorScreen->parseTryCatch(tryCatch);
	errorScreen->buildAndShow();
}

void TiErrorScreen::parseTryCatch(TryCatch tryCatch)
{
	HandleScope scope;
	if(tryCatch.HasCaught())
    {
    	Handle<Message> message = tryCatch.Message();
    	if(!message.IsEmpty()) {
        	_fileName = Ti::TiHelper::QStringFromValue(message->GetScriptResourceName());
        	_sourceLine = Ti::TiHelper::QStringFromValue(message->GetSourceLine());
        	_lineNumber = message->GetLineNumber();
        	_colNumber = message->GetStartColumn();
    	}
    	_stackTrace = Ti::TiHelper::QStringFromValue(tryCatch.StackTrace());
    	if (_stackTrace.isEmpty()) {
    		Local<Value> er = tryCatch.Exception();
			if (er->IsObject()) {
				Local<Object> exObj = er->ToObject();
				_exceptionName = Ti::TiHelper::QStringFromValue(exObj->Get(String::New("name")));
				_exceptionMessage = Ti::TiHelper::QStringFromValue(exObj->Get(String::New("message")));
			} else {
				_exceptionMessage = Ti::TiHelper::QStringFromValue(er);
			}
		}

	}
}
}
