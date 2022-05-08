TEMPLATE = lib
CONFIG += staticlib

include(../Configure.pri)

unix::QMAKE_CXXFLAGS += -std=gnu++0x

SOURCES += \
    pugixml/pugixml.cpp \
    XMLElement.cpp \
    XMLValueRef.cpp \
    XMLRefFactory.cpp \
    XMLServiceFunctions.cpp \
    XMLDocument.cpp \
    XMLListRef.cpp \
    XMLRef.cpp \
    XMLChildRef.cpp \
    XMLChildRefGroup.cpp \
    XMLRefGroup.cpp \
    XMLParentRef.cpp

HEADERS += \
    pugixml/pugiconfig.hpp \
    pugixml/pugixml.hpp \
    XMLElement.h \
    XMLValueRef.h \
    XMLRefFactory.h \
    XMLServiceFunctions.h \
    XMLDocument.h \
    XMLListRef.h \
    XMLRef.h \
    XMLChildRef.h \
    XMLChildRefGroup.h \
    XMLRefGroup.h \
    XMLParentRef.h

CONFIG(debug, debug|release) {
    TARGET = ../../VLSXMLd
    OBJECTS_DIR = ./debug
} else {
    TARGET = ../../VLSXML
    OBJECTS_DIR = ./release
}
