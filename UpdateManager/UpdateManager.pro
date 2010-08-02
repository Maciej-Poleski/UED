TEMPLATE = lib
CONFIG += plugin static

DEFINES += VERSION=1

HEADERS += \
    include/BasicUpdateManager.hxx

SOURCES += \
    src/BasicUpdateManager.cxx

INCLUDEPATH += include ../Core/include
TARGET = ../Core/$$qtLibraryTarget(ued_basic_update_manager)
