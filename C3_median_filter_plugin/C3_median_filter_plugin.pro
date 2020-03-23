#-------------------------------------------------
#
# Project created by QtCreator 2020-03-21T07:07:13
#
#-------------------------------------------------

QT       -= gui

TARGET = C3_median_filter_plugin
TEMPLATE = lib
CONFIG += plugin

DEFINES += C3_MEDIAN_FILTER_PLUGIN_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        c3_median_filter_plugin.cpp

HEADERS += \
        c3_median_filter_plugin.h \
        c3_median_filter_plugin_global.h \ 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(../opencv.pri)
