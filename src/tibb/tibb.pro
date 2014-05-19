TEMPLATE = lib

QMAKE_CC = $(NDK_CCACHE) $${QMAKE_CC}
QMAKE_CXX = $(NDK_CCACHE) $${QMAKE_CXX}

CONFIG += qt staticlib warn_on debug_and_release cascades mobility
CONFIG += console warn_off
MOBILITY += sensors

LIBS += -lz -lsqlite3 -lQtLocationSubset -lbbcascadesmaps -lGLESv1_CM -lOpenAL -lalut
LIBS += -lasound -lbbmultimedia -lbbdata -lbbsystem -lbbpim -lbbcascadespickers
LIBS += -lbbplatform -lbbnetwork -lbbutility

INCLUDEPATH += \
	. \
	./include \
	../../runtime/v8/include \
	../ticore/include

SOURCES += \
	../src/*.cpp \
	../src/Contacts/*.cpp \
    ../src/Media/*.cpp \ 
    ../src/Modules/App/*.cpp \
    ../src/Modules/API/*.cpp \
    ../src/Modules/Blackberry/*.cpp \
    ../src/Modules/Blackberry/PushNotification/*.cpp \
    ../src/Modules/Blackberry/PushNotification/dao/*.cpp \
    ../src/Modules/Blackberry/PushNotification/service/*.cpp \
    ../src/Modules/Blackberry/PushNotification/vo/*.cpp \
    ../src/Modules/Filesystem/*.cpp \
    ../src/Modules/Geolocation/*.cpp \
    ../src/Modules/Platform/*.cpp \    
    ../src/Modules/UI/BlackBerry/*.cpp \
    ../src/Modules/UI/BlackBerry/NavButton/*.cpp \
    ../src/Modules/UI/BlackBerry/ApplicationMenu/*.cpp \
    ../src/Modules/UI/BlackBerry/View/*.cpp \
    ../src/Modules/UI/BlackBerry/WebView/*.cpp \
    ../src/Modules/UI/BlackBerry/Button/*.cpp \
    ../src/Modules/UI/BlackBerry/Window/*.cpp \
    ../src/Modules/UI/BlackBerry/TabGroup/*.cpp \
    ../src/Modules/UI/BlackBerry/AlertDialog/*.cpp \
    ../src/Modules/UI/BlackBerry/AlertDialog/*.cpp \
    ../src/Modules/UI/BlackBerry/TableView/*.cpp \
    ../src/Modules/UI/BlackBerry/TableView/Components/*.cpp \
    ../src/Modules/UI/BlackBerry/ScrollableView/*.cpp \
    ../src/Modules/UI/BlackBerry/ScrollView/*.cpp \
    ../src/Modules/UI/BlackBerry/ImageView/*.cpp \
    ../src/Modules/UI/BlackBerry/Label/*.cpp \
    ../src/Modules/UI/BlackBerry/TextWidget/*.cpp \
    ../src/Modules/UI/BlackBerry/TextWidget/TextArea/*.cpp \
    ../src/Modules/UI/BlackBerry/TextWidget/TextField/*.cpp \
    ../src/Modules/UI/BlackBerry/Switch/*.cpp \
    ../src/Modules/UI/BlackBerry/Slider/*.cpp \
    ../src/Modules/UI/BlackBerry/ImageButton/*.cpp \
    ../src/Modules/UI/BlackBerry/ProgressBar/*.cpp \
    ../src/Modules/UI/BlackBerry/ActivityIndicator/*.cpp \
    ../src/Modules/UI/BlackBerry/EmailDialog/*.cpp \
    ../src/Modules/UI/BlackBerry/OptionDialog/*.cpp \
    ../src/Modules/UI/BlackBerry/NavigationWindow/*.cpp \
    ../src/Modules/Utils/*.cpp \
    ../src/Modules/Blackberry/Notification/*.cpp \
    ../src/Modules/Blackberry/*.cpp

HEADERS += \
	../src/*.h \
    ../src/Contacts/*.h \
    ../src/Media/*.h \ 
    ../src/Modules/App/*.h \
    ../src/Modules/APi/*.h \
    ../src/Modules/Blackberry/*.h \
    ../src/Modules/Blackberry/PushNotification/*.h \
    ../src/Modules/Blackberry/PushNotification/dao/*.hpp \
    ../src/Modules/Blackberry/PushNotification/service/*.hpp \
    ../src/Modules/Blackberry/PushNotification/vo/*.hpp \
    ../src/Modules/Filesystem/*.h \
    ../src/Modules/Geolocation/*.h \
    ../src/Modules/Platform/*.h \    
    ../src/Modules/UI/BlackBerry/*.h \
    ../src/Modules/UI/BlackBerry/NavButton/*.h \
    ../src/Modules/UI/BlackBerry/ApplicationMenu/*.h \
    ../src/Modules/UI/BlackBerry/View/*.h \
    ../src/Modules/UI/BlackBerry/WebView/*.h \
    ../src/Modules/UI/BlackBerry/Button/*.h \
    ../src/Modules/UI/BlackBerry/Window/*.h \
    ../src/Modules/UI/BlackBerry/TabGroup/*.h \
    ../src/Modules/UI/BlackBerry/AlertDialog/*.h \
    ../src/Modules/UI/BlackBerry/TableView/*.h \
    ../src/Modules/UI/BlackBerry/TableView/Components/*.h \
    ../src/Modules/UI/BlackBerry/ScrollableView/*.h \
    ../src/Modules/UI/BlackBerry/ScrollView/*.h \
    ../src/Modules/UI/BlackBerry/ImageView/*.h \
    ../src/Modules/UI/BlackBerry/Label/*.h \
    ../src/Modules/UI/BlackBerry/TextWidget/*.h \
    ../src/Modules/UI/BlackBerry/TextWidget/TextArea/*.h \
    ../src/Modules/UI/BlackBerry/TextWidget/TextField/*.h \
    ../src/Modules/UI/BlackBerry/Switch/*.h \
    ../src/Modules/UI/BlackBerry/Slider/*.h \
    ../src/Modules/UI/BlackBerry/ImageButton/*.h \
    ../src/Modules/UI/BlackBerry/ProgressBar/*.h \
    ../src/Modules/UI/BlackBerry/ActivityIndicator/*.h \
    ../src/Modules/UI/BlackBerry/EmailDialog/*.h \
    ../src/Modules/UI/BlackBerry/OptionDialog/*.h \
    ../src/Modules/UI/BlackBerry/NavigationWindow/*.h \
    ../src/Modules/Utils/*.h \
    ../src/Modules/Blackberry/Notification/*.h \
    ../src/Modules/Blackberry/*.h


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
