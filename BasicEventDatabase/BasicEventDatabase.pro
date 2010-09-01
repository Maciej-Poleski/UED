TEMPLATE = lib
CONFIG += plugin release
TARGET = ../Core/$$qtLibraryTarget(ued_eventdatabase_basiceventdatabase)
DEFINES += VERSION=1 \
    NAME="'\"UED.EventDatabase.BasicEventDatabase\"'"
INCLUDEPATH += include \
    ../Core/include
QT = core \
    gui
HEADERS += include/ExecuteButton.hxx \
    include/BasicEventDatabase.hxx \
    include/EventsWidget.hxx \
    include/BinarySerializable.hxx \
    include/BasicEvent.hxx
SOURCES += src/ExecuteButton.cxx \
    src/BasicEventDatabase.cxx \
    src/EventsWidget.cxx \
    src/BasicEvent.cxx
FORMS += forms/EventsWidget.ui
RESOURCES += 
TRANSLATIONS    = ued_basiceventdatabase_pl.ts 
CODECFORTR      = UTF-8