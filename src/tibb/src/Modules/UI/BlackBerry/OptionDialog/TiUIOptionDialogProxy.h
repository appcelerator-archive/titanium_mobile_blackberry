/*
 * TiUIOptionDialogProxy.h
 *
 *  Created on: Sunday, September 15, 2013
 *      Author: penrique
 */

#ifndef TI_TIUIOPTIONDIALOGPROXY_H_
#define TI_TIUIOPTIONDIALOGPROXY_H_

#include <TiCore.h>
#include <bb/system/SystemListDialog>
#include <bb/system/SystemUiButton>

namespace TiUI {

class TiUIOptionDialogProxy : public Ti::TiProxy
{
public:
	CREATE_PROXY(TiUIOptionDialogProxy)
	TiUIOptionDialogProxy(const char*);
	virtual ~TiUIOptionDialogProxy();

	void setAndroidView(Ti::TiValue);
	void setTizenView(Ti::TiValue);
	void setCancel(Ti::TiValue);
	void setDestructive(Ti::TiValue);
	void setOptions(Ti::TiValue);
	void setPersistent(Ti::TiValue);
	void setSelectedIndex(Ti::TiValue);
	void setTitle(Ti::TiValue);
	void setTitleid(Ti::TiValue);

	Ti::TiValue getAndroidView();
	Ti::TiValue getTizenView();
	Ti::TiValue getCancel();
	Ti::TiValue getDestructive();
	Ti::TiValue getOptions();
	Ti::TiValue getPersistent();
	Ti::TiValue getSelectedIndex();
	Ti::TiValue getTitle();
	Ti::TiValue getTitleid();

	Ti::TiValue show(Ti::TiValue);
	Ti::TiValue hide(Ti::TiValue);


	EXPOSE_SETTER(TiUIOptionDialogProxy, setAndroidView)
	EXPOSE_SETTER(TiUIOptionDialogProxy, setTizenView)
	EXPOSE_SETTER(TiUIOptionDialogProxy, setCancel)
	EXPOSE_SETTER(TiUIOptionDialogProxy, setDestructive)
	EXPOSE_SETTER(TiUIOptionDialogProxy, setOptions)
	EXPOSE_SETTER(TiUIOptionDialogProxy, setPersistent)
	EXPOSE_SETTER(TiUIOptionDialogProxy, setSelectedIndex)
	EXPOSE_SETTER(TiUIOptionDialogProxy, setTitle)
	EXPOSE_SETTER(TiUIOptionDialogProxy, setTitleid)

	EXPOSE_GETTER(TiUIOptionDialogProxy, getAndroidView)
	EXPOSE_GETTER(TiUIOptionDialogProxy, getTizenView)
	EXPOSE_GETTER(TiUIOptionDialogProxy, getCancel)
	EXPOSE_GETTER(TiUIOptionDialogProxy, getDestructive)
	EXPOSE_GETTER(TiUIOptionDialogProxy, getOptions)
	EXPOSE_GETTER(TiUIOptionDialogProxy, getPersistent)
	EXPOSE_GETTER(TiUIOptionDialogProxy, getSelectedIndex)
	EXPOSE_GETTER(TiUIOptionDialogProxy, getTitle)
	EXPOSE_GETTER(TiUIOptionDialogProxy, getTitleid)

	EXPOSE_METHOD(TiUIOptionDialogProxy, show)
	EXPOSE_METHOD(TiUIOptionDialogProxy, hide)

	void setOptionNames();
private:
	bb::system::SystemListDialog *_dialog;
	QStringList _buttonNames;
	int _selectedIndex;

};

class TiUIOptionDialogEventHandler: public QObject
{
	Q_OBJECT;
public:
	TiUIOptionDialogEventHandler(TiUIOptionDialogProxy*);
	virtual ~TiUIOptionDialogEventHandler();
private:
	TiUIOptionDialogProxy* _proxy;
public slots:
	void clicked(bb::system::SystemUiResult::Type);
};

}
#endif /* TIUIOPTIONDIALOGPROXY_H_ */
