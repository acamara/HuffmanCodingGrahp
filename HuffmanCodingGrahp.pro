#-------------------------------------------------
#
# Project created by QtCreator 2013-07-21T17:35:52
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HuffmanCodingGrahp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphelement.cpp \
    node.cpp

HEADERS  += mainwindow.h \
    graphelement.h \
    node.h

FORMS    += mainwindow.ui
