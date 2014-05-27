TEMPLATE = lib

QMAKE_CC = $(NDK_CCACHE) $${QMAKE_CC}
QMAKE_CXX = $(NDK_CCACHE) $${QMAKE_CXX}

CONFIG += qt staticlib warn_on debug_and_release cascades mobility
CONFIG += console warn_off
MOBILITY += sensors

LIBS += -lz -lsqlite3 -lQtLocationSubset -lbbcascadesmaps -lGLESv1_CM -lOpenAL -lalut
LIBS += -lasound -lbbmultimedia -lbbdata -lbbsystem -lbbpim -lbbcascadespickers
LIBS += -lbbplatform -lbbnetwork -lbbutility

BASEDIR =  $$quote($$_PRO_FILE_PWD_)

INCLUDEPATH += \
	. \
	$$quote($$BASEDIR/include) \
	$$quote($$BASEDIR/../../runtime/v8/include) \
	$$quote($$BASEDIR/../ticore/include)

SOURCES += \
	$$quote($$BASEDIR/src/*.cpp) \
	$$quote($$BASEDIR/src/Contacts/*.cpp) \
    $$quote($$BASEDIR/src/Media/*.cpp )\ 
    $$quote($$BASEDIR/src/Modules/App/*.cpp) \
    $$quote($$BASEDIR/src/Modules/API/*.cpp) \
    $$quote($$BASEDIR/src/Modules/Blackberry/*.cpp) \
    $$quote($$BASEDIR/src/Modules/Blackberry/PushNotification/*.cpp) \
    $$quote($$BASEDIR/src/Modules/Blackberry/PushNotification/dao/*.cpp) \
    $$quote($$BASEDIR/src/Modules/Blackberry/PushNotification/service/*.cpp) \
    $$quote($$BASEDIR/src/Modules/Blackberry/PushNotification/vo/*.cpp) \
    $$quote($$BASEDIR/src/Modules/Filesystem/*.cpp) \
    $$quote($$BASEDIR/src/Modules/Geolocation/*.cpp) \
    $$quote($$BASEDIR/src/Modules/Platform/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/NavButton/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ApplicationMenu/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/View/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/WebView/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/Button/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/Window/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/TabGroup/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/AlertDialog/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/AlertDialog/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/TableView/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/TableView/Components/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ScrollableView/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ScrollView/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ImageView/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/Label/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/TextWidget/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/TextWidget/TextArea/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/TextWidget/TextField/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/Switch/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/Slider/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ImageButton/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ProgressBar/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ActivityIndicator/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/EmailDialog/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/OptionDialog/*.cpp) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/NavigationWindow/*.cpp) \
    $$quote($$BASEDIR/src/Modules/Utils/*.cpp) \
    $$quote($$BASEDIR/src/Modules/Blackberry/Notification/*.cpp) \
    $$quote($$BASEDIR/src/Modules/Blackberry/*.cpp) \
    $$quote($$BASEDIR/src/Modules/Media_/*.cpp)

HEADERS += \
	$$quote($$BASEDIR/src/*.h) \
    $$quote($$BASEDIR/src/Contacts/*.h) \
    $$quote($$BASEDIR/src/Media/*.h )\ 
    $$quote($$BASEDIR/src/Modules/App/*.h) \
    $$quote($$BASEDIR/src/Modules/API/*.h) \
    $$quote($$BASEDIR/src/Modules/Blackberry/*.h) \
    $$quote($$BASEDIR/src/Modules/Blackberry/PushNotification/*.h) \
    $$quote($$BASEDIR/src/Modules/Blackberry/PushNotification/dao/*.hpp) \
    $$quote($$BASEDIR/src/Modules/Blackberry/PushNotification/service/*.hpp) \
    $$quote($$BASEDIR/src/Modules/Blackberry/PushNotification/vo/*.hpp) \
    $$quote($$BASEDIR/src/Modules/Filesystem/*.h) \
    $$quote($$BASEDIR/src/Modules/Geolocation/*.h) \
    $$quote($$BASEDIR/src/Modules/Platform/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/NavButton/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ApplicationMenu/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/View/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/WebView/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/Button/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/Window/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/TabGroup/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/AlertDialog/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/TableView/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/TableView/Components/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ScrollableView/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ScrollView/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ImageView/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/Label/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/TextWidget/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/TextWidget/TextArea/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/TextWidget/TextField/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/Switch/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/Slider/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ImageButton/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ProgressBar/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/ActivityIndicator/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/EmailDialog/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/OptionDialog/*.h) \
    $$quote($$BASEDIR/src/Modules/UI/BlackBerry/NavigationWindow/*.h) \
    $$quote($$BASEDIR/src/Modules/Utils/*.h) \
    $$quote($$BASEDIR/src/Modules/Blackberry/Notification/*.h) \
    $$quote($$BASEDIR/src/Modules/Blackberry/*.h) \
    $$quote($$BASEDIR/src/Modules/Media_/*.h)

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
