#-------------------------------------------------
#
# Project created by QtCreator 2014-04-20T16:52:50
#
#-------------------------------------------------

QT       += core gui opengl
CONFIG   += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CGM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    lowlevelgeometry.cpp \
    polygon.cpp \
    polyhedron.cpp \
    tree.cpp \
    qucolorselectbutton.cpp \
    mygroupbox.cpp

HEADERS  += mainwindow.h \
    scene.h \
    lowlevelgeometry.h \
    polygon.h \
    polyhedron.h \
    tree.h \
    treeNodes.h \
    qucolorselectbutton.h \
    mygroupbox.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
