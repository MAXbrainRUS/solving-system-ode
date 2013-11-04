#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T17:57:01
#
#-------------------------------------------------

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../Qt/Qwt-6.1.0-rc3/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../Qt/Qwt-6.1.0-rc3/lib/ -lqwtd

INCLUDEPATH += $$PWD/../../../../../Qt/Qwt-6.1.0-rc3/include
DEPENDPATH += $$PWD/../../../../../Qt/Qwt-6.1.0-rc3/include

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = solving-system-ode
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
