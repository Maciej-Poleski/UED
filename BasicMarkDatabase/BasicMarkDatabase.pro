TEMPLATE = lib
CONFIG += plugin release
TARGET = ../Core/$$qtLibraryTarget(ued_markdatabase_basicmarkdatabase)
DEFINES += VERSION=1 \
    NAME="'\"UED.MarkDatabase.BasicMarkDatabase\"'"
INCLUDEPATH += include \
    ../Core/include
QT = core gui
HEADERS += include/BasicAbsoluteMark.hxx \
    include/BasicClassicMark.hxx \
    include/BasicModernMark.hxx \
    include/NewMarkDialog.hxx \
    include/MarksTabWidget.hxx \
    include/AddMarkButton.hxx \
    include/SubjectTab.hxx \
    include/AbstractBasicMark.hxx \
    include/BasicStringMark.hxx \
    include/BinarySerializable.hxx \
    include/BasicMarkDatabase.hxx
SOURCES += src/BasicAbsoluteMark.cxx \
    src/BasicClassicMark.cxx \
    src/BasicModernMark.cxx \
    src/NewMarkDialog.cxx \
    src/MarksTabWidget.cxx \
    src/AddMarkButton.cxx \
    src/SubjectTab.cxx \
    src/AbstractBasicMark.cxx \
    src/BasicStringMark.cxx \
    src/BasicMarkDatabase.cxx
FORMS += forms/NewMarkDialog.ui
RESOURCES += 
TRANSLATIONS    = ued_basicmarkdatabase_pl.ts 
CODECFORTR      = UTF-8