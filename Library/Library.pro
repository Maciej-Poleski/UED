TEMPLATE = lib
CONFIG += plugin
DEFINES += VERSION=1 NAME="'\"UED.Library\"'"
TARGET = ../Core/$$qtLibraryTarget(ued_library)
QT = core
INCLUDEPATH += include ../Core/include
HEADERS += include/Library.hxx
SOURCES += src/Library.cxx
FORMS += 
RESOURCES += 
