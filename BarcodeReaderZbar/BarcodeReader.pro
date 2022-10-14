QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gallo.cpp \
    main.cpp \
    mainwindow.cpp \
    soros.cpp \
    yun.cpp

HEADERS += \
    gallo.h \
    mainwindow.h \
    soros.h \
    yun.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



INCLUDEPATH += $$PWD/../../../../usr/include/tesseract
DEPENDPATH += $$PWD/../../../../usr/include/tesseract


INCLUDEPATH += $$PWD/../../../../usr/include/opencv4
DEPENDPATH += $$PWD/../../../../usr/include/opencv4

INCLUDEPATH += $$PWD/../../../../usr/include/cpprest
DEPENDPATH += $$PWD/../../../../usr/include/cpprest

INCLUDEPATH += $$PWD/../../../../include/zbar
DEPENDPATH += $$PWD/../../../../include/zbar

LIBS += `pkg-config --cflags --libs opencv4`
LIBS += -ltesseract
LIBS += -lleptonica
LIBS += -lcpprest
LIBS += -lzbar
