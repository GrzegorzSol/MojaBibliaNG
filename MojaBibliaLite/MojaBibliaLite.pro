QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_TARGET_COMPANY = Grzegorz Sołtysik
QMAKE_TARGET_DESCRIPTION = Aplikacja do studiowania Pisma Świętego
QMAKE_TARGET_COPYRIGHT = (c) Grzegorz Sołtysik. All rights reserved.
RC_ICONS = MojaBibliaLite.ico

#INCLUDEPATH += QGsReadBibleTextClass

SOURCES += \
    QGsReadBibleTextClass/qgsreadbibletextclass.cpp \
    globalvar.cpp \
    informationswindow.cpp \
    main.cpp \
    mainwindow.cpp \
    mblitelibrary.cpp \
    searchwindow.cpp \
    setupswindow.cpp

HEADERS += \
    QGsReadBibleTextClass/qgsreadbibletextclass.h \
    globalvar.h \
    informationswindow.h \
    mainwindow.h \
    mblitelibrary.h \
    searchwindow.h \
    setupswindow.h

FORMS += \
    informationswindow.ui \
    mainwindow.ui \
    searchwindow.ui \
    setupswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
 MojaBibliaLite.qrc
 
VERSION = 0.8.188.7511
NAME = MojaBibliaLite

DEFINES += APP_VERSION_STRING=\\\"$${VERSION}\\\" \
           APP_NAME_STRING=\\\"$${NAME}\\\"
