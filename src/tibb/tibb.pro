TEMPLATE = lib

QMAKE_CC = $(NDK_CCACHE) $${QMAKE_CC}
QMAKE_CXX = $(NDK_CCACHE) $${QMAKE_CXX}

CONFIG += qt staticlib warn_on debug_and_release cascades mobility
MOBILITY += sensors
CONFIG += console

INCLUDEPATH += \
	. \
	./include \
	../../runtime/v8/include \
	../ticore/include

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
	./TiScrollableView/TiScrollableView.cpp \
	./TiScrollableView/TiScrollableViewPage.cpp \
	./Contacts/ContactsModule.cpp \
	./Contacts/ContactsPersonProxy.cpp \
    ./TableView/BasicTableViewRow.cpp \
    ./TableView/CustomTableViewRow.cpp \
    ./TableView/HeaderTableViewRow.cpp \
    ./Media/CameraInvocation.cpp \ 
    ./TiCore/Ti_Blob.cpp \
    ./TiCore/Ti_Constants.cpp \
    ./TiCore/Ti_Event.cpp \
    ./TiCore/Ti_EventParameters.cpp \
    ./TiCore/Ti_Helper.cpp \
    ./TiCore/Ti_Module.cpp \
    ./TiCore/Ti_Property.cpp \
    ./TiCore/Ti_Proxy.cpp \
    ./TiCore/Ti_SceneManager.cpp \
    ./TiCore/Ti_Timer.cpp \
    ./TiCore/Ti_Value.cpp \
    ./Modules/Filesystem/TiFilesystemModule.cpp \
    ./Modules/Filesystem/TiFilesystemFileProxy.cpp \
    ./Modules/Filesystem/TiFilesystemBlobProxy.cpp \
    ./TiCore/Ti_Value.cpp \
    ./Modules/Platform/TiPlatformModule.cpp
    
HEADERS += \
	./*.h \
	TiScrollableView/TiScrollableView.h \
	TiScrollableView/TiScrollableViewPage.h \
	Contacts/ContactsModule.h \
	Contacts/ContactsPersonProxy.h \
    TableView/BasicTableViewRow.h \
    TableView/CustomTableViewRow.h \
    TableView/TableViewRowData.h \
    TableView/HeaderTableViewRow.h \
    Media/CameraInvocation.h \
    TiCore/Ti_Blob.h \
    TiCore/Ti_Constants.h \
    TiCore/Ti_Event.h \
    TiCore/Ti_EventParameters.h \
    TiCore/Ti_Helper.h \
    TiCore/Ti_Module.h \
    TiCore/Ti_Property.h \
    TiCore/Ti_Proxy.h \
    TiCore/Ti_SceneManager.h \
    TiCore/Ti_Timer.h \
    TiCore/Ti_Value.h \
    Modules/Filesystem/TiFilesystemModule.h \
    Modules/Filesystem/TiFilesystemFileProxy.h \
    Modules/Filesystem/TiFilesystemBlobProxy.h \
    TiCore/Ti_Value.h \
    Modules/Platform/TiPlatformModule.h

LIBS += -lz -lsqlite3 -lQtLocationSubset -lbbcascadesmaps -lGLESv1_CM -lOpenAL -lalut -lasound -lbbmultimedia -lbbdata -lbbsystem
LIBS += -lbbpim
LIBS += -lbbutility

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
