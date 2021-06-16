#-------------------------------------------------
#
# Project created by QtCreator 2021-06-07T14:00:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DizzyEditor
TEMPLATE = app


SOURCES += main.cpp\
        cmainwindow.cpp \
    cmapeditor.cpp \
    cimagestorage.cpp \
    cpart.cpp

HEADERS  += cmainwindow.h \
    cmapeditor.h \
    cimagestorage.h \
    cpart.h

FORMS    += cmainwindow.ui
