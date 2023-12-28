QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Functions.cpp \
    MyUniqueCompression.cpp \
    XMLtoTree.cpp \
    formatting.cpp \
    globals.cpp \
    main.cpp \
    mainwindow.cpp \
    tree.cpp \
    xml_parser.cpp \
    xmltojson.cpp

HEADERS += \
    Functions.h \
    MyUniqueCompression.h \
    Tree.h \
    XMLtoTree.h \
    formatting.h \
    globals.h \
    mainwindow.h \
    xml_parser.h \
    xmltojson.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
