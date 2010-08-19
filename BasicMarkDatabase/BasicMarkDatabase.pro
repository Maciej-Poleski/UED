TEMPLATE = lib
CONFIG += plugin
TARGET = ../Core/$$qtLibraryTarget(ued_markdatabase_basicmarkdatabase)
DEFINES += VERSION=1 \
    NAME="'\"UED.MarkDatabase.BasicMarkDatabase\"'"
INCLUDEPATH += include \
    ../Core/include
QT = core
HEADERS += include/MarksTabWidget.hxx \
    include/AddMarkButton.hxx \
    include/SubjectTab.hxx \
    include/AbstractBasicMark.hxx \
    include/BasicStringMark.hxx \
    include/BinarySerializable.hxx \
    include/BasicMarkDatabase.hxx
SOURCES += src/MarksTabWidget.cxx \
    src/AddMarkButton.cxx \
    src/SubjectTab.cxx \
    src/AbstractBasicMark.cxx \
    src/BasicStringMark.cxx \
    src/BasicMarkDatabase.cxx
FORMS += 
RESOURCES += 
