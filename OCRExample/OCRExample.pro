QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ocr.cpp

HEADERS += \
    mainwindow.h \
    ocr.h \
    rapidfuzz.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/release/ -ltesseract
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/debug/ -ltesseract
#else:unix: LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/ -ltesseract

INCLUDEPATH += $$PWD/../../../../usr/include/tesseract
DEPENDPATH += $$PWD/../../../../usr/include/tesseract


INCLUDEPATH += $$PWD/../../../../usr/include/opencv4
DEPENDPATH += $$PWD/../../../../usr/include/opencv4

LIBS += `pkg-config --cflags --libs opencv4`
LIBS += -ltesseract
LIBS += -lleptonica


#unix:!macx: LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/ -ltesseract

#INCLUDEPATH += $$PWD/../../../../usr/include
#DEPENDPATH += $$PWD/../../../../usr/include

INCLUDEPATH += /usr/include/c++/8
