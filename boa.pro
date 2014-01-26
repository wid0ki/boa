#-------------------------------------------------
#
# Project created by QtCreator 2014-01-25T02:43:08
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = boa
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += resourse.qrc

OTHER_FILES += \
    content_json
