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
    ./src/Ti_Value.cpp \
    ./src/Ti_View.cpp \
    ./src/Ti_ViewProxy.cpp \
    ./src/TitaniumLayout.cpp \
    ./src/Ti_ErrorScreen.cpp \
    ./src/Layout/Common.cpp \
    ./src/Layout/Composite.cpp \
    ./src/Layout/Element.cpp \
    ./src/Layout/Horizontal.cpp \
    ./src/Layout/Node.cpp \
    ./src/Layout/ParseProperty.cpp \
    ./src/Layout/Vertical.cpp

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
    ./include/Ti_View.h \
    ./include/Ti_ViewProxy.h \
    ./include/TiCore.h \
    ./include/TitaniumLayout.h \
    ./include/Ti_ErrorScreen.h \
    ./include/Layout/Common.h \
    ./include/Layout/Composite.h \
    ./include/Layout/Element.h \
    ./include/Layout/Horizontal.h \
    ./include/Layout/Node.h \
    ./include/Layout/ParseProperty.h \
    ./include/Layout/Vertical.h \
    ./include/Layout/Headers.h \
    ./include/Layout/Structs.h
   
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
