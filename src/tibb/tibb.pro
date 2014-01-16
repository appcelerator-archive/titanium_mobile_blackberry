TEMPLATE = lib

QMAKE_CC = $(NDK_CCACHE) $${QMAKE_CC}
QMAKE_CXX = $(NDK_CCACHE) $${QMAKE_CXX}

CONFIG += qt staticlib warn_on debug_and_release cascades mobility
MOBILITY += sensors
CONFIG += console warn_off

INCLUDEPATH += \
	. \
	./include \
	../../runtime/v8/include \
	../ticore/include

SOURCES += \
	./*.cpp \
	../Layout/*.cpp \
	../TiScrollableView/*.cpp \
	../Contacts/*.cpp \
    ../TableView/*.cpp \
    ../Media/*.cpp \ 
    ../Modules/App/*.cpp \
    ../Modules/Blackberry/*.cpp \
    ../Modules/Blackberry/PushNotification/*.cpp \
    ../Modules/Blackberry/PushNotification/dao/*.cpp \
    ../Modules/Blackberry/PushNotification/service/*.cpp \
    ../Modules/Blackberry/PushNotification/vo/*.cpp \
    ../Modules/Filesystem/*.cpp \
    ../Modules/Platform/*.cpp \    
    ../Modules/UI/BlackBerry/*.cpp \
    ../Modules/UI/BlackBerry/NavButton/*.cpp \
    ../Modules/UI/BlackBerry/ApplicationMenu/*.cpp \
    ../Modules/Utils/*.cpp    
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
    ./Modules/Filesystem/TiFilesystemModule.cpp \
    ./Modules/Filesystem/TiFilesystemFileProxy.cpp \
    ./Modules/Filesystem/TiFilesystemBlobProxy.cpp \
    ./Modules/Geolocation/TiGeolocationModule.cpp \
    ./Modules/Geolocation/TiGeolocationSession.cpp \
    ./Modules/Geolocation/TiCompassSession.cpp \
    ./Modules/Platform/TiPlatformModule.cpp \    
    ./Modules/Filesystem/TiFilesystemBlobProxy.cpp \
    ./Modules/Utils/sha256.cpp \    
    ./Modules/Utils/TiUtilsModule.cpp \
    ./Modules/UI/BlackBerry/TiUIBlackberryModule.cpp \
    ./Modules/UI/BlackBerry/ApplicationMenu/ApplicationMenuProxy.cpp \ 
    ./Modules/UI/BlackBerry/NavButton/NavButtonProxy.cpp \ 
    ./Modules/App/TiAppModule.cpp \
    ./Modules/App/TiAppPropertiesModule.cpp \
    ../Modules/Blackberry/Notification/*.cpp \
    ../Modules/Blackberry/*.cpp

HEADERS += \
	./*.h \
    ../Layout/*.h \
    ../TiScrollableView/*.h \
    ../Contacts/*.h \
    ../TableView/*.h \
    ../Media/*.h \ 
    ../Modules/App/*.h \
    ../Modules/Blackberry/*.h \
    ../Modules/Blackberry/PushNotification/*.h \
    ../Modules/Blackberry/PushNotification/dao/*.hpp \
    ../Modules/Blackberry/PushNotification/service/*.hpp \
    ../Modules/Blackberry/PushNotification/vo/*.hpp \
    ../Modules/Filesystem/*.h \
    ../Modules/Platform/*.h \    
    ../Modules/UI/BlackBerry/*.h \
    ../Modules/UI/BlackBerry/NavButton/*.h \
    ../Modules/UI/BlackBerry/ApplicationMenu/*.h \
    ../Modules/Utils/*.h    
	TiScrollableView/TiScrollableView.h \
	TiScrollableView/TiScrollableViewPage.h \
	Contacts/ContactsModule.h \
	Contacts/ContactsPersonProxy.h \
    TableView/BasicTableViewRow.h \
    TableView/CustomTableViewRow.h \
    TableView/TableViewRowData.h \
    TableView/HeaderTableViewRow.h \
    Media/CameraInvocation.h \
    Modules/Filesystem/TiFilesystemModule.h \
    Modules/Filesystem/TiFilesystemFileProxy.h \
    Modules/Filesystem/TiFilesystemBlobProxy.h \
    Modules/Geolocation/TiGeolocationModule.h \
    Modules/Geolocation/TiGeolocationSession.h \
    Modules/Geolocation/TiCompassSession.h \
    Modules/Platform/TiPlatformModule.h \
    Modules/Filesystem/TiFilesystemBlobProxy.h \
    Modules/Utils/sha256.h \    
    Modules/Utils/TiUtilsModule.h  \
    Modules/UI/BlackBerry/TiUIBlackberryModule.h \
    Modules/UI/BlackBerry/ApplicationMenu/ApplicationMenuProxy.h  \
    Modules/UI/BlackBerry/NavButton/NavButtonProxy.h \ 
    Modules/App/TiAppModule.h \
    Modules/App/TiAppPropertiesModule.h \
    ../Modules/Blackberry/Notification/*.h \
    ../Modules/Blackberry/*.h

LIBS += -lz -lsqlite3 -lQtLocationSubset -lbbcascadesmaps -lGLESv1_CM -lOpenAL -lalut -lasound -lbbmultimedia -lbbdata -lbbsystem
LIBS += -lbbpim -lbbcascadespickers
LIBS += -lbbplatform -lbbnetwork
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
