TEMPLATE = lib
CONFIG += plugin release
TARGET = ../Core/$$qtLibraryTarget(ued_core_basicdatabase)
QT = core \
    gui
INCLUDEPATH += include \
    ../Core/include
DEFINES += VERSION=1 \
    NAME="'\"UED.Core.BasicDatabase\"'"
HEADERS += include/BinarySerializable.hxx \
    include/BasicType.hxx \
    include/BasicSubject.hxx \
    include/BasicDatabase.hxx
SOURCES += src/BasicType.cxx \
    src/BasicSubject.cxx \
    src/BasicDatabase.cxx
FORMS += 
RESOURCES += 
TRANSLATIONS    = ued_basicdatabase_pl.ts 
CODECFORTR      = UTF-8