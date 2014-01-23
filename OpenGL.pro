#-------------------------------------------------
#
# Project created by QtCreator 2014-01-23T12:28:26
#
#-------------------------------------------------

QT       += core opengl

QT       += gui

TARGET = OpenGL
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app


SOURCES += main.cpp \
    polygon.cpp

HEADERS += \
    polygon.h
