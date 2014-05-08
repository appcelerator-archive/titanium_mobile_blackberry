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
	../Contacts/*.cpp \
    ../Media/*.cpp \ 
    ../Modules/App/*.cpp \
    ../Modules/API/*.cpp \
    ../Modules/Blackberry/*.cpp \
    ../Modules/Blackberry/PushNotification/*.cpp \
    ../Modules/Blackberry/PushNotification/dao/*.cpp \
    ../Modules/Blackberry/PushNotification/service/*.cpp \
    ../Modules/Blackberry/PushNotification/vo/*.cpp \
    ../Modules/Filesystem/*.cpp \
    ../Modules/Geolocation/*.cpp \
    ../Modules/Platform/*.cpp \    
    ../Modules/UI/BlackBerry/*.cpp \
    ../Modules/UI/BlackBerry/NavButton/*.cpp \
    ../Modules/UI/BlackBerry/ApplicationMenu/*.cpp \
    ../Modules/UI/BlackBerry/View/*.cpp \
    ../Modules/UI/BlackBerry/WebView/*.cpp \
    ../Modules/UI/BlackBerry/Button/*.cpp \
    ../Modules/UI/BlackBerry/Window/*.cpp \
    ../Modules/UI/BlackBerry/TabGroup/*.cpp \
    ../Modules/UI/BlackBerry/AlertDialog/*.cpp \
    ../Modules/UI/BlackBerry/AlertDialog/*.cpp \
    ../Modules/UI/BlackBerry/TableView/*.cpp \
    ../Modules/UI/BlackBerry/TableView/Components/*.cpp \
    ../Modules/UI/BlackBerry/ScrollableView/*.cpp \
    ../Modules/UI/BlackBerry/ScrollView/*.cpp \
    ../Modules/Utils/*.cpp \
    ../Modules/Blackberry/Notification/*.cpp \
    ../Modules/Blackberry/*.cpp

HEADERS += \
	./*.h \
    ../Contacts/*.h \
    ../Media/*.h \ 
    ../Modules/App/*.h \
    ../Modules/APi/*.h \
    ../Modules/Blackberry/*.h \
    ../Modules/Blackberry/PushNotification/*.h \
    ../Modules/Blackberry/PushNotification/dao/*.hpp \
    ../Modules/Blackberry/PushNotification/service/*.hpp \
    ../Modules/Blackberry/PushNotification/vo/*.hpp \
    ../Modules/Filesystem/*.h \
    ../Modules/Geolocation/*.h \
    ../Modules/Platform/*.h \    
    ../Modules/UI/BlackBerry/*.h \
    ../Modules/UI/BlackBerry/NavButton/*.h \
    ../Modules/UI/BlackBerry/ApplicationMenu/*.h \
    ../Modules/UI/BlackBerry/View/*.h \
    ../Modules/UI/BlackBerry/WebView/*.h \
    ../Modules/UI/BlackBerry/Button/*.h \
    ../Modules/UI/BlackBerry/Window/*.h \
    ../Modules/UI/BlackBerry/TabGroup/*.h \
    ../Modules/UI/BlackBerry/AlertDialog/*.h \
    ../Modules/UI/BlackBerry/TableView/*.h \
    ../Modules/UI/BlackBerry/TableView/Components/*.h \
    ../Modules/UI/BlackBerry/ScrollableView/*.h \
    ../Modules/UI/BlackBerry/ScrollView/*.h \
    ../Modules/Utils/*.h \
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
