TEMPLATE = lib

QMAKE_CC = $(NDK_CCACHE) $${QMAKE_CC}
QMAKE_CXX = $(NDK_CCACHE) $${QMAKE_CXX}

CONFIG += qt staticlib warn_on debug_and_release cascades mobility
MOBILITY += sensors

INCLUDEPATH += \
	. \
	./include \
	../../runtime/v8/include
SOURCES += \
	./*.cpp \
	./Layout/Common.cpp \
	./Layout/Composite.cpp \
	./Layout/Horizontal.cpp \
	./Layout/Vertical.cpp \
	./Layout/Element.cpp \
	./Layout/Horizontal.cpp\
	./Layout/Node.cpp \
	./Layout/ParseProperty.cpp \
	./Layout/Vertical.cpp \
	./TableView/BasicListItem.cpp \
	./TiScrollableView/TiScrollableView.cpp \
	./TiScrollableView/TiScrollableViewPage.cpp
HEADERS += \
	./*.h \
	TableView/BasicListItem.h \
	TableView/ListItemData.h \
	TiScrollableView/TiScrollableView.h \
	TiScrollableView/TiScrollableViewPage.h

LIBS += -lz -lsqlite3 -lQtLocationSubset -lbbcascadesmaps -lGLESv1_CM -lOpenAL -lalut -lasound -lbbmultimedia -lbbdata

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
