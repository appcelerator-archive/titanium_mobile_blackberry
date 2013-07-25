TEMPLATE = lib

CONFIG += qt warn_on staticlib debug_and_release cascades

INCLUDEPATH += \
	. \
	./include
QMAKE_LIBDIR += \
	. \
	../lib 
SOURCES += \
	./*.cpp 
HEADERS += \
	./*.h 

device {
	CONFIG(release, debug|release) {
		DESTDIR = a.le-v7
	}
	CONFIG(debug, debug|release) {
		DESTDIR = a.le-v7-g
	}
}

simulator {
	CONFIG(release, debug|release) {
		DESTDIR = a
	}
	CONFIG(debug, debug|release) {
		DESTDIR = a-g
	}
}

OBJECTS_DIR = $${DESTDIR}/.obj
MOC_DIR = $${DESTDIR}/.moc
RCC_DIR = $${DESTDIR}/.rcc
UI_DIR = $${DESTDIR}/.ui
