TEMPLATE = lib
CONFIG += plugin
TARGET = ../Core/$$qtLibraryTarget(ued_core_mainwindow)
DEFINES += VERSION=1 \
    NAME="'\"UED.Core.MainWindow\"'"

INCLUDEPATH += include \
    ../Core/include
HEADERS += include/MainWindow.hxx
SOURCES += src/MainWindow.cxx
FORMS += 
RESOURCES += 
