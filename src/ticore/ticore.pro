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
    ./src/Ti_Blob.cpp \
    ./src/Ti_Constants.cpp \
    ./src/Ti_Data.cpp \
    ./src/Ti_Event.cpp \
    ./src/Ti_EventParameters.cpp \
    ./src/Ti_Helper.cpp \
    ./src/Ti_Module.cpp \
    ./src/Ti_Property.cpp \
    ./src/Ti_Proxy.cpp \
    ./src/Ti_Runtime.cpp \
    ./src/Ti_SceneManager.cpp \
    ./src/Ti_Timer.cpp \
    ./src/Ti_Value.cpp

HEADERS += \
    ./include/Ti_Blob.h \
    ./include/Ti_Constants.h \
    ./include/Ti_Data.h \
    ./include/Ti_Event.h \
    ./include/Ti_EventParameters.h \
    ./include/Ti_Helper.h \
    ./include/Ti_Module.h \
    ./include/Ti_Property.h \
    ./include/Ti_Proxy.h \
    ./include/Ti_Runtime.h \
    ./include/Ti_SceneManager.h \
    ./include/Ti_Timer.h \
    ./include/Ti_Value.h \
    ./include/TiCore.h    
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
