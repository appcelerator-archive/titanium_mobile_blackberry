#include <tibb.h>
#include <QObject>
#include <QFile>
#include <QIODevice>
#include <QDebug>

/*
 * Include native modules here
 * #include "TiModuleNameStartup.h"
 */

${module_headers}

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

Q_DECL_EXPORT int main(int argc, char** argv)
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
    ${module_includes}
    return tibb_run(js.toLocal8Bit().constData(), argc, argv);
}
