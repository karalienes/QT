QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    zlibclass.cpp
HEADERS += \
    mainwindow.h \
    zlibclass.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#Linux
LIBS += -L/usr/local/lib/ -lzint

INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

# INCLUDEPATH += /home/karali/External_Lib/quazip_Qt5
# DEPENDPATH += /home/karali/External_Lib/quazip_Qt5

LIBS += -L/usr/local/lib/ -lz
# LIBS += -L/home/karali/External_Lib/quazip_Qt5/build/build/quazip -lquazip1-qt5

INCLUDEPATH += /home/karali/External_Lib/quazip_Qt6
DEPENDPATH += /home/karali/External_Lib/quazip_Qt6
LIBS += -L/home/karali/External_Lib/quazip_Qt6/build/build/quazip -lquazip1-qt6
