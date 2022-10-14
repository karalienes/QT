QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



!defined(PYLON_DEV_DIR) {
    PYLON_DEV_DIR = $$shell_path(/opt/pylon)
}

# Make sure we can include pylon headers, etc.
INCLUDEPATH +=  $$shell_path($$PYLON_DEV_DIR/include)

# Need to be more verbose about pylon libs with unix.


unix{
    PYLON_LIBS = $$shell_path($$PYLON_DEV_DIR/lib)
    message("unix build")
    LIBS += -L$$shell_path($$PYLON_DEV_DIR/lib) -lpylonbase \
            -lpylonutility \
            -lGenApi_gcc_v3_1_Basler_pylon \
            -lGCBase_gcc_v3_1_Basler_pylon
}


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lopencv_highgui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lopencv_highgui
else:unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lopencv_highgui

INCLUDEPATH += $$PWD/../../../../usr/local/include/opencv4
DEPENDPATH += $$PWD/../../../../usr/local/include/opencv4

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lopencv_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lopencv_core
else:unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lopencv_core

INCLUDEPATH += $$PWD/../../../../usr/local/include/opencv4
DEPENDPATH += $$PWD/../../../../usr/local/include/opencv4

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/release/ -lopencv_imgcodecs
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../usr/local/lib/debug/ -lopencv_imgcodecs
else:unix:!macx: LIBS += -L$$PWD/../../../../usr/local/lib/ -lopencv_imgcodecs

INCLUDEPATH += $$PWD/../../../../usr/local/include/opencv4/opencv2
DEPENDPATH += $$PWD/../../../../usr/local/include/opencv4/opencv2
