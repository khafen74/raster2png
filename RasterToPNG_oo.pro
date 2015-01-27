#-------------------------------------------------
#
# Project created by QtCreator 2015-01-08T14:11:13
#
#-------------------------------------------------

QT       += core widgets

TARGET = RasterToPNG_oo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    renderer.cpp \
    renderer_classified.cpp \
    renderer_stretchminmax.cpp \
    renderer_stretchstddev.cpp \
    renderer_gcdptdens.cpp \
    renderer_gcdslopedeg.cpp \
    renderer_gcdslopeper.cpp \
    renderer_gcderror.cpp \
    renderer_bytedata.cpp

HEADERS += \
    renderer.h \
    renderer_classified.h \
    renderer_stretchminmax.h \
    renderer_stretchstddev.h \
    renderer_gcdptdens.h \
    renderer_gcdslopedeg.h \
    renderer_gcdslopeper.h \
    renderer_gcderror.h \
    renderer_bytedata.h

win32: LIBS += -L$$PWD/../../../../../MinGW/msys/1.0/local/lib/ -llibgdal

INCLUDEPATH += $$PWD/../../../../../MinGW/msys/1.0/local/include
DEPENDPATH += $$PWD/../../../../../MinGW/msys/1.0/local/include
