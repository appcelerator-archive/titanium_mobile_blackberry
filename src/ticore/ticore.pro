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
    ./src/Ti_Constants.cpp \
    ./src/Ti_Event.cpp \
    ./src/Ti_EventParameters.cpp \
    ./src/Ti_Helper.cpp \
    ./src/Ti_Module.cpp \
    ./src/Ti_Property.cpp \
    ./src/Ti_Proxy.cpp \
    ./src/Ti_SceneManager.cpp \
    ./src/Ti_Timer.cpp \
    ./src/Ti_Value.cpp
    
HEADERS += \
    ./src/Ti_Constants.h \
    ./src/Ti_Event.h \
    ./src/Ti_EventParameters.h \
    ./src/Ti_Helper.h \
    ./src/Ti_Module.h \
    ./src/Ti_Property.h \
    ./src/Ti_Proxy.h \
    ./src/Ti_SceneManager.h \
    ./src/Ti_Timer.h \
    ./src/Ti_Value.h

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
