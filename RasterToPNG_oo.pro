#-------------------------------------------------
#
# Project created by QtCreator 2015-01-08T14:11:13
#
#-------------------------------------------------

QT       += core widgets

QT       -= gui

TARGET = RasterToPNG_oo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    renderer.cpp \
    classifyrenderer.cpp \
    stretchrendererstdev.cpp \
    stretchrendererminmax.cpp

win32: LIBS += -L$$PWD/../../../../../MinGW/msys/1.0/local/lib/ -llibgdal

INCLUDEPATH += $$PWD/../../../../../MinGW/msys/1.0/local/include
DEPENDPATH += $$PWD/../../../../../MinGW/msys/1.0/local/include

HEADERS += \
    renderer.h \
    classifyrenderer.h \
    stretchrendererstdev.h \
    stretchrendererminmax.h
