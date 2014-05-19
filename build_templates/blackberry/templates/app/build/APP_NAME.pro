CONFIG += qt warn_on cascades10
BASEDIR =  $$quote($$_PRO_FILE_PWD_)

INCLUDEPATH += "SDK_PATH/libs/tibb/include"
INCLUDEPATH += "SDK_PATH/libs/ticore/include"
INCLUDEPATH += "SDK_PATH/libs/libv8/include"
INCLUDEPATH += "libs/headers"

device {
    CONFIG(release, debug|release) {
        LIBS += "SDK_PATH/libs/tibb/arm/libtibb.a"
        LIBS += "SDK_PATH/libs/ticore/arm/libticore.a"
        LIBS += "SDK_PATH/libs/libv8/arm/libv8.a"
        ${modules_arm_a}
    }
    CONFIG(debug, debug|release) {
        LIBS += "SDK_PATH/libs/tibb/arm/libtibb.a"
        LIBS += "SDK_PATH/libs/ticore/arm/libticore.a"
        LIBS += "SDK_PATH/libs/libv8/arm/libv8.a"
        ${modules_arm_a_g}
    }
}

simulator {
    CONFIG(release, debug|release) {
        LIBS += "SDK_PATH/libs/tibb/x86/libtibb.a"
        LIBS += "SDK_PATH/libs/ticore/x86/libticore.a"
        LIBS += "SDK_PATH/libs/libv8/x86/libv8.a"
        ${modules_x86_a}
    }
    CONFIG(debug, debug|release) {
        LIBS += "SDK_PATH/libs/tibb/x86/libtibb.a"
        LIBS += "SDK_PATH/libs/ticore/x86/libticore.a"
        LIBS += "SDK_PATH/libs/libv8/x86/libv8.a"
        ${modules_x86_a_g}
    }
}




LIBS+=-lbbcascades -lbbdevice -lbbsystem -lQtCore -lQtDeclarative -lQtGui -lQtMultimedia -lQtNetwork -lm -lbb -lbbdata
LIBS+=-lQtSensors -lQtSql -lQtSvg -lQtTest -lQtXml -lsqlite3 -lQtLocationSubset -lbbcascadesmaps -lGLESv1_CM -lOpenAL -lalut -lasound -lbbmultimedia -lbbpim
LIBS+=-lbbutility -lbbcascadespickers -lbbnetwork -lbbplatform


include(config.pri)
