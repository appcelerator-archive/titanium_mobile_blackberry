/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */


#include "tibb.h"
#include <QFile>
#include <QIODevice>
#include <QDebug>

/*
 * Include native modules here
 * #include "TiModuleNameStartup.h"
 */


using namespace std;

QString readAppJs(QString filePath) {
	QFile file(filePath);
	QString jsContent;
	if(!file.open(QIODevice::ReadOnly)) {
		return jsContent;
	}
    QTextStream in(&file);
    in.setCodec("UTF-8");
    while(!in.atEnd())
    {
    	QString s = in.readLine().append("\n");
        jsContent.append(s);
    }
	file.close();
	return jsContent;}

int main(int argc, char** argv)
{
	QString js = readAppJs("app/native/assets/blackberry/app.js");
	if(js.isEmpty()) {
		js = readAppJs("app/native/assets/app.js");
	}
	if(js.isEmpty()) {
		// die
		qDebug() << "app.js not found!";
		js = QString("");
	}

    startV8Engine();
    /*
     * Include native modules here
     * tiRegisterModule("ti.module.name", TiModuleNameStartup);
     */
    return tibb_run(js.toLocal8Bit().constData(), argc, argv);
}
