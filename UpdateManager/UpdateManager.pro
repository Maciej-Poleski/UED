TEMPLATE = lib
CONFIG += plugin static release
QT = core gui network
DEFINES += VERSION=1

HEADERS += \
    include/BasicUpdateManager.hxx

SOURCES += \
    src/BasicUpdateManager.cxx

INCLUDEPATH += include ../Core/include
TARGET = ../Core/$$qtLibraryTarget(ued_basic_update_manager)
TRANSLATIONS    = ued_update_manager_pl.ts 
CODECFORTR      = UTF-8