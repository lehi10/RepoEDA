#-------------------------------------------------
#
# Project created by QtCreator 2017-10-21T21:29:52
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets




TARGET = RangeTree
TEMPLATE = app


CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    framegl.cpp \
    rangetree.cpp

HEADERS  += mainwindow.h \
    framegl.h \
    nodetree.h \
    rangetree.h

FORMS    += mainwindow.ui

LIBS += -lglut -lGLU
