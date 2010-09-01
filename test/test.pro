TEMPLATE = lib
CONFIG += plugin \
    debug
TARGET = ../Core/$$qtLibraryTarget(ued_test)
DEFINES += VERSION=1 \
    NAME="'\"UED.EventDatabase.BasicEventDatabase\"'"
INCLUDEPATH += include \
    ../Core/include
HEADERS += BinarySerializable.hxx \
    testClass.h
SOURCES += testClass.cpp
FORMS += 
RESOURCES += 
