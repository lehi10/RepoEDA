#-------------------------------------------------
#
# Project created by QtCreator 2017-11-17T11:37:06
#
#-------------------------------------------------
QT       += core gui opengl


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KDTree
TEMPLATE = app


CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    framegl.cpp \
    kdtree.cpp

HEADERS  += mainwindow.h \
    framegl.h \
    kdtree.h

FORMS    += mainwindow.ui


LIBS += -lglut -lGLU
