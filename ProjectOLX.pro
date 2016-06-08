QT += core
QT += network
QT -= gui

CONFIG += c++11

TARGET = ProjectOLX
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    filedownload.cpp \
    jsonserializable.cpp \
    imovel.cpp \
    managerest.cpp

HEADERS += \
    filedownload.h \
    jsonserializable.h \
    imovel.h \
    managerest.h
