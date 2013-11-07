/*
 * PhotoGalleryEventHandler.h
 *
 *  Created on: Nov 7, 2013
 *      Author: penrique
 */

#ifndef PHOTOGALLERYEVENTHANDLER_H_
#define PHOTOGALLERYEVENTHANDLER_H_

#include <QObject>
#include <bb/cascades/pickers/FilePicker>
class TiObject;
//#include <bb/cascades/pickers/FilePickerError>

class PhotoGalleryEventHandler: public QObject
{
	Q_OBJECT;
public:
	PhotoGalleryEventHandler(TiObject*);
	virtual ~PhotoGalleryEventHandler();
	void showPicker();
private:
	bb::cascades::pickers::FilePicker *_picker;
	TiObject *_object;
public slots:
	void onFileSelected(const QStringList&);
	void onCanceled();
//	void onError(bb::cascades::pickers::FilePickerError);
};

#endif /* PHOTOGALLERYEVENTHANDLER_H_ */
