QT += core gui widgets

CONFIG += c++11 utf8_source

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui


INCLUDEPATH += $$PWD/Unit2
include($$PWD/Unit2/Unit2.pri)

INCLUDEPATH += $$PWD/Unit3
include($$PWD/Unit3/Unit3.pri)

INCLUDEPATH += $$PWD/Unit4
include($$PWD/Unit4/Unit4.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
