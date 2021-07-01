#-------------------------------------------------
#
# Project created by QtCreator 2021-06-22T11:49:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DizzyEditor
TEMPLATE = app


SOURCES += main.cpp\
        cmainwindow.cpp \
    cimagestorage.cpp \
    cmapeditor.cpp \
    cpart.cpp \
    cpartunion.cpp \
    ctile.cpp \
    ctilessequence.cpp \
    ipart.cpp \
    cdialog_animations.cpp

HEADERS  += cmainwindow.h \
    cimagestorage.h \
    cmapeditor.h \
    cpart.h \
    cpartunion.h \
    ctile.h \
    ctilessequence.h \
    ipart.h \
    cdialog_animations.h

FORMS    += cmainwindow.ui \
    cdialog_animations.ui

DISTFILES +=

RESOURCES += \
    resource.qrc
